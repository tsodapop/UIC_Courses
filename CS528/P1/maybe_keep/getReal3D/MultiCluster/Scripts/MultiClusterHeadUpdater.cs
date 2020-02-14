using UnityEngine;

namespace getReal3D.MultiCluster {

    /// <summary>
    /// Updates the head position and rotation via the information retrieved from the
    /// attached PlayerInputs interface.
    /// </summary>
    [AddComponentMenu("getReal3D/Multi Cluster/Head Updater")]
    [RequireComponent(typeof(PlayerInputs))]
    public class MultiClusterHeadUpdater : NetworkBehaviour {
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
                getReal3D.Sensor headSensor = m_playerInputs.Head;
                target.localPosition = headSensor.position;
                target.localRotation = headSensor.rotation;
            }
        }
    }
}
