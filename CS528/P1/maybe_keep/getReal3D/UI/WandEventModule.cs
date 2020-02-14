
// This class is deprecated. GenericWandEventModule should be used instead.
public class WandEventModule : WandEventModuleBase {

    // name of button to use for click/submit
    public string submitButtonName = "WandButton";
    public string horizontalAxisName = "Yaw";
    public string verticalAxisName = "Forward";

    protected override bool GetButtonDown(ButtonFunction function)
    {
        switch (function)
        {
            case ButtonFunction.WandSubmit:
                return getReal3D.Input.GetButtonDown(submitButtonName);
        }
        return false;
    }

    protected override bool GetButtonUp(ButtonFunction function)
    {
        switch (function)
        {
            case ButtonFunction.WandSubmit:
                return getReal3D.Input.GetButtonUp(submitButtonName);
        }
        return false;
    }

    protected override UnityEngine.Vector2 GetRawMoveVector()
    {
        return new UnityEngine.Vector2(getReal3D.Input.GetAxis(horizontalAxisName),
            getReal3D.Input.GetAxis(verticalAxisName));
    }
}
