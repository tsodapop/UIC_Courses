using System.Linq;
using UnityEngine;
using getReal3D.MultiCluster;

/// <summary>
/// Testing class for NetworkInstanceId.
/// </summary>
public class TestNetId : NetworkBehaviour
{
    public uint thisObjectId;

    [SyncVar]
    private NetworkInstanceId syncVar;

    private SyncListStruct<NetworkInstanceId> syncList = new SyncListStruct<NetworkInstanceId>();

    // Use this for initialization
    void Start()
    {
        thisObjectId = netId.Value;
        GameObject go = ClientScene.FindLocalObject(netId);
        if (go != gameObject) {
            Debug.LogError("Unexpected game object!");
        }
    }

    public override void OnStartServer()
    {
        Debug.Log(name + ".OnStartServer netId " + netId);
        syncVar = netId;
        syncList.Add(netId);
        syncList.Add(netId);
        syncList.Add(netId);
    }

    public override void OnStartClient()
    {
        Debug.Log(name + ".OnStartClient netId " + netId);
        Debug.Log(name + ".OnStartClient sync var " + syncVar);
    }

    public override void OnStartLocalPlayer()
    {
        Debug.Log(name + ".OnStartLocalPlayer netId " + netId);
        CmdTestSendNetId(netId);
    }

    [Command]
    private void CmdTestSendNetId(NetworkInstanceId networkInstanceId)
    {
        TestSendNetId(networkInstanceId);
    }

    private void TestSendNetId(NetworkInstanceId networkInstanceId)
    {
        Debug.Log("Server received NetworkInstanceId " + networkInstanceId);
    }
}
