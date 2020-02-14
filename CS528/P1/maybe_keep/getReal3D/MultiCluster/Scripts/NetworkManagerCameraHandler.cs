using System;
using UnityEngine;
using getReal3D.MultiCluster;
using getReal3D.MultiCluster.Message;

/// <summary>
/// Specialization of NetworkManager that disable a camera when the NetworkManager is connected,
/// and re-enable it upon disconnection.
/// </summary>
class NetworkManagerCameraHandler : NetworkManager
{
    [Tooltip("The camera that is used when the network manager is disconnected.")]
    public Camera cameraWhenDisconnected = null;

    public void EnableCamera()
    {
        if(cameraWhenDisconnected) {
            cameraWhenDisconnected.gameObject.SetActive(true);
        }
    }

    public void DisableCamera()
    {
        if(cameraWhenDisconnected) {
            cameraWhenDisconnected.gameObject.SetActive(false);
        }
    }

    public override void OnStopClient()
    {
        EnableCamera();
    }

    public override void OnStartServer()
    {
        DisableCamera();
    }

    public override void OnStopServer()
    {
        EnableCamera();
    }

    public override void OnStartClient(NetworkClient client)
    {
        DisableCamera();
    }
}
