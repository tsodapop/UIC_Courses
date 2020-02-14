using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;
using System.Linq;
using System.Reflection;

/// <summary>
/// WandEventModuleBase is used to send inputs to Unity UI.
/// </summary>
/// <remarks>
/// This class is abstract: it doesn't know how to retrieve the submit button.
/// </remarks>
public abstract class WandEventModuleBase : PointerInputModule
{

    public bool m_sendWandEvents = true;

    // the UI element to use for the cursor
    // the cursor will appear on the plane of the current UI element being looked at - so it adjusts
    // to depth correctly recommended to use a simple Image component (typical mouse cursor works
    // pretty well) and you MUST add the Unity created IgnoreRaycast component (script included in
    // example) so that the cursor will not be see by the UI event system
    [Tooltip("The UI element to use for the cursor")]
    public RectTransform cursor;

    public bool m_sendMoveEvents = false;

    public float m_inputActionsPerSecond = 10f;

    public float m_repeatDelay = 0.5f;

    public enum MouseInteractionMode
    {
        WorldOnly,
        OverlayOnly,
        All,
        None
    };

    protected enum ButtonFunction
    {
        WandSubmit,
        NavSubmit,
        Cancel,
        Up,
        Down,
        Left,
        Right
    }

    public MouseInteractionMode m_mouseInteractionMode = MouseInteractionMode.OverlayOnly;
    public Camera m_mouseCamera = null;

    private class WandEventData : PointerEventData
    {
        public WandEventData(EventSystem eventSystem) : base(eventSystem) { }
    }

    private WandEventData m_wand = null;
    private PointerEventData m_mouse = null;

    public GameObject currentLook {
        get { return m_wand != null ? m_wand.pointerCurrentRaycast.gameObject : null; }
    }

    private static RenderMode GetRootCanvasRenderMode(GameObject go)
    {
        foreach (var canvas in go.GetComponentsInParent<Canvas>())
        {
            if (canvas.isRootCanvas)
            {
                return canvas.renderMode;
            }
        }
        return RenderMode.WorldSpace;
    }

    private static RaycastResult FindFirstRaycastRendermode(List<RaycastResult> candidates,
        RenderMode renderMode)
    {
        candidates.RemoveAll(candidate =>
            GetRootCanvasRenderMode(candidate.gameObject) != renderMode);
        return FindFirstRaycast(candidates);
    }

    private void BuildPointerEventData(PointerEventData pointerEventData, Vector2 position)
    {
        var lastPos = pointerEventData.position;
        pointerEventData.Reset();
        pointerEventData.delta = position - lastPos;
        pointerEventData.position = position;
        pointerEventData.scrollDelta = Vector2.zero;
    }

    private void GetWandPointerEventData(PointerEventData pointerEventData)
    {
        var screenCenter = new Vector2(Screen.width / 2, Screen.height / 2);
        BuildPointerEventData(pointerEventData, screenCenter);
        eventSystem.RaycastAll(pointerEventData, m_RaycastResultCache);
        pointerEventData.pointerCurrentRaycast = FindFirstRaycastRendermode(m_RaycastResultCache,
            RenderMode.WorldSpace);
        pointerEventData.useDragThreshold = false;
        m_RaycastResultCache.Clear();
    }

    private void GetMousePointerEventData(PointerEventData pointerEventData)
    {
        BuildPointerEventData(pointerEventData, Input.mousePosition); // no gr3d warning
        eventSystem.RaycastAll(pointerEventData, m_RaycastResultCache);
        switch (m_mouseInteractionMode)
        {
            case MouseInteractionMode.All:
                pointerEventData.pointerCurrentRaycast = FindFirstRaycast(m_RaycastResultCache);
                break;
            case MouseInteractionMode.None:
                break;
            case MouseInteractionMode.WorldOnly:
                pointerEventData.pointerCurrentRaycast = FindFirstRaycastRendermode(
                    m_RaycastResultCache, RenderMode.WorldSpace);
                break;
            case MouseInteractionMode.OverlayOnly:
                pointerEventData.pointerCurrentRaycast = FindFirstRaycastRendermode(
                    m_RaycastResultCache, RenderMode.ScreenSpaceOverlay);
                break;
        }
        //Debug.Log(string.Join("/", m_RaycastResultCache.Select(t=>t.gameObject.name).ToArray()));
        pointerEventData.useDragThreshold = false;
        m_RaycastResultCache.Clear();
    }

