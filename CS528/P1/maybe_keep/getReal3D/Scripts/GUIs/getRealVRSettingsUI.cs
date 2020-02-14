using UnityEngine;
using System.Collections;
using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Linq;

/** getRealVRSettingsUI script
 *
 * Part of: getReal3D for Unity 2.1, (C) Mechdyne, 2013
 *
 **/

public class getRealVRSettingsUI : getReal3D.MonoBehaviourWithRpc {
    /// <summary>
    /// Constructor
    /// </summary>
    /// Make sure RPC are not automatically registered so that we can disable the
    /// behavior before registration.
    public getRealVRSettingsUI() : base(false)
    {

    }

    /// <summary>
    /// A helper class for handling a text field as float data.
    /// </summary>
    private class TextFieldAsFloatData {
        public TextFieldAsFloatData(string l, float fv, string tf = "##0.000")
        {
            label = l;
            floatValue = fv;
            textFormat = tf;
            minLimit = float.MinValue;
            maxLimit = float.MaxValue;

            if(validStyle == null) {
                GUISkin skin = (GUISkin) Instantiate(Resources.Load("gr2DUISkin"));
                validStyle = new GUIStyle(skin.GetStyle("TextField"));
                invalidStyle = new GUIStyle(skin.GetStyle("TextField"));

                invalidStyle.normal.textColor = Color.red;
                invalidStyle.active.textColor = Color.red;
                invalidStyle.hover.textColor = Color.red;
                invalidStyle.focused.textColor = Color.red;
            }

            style = validStyle;
        }

        public bool OnGUIUpdate()
        {
            bool retVal = false;
            GUILayout.BeginHorizontal();
            GUILayout.Label(label);

            textValue = (style == validStyle) ? floatValue.ToString(textFormat) : textValue;
            textValue = GUILayout.TextField(textValue, 6, style);

            double tempVal = floatValue;
            if(GUI.changed) {
                if(System.Double.TryParse(textValue, out tempVal) && tempVal >= minLimit && tempVal <= maxLimit) {
                    style = validStyle;
                    retVal = (float) tempVal != floatValue;
                    floatValue = (float) tempVal;
                }
                else {
                    style = invalidStyle;
                }
            }
            GUILayout.EndHorizontal();
            return retVal;
        }

        public string label { get; set; }
        public float floatValue { get; set; }
        public string textFormat { get; set; }

        public float minLimit { get; set; }
        public float maxLimit { get; set; }

        string textValue { get; set; }
        GUIStyle style { get; set; }

        static GUIStyle validStyle = null;
        static GUIStyle invalidStyle = null;
    }

    TextFieldAsFloatData m_worldScale = null;
    TextFieldAsFloatData m_eyeSeparation = null;
    TextFieldAsFloatData m_translationSpeed = null;
    TextFieldAsFloatData m_rotationSpeed = null;

    private float m_eventTime = 0.0f;
    private int m_eventFrame = 0;
    private bool m_drawGUI = true;
    private bool m_keepOpen = false;
    private bool m_showAvatars = false;

    private bool switchNavEnabled = false;

    private const string None = "None";
    private string m_currentScreenName = None;
    private List<string> m_screenNames = null;
    private float m_defaultDistanceBackup = 0;
    private Transform m_menuSpawnReferenceBackup;
    private Vector2 m_scrollPosition = Vector2.zero;

    public string m_avatarLayerPrefix = "Avatar_";

    /// <summary>
    /// Late initialization (give dependencies a chance to run their Awake).
    /// </summary>
    void Start()
    {
        registerRpc();

        m_worldScale = new TextFieldAsFloatData("World Scale", getReal3D.Scale.userScale, "##0.0000");
        m_worldScale.minLimit = 1e-3f;
        m_worldScale.maxLimit = 1e3f;

        m_eyeSeparation = new TextFieldAsFloatData("Eye Separation (unknown)", getReal3D.Scale.eyeSeparation);
        m_eyeSeparation.minLimit = -1e3f;
        m_eyeSeparation.maxLimit = 1e3f;

        m_translationSpeed = new TextFieldAsFloatData("Translation Speed", 1.0f);
        m_translationSpeed.minLimit = 1e-3f;
        m_translationSpeed.maxLimit = 1e3f;

        m_rotationSpeed = new TextFieldAsFloatData("Rotation Speed", 1.0f);
        m_rotationSpeed.minLimit = 1e-3f;
        m_rotationSpeed.maxLimit = 1e3f;

        switchNavEnabled = gameObject.GetComponent<getRealWalkthruController>() != null
                        && gameObject.GetComponent<getRealAimAndGoController>() != null;
    }

