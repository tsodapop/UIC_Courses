using getReal3D.MultiCluster;
using getReal3D.MultiCluster.Message;
using UnityEngine;

/// <summary>
/// This custom MultiClusterManager shows how to let the client tell
/// the server what type of player prefab to spawn.
/// </summary>
public class TestPlayerSpawning : NetworkManager {

    public GameObject prefabA;
    public GameObject prefabB;
    enum SpawnType {
        A, B
    }

    [System.Serializable]
    class PlayerConfigMessage : MessageBase {
        public SpawnType spawnType;
    }

    public override void OnServerAddPlayer(NetworkConnection conn, short playerControllerId,
        NetworkReader extraMessageReader)
    {
        PlayerConfigMessage message = extraMessageReader.ReadMessage<PlayerConfigMessage>();
        Debug.Log("Server add player of type: " + message.spawnType.ToString() + ".");

        GameObject player = null;
        switch(message.spawnType) {
        case SpawnType.A: player = Instantiate(prefabA); break;
        case SpawnType.B: player = Instantiate(prefabB); break;
        }
        player.SetActive(true);
        NetworkServer.AddPlayerForConnection(conn, player, playerControllerId);
    }

    public override void OnClientConnect(NetworkConnection conn)
    {
        PlayerConfigMessage message = new PlayerConfigMessage();
        message.spawnType = SpawnType.A;
        ClientScene.AddPlayer(conn, 0, message);
    }
}