    private Camera[] m_camerasBackup = null;

    private MethodInfo m_getRaycasters = null;
    private bool m_methodSearched = false;

    private List<UnityEngine.EventSystems.BaseRaycaster> GetRaycasters()
    {
        if (!m_methodSearched)
        {
            var assembly = typeof(PointerInputModule).Assembly;
            var t = assembly.GetType("UnityEngine.EventSystems.RaycasterManager");
            if (t != null)
            {
                var bindingFlags = BindingFlags.NonPublic | BindingFlags.Static |
                    BindingFlags.Public | BindingFlags.InvokeMethod;
                m_getRaycasters = t.GetMethod("GetRaycasters", bindingFlags);
            }
            m_methodSearched = true;
        }
        if (m_getRaycasters == null)
        {
            return FindObjectsOfType<BaseRaycaster>().ToList();
        }
        else
        {
            return (List<BaseRaycaster>)m_getRaycasters.Invoke(null, null);
        }
    }

    private void replaceCanvasCameras(Camera camera)
    {
        var raycasters = GetRaycasters();
        m_camerasBackup = raycasters.Select(rc => rc.GetComponent<Canvas>().worldCamera).ToArray();
        foreach (var rc in raycasters)
        {
            rc.GetComponent<Canvas>().worldCamera = camera;
        }
    }

    private void restoreCanvasCameras()
    {
        var raycasters = GetRaycasters();
        for (int i = 0; i < raycasters.Count; ++i)
        {
            raycasters[i].GetComponent<Canvas>().worldCamera = m_camerasBackup[i];
        }
    }

    // update the cursor location and whether it is enabled
    // this code is based on Unity's DragMe.cs code provided in the UI drag and drop example
    private void UpdateCursor(PointerEventData lookData)
    {
        if (cursor != null)
        {
            if (lookData.pointerEnter != null)
            {
                RectTransform draggingPlane = lookData.pointerEnter.GetComponent<RectTransform>();
                Vector3 globalLookPos;
                if (RectTransformUtility.ScreenPointToWorldPointInRectangle(draggingPlane,
                    lookData.position, lookData.enterEventCamera, out globalLookPos))
                {
                    cursor.gameObject.SetActive(true);
                    cursor.position = globalLookPos;
                    cursor.rotation = draggingPlane.rotation;
                }
                else
                {
                    cursor.gameObject.SetActive(false);
                }
            }
            else
            {
                cursor.gameObject.SetActive(false);
            }
        }
    }

    // send update event to selected object
    // needed for InputField to receive keyboard input
    private bool SendUpdateEventToSelectedObject()
    {
        if (eventSystem.currentSelectedGameObject == null)
            return false;
        BaseEventData data = GetBaseEventData();
        ExecuteEvents.Execute(eventSystem.currentSelectedGameObject, data,
            ExecuteEvents.updateSelectedHandler);
        return data.used;
    }

    protected override void Awake()
    {
        base.Awake();
        m_wand = new WandEventData(eventSystem);
        m_mouse = new PointerEventData(eventSystem);
    }

    public override void Process()
    {
        bool selectedObject = SendUpdateEventToSelectedObject();
        if (m_sendMoveEvents)
        {
            if (!selectedObject)
            {
                selectedObject |= SendMoveEventToSelectedObject();
            }
            if (!selectedObject)
            {
                SendSubmitEventToSelectedObject();
            }
        }

        if (m_mouseInteractionMode != MouseInteractionMode.None)
        {
            if (m_mouseInteractionMode != MouseInteractionMode.OverlayOnly)
            {
                replaceCanvasCameras(m_mouseCamera);
            }
            GetMousePointerEventData(m_mouse);
            ProcessMousePress(m_mouse, Input.GetMouseButtonDown(0), Input.GetMouseButtonUp(0)); // no gr3d warning
            ProcessMove(m_mouse);
            ProcessDrag(m_mouse);
            if (m_mouseInteractionMode != MouseInteractionMode.OverlayOnly)
            {
                restoreCanvasCameras();
            }
        }

        if (m_sendWandEvents)
        {
            GetWandPointerEventData(m_wand);
            ProcessMousePress(m_wand,
                GetButtonDownInternal(ButtonFunction.WandSubmit),
                GetButtonUpInternal(ButtonFunction.WandSubmit));
            ProcessMove(m_wand);
            ProcessDrag(m_wand);
        }
    }