    void LateUpdate()
    {
        float tempVal = 1.0f;
        if(getReal3D.Input.NavOptions.GetValue<float>("TranslationSpeed", ref tempVal))
            m_translationSpeed.floatValue = tempVal;
        if(getReal3D.Input.NavOptions.GetValue<float>("RotationSpeed", ref tempVal))
            m_rotationSpeed.floatValue = tempVal;
        m_worldScale.floatValue = getReal3D.Scale.userScale;
        m_eyeSeparation.floatValue = getReal3D.Scale.eyeSeparation;
        m_eyeSeparation.label = "Eye Separation (" + getReal3D.Scale.eyeSeparationUnitString + ")";
    }

    [getReal3D.RPC]
    void ChangeWorldScale(float val)
    {
        getReal3D.Scale.userScale = val;
    }

    [getReal3D.RPC]
    void ChangeEyeSeparation(float val)
    {
        getReal3D.Scale.eyeSeparation = val;
    }

    [getReal3D.RPC]
    void ChangeNavigation(int val)
    {
        switch(val) {
        case 0:
            gameObject.GetComponent<getRealAimAndGoController>().enabled = false;
            gameObject.GetComponent<getRealWandDriveController>().enabled = false;
            gameObject.GetComponent<getRealWalkthruController>().enabled = true;
            gameObject.GetComponent<getRealWandLook>().ContinuousDrive = false;
            break;
        case 1:
            gameObject.GetComponent<getRealWalkthruController>().enabled = false;
            gameObject.GetComponent<getRealWandDriveController>().enabled = false;
            gameObject.GetComponent<getRealAimAndGoController>().enabled = true;
            gameObject.GetComponent<getRealWandLook>().ContinuousDrive = false;
            break;
        case 2:
            gameObject.GetComponent<getRealWalkthruController>().enabled = false;
            gameObject.GetComponent<getRealWandDriveController>().enabled = true;
            gameObject.GetComponent<getRealAimAndGoController>().enabled = false;
            gameObject.GetComponent<getRealWandLook>().ContinuousDrive = true;
            break;
        }
    }

    private int getSelectedNav()
    {
        if(gameObject.GetComponent<getRealWandLook>().ContinuousDrive) {
            return 2;
        }
        else if(gameObject.GetComponent<getRealWalkthruController>().enabled) {
            return 0;
        }
        else {
            return 1;
        }
    }

    [getReal3D.RPC]
    void ChangeTranslationSpeed(float val)
    {
        getReal3D.Input.NavOptions.SetValue<float>("TranslationSpeed", val);
    }

    [getReal3D.RPC]
    void ChangeRotationSpeed(float val)
    {
        getReal3D.Input.NavOptions.SetValue<float>("RotationSpeed", val);
    }

    [getReal3D.RPC]
    void ShowAvatars(bool visible)
    {
        m_showAvatars = visible;
        foreach(getRealUser user in getRealUser.users) {
            string avatarLayer = m_avatarLayerPrefix + (user.userId + 1).ToString();
            int avatarLayerId = LayerMask.NameToLayer(avatarLayer);
            if(avatarLayerId >= 0) {
                foreach(GameObject obj in GetObjectsInLayer(user.transform.root.gameObject, avatarLayerId)) {
                    obj.SetActive(visible);
                }
            }
        }
    }

    [getReal3D.RPC]
    void SetMenuScreen(string screenName)
    {
        if(screenName == m_currentScreenName)
        {
            return;
        }
        var genericShowMenu = GetComponent<GenericShowMenu>();
        if (screenName == None)
        {
            genericShowMenu.m_defaultDistance = m_defaultDistanceBackup;
            genericShowMenu.m_menuSpawnReference = m_menuSpawnReferenceBackup;
            genericShowMenu.setDefaultPosition();
        }
        else
        {
            if(m_currentScreenName == None)
            {
                m_defaultDistanceBackup = genericShowMenu.m_defaultDistance;
                m_menuSpawnReferenceBackup = genericShowMenu.m_menuSpawnReference;
            }
            var createScreens = GetComponent<CreateScreens>();
            genericShowMenu.m_defaultDistance = 0;
            genericShowMenu.m_menuSpawnReference = createScreens.screens.Where(go =>
                go.GetComponent<getRealScreenUpdater>().screenName == screenName).
                FirstOrDefault().transform;
            genericShowMenu.setDefaultPosition();
        }
        m_currentScreenName = screenName;
    }

