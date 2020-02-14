using UnityEngine;

/// <summary>
/// This class implements the PlayerInputs interface and is used as a proxy over an another
/// PlayerInputs instance.
/// </summary>
/// <remarks>
///
/// </remarks>
public class PlayerInputsProxy : MonoBehaviour, PlayerInputs
{
    [Tooltip("Target PlayerInputs object.")]
    public PlayerInputs target;
    public enum InitializationMode
    {
        None,
        SearchInParents,
        SearchInObject
    }

    [Tooltip("How the proxy is initialized. It can either search for a target proxy in its " +
        " parents or in a specified object.")]
    public InitializationMode initializationMode = InitializationMode.None;

    [Tooltip("The object on which to search for the target PlayerInputs.")]
    public Transform searchInThisObject;

    private void Start()
    {
        if(initializationMode == InitializationMode.SearchInParents && transform.parent) {
            target = transform.parent.GetComponentInParent<PlayerInputs>();
        }
        else if(initializationMode == InitializationMode.SearchInObject && searchInThisObject) {
            target = searchInThisObject.GetComponent<PlayerInputs>();
        }
    }

    private getReal3D.Sensor m_identitySensor = new getReal3D.Sensor();

    public MonoBehaviour behaviour {
        get {
            return this;
        }
    }

    public float YawAxis {
        get {
            return target != null ? target.YawAxis : 0;
        }
    }

    public float PitchAxis {
        get {
            return target != null ? target.PitchAxis : 0;
        }
    }

    public bool WandLookButtonDown {
        get {
            return target != null ? target.WandLookButtonDown : false;
        }
    }

    public bool WandLookButtonUp {
        get {
            return target != null ? target.WandLookButtonUp : false;
        }
    }

    public bool WandLookButton {
        get {
            return target != null ? target.WandLookButton : false;
        }
    }

    public bool WandDriveButtonDown {
        get {
            return target != null ? target.WandDriveButtonDown : false;
        }
    }

    public bool WandDriveButtonUp {
        get {
            return target != null ? target.WandDriveButtonUp : false;
        }
    }

    public bool WandDriveButton {
        get {
            return target != null ? target.WandDriveButton : false;
        }
    }

    public float StrafeAxis {
        get {
            return target != null ? target.StrafeAxis : 0;
        }
    }

    public float ForwardAxis {
        get {
            return target != null ? target.ForwardAxis : 0;
        }
    }

    public bool NavSpeedButtonDown {
        get {
            return target != null ? target.NavSpeedButtonDown : false;
        }
    }

    public bool NavSpeedButtonUp {
        get {
            return target != null ? target.NavSpeedButtonUp : false;
        }
    }

    public bool NavSpeedButton {
        get {
            return target != null ? target.NavSpeedButton : false;
        }
    }

    public bool JumpButtonDown {
        get {
            return target != null ? target.JumpButtonDown : false;
        }
    }

    public bool JumpButtonUp {
        get {
            return target != null ? target.JumpButtonUp : false;
        }
    }

    public bool JumpButton {
        get {
            return target != null ? target.JumpButton : false;
        }
    }

    public bool WandButtonDown {
        get {
            return target != null ? target.WandButtonDown : false;
        }
    }

    public bool WandButtonUp {
        get {
            return target != null ? target.WandButtonUp : false;
        }
    }

    public bool WandButton {
        get {
            return target != null ? target.WandButton : false;
        }
    }

    public bool ChangeWandButtonDown {
        get {
            return target != null ? target.ChangeWandButtonDown : false;
        }
    }

    public bool ChangeWandButtonUp {
        get {
            return target != null ? target.ChangeWandButtonUp : false;
        }
    }

    public bool ChangeWandButton {
        get {
            return target != null ? target.ChangeWandButton : false;
        }
    }

    public bool ResetButtonDown {
        get {
            return target != null ? target.ResetButtonDown : false;
        }
    }

    public bool ResetButtonUp {
        get {
            return target != null ? target.ResetButtonUp : false;
        }
    }

    public bool ResetButton {
        get {
            return target != null ? target.ResetButton : false;
        }
    }

    getReal3D.Sensor PlayerInputs.Wand {
        get {
            return target != null ? target.Wand : m_identitySensor;
        }
    }

    getReal3D.Sensor PlayerInputs.Head {
        get {
            return target != null ? target.Head : m_identitySensor;
        }
    }
}
