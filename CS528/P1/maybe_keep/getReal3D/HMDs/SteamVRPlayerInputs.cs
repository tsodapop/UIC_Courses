using System;
using getReal3D;
using UnityEngine;
using Valve.VR;
using System.Xml.Serialization;
using System.IO;
using System.Collections.Generic;
using System.Xml.XPath;
using System.Xml;

/// <summary>
/// This class is the SteamVR implementation of PlayerInputs interface.
/// </summary>
public class SteamVRPlayerInputs : MonoBehaviour, PlayerInputs {

    [Tooltip("This must be set to the SteamVR head in order to retrieve the user head position.")]
    public Transform viveHead;

    [Tooltip("This must be set to the SteamVR right controller.")]
    public Transform viveRightController;

    public MonoBehaviour behaviour { get { return this;} }

    public enum Button {
        System = EVRButtonId.k_EButton_System,
        ApplicationMenu = EVRButtonId.k_EButton_ApplicationMenu,
        Grip = EVRButtonId.k_EButton_Grip,
        DPadLeft = EVRButtonId.k_EButton_DPad_Left,
        DPadUp = EVRButtonId.k_EButton_DPad_Up,
        DPadRight = EVRButtonId.k_EButton_DPad_Right,
        DPadDown = EVRButtonId.k_EButton_DPad_Down,
        A = EVRButtonId.k_EButton_A,
        ProximitySensor = EVRButtonId.k_EButton_ProximitySensor,
        Axis2 = EVRButtonId.k_EButton_Axis2,
        Axis3 = EVRButtonId.k_EButton_Axis3,
        Axis4 = EVRButtonId.k_EButton_Axis4,
        Touchpad = EVRButtonId.k_EButton_SteamVR_Touchpad,
        Trigger = EVRButtonId.k_EButton_SteamVR_Trigger
    }

    [Serializable]
    public struct Binding {
        public Binding(ETrackedControllerRole controllerRole, Button button)
        {
            this.controllerRole = controllerRole;
            this.button = button;
        }
        [XmlAttribute(AttributeName = "Controller")]
        public ETrackedControllerRole controllerRole;
        [XmlAttribute(AttributeName = "Button")]
        public Button button;
        public ulong index { get { return (ulong) (1ul << (int) button); } }
    }

    public enum AxisName {
        Horizontal = 0,
        Vertical = 1
    }

    [Serializable]
    public struct Axis {
        public Axis(ETrackedControllerRole controllerRole=ETrackedControllerRole.Invalid,
            AxisName axis = AxisName.Vertical, float deadZone = 0.2f)
        {
            this.controllerRole = controllerRole;
            this.axis = axis;
            this.deadZone = deadZone;
        }
        [XmlAttribute(AttributeName = "Controller")]
        public ETrackedControllerRole controllerRole;
        [XmlAttribute(AttributeName = "Axis")]
        public AxisName axis;
        [XmlAttribute(AttributeName = "DeadZone")]
        public float deadZone;
        public ulong index { get { return (ulong) axis; } }
    }

    [Serializable]
    public class Bindings {
        public Binding JumpButton =
            new Binding(ETrackedControllerRole.LeftHand, Button.Trigger);

        public Binding ResetButton =
            new Binding(ETrackedControllerRole.LeftHand, Button.ApplicationMenu);

        public Binding ChangeWandButton =
            new Binding(ETrackedControllerRole.RightHand, Button.ApplicationMenu);

        public Binding WandButton =
            new Binding(ETrackedControllerRole.RightHand, Button.Trigger);

        public Binding WandDrive =
            new Binding(ETrackedControllerRole.RightHand, Button.Grip);

        public Binding WandLook =
            new Binding(ETrackedControllerRole.LeftHand, Button.Grip);

        public Binding NavSpeedButton =
            new Binding(ETrackedControllerRole.Invalid, Button.System);

        public Axis ForwardAxis =
            new Axis(ETrackedControllerRole.RightHand, AxisName.Vertical);

        public Axis PitchAxis =
            new Axis(ETrackedControllerRole.LeftHand, AxisName.Vertical);

        public Axis StrafeAxis =
            new Axis(ETrackedControllerRole.LeftHand, AxisName.Horizontal);

        public Axis YawAxis =
            new Axis(ETrackedControllerRole.RightHand, AxisName.Horizontal);
    }

    public Bindings bindings = new Bindings();