    private static List<GameObject> GetObjectsInLayer(GameObject root, int layer)
    {
        var ret = new List<GameObject>();
        if(root.layer == layer) {
            ret.Add(root);
        }
        foreach(Transform t in root.transform) {
            ret.AddRange(GetObjectsInLayer(t.gameObject, layer));
        }
        return ret;
    }

    void OnGUI()
    {
        var createScreens = GetComponent<CreateScreens>();
        if (m_screenNames == null && createScreens != null && createScreens.isActiveAndEnabled)
        {
            m_screenNames = createScreens.screens.Select(go =>
                go.GetComponent<getRealScreenUpdater>().screenName).ToList();
        }
        if(Event.current.isKey || Event.current.isMouse) {
            m_eventTime = Time.time;
        }
        if(Event.current.type == EventType.Layout && Time.frameCount != m_eventFrame) {
            m_eventFrame = Time.frameCount;
            m_drawGUI = Time.time < m_eventTime + 5.0f || m_keepOpen;
        }
        if(!m_drawGUI) return;
        if(!getReal3D.GUI.BeginGUI()) return;

        GUILayout.BeginArea(new Rect(0, 0, 220, getReal3D.GUI.height));
        GUILayout.BeginVertical("VR Settings", GUI.skin.window);

        if(m_worldScale.OnGUIUpdate()) {
            CallRpc("ChangeWorldScale", m_worldScale.floatValue);
        }

        if(m_eyeSeparation.OnGUIUpdate()) {
            CallRpc("ChangeEyeSeparation", m_eyeSeparation.floatValue);
        }

        if(switchNavEnabled) {
            int selectedNav = getSelectedNav();
            selectedNav = GUILayout.SelectionGrid(selectedNav, new string[] { "Walk Through", "Aim-N-Go", "Wand Drive" }, 2);
            if(GUI.changed) {
                CallRpc("ChangeNavigation", selectedNav);
            }
        }

        if(m_translationSpeed.OnGUIUpdate()) {
            CallRpc("ChangeTranslationSpeed", m_translationSpeed.floatValue);
        }

        if(m_rotationSpeed.OnGUIUpdate()) {
            CallRpc("ChangeRotationSpeed", m_rotationSpeed.floatValue);
        }

        bool showAvatars = GUILayout.Toggle(m_showAvatars, "Avatars");
        if(showAvatars != m_showAvatars) {
            CallRpc("ShowAvatars", showAvatars);
        }

        if (m_screenNames != null)
        {
            GUILayout.Label("Snap menu to screen:");
            m_scrollPosition = GUILayout.BeginScrollView(m_scrollPosition);
            if (GUILayout.Toggle(m_currentScreenName == None, None) && m_currentScreenName != None)
            {
                CallRpc("SetMenuScreen", None);
            }
            foreach(var screenName in m_screenNames)
            {
                if (GUILayout.Toggle(m_currentScreenName == screenName, screenName) &&
                    m_currentScreenName != screenName)
                {
                    CallRpc("SetMenuScreen", screenName);
                }
            }
            GUILayout.EndScrollView();
        }

        GUILayout.BeginHorizontal();
        GUILayout.Label("FPS: " + (1.0f / Time.smoothDeltaTime).ToString("##0.00"));
        GUILayout.FlexibleSpace();
        GUILayout.Label("SPF: " + Time.smoothDeltaTime.ToString("##0.000"));
        GUILayout.EndHorizontal();

        GUILayout.BeginHorizontal();
        GUILayout.Label("Frame: " + Time.frameCount);
        if(getReal3D.Plugin.isDistrib()) {
            GUILayout.FlexibleSpace();
            GUILayout.Label("Cluster frame: " + getReal3D.Cluster.frameCount);
        }
        GUILayout.EndHorizontal();

        m_keepOpen = GUILayout.Toggle(m_keepOpen, "Keep open");

        GUILayout.EndVertical();

        GUILayout.FlexibleSpace();
        GUILayout.EndArea();
        getReal3D.GUI.EndGUI();
    }
}
