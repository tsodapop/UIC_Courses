using UnityEngine;
using getReal3D;

/// <summary>
/// Script used to navigate (internally use NavigationHelper class).
/// </summary>
[AddComponentMenu("getReal3D/Generic Navigation")]
[RequireComponent(typeof(CharacterController))]
[RequireComponent(typeof(CharacterMotorC))]
[RequireComponent(typeof(PlayerInputs))]
public class Navigation : MonoBehaviour, NavigationScriptInterface
{
    public NavigationHelper m_navigationHelper = new NavigationHelper();
    public NavigationHelper navigationHelper { get { return m_navigationHelper; } }

    void Awake()
    {
        m_navigationHelper.playerInputs = GetComponent<PlayerInputs>();
    }

    void Update()
    {
        m_navigationHelper.Update(transform);
    }

    void FixedUpdate()
    {
        m_navigationHelper.FixedUpdate(transform);
    }
}
