using UnityEngine;
using UnityEditor;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine.EventSystems;
using System;

public class getReal3D_Menu {

    [UnityEditor.Callbacks.PostProcessScene(101)]
    [MenuItem("getReal3D/Advanced/getReal3D Script Execution Order", false, 105)]
    static public void FixExecutionOrder()
    {
        getReal3D.Editor.Utils.FixScriptExecutionOrder();
    }

    [UnityEditor.Callbacks.PostProcessScene(102)]
    static public void CheckForMultisampling()
    {
        if(Application.isPlaying) {
            return;
        }

        System.IO.StringWriter errors = new System.IO.StringWriter();
        errors.WriteLine("This build might fail when running with getReal3D for Unity:\n");

        bool hasWarning = false;
        int currentLevel = UnityEngine.QualitySettings.GetQualityLevel();
        int levelCount = UnityEngine.QualitySettings.names.Length;
        for(int i=0; i<levelCount; ++i) {
            UnityEngine.QualitySettings.SetQualityLevel(i);
            if(UnityEngine.QualitySettings.vSyncCount != 0) {
                string err = "VSync is activated for quality settings " +
                    UnityEngine.QualitySettings.names[i] + ".";
                errors.WriteLine(err);
                hasWarning = true;
            }
        }

        UnityEngine.QualitySettings.SetQualityLevel(currentLevel);

        if(hasWarning) {
            ShowBuildError(errors.ToString());
        }
    }

    static private bool CameraHasHdr(Camera c)
    {
#if UNITY_5_6_OR_NEWER
        return c && c.allowHDR;
#else
        return c && c.hdr;
#endif
    }

    static private void ShowBuildError(string message)
    {
        if(UnityEditorInternal.InternalEditorUtility.inBatchMode) {
            Debug.LogError(message);
        }
        else {
            EditorUtility.DisplayDialog("getReal3D", message, "Ok");
        }
    }

    [UnityEditor.Callbacks.PostProcessScene(103)]
    static public void CheckDuplicatedNetworkIdentities()
    {
        if(Application.isPlaying) {
            return;
        }
        var duplicates = getReal3D.MultiCluster.NetworkIdentity.GetDuplicated();
        if(duplicates.Count != 0) {
            ShowBuildError("Duplicated NetworkIdentity found. " +
                "Please check the scene in the getReal3D menu.");
        }
    }

    [UnityEditor.Callbacks.PostProcessScene(104)]
    static public void CheckVRStuff()
    {
        if(Application.isPlaying) {
            return;
        }
        if(!SceneIsUsingSteamVR()) {
            return;
        }
        if(!SceneIsUsingGetReal3D()) {
            return;
        }
        var devices = UnityEditorInternal.VR.VREditor.GetVREnabledDevicesOnTargetGroup
            (BuildTargetGroup.Standalone).Select(name => name.ToLower());

        bool VREnabled = UnityEditorInternal.VR.VREditor.GetVREnabledOnTargetGroup
            (BuildTargetGroup.Standalone);

        var fixMessage = "Use the getReal3D / Advanced / VR Priority menu to fix the issue.";

        if(!VREnabled) {
            var message = "getReal3D HMD enabled games should be built with VR enabled. " +
                fixMessage;
            ShowBuildError(message);
        }
        else if(devices.Count() == 0 || devices.First() != "none") {
            var message = "getReal3D HMD enabled games should have 'None' in as the top" +
                " priority VR device. " + fixMessage;
            ShowBuildError(message);
        }
        else if(!devices.Contains("openvr")) {
            var message = "getReal3D HMD enabled games is missing OpenVR device. " + fixMessage;
            ShowBuildError(message);
        }
    }

    [UnityEditor.Callbacks.PostProcessScene(105)]
    static public void CheckScriptPriority()
    {
        if (Application.isPlaying) {
            return;
        }
        if (getReal3D.SceneChecker.GetScriptPriorityErrors().Count() != 0) {
            var message = "Script priority error(s) detected. Please use getReal3D scene checker.";
            ShowBuildError(message);
        }
    }

