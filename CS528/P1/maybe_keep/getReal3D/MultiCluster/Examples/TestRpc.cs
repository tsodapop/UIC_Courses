using getReal3D.MultiCluster;
using UnityEngine;

/// <summary>
/// This example shows how to use Command and ClientRpc.
/// </summary>
public class TestRpc : NetworkBehaviour {

    private float m_lastChange;

    private void Update()
    {
        if((isLocalPlayer||(isClient && hasAuthority)) && Time.time > m_lastChange + 2){
            CmdBcastRandomColor(Random.ColorHSV(.2f, .8f));
            m_lastChange = Time.time;
        }
    }

    [Command]
    public void CmdBcastRandomColor(Color color)
    {
        Debug.Assert(isServer);
        RpcReceiveColor(color);
    }

    [ClientRpc]
    public void RpcReceiveColor(Color color)
    {
        Debug.Assert(isClient);
        Debug.Log("TestRpc: received color " + color + ".");
    }
}
