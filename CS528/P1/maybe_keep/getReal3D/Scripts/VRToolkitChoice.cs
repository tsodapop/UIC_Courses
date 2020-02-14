using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using UnityEngine.VR;
#if (UNITY_2017_2_OR_NEWER)
using VRSettings = UnityEngine.XR.XRSettings;
#else
using VRSettings = UnityEngine.VR.VRSettings;
#endif

/// <summary>
/// This script does the setup for either SteamVR or getReal3D.
/// The startup can be forced. When not forced (DeviceChoice) the loaded VR device (Unity
/// command line arguments) will be used. If no VR device is loaded, then a 2D UI is displayed to
/// </summary>
/// <remarks>
/// Once the toolkit is chosen, the PlayerInputsProxy in this Game Object is set using any
/// PlayerInputs in the activated child.
/// </remarks>
[RequireComponent(typeof(PlayerInputsProxy))]
public class VRToolkitChoice : MonoBehaviour
{
    [Tooltip("The child to activate in order to start with getReal3D.")]
    public GameObject m_getReal3D;

    [Tooltip("The child to activate in order to start with SteamVR.")]
    public GameObject m_steamVR;

    [Tooltip("The setup type.")]
    public SetupType m_setupType = SetupType.ChooseAtRuntime;

    [Tooltip("If set to true, then the warning is not displayed.")]
    public bool m_hideWarningDialog = false;

    private bool m_done = false;
    private string m_error;

    public enum SetupType
    {
        ChooseAtRuntime,
        ForceGetReal3D,
        ForceSteamVR,
    }

    void Start()
    {
        if(m_setupType == SetupType.ForceGetReal3D || isWithinGetReal3D) {
            StartCoroutine(SetupGetReal3D());
        }
        else if(m_setupType == SetupType.ForceSteamVR) {
            StartCoroutine(SetupSteamVR());
        }
        else if(m_setupType == SetupType.ChooseAtRuntime) {
            if(!string.IsNullOrEmpty(VRSettings.loadedDeviceName)) {
                StartCoroutine(SetupByName(VRSettings.loadedDeviceName));
            }
            else if(GetSupportedDevices().Count() == 1) {
                StartCoroutine(SetupByName(GetSupportedDevices().First()));
            }
        }
    }

    IEnumerator SetupByName(string device)
    {
        if(device == "OpenVR") {
            yield return StartCoroutine(SetupSteamVR());
        }
        else if(device == "stereo") {
            yield return StartCoroutine(SetupGetReal3D());
        }
        else if(device == "getReal3D") {
            yield return StartCoroutine(SetupGetReal3D());
        }
        else {
            m_error = "Unsupported VR device: '" + device + "'";
        }
        yield break;
    }

    IEnumerator SetupGetReal3D()
    {
        Setup(m_getReal3D);
        m_done = true;
        var createScreens = GetComponent<CreateScreens>();
        if (createScreens)
        {
            createScreens.enabled = true;
        }
        yield break;
    }

    IEnumerator SetupSteamVR()
    {
        if(VRSettings.loadedDeviceName != "OpenVR") {
            VRSettings.LoadDeviceByName("OpenVR");
            yield return null;
            if(VRSettings.loadedDeviceName != "OpenVR") {
                m_error = "Failed to load OpenVR.";
                yield break;
            }
            VRSettings.enabled = true;
        }
        Setup(m_steamVR);
        m_done = true;
        yield break;
    }

    public void OnGUI()
    {
        if(m_done) {
            return;
        }

        int w = 300;
        int h = 200 + (m_hideWarningDialog?0:100);
        int x = Screen.width / 2 - w/2;
        int y = Screen.height / 2 - h/2;

        Rect rect = new Rect(x, y, w, h);
        GUILayout.BeginArea(rect);

        GUILayout.BeginVertical("VR Device", GUI.skin.window);

        foreach(var device in GetSupportedDevices()) {
            if(GUILayout.Button("Start with " + device)) {
                StartCoroutine(SetupByName(device));
            }
        }

        if(!string.IsNullOrEmpty(m_error)) {
            GUILayout.Label(m_error);
        }

        if(!m_hideWarningDialog) {
            GUILayout.Label("If this project is not going to be used with a Vive, you can " +
                "bypass this dialog by changing the VRToolKit Setup Type to Force Get Real 3D.");
        }

        GUILayout.EndVertical();
        GUILayout.EndArea();
    }

    IEnumerable<string> GetSupportedDevices()
    {
        return VRSettings.supportedDevices.
            Where(d => d != "None").
            Where(d => d != "stereo").
            Concat(new string[] { "getReal3D" });
    }

    void Setup(GameObject target)
    {
        target.SetActive(true);
        var playerInputsProxy = GetComponent<PlayerInputsProxy>();
        playerInputsProxy.target = target.GetComponent<PlayerInputs>();
        if(playerInputsProxy.target == null) {
            Debug.LogError("Failed to find PlayerInputs component in target.");
        }
        var wandEventModule = GameObject.FindObjectOfType<GenericWandEventModule>();
        if(wandEventModule) {
            wandEventModule.playerInputs = playerInputsProxy;
        }
        else {
            Debug.LogError("Failed to find GenericWandEventModule component in scene.");
        }
    }

    bool isWithinGetReal3D {
        get {
            return System.Environment.GetEnvironmentVariable("GETREAL_CONFIG") != null;
        }
    }
}
