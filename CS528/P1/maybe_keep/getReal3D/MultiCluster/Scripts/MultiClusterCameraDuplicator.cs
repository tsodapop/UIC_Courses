using getReal3D.MultiCluster;
using UnityEngine;

namespace getReal3D.MultiCluster {

    /// <summary>
    /// Script used to handle local player getReal3D cameras duplication.
    /// </summary>
    [AddComponentMenu("getReal3D/Multi Cluster/Camera Duplicator")]
    [DisallowMultipleComponent]
    public class MultiClusterCameraDuplicator : getRealUserScript, MultiClusterSetupScript
    {
        public MultiClusterCameraUpdater target;
        public void MultiClusterSetup(bool localPlayer)
        {
            if(target == null) {
                return;
            }
            if(localPlayer) {
                CameraUpdaterHelper.CreateCamerasForUserIfNeeded(target.GetComponent<Camera>(),
                    userId());
            }
            else {
                target.GetComponent<Camera>().enabled = false;
                var audioListener = target.GetComponent<AudioListener>();
                if(audioListener) {
                    audioListener.enabled = false;
                }
            }
        }

    }

}