    private static bool ObjectUsesSteamVR(GameObject go)
    {
        return
            go.GetComponentInChildren<SteamVR_Camera>(true) != null ||
            go.GetComponentInChildren<SteamVR_CameraFlip>(true) != null ||
            go.GetComponentInChildren<SteamVR_CameraMask>(true) != null ||
            go.GetComponentInChildren<SteamVR_ControllerManager>(true) != null ||
            go.GetComponentInChildren<SteamVR_Ears>(true) != null ||
            go.GetComponentInChildren<SteamVR_ExternalCamera>(true) != null ||
            go.GetComponentInChildren<SteamVR_Fade>(true) != null ||
            go.GetComponentInChildren<SteamVR_Frustum>(true) != null ||
            go.GetComponentInChildren<SteamVR_GameView>(true) != null ||
            go.GetComponentInChildren<SteamVR_IK>(true) != null ||
            go.GetComponentInChildren<SteamVR_LoadLevel>(true) != null ||
            go.GetComponentInChildren<SteamVR_Menu>(true) != null ||
            go.GetComponentInChildren<SteamVR_Overlay>(true) != null ||
            go.GetComponentInChildren<SteamVR_PlayArea>(true) != null ||
            go.GetComponentInChildren<SteamVR_Render>(true) != null ||
            go.GetComponentInChildren<SteamVR_RenderModel>(true) != null ||
            go.GetComponentInChildren<SteamVR_Skybox>(true) != null ||
            go.GetComponentInChildren<SteamVR_SphericalProjection>(true) != null ||
            go.GetComponentInChildren<SteamVR_Stats>(true) != null ||
            go.GetComponentInChildren<SteamVR_TestController>(true) != null ||
            go.GetComponentInChildren<SteamVR_TrackedObject>(true) != null ||
            go.GetComponentInChildren<SteamVR_UpdatePoses>(true) != null
            ;
    }

    private static bool ObjectUsesGetReal3D(GameObject go)
    {
        return
            go.GetComponentInChildren<getRealCameraUpdater>(true) != null ||
            go.GetComponentInChildren<getRealHeadUpdater>(true) != null ||
            go.GetComponentInChildren<getRealSensorUpdater>(true) != null ||
            go.GetComponentInChildren<getRealWandUpdater>(true) != null ||
            go.GetComponentInChildren<getReal3D.MultiCluster.MultiClusterCameraUpdater>(true) != null ||
            go.GetComponentInChildren<getReal3D.MultiCluster.MultiClusterCameraDuplicator>(true) != null ||
            go.GetComponentInChildren<getReal3D.MultiCluster.MultiClusterHeadUpdater>(true) != null ||
            go.GetComponentInChildren<getReal3D.MultiCluster.MultiClusterWandUpdater>(true) != null
            ;
    }

    private static bool SceneCheckFunctor(Func<GameObject, bool> testFunctor)
    {
        if(Roots.Any(go => testFunctor(go))) {
            return true;
        }

        var networkManager = UnityEngine.Object.FindObjectOfType
            <getReal3D.MultiCluster.NetworkManager>();
        if(!networkManager) {
            return false;
        }
        foreach(var identity in networkManager.m_spawnPrefabs) {
            if(testFunctor(identity.gameObject)) {
                return true;
            }
        }
        return false;
    }

    private static bool SceneIsUsingSteamVR()
    {
        return SceneCheckFunctor(ObjectUsesSteamVR);
    }

    private static bool SceneIsUsingGetReal3D()
    {
        return SceneCheckFunctor(ObjectUsesGetReal3D);
    }

    private static GameObject[] Roots {
        get { return UnityEngine.SceneManagement.SceneManager.GetActiveScene().GetRootGameObjects(); }
    }

    static T[] FindObjectsOfTypeInScene<T>() where T : Behaviour
    {
        List<T> res = new List<T>();
        T[] allComponents = Resources.FindObjectsOfTypeAll<T>();
        foreach(var monoBehaviour in allComponents) {
            if(monoBehaviour.hideFlags != HideFlags.None) {
                continue;
            }
            res.Add(monoBehaviour);
        }
        return res.ToArray();
    }

