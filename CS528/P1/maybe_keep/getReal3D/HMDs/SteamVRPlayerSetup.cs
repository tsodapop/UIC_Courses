using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SteamVRPlayerSetup : MonoBehaviour, MultiClusterSetupScript
{
    public void MultiClusterSetup(bool localPlayer)
    {
        if(localPlayer) {
            transform.Find("[CameraRig]").gameObject.SetActive(true);
        }
    }
}
