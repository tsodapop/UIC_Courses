using getReal3D.MultiCluster;
using UnityEngine;

/// <summary>
/// This example shows how to spawn an object. The object must have a NetworkIdentity and
/// must be registered in the NetworkManager.
/// </summary>
public class TestObjectSpawning : NetworkBehaviour {
    [Tooltip("Prefab to spawn.")]
    public GameObject prefab = null;
    private float m_lastChange;

    void Update()
    {
        if (isServer && Time.time > m_lastChange + 2 && prefab != null) {
            doSpawn();
            m_lastChange = Time.time;
        }
    }
    void doSpawn()
    {
        Debug.Assert(isServer);
        var position = transform.position + Random.insideUnitSphere;
        var rotation = Random.rotation;
        GameObject newObject = Instantiate(prefab, position, rotation);
        NetworkServer.Spawn(newObject);
    }
}
