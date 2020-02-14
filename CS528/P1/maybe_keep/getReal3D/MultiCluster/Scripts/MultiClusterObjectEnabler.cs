using UnityEngine;

namespace getReal3D.MultiCluster {

    [AddComponentMenu("getReal3D/Multi Cluster/Object Enabler")]
    public class MultiClusterObjectEnabler : NetworkBehaviour {

        [Tooltip("List of objects to enable when the player is local.")]
        public GameObject[] enableWhenLocalPlayer = new GameObject[0];

        [Tooltip("List of objects to enable when the player is remote.")]
        public GameObject[] enableWhenRemotePlayer = new GameObject[0];

        void Start()
        {
            if(isLocalPlayer) {
                foreach(var target in enableWhenLocalPlayer) {
                    target.SetActive(true);
                }
            }
            else {
                foreach(var target in enableWhenRemotePlayer) {
                    target.SetActive(true);
                }
            }
        }
    }
}