    public bool ChangeWandButtonDown {
        get {
            return GetButtonDown(bindings.ChangeWandButton);
        }
    }

    public bool ChangeWandButtonUp {
        get {
            return GetButtonUp(bindings.ChangeWandButton);
        }
    }

    public bool ChangeWandButton {
        get {
            return GetButton(bindings.ChangeWandButton);
        }
    }

    public float ForwardAxis {
        get {
            return GetAxis(bindings.ForwardAxis);
        }
    }

    public Sensor Head {
        get {
            return GetSensor(viveHead);
        }
    }

    public bool JumpButtonDown {
        get {
            return GetButtonDown(bindings.JumpButton);
        }
    }

    public bool JumpButtonUp {
        get {
            return GetButtonUp(bindings.JumpButton);
        }
    }

    public bool JumpButton {
        get {
            return GetButton(bindings.JumpButton);
        }
    }

    public bool NavSpeedButtonDown {
        get {
            return GetButtonDown(bindings.NavSpeedButton);
        }
    }

    public bool NavSpeedButtonUp {
        get {
            return GetButtonUp(bindings.NavSpeedButton);
        }
    }

    public bool NavSpeedButton {
        get {
            return GetButton(bindings.NavSpeedButton);
        }
    }

    public float PitchAxis {
        get {
            return GetAxis(bindings.PitchAxis);
        }
    }

    public bool ResetButtonDown {
        get {
            return GetButtonDown(bindings.ResetButton);
        }
    }

    public bool ResetButtonUp {
        get {
            return GetButtonUp(bindings.ResetButton);
        }
    }

    public bool ResetButton {
        get {
            return GetButton(bindings.ResetButton);
        }
    }

    public float StrafeAxis {
        get {
            return GetAxis(bindings.StrafeAxis);
        }
    }

    public Sensor Wand {
        get {
            return GetSensor(viveRightController);
        }
    }

    public bool WandButtonDown {
        get {
            return GetButtonDown(bindings.WandButton);
        }
    }

    public bool WandButtonUp {
        get {
            return GetButtonUp(bindings.WandButton);
        }
    }

    public bool WandButton {
        get {
            return GetButton(bindings.WandButton);
        }
    }

    public bool WandDriveButton {
        get {
            return GetButton(bindings.WandDrive);
        }
    }

    public bool WandDriveButtonDown {
        get {
            return GetButtonDown(bindings.WandDrive);
        }
    }

    public bool WandDriveButtonUp {
        get {
            return GetButtonUp(bindings.WandDrive);
        }
    }

    public bool WandLookButton {
        get {
            return GetButton(bindings.WandLook);
        }
    }

    public bool WandLookButtonDown {
        get {
            return GetButtonDown(bindings.WandLook);
        }
    }

    public bool WandLookButtonUp {
        get {
            return GetButtonUp(bindings.WandLook);
        }
    }

    public float YawAxis {
        get {
            return GetAxis(bindings.YawAxis);
        }
    }

    private Sensor GetSensor(Transform t)
    {
        Sensor res;
        res.position = t.localPosition;
        res.rotation = t.localRotation;
        return res;
    }
    private static uint GetDeviceForRole(ETrackedControllerRole controllerRole)
    {
        if(OpenVR.System != null) {
            return OpenVR.System.GetTrackedDeviceIndexForControllerRole(controllerRole);
        }
        else {
            return OpenVR.k_unTrackedDeviceIndexInvalid;
        }
    }
    private float ApplyDeadZone(float value, float deadZone)
    {
        if(value < -deadZone) {
            return (value + deadZone) / (1 - deadZone);
        }
        else if(value > deadZone) {
            return (value - deadZone) / (1 - deadZone);
        }
        else {
            return 0;
        }
    }

