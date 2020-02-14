using UnityEngine;

/// <summary>
/// Example script using showing how to react to a wand button push using the generic
/// player inputs interface.
/// </summary>
[RequireComponent(typeof(PlayerInputs))]
public class PlayerInputsExample : MonoBehaviour
{
    private PlayerInputs m_playerInputs;
    void Start()
    {
        m_playerInputs = GetComponent<PlayerInputs>();
    }
    void Update()
    {
        if(m_playerInputs.WandButtonDown) {
            // Wand button has been pushed, do something...
        }
    }
}
