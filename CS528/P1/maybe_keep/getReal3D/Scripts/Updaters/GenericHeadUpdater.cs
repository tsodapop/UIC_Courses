using UnityEngine;

namespace getReal3D
{
    /// <summary>
    /// Updates the head position and rotation via the information retrieved from the
    /// attached PlayerInputs interface.
    /// </summary>
    [AddComponentMenu("getReal3D/Generic Head Updater")]
    [RequireComponent(typeof(PlayerInputs))]
    public class GenericHeadUpdater : MonoBehaviour
    {
        private PlayerInputs m_playerInputs;

        /// <summary>
        /// The target object to update.
        /// </summary>
        [Tooltip("Target object to update.")]
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
            getReal3D.Sensor headSensor = m_playerInputs.Head;
            target.localPosition = headSensor.position;
            target.localRotation = headSensor.rotation;
        }
    }
}
