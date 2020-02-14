using getReal3D.MultiCluster;
using UnityEngine;

/// <summary>
/// Script handling command and RPC used to enable and disable lights on a MultiCluster.
/// </summary>
public class LightHandler : NetworkBehaviour {
    public void EnableLight(Light light, bool e)
    {
        string path = GetPath(light.transform);
        CmdEnableLight(path, e);
    }

    private void Start()
    {
        if(isServer) {
            foreach(Light light in FindObjectsOfType<Light>()) {
                RpcEnableLight(GetPath(light.transform), light.enabled);
            }
        }
    }

    [Command]
    private void CmdEnableLight(string path, bool enabled)
    {
        RpcEnableLight(path, enabled);
    }

    [ClientRpc]
    private void RpcEnableLight(string path, bool enabled)
    {
        GameObject go = GameObject.Find(path);
        if(!go) {
            Debug.LogError("Failed to find object named " + path + ".");
            return;
        }
        Light light = go.GetComponent<Light>();
        if(!light) {
            Debug.LogError("Object " + path + " doesn't have a light.");
            return;
        }
        light.enabled = enabled;
    }
    private string GetPath(Transform t)
    {
        string path = t.name;
        while(t.parent != null && t.parent != transform) {
            t = t.parent;
            path = t.name + "/" + path;
        }
        return path;
    }
}
