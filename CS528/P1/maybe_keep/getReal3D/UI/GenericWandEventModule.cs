using UnityEngine;
using System.Collections;
using System;

/// <summary>
/// GenericWandEventModule is used to send generic inputs to Unity UI.
/// </summary>
/// <remarks>
/// A generic PlayerInputs must be set in order for this class to retrieve the submit button.
/// This is usually set via the VRToolkitChoice script.
/// </remarks>
public class GenericWandEventModule : WandEventModuleBase
{

    public PlayerInputs playerInputs {
        get { return m_playerInputs; }
        set { m_playerInputs = value; }
    }

    private PlayerInputs m_playerInputs;

    protected override bool GetButtonDown(ButtonFunction function)
    {
        switch (function)
        {
            case ButtonFunction.WandSubmit:
                return playerInputs != null ? playerInputs.WandButtonDown : false;
            case ButtonFunction.NavSubmit:
                return playerInputs != null ? playerInputs.ChangeWandButtonDown : false;
        }
        return false;
    }

    protected override bool GetButtonUp(ButtonFunction function)
    {
        switch(function){
            case ButtonFunction.WandSubmit:
                return playerInputs != null ? playerInputs.WandButtonUp : false;
        }
        return false;
    }

    protected override Vector2 GetRawMoveVector()
    {
        return playerInputs != null ? new Vector2(playerInputs.YawAxis, playerInputs.ForwardAxis) :
            Vector2.zero;
    }
}
