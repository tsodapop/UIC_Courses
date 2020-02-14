using UnityEngine;
using System.Collections;

/// <summary>
/// This script is used to exit getReal3D upon a key press.
/// </summary>
public class getRealExit : MonoBehaviour {

    [Tooltip("Key used to exit.")]
    public getReal3D.VirtualKeyCode m_exitKey = getReal3D.VirtualKeyCode.VK_ESCAPE;

    void Update()
    {
        if(getReal3D.Input.GetKeyDown(m_exitKey)) {
#if         UNITY_EDITOR
            UnityEditor.EditorApplication.isPlaying = false;
#           else
            getReal3D.Plugin.clusterShutdown();
#           endif
        }
    }
}