    public static void BuildPlayerImpl(string[] levels, string output, bool arch64 = false)
    {
        BuildTarget currentTarget = EditorUserBuildSettings.activeBuildTarget;
        SwitchActiveBuildStandaloneTarget(BuildTarget.StandaloneWindows);

        BuildTarget buildTarget = arch64 ? BuildTarget.StandaloneWindows64 :
            BuildTarget.StandaloneWindows;
        AddGraphicApi(buildTarget, UnityEngine.Rendering.GraphicsDeviceType.Direct3D11);
#if !UNITY_2017_2_OR_NEWER
        AddGraphicApi(buildTarget, UnityEngine.Rendering.GraphicsDeviceType.Direct3D9);
#endif
        UnityEditor.BuildOptions options = BuildOptions.None;
        BuildPipeline.BuildPlayer(levels, output, buildTarget, options);
        SwitchActiveBuildStandaloneTarget(currentTarget);
    }

    public static void BuildPlayerImpl(string output, bool arch64 = false)
    {
        BuildPlayerImpl(getEnabledScenes(), output, arch64);
    }

    public static string[] getEnabledScenes()
    {
        List<string> temp = new List<string>();
        foreach(UnityEditor.EditorBuildSettingsScene S in UnityEditor.EditorBuildSettings.scenes) {
            if(S.enabled) {
                temp.Add(S.path);
            }
        }
        return temp.ToArray();
    }

    private static void AddGraphicApi(BuildTarget target,
        UnityEngine.Rendering.GraphicsDeviceType type)
    {
        List<UnityEngine.Rendering.GraphicsDeviceType> deviceTypes = PlayerSettings.GetGraphicsAPIs
            (BuildTarget.StandaloneWindows).ToList<UnityEngine.Rendering.GraphicsDeviceType>();
        if(!deviceTypes.Contains(type)) {
            deviceTypes.Add(type);
            PlayerSettings.SetGraphicsAPIs(target, deviceTypes.ToArray());
        }
    }

    [MenuItem("getReal3D/Advanced/VR Priority/Print list", false, 200)]
    static public void PrintList()
    {
        var devices = UnityEditorInternal.VR.VREditor.GetVREnabledDevicesOnTargetGroup(BuildTargetGroup.Standalone);
        Debug.Log("VR device list is: [" + string.Join(", ", devices.ToArray()) + "].");
    }

    [MenuItem("getReal3D/Advanced/VR Priority/Put None on top", false, 120)]
    static public void PutNoneOnTop()
    {
        PutOnTop("None");
    }

    [MenuItem("getReal3D/Advanced/VR Priority/Put OpenVR on top", false, 121)]
    static public void PutOpenVROnTop()
    {
        PutOnTop("OpenVR");
    }

    [MenuItem("getReal3D/Advanced/VR Priority/Setup MultiCluster HMD build", false, 10)]
    static public void SetupMultiClusterHMD()
    {
        PutOnTop("OpenVR");
        PutOnTop("None");
    }

    private static void PutOnTop(string name)
    {
        if(!UnityEditorInternal.VR.VREditor.GetVREnabledOnTargetGroup(BuildTargetGroup.Standalone)) {
            UnityEditorInternal.VR.VREditor.SetVREnabledOnTargetGroup(BuildTargetGroup.Standalone, true);
        }
        List<string> devices = UnityEditorInternal.VR.VREditor.GetVREnabledDevicesOnTargetGroup(BuildTargetGroup.Standalone)
            .Where(x => x.ToLower() != name.ToLower()).ToList();
        devices.Insert(0, name);
        UnityEditorInternal.VR.VREditor.SetVREnabledDevicesOnTargetGroup(BuildTargetGroup.Standalone, devices.ToArray());
        PrintList();
    }

    public static void SwitchActiveBuildStandaloneTarget(BuildTarget target)
    {
#if UNITY_5_6_OR_NEWER
        EditorUserBuildSettings.SwitchActiveBuildTarget(BuildTargetGroup.Standalone, target);
#else
        EditorUserBuildSettings.SwitchActiveBuildTarget(target);
#endif
    }
}
