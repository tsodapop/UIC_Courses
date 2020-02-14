using getReal3D.MultiCluster;
using UnityEngine;

/// <summary>
/// This example shows how to use SyncVar.
/// </summary>
public class TestSyncVar : NetworkBehaviour {

    [SyncVar(hook = "ColorChanged")]
    Color color = Color.white;

    private float m_lastChange;

    public override void OnStartClient()
    {
        Debug.Log("TestSyncVar.OnStartClient: color is " + color + ".");
    }

    void Update()
    {
        if(isServer && Time.time > m_lastChange + 2) {
            color = Random.ColorHSV(.2f, .8f);
            m_lastChange = Time.time;
        }
    }

    private void ColorChanged(Color newColor)
    {
        Debug.Assert(isClient);
        Debug.Log("TestSyncVar color changed from " + color + " to " + newColor + ".");
        color = newColor;
        Renderer renderer = GetComponent<Renderer>();
        renderer.material.color = color;
    }
}
