using UnityEngine.EventSystems;

/// <summary>
/// This class is a Unity EventSystem that bypasses the application focus.
/// </summary>
public class FixedFocusEventSystem : EventSystem {
    protected override void OnApplicationFocus(bool hasFocus) { }
}
