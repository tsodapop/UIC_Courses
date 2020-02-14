using UnityEngine;

namespace getReal3D.MultiCluster {

    [AddComponentMenu("getReal3D/Multi Cluster/Object Disabler")]
    public class MultiClusterObjectDisabler : NetworkBehaviour {

        [Tooltip("List of objects to disable when the player is local.")]
        public GameObject[] disableWhenLocalPlayer = new GameObject[0];

        [Tooltip("List of objects to disable when the player is remote.")]
        public GameObject[] disableWhenRemotePlayer = new GameObject[0];

        void Start()
        {
            if(isLocalPlayer) {
                foreach(var target in disableWhenLocalPlayer) {
                    target.SetActive(false);
                }
            }
            else {
                foreach(var target in disableWhenRemotePlayer) {
                    target.SetActive(false);
                }
            }
        }
    }
}
