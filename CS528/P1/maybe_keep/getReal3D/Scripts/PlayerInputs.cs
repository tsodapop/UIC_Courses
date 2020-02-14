using getReal3D;
using UnityEngine;

/// <summary>
/// Generic interface for retrieving player inputs.
/// </summary>
public interface PlayerInputs {
    MonoBehaviour behaviour { get; }
    float YawAxis { get; }
    float PitchAxis { get; }
    bool WandLookButtonDown { get; }
    bool WandLookButtonUp { get; }
    bool WandLookButton { get; }
    bool WandDriveButtonDown { get; }
    bool WandDriveButtonUp { get; }
    bool WandDriveButton { get; }
    float StrafeAxis { get; }
    float ForwardAxis { get; }
    bool NavSpeedButtonDown { get; }
    bool NavSpeedButtonUp { get; }
    bool NavSpeedButton { get; }
    bool JumpButtonDown { get; }
    bool JumpButtonUp { get; }
    bool JumpButton { get; }
    bool WandButtonDown { get; }
    bool WandButtonUp { get; }
    bool WandButton { get; }
    bool ChangeWandButtonDown { get; }
    bool ChangeWandButtonUp { get; }
    bool ChangeWandButton { get; }
    bool ResetButtonDown { get; }
    bool ResetButtonUp { get; }
    bool ResetButton { get; }
    Sensor Wand { get; }
    Sensor Head { get; }
}
