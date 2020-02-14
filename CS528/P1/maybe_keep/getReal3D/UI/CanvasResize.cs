using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(RectTransform))]
[ExecuteInEditMode]
public class CanvasResize : MonoBehaviour
{
    public float m_worldWidth = 1;
    public float m_worldHeight = 1;
    public bool m_updateAtStartup = true;
    public bool m_updateInPlayMode = false;
    public bool m_updateInEditor = true;

    private RectTransform m_rectTransform = null;

    void Start()
    {
        m_rectTransform = (RectTransform) transform;
        if (m_updateAtStartup)
        {
            UpdateSize();
        }
    }

    void Update()
    {
        if ((Application.isPlaying && m_updateInPlayMode) ||
            (!Application.isPlaying && m_updateInEditor))
        {
            UpdateSize();
        }
    }

    void UpdateSize()
    {
        m_rectTransform.localScale = new Vector3(
            m_worldWidth / m_rectTransform.rect.size.x,
            m_worldHeight / m_rectTransform.rect.size.y,
            1
        );
    }
}
