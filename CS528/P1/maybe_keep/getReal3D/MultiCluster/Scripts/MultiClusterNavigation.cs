using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using getReal3D;
using getReal3D.MultiCluster;

/// <summary>
/// Script used to navigate (internally use NavigationHelper class).
/// </summary>
[AddComponentMenu("getReal3D/Multi Cluster/Navigation")]
[RequireComponent(typeof(CharacterController))]
[RequireComponent(typeof(CharacterMotorC))]
[RequireComponent(typeof(PlayerInputs))]
public class MultiClusterNavigation : NetworkBehaviour, NavigationScriptInterface
{
    public NavigationHelper m_navigationHelper = new NavigationHelper();
    public NavigationHelper navigationHelper { get { return m_navigationHelper; } }

    void Awake()
    {
        m_navigationHelper.playerInputs = GetComponent<PlayerInputs>();
    }

    void Start()
    {
        if(isLocalPlayer) {
            m_navigationHelper.WriteSettings();
        }
        else {
            GetComponent<CharacterController>().enabled = false;
            GetComponent<CharacterMotorC>().enabled = false;
        }
    }

    void Update()
    {
        if(isLocalPlayer) {
            m_navigationHelper.Update(transform);
        }
    }

    void FixedUpdate()
    {
        if(isLocalPlayer) {
            m_navigationHelper.FixedUpdate(transform);
        }
    }
}
