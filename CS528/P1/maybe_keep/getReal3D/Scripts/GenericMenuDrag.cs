using UnityEngine;
using System.Collections.Generic;
using System;

public interface MenuClickedOustideCallback
{
    void clickOutside();
}

/// <summary>
/// Script used to drag a 3D menu by clicking on some part of it (see draggable field).
/// </summary>
///
[RequireComponent(typeof(RectTransform)), RequireComponent(typeof(Canvas))]
public class GenericMenuDrag : MonoBehaviour {

    private Canvas m_canvas;
    private RectTransform m_rectTransform;
    public MenuClickedOustideCallback m_showMenu;
    public PlayerInputs m_inputs;

    [Tooltip("Parts of the menu that can be used to drag it.")]
    public List<GameObject> m_draggable = new List<GameObject>();

    [Tooltip("Object that is set as the new menu parent while it is being dragged.")]
    public Transform m_hand;

    private Transform m_originalParent;
    private GenericWandEventModule m_wandEventModule;

    void Start()
    {
        m_canvas = GetComponent<Canvas>() as Canvas;
        m_rectTransform = gameObject.transform as RectTransform;
        m_originalParent = transform.parent;
        m_wandEventModule = GameObject.FindObjectOfType<GenericWandEventModule>();
    }

    void Update()
    {
        if(m_inputs == null) {
            return;
        }

        bool pointerOnRect = RectTransformUtility.RectangleContainsScreenPoint
            (m_rectTransform, m_canvas.worldCamera.pixelRect.center, m_canvas.worldCamera);



        if(m_inputs.WandButtonDown) {
            if(!pointerOnRect) {
                m_showMenu.clickOutside();
            }
        }

        if(m_inputs.WandButtonDown && pointerOnRect & isDraggable()) {
            Grab();
        }

        if(m_inputs.WandButtonUp) {
            Release();
        }
    }

    private bool isDraggable()
    {
        if(m_wandEventModule == null) {
            return false;
        }
        var currentLook = m_wandEventModule.currentLook;
        if(currentLook == null) {
            return false;
        }
        foreach(var obj in m_draggable) {
            if(currentLook.transform.IsChildOf(obj.transform)) {
                return true;
            }
        }
        return false;
    }

    void Grab()
    {
        transform.SetParent(m_hand.transform, true);
    }

    void Release()
    {
        transform.SetParent(m_originalParent, true);
    }
}