    private void ProcessMousePress(PointerEventData buttonData, bool pressedThisFrame, bool releasedThisFrame)
    {
        GameObject gameObject1 = buttonData.pointerCurrentRaycast.gameObject;
        if (pressedThisFrame)
        {
            //Debug.Log(buttonData.ToString());
            buttonData.eligibleForClick = true;
            buttonData.delta = Vector2.zero;
            buttonData.dragging = false;
            buttonData.useDragThreshold = true;
            buttonData.pressPosition = buttonData.position;
            buttonData.pointerPressRaycast = buttonData.pointerCurrentRaycast;
            DeselectIfSelectionChanged(gameObject1, buttonData);
            GameObject gameObject2 = ExecuteEvents.ExecuteHierarchy<IPointerDownHandler>
                (gameObject1, buttonData, ExecuteEvents.pointerDownHandler);
            if (gameObject2 == null)
                gameObject2 = ExecuteEvents.GetEventHandler<IPointerClickHandler>(gameObject1);
            float unscaledTime = Time.unscaledTime;
            if (gameObject2 == buttonData.lastPress)
            {
                if ((double)(unscaledTime - buttonData.clickTime) < 0.300000011920929)
                    ++buttonData.clickCount;
                else
                    buttonData.clickCount = 1;
                buttonData.clickTime = unscaledTime;
            }
            else
                buttonData.clickCount = 1;
            buttonData.pointerPress = gameObject2;
            buttonData.rawPointerPress = gameObject1;
            buttonData.clickTime = unscaledTime;
            buttonData.pointerDrag = ExecuteEvents.GetEventHandler<IDragHandler>(gameObject1);
            if (buttonData.pointerDrag != null)
            {
                ExecuteEvents.Execute<IInitializePotentialDragHandler>(buttonData.pointerDrag,
                    buttonData, ExecuteEvents.initializePotentialDrag);
            }
        }
        if (!releasedThisFrame)
            return;
        ExecuteEvents.Execute<IPointerUpHandler>(buttonData.pointerPress, buttonData,
            ExecuteEvents.pointerUpHandler);
        GameObject eventHandler = ExecuteEvents.GetEventHandler<IPointerClickHandler>(gameObject1);
        if (buttonData.pointerPress == eventHandler &&
            buttonData.eligibleForClick)
            ExecuteEvents.Execute<IPointerClickHandler>(buttonData.pointerPress,
                buttonData, ExecuteEvents.pointerClickHandler);
        else if (buttonData.pointerDrag != null && buttonData.dragging)
            ExecuteEvents.ExecuteHierarchy<IDropHandler>(gameObject1, buttonData,
                ExecuteEvents.dropHandler);
        buttonData.eligibleForClick = false;
        buttonData.pointerPress = null;
        buttonData.rawPointerPress = null;
        if (buttonData.pointerDrag != null && buttonData.dragging)
            ExecuteEvents.Execute<IEndDragHandler>(buttonData.pointerDrag, buttonData,
                ExecuteEvents.endDragHandler);
        buttonData.dragging = false;
        buttonData.pointerDrag = null;
        if (!(gameObject1 != buttonData.pointerEnter))
            return;
        HandlePointerExitAndEnter(buttonData, null);
        HandlePointerExitAndEnter(buttonData, gameObject1);
    }

