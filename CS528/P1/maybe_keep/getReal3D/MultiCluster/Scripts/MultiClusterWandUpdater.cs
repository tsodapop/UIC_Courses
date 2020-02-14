using UnityEngine;

namespace getReal3D.MultiCluster {

    /// <summary>
    /// Updates the wand position and rotation via the information retrieved from the
    /// attached PlayerInputs interface.
    /// </summary>
    [AddComponentMenu("getReal3D/Multi Cluster/Wand Updater")]
    [RequireComponent(typeof(PlayerInputs))]
    public class MultiClusterWandUpdater : NetworkBehaviour {
        private PlayerInputs m_playerInputs;

        /// <summary>
        /// The target object to update.
        /// </summary>
        [Tooltip("Target to update.")]
        public Transform target;

        void Awake()
        {
            if(!target) {
                target = transform;
            }
            m_playerInputs = GetComponent<PlayerInputs>();
        }

        void Update()
        {
            if(isLocalPlayer) {
                getReal3D.Sensor headSensor = m_playerInputs.Wand;
                target.localPosition = headSensor.position;
                target.localRotation = headSensor.rotation;
            }
        }
    }
}
