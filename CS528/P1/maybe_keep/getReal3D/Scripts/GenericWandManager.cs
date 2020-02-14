using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// This scripts allows the player to cycle through the different wands.
/// </summary>
[RequireComponent(typeof(PlayerInputs))]
public class GenericWandManager : MonoBehaviour
{
    [Tooltip("List of the different wands the player can choose from.")]
    public List<GameObject> m_managedObjects;

    private int m_activeIndex = 0;
    private PlayerInputs m_playerInputs;
    void Awake()
    {
        m_playerInputs = GetComponent<PlayerInputs>();
    }

    void Start()
    {
        SetWandActive(0);
    }

    void Update()
    {
        if(m_playerInputs.ChangeWandButtonDown) {
            SetWandActive((m_activeIndex + 1) % m_managedObjects.Count);
        }
    }

    private void SetWandActive(int index)
    {
        getReal3D.Plugin.debug(string.Format("{0} SetWandActive({1})", gameObject.name, index));
        m_activeIndex = index;
        for(int i = 0; i < m_managedObjects.Count; ++i) {
            m_managedObjects[i].SetActive(i == index);
        }
    }
}
