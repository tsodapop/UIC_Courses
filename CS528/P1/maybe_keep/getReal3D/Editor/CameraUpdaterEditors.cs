using UnityEditor;
using getReal3D;
using getReal3D.MultiCluster;

/// <summary>
/// Provides CameraUpdaterEditor for getRealCameraUpdater behaviour.
/// </summary>
[CustomEditor(typeof(getRealCameraUpdater))]
public class getRealCameraUpdaterEditor : CameraUpdaterEditor { }

/// <summary>
/// Provides CameraUpdaterEditor for MultiClusterCameraUpdater behaviour.
/// </summary>
[CustomEditor(typeof(MultiClusterCameraUpdater))]
public class MultiClusterCameraUpdaterEditor : CameraUpdaterEditor { }
