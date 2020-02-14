using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using getReal3D.MultiCluster;

/// <summary>
/// This scripts allows the player to cycle through the different wands.
/// </summary>
[AddComponentMenu("getReal3D/Multi Cluster/Wand Manager")]
[RequireComponent(typeof(PlayerInputs))]
public class MultiClusterWandManager : NetworkBehaviour {

    [Tooltip("List of the different wands the player can choose from.")]
    public List<GameObject> m_managedObjects;

    [SyncVar(hook = "SetWandActive")]
    private int m_activeIndex = 0;
    private PlayerInputs m_playerInputs;
    void Awake()
    {
        m_playerInputs = GetComponent<PlayerInputs>();
    }

    void Start()
    {
        if(isLocalPlayer) {
            SetWandActive(0);
        }
        else {
            for(int i = 0; i < m_managedObjects.Count; ++i) {
                var wand = m_managedObjects[i];
                foreach(var collider in wand.GetComponentsInChildren<Collider>()) {
                    collider.enabled = false;
                }
                wand.SetActive(i == m_activeIndex);
            }
        }
    }

    void Update()
    {
        if(m_playerInputs.ChangeWandButtonDown) {
            getReal3D.Plugin.debug(string.Format("{0} Button pushed", gameObject.name));
            if(isLocalPlayer) {
                getReal3D.Plugin.debug(string.Format("{0} Changing wand", gameObject.name));
                CmdChangeWand((m_activeIndex + 1) % m_managedObjects.Count);
            }
        }
    }

    [Command]
    void CmdChangeWand(int index)
    {
        getReal3D.Plugin.debug(string.Format("{0} CmdChangeWand({1})", gameObject.name, index));
        m_activeIndex = index;
    }

    private void SetWandActive(int index)
    {
        getReal3D.Plugin.debug(string.Format("{0} SetWandActive({1})", gameObject.name, index));
        m_activeIndex = index;
        for(int i=0; i<m_managedObjects.Count; ++i) {
            m_managedObjects[i].SetActive(i == index);
        }
    }
}
