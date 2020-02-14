using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.VR;
using getReal3D.MultiCluster;
#if (UNITY_2017_2_OR_NEWER)
using VRSettings = UnityEngine.XR.XRSettings;
#else
using VRSettings = UnityEngine.VR.VRSettings;
#endif

public interface MultiClusterSetupScript
{
    void MultiClusterSetup(bool localPlayer);
}

/// <summary>
/// Script enabling the correct child transform according to the loaded VR device.
/// </summary>
/// <remarks>
/// After the child is enabled, all of its MultiClusterSetupScript components are called.
/// </remarks>
[RequireComponent(typeof(PlayerInputsProxy))]
public class MultiClusterPlayerSetup : NetworkBehaviour
{
    Dictionary<string, string> m_deviceToObject = new Dictionary<string, string>()
    {
        { "", "[getReal3D]" },
        { "OpenVR", "[SteamVR]" },
    };

    void Start()
    {
        try {
            string childName = m_deviceToObject[VRSettings.loadedDeviceName];
            Transform child = transform.Find(childName);
            if(child) {
                Setup(child);
            }
            else {
                Debug.LogError("Unable to find the child corresponding to the VR device " +
                    childName);
            }
        }
        catch(KeyNotFoundException) {
            Debug.LogError("Unable to find VR device in list: " + VRSettings.loadedDeviceName);
        }
    }

    void Setup(Transform target)
    {
        target.gameObject.SetActive(true);
        if(isLocalPlayer) {
            var playerInputsProxy = GetComponent<PlayerInputsProxy>();
            playerInputsProxy.target = target.GetComponent<PlayerInputs>();
            if(playerInputsProxy.target == null) {
                Debug.LogError("Failed to find PlayerInputs component in target.");
            }
            var wandEventModule = FindObjectOfType<GenericWandEventModule>();
            if(wandEventModule) {
                wandEventModule.playerInputs = playerInputsProxy;
            }
            else {
                Debug.LogError("Failed to find GenericWandEventModule component in scene.");
            }
        }
        foreach(var mcs in target.GetComponentsInChildren<MultiClusterSetupScript>()) {
            mcs.MultiClusterSetup(isLocalPlayer);
        }
    }
}
