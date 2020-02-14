using UnityEngine;

/// <summary>
/// This script, when attached to an object with a canvas prevents the GenericShowMenu to
/// pop up the getReal3D menu when the wand is pointing at the canvas.
/// </summary>
[RequireComponent(typeof(RectTransform)), RequireComponent(typeof(Canvas))]
public class PreventShowMenu : MonoBehaviour, PreventShowMenuCallback
{
    private Canvas m_canvas;
    private RectTransform m_rectTransform;

    void Start()
    {
        m_canvas = GetComponent<Canvas>() as Canvas;
        m_rectTransform = gameObject.transform as RectTransform;
        var genericShowMenu = FindObjectsOfType<GenericShowMenu>() as GenericShowMenu[];
        foreach(var gsm in genericShowMenu) {
            gsm.Register(this);
        }
    }

    void OnDestroy()
    {
        var genericShowMenu = FindObjectsOfType<GenericShowMenu>() as GenericShowMenu[];
        foreach(var gsm in genericShowMenu) {
            gsm.Deregister(this);
        }
    }

    public bool preventsShowMenu(Transform wandObject)
    {
        return RectTransformUtility.RectangleContainsScreenPoint
            (m_rectTransform, m_canvas.worldCamera.pixelRect.center, m_canvas.worldCamera);
    }

}
