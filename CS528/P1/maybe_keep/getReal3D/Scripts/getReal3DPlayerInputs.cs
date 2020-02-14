using System;
using getReal3D;
using UnityEngine;

/// <summary>
/// This class is the getReal3D implementation of PlayerInputs interface.
/// </summary>
public class getReal3DPlayerInputs : getRealUserScript, PlayerInputs {

    [Header("Axis")]
    [Tooltip("getReal3D axis name for forward axis.")]
    public string forwardAxis = "Forward";
    [Tooltip("getReal3D axis name for strafe axis.")]
    public string strafeAxis = "Strafe";
    [Tooltip("getReal3D axis name for yaw axis.")]
    public string yawAxis = "Yaw";
    [Tooltip("getReal3D axis name for pitch axis.")]
    public string pitchAxis = "Pitch";

    [Header("Buttons")]
    [Tooltip("getReal3D button name for wand type change.")]
    public string changeWandButton = "ChangeWand";
    [Tooltip("getReal3D button name for wand main action.")]
    public string wandButton = "WandButton";
    [Tooltip("getReal3D button name for toggling fast navigation.")]
    public string navSpeedButton = "NavSpeed";
    [Tooltip("getReal3D button name for reseting player position.")]
    public string resetButton = "Reset";
    [Tooltip("getReal3D button name for jumping.")]
    public string jumpButton = "Jump";
    [Tooltip("getReal3D button name for wand drive mode.")]
    public string wandDriveButton = "WandDrive";
    [Tooltip("getReal3D button name for wand look mode.")]
    public string wandlookButton = "WandLook";

    public MonoBehaviour behaviour {
        get{
            return this;
        }
    }

    public float YawAxis {
        get {
            return getReal3D.Input.GetAxis(yawAxis);
        }
    }

    public float PitchAxis {
        get {
            return getReal3D.Input.GetAxis(pitchAxis);
        }
    }

    public bool WandLookButtonDown {
        get {
            return getReal3D.Input.GetButtonDown(wandlookButton);
        }
    }

    public bool WandLookButtonUp {
        get {
            return getReal3D.Input.GetButtonUp(wandlookButton);
        }
    }

    public bool WandLookButton {
        get {
            return getReal3D.Input.GetButton(wandlookButton);
        }
    }

    public bool WandDriveButtonDown {
        get {
            return getReal3D.Input.GetButtonDown(wandDriveButton);
        }
    }

    public bool WandDriveButtonUp {
        get {
            return getReal3D.Input.GetButtonUp(wandDriveButton);
        }
    }

    public bool WandDriveButton {
        get {
            return getReal3D.Input.GetButton(wandDriveButton);
        }
    }

    public float StrafeAxis {
        get {
            return getReal3D.Input.GetAxis(strafeAxis);
        }
    }

    public float ForwardAxis {
        get {
            return getReal3D.Input.GetAxis(forwardAxis);
        }
    }

    public bool NavSpeedButtonDown {
        get {
            return getReal3D.Input.GetButtonDown(navSpeedButton);
        }
    }

    public bool NavSpeedButtonUp {
        get {
            return getReal3D.Input.GetButtonUp(navSpeedButton);
        }
    }

    public bool NavSpeedButton {
        get {
            return getReal3D.Input.GetButton(navSpeedButton);
        }
    }

    public bool JumpButtonDown {
        get {
            return getReal3D.Input.GetButtonDown(jumpButton);
        }
    }

    public bool JumpButtonUp {
        get {
            return getReal3D.Input.GetButtonUp(jumpButton);
        }
    }

    public bool JumpButton {
        get {
            return getReal3D.Input.GetButton(jumpButton);
        }
    }

    public bool WandButtonDown {
        get {
            return getReal3D.Input.GetButtonDown(wandButton);
        }
    }

    public bool WandButtonUp {
        get {
            return getReal3D.Input.GetButtonUp(wandButton);
        }
    }

    public bool WandButton {
        get {
            return getReal3D.Input.GetButton(wandButton);
        }
    }

    public bool ChangeWandButtonDown {
        get {
            return getReal3D.Input.GetButtonDown(changeWandButton);
        }
    }

    public bool ChangeWandButtonUp {
        get {
            return getReal3D.Input.GetButtonUp(changeWandButton);
        }
    }

    public bool ChangeWandButton {
        get {
            return getReal3D.Input.GetButton(changeWandButton);
        }
    }

    public bool ResetButtonDown {
        get {
            return getReal3D.Input.GetButtonDown(resetButton);
        }
    }

    public bool ResetButtonUp {
        get {
            return getReal3D.Input.GetButtonUp(resetButton);
        }
    }

    public bool ResetButton {
        get {
            return getReal3D.Input.GetButton(resetButton);
        }
    }

    Sensor PlayerInputs.Wand {
        get {
            return getWand();
        }
    }

    Sensor PlayerInputs.Head {
        get {
            return getHead();
        }
    }
}