    private static float GetElement(UnityEngine.Vector2 v, ulong idx)
    {
        Debug.Assert(idx == 0 || idx == 1);
        if(idx == 0) { return v.x; }
        else { return v.y; }
    }
    private static bool isValid(uint deviceIndex)
    {
        return deviceIndex != OpenVR.k_unTrackedDeviceIndexInvalid;
    }
    protected float GetAxis(Axis axis)
    {
        return GetAxis(axis.controllerRole, axis.index, axis.deadZone);
    }
    private float GetAxis(ETrackedControllerRole controllerRole, ulong index, float deadZone)
    {
        var deviceIndex = GetDeviceForRole(controllerRole);
        float value = isValid(deviceIndex) ?
                GetElement(SteamVR_Controller.Input((int) deviceIndex).GetAxis(), index) :
                0;
        return ApplyDeadZone(value, deadZone);
    }
    private static bool GetButton(ETrackedControllerRole controllerRole, ulong index)
    {
        var deviceIndex = GetDeviceForRole(controllerRole);
        return isValid(deviceIndex) ?
            SteamVR_Controller.Input((int) deviceIndex).GetPress(index) :
            false;
    }
    private static bool GetButtonDown(ETrackedControllerRole controllerRole, ulong index)
    {
        var deviceIndex = GetDeviceForRole(controllerRole);
        return isValid(deviceIndex) ?
            SteamVR_Controller.Input((int) deviceIndex).GetPressDown(index) :
            false;
    }
    private static bool GetButtonUp(ETrackedControllerRole controllerRole, ulong index)
    {
        var deviceIndex = GetDeviceForRole(controllerRole);
        return isValid(deviceIndex) ?
            SteamVR_Controller.Input((int) deviceIndex).GetPressUp(index) :
            false;
    }
    protected static bool GetButton(Binding binding)
    {
        return GetButton(binding.controllerRole, binding.index);
    }
    protected static bool GetButtonDown(Binding binding)
    {
        return GetButtonDown(binding.controllerRole, binding.index);
    }
    protected static bool GetButtonUp(Binding binding)
    {
        return GetButtonUp(binding.controllerRole, binding.index);
    }

    private void SetupInputs()
    {
        string filename = Application.dataPath + "/SteamVRInputs.xml";

        try {
            using(var fs = new FileStream(filename, FileMode.Open)) {
                XmlDocument doc = new XmlDocument();
                doc.Load(fs);
                XmlNode root = doc.FirstChild;
                {
                    XmlSerializer serializer = new XmlSerializer(typeof(Bindings));
                    XmlNode bindingsNode = root.SelectSingleNode("//Bindings");
                    if(bindingsNode != null) {
                        XPathNavigator nav = bindingsNode.CreateNavigator();
                        using(var reader = nav.ReadSubtree()) {
                            bindings = serializer.Deserialize(reader) as Bindings;
                        }
                    }
                }
                if(AdditionalSerializationType != null) {
                    XmlSerializer serializer = new XmlSerializer(AdditionalSerializationType);
                    XmlNode node = root.SelectSingleNode("//" + AdditionalSerializationType.Name);
                    if(node != null) {
                        XPathNavigator nav = node.CreateNavigator();
                        using(var reader = nav.ReadSubtree()) {
                            AdditionalSerializationData = serializer.Deserialize(reader);
                        }
                    }
                }
            }
        }
        catch(Exception) {

        }

        using(var writer = new StreamWriter(filename)) {
            //serializer.Serialize(writer, bindings);
            XmlDocument doc = new XmlDocument();
            XmlNode root = doc.AppendChild(doc.CreateElement("SteamVRInputs"));

            string commentString = "\n" +
                "Controller can be one of " +
             string.Join(", ", Enum.GetNames(typeof(ETrackedControllerRole))) + ".\n" +
             "Axis can be one of " +
             string.Join(", ", Enum.GetNames(typeof(AxisName))) + ".\n" +
             "Button can be one of " +
             string.Join(", ", Enum.GetNames(typeof(Button))) + ".\n";

            root.AppendChild(doc.CreateComment(commentString));

            serializeAppend(root, bindings);
            if(AdditionalSerializationData != null) {
                serializeAppend(root, AdditionalSerializationData);
            }
            doc.Save(writer);
        }
    }

    private void serializeAppend(XmlNode parentNode, object obj)
    {
        XmlSerializerNamespaces ns = new XmlSerializerNamespaces();
        ns.Add("", "");

        XPathNavigator nav = parentNode.CreateNavigator();
        using(var writer = nav.AppendChild()) {
            var serializer = new XmlSerializer(obj.GetType());
            writer.WriteWhitespace("");
            serializer.Serialize(writer, obj, ns);
            writer.Close();
        }
    }

    protected virtual object AdditionalSerializationData {
        get { return null; }
        set { }
    }

    protected virtual Type AdditionalSerializationType {
        get { return null; }
    }

    public void Start()
    {
        SetupInputs();
    }
}