    private int m_ConsecutiveMoveCount;
    private Vector2 m_LastMoveVector;
    private float m_PrevActionTime;
    protected bool SendMoveEventToSelectedObject()
    {
        float unscaledTime = Time.unscaledTime;
        Vector2 rawMoveVector = GetRawMoveVectorInternal();
        if (Mathf.Approximately(rawMoveVector.x, 0.0f) && Mathf.Approximately(rawMoveVector.y, 0.0f))
        {
            m_ConsecutiveMoveCount = 0;
            return false;
        }
        bool flag1 =
            GetButtonDownInternal(ButtonFunction.Left) ||
            GetButtonDownInternal(ButtonFunction.Right) ||
            GetButtonDownInternal(ButtonFunction.Up) ||
            GetButtonDownInternal(ButtonFunction.Down)
            ;
        bool flag2 = Vector2.Dot(rawMoveVector, m_LastMoveVector) > 0.0;
        if (!flag1)
            flag1 = !flag2 || m_ConsecutiveMoveCount != 1 ? unscaledTime > m_PrevActionTime + 1.0 / m_inputActionsPerSecond : unscaledTime > m_PrevActionTime + m_repeatDelay;
        if (!flag1)
            return false;
        AxisEventData axisEventData = GetAxisEventData(rawMoveVector.x, rawMoveVector.y, 0.6f);
        if (axisEventData.moveDir != MoveDirection.None)
        {
            ExecuteEvents.Execute<IMoveHandler>(eventSystem.currentSelectedGameObject, (BaseEventData)axisEventData, ExecuteEvents.moveHandler);
            if (!flag2)
                m_ConsecutiveMoveCount = 0;
            ++m_ConsecutiveMoveCount;
            m_PrevActionTime = unscaledTime;
            m_LastMoveVector = rawMoveVector;
        }
        else
            m_ConsecutiveMoveCount = 0;
        return axisEventData.used;
    }
    protected bool SendSubmitEventToSelectedObject()
    {
        if (eventSystem.currentSelectedGameObject == null)
            return false;
        BaseEventData baseEventData = GetBaseEventData();
        if (GetButtonDownInternal(ButtonFunction.NavSubmit))
            ExecuteEvents.Execute<ISubmitHandler>(eventSystem.currentSelectedGameObject, baseEventData, ExecuteEvents.submitHandler);
        if (GetButtonDownInternal(ButtonFunction.Cancel))
            ExecuteEvents.Execute<ICancelHandler>(eventSystem.currentSelectedGameObject, baseEventData, ExecuteEvents.cancelHandler);
        return baseEventData.used;
    }
    protected abstract bool GetButtonUp(ButtonFunction function);
    protected abstract bool GetButtonDown(ButtonFunction function);
    protected abstract Vector2 GetRawMoveVector();
    private bool GetButtonUpInternal(ButtonFunction function)
    {
        return GetButtonUp(function);
    }
    private bool GetButtonDownInternal(ButtonFunction function)
    {
        return GetButtonDown(function);
    }

    private Vector2 GetRawMoveVectorInternal()
    {
        Vector2 zero = GetRawMoveVector();
        if (GetButtonDownInternal(ButtonFunction.Left))
        {
            zero.x = -1;
        }
        if (GetButtonDownInternal(ButtonFunction.Right))
        {
            zero.x = 1;
        }
        if (GetButtonDownInternal(ButtonFunction.Up))
        {
            zero.y = 1;
        }
        if (GetButtonDownInternal(ButtonFunction.Down))
        {
            zero.y = -11;
        }
        return zero;
    }
    protected override void ProcessDrag(PointerEventData pointerEvent)
    {
        bool flag = pointerEvent.IsPointerMoving() || pointerEvent is WandEventData;
        if (flag && pointerEvent.pointerDrag != null && (!pointerEvent.dragging))
        {
            ExecuteEvents.Execute<IBeginDragHandler>(pointerEvent.pointerDrag, pointerEvent, ExecuteEvents.beginDragHandler);
            pointerEvent.dragging = true;
        }
        if (!pointerEvent.dragging || !flag || !(pointerEvent.pointerDrag != null))
            return;
        /*
        if (pointerEvent.pointerPress != pointerEvent.pointerDrag)
        {
            ExecuteEvents.Execute<IPointerUpHandler>(pointerEvent.pointerPress, pointerEvent, ExecuteEvents.pointerUpHandler);
            pointerEvent.eligibleForClick = false;
            pointerEvent.pointerPress = null;
            pointerEvent.rawPointerPress = null;
        }
        */
        ExecuteEvents.Execute<IDragHandler>(pointerEvent.pointerDrag, pointerEvent, ExecuteEvents.dragHandler);
    }
}
