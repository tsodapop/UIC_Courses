using UnityEngine;

/// <summary>
/// Script added to objects while they are being grabbed by the player wand.
/// </summary>
[RequireComponent(typeof(VelocityTracking))]
public class GrabbedObject : MonoBehaviour {

    private Transform m_originalParent = null;
    private Transform m_grabParent = null;
    private bool m_wasKinematic = false;
    private bool m_allowGrabSteal = false;

    private VelocityTracking m_velocityTracking;

    public void Awake()
    {
        m_velocityTracking = GetComponent<VelocityTracking>();
    }

    /// <summary>
    /// Signal that this object is to be grabbed by a new parent (the grabbing user's wand)
    /// </summary>
    /// <param name="newParent">The new parent. Usually the grabbing user's wand.</param>
    /// <param name="allowGrabSteal">Whether or not to allow other user's to grab this object and
    /// take if from the original grabber.</param>
    public void grabObject(Transform newParent, bool allowGrabSteal)
    {
        // Don't allow the grab if the object is already grabbed by someone else and grab steal is
        // disallowed
        if (m_grabParent != null && !m_allowGrabSteal)
            return;

        // Set initial values if this is the first user to grab the object
        if (m_grabParent == null)
        {
            m_originalParent = transform.parent;
            m_allowGrabSteal = allowGrabSteal;
        }

        // Set the starting position, orientation, and velocity
        m_velocityTracking.ResetVelocity();

        // Reparent the grabbed object
        m_grabParent = newParent;
        transform.parent = newParent;

        Rigidbody rigidbody = GetComponent<Rigidbody>();
        if (rigidbody)
        {
            // Set kinematic to true so physics don't apply to it while grabbed
            m_wasKinematic = rigidbody.isKinematic;
            rigidbody.isKinematic = true;
        }
    }

    /// <summary>
    /// Signal that this object is to be dropped
    /// </summary>
    /// <param name="parent">The dropping parent. Used to determine if the dropping user is the
    /// current parent of the object.</param>
    public void dropObject(Transform parent)
    {
        // Don't do anything if a different user has grabbed this object
        if (m_grabParent != parent)
            return;

        // Restore the original parent
        transform.parent = m_originalParent;

        // Re-enable physics on the object and initialize its velocity
        Rigidbody rigidbody = GetComponent<Rigidbody>();
        if (rigidbody)
        {
            rigidbody.isKinematic = m_wasKinematic;
            if (!m_wasKinematic)
            {
                rigidbody.velocity = m_velocityTracking.velocitySmoothed;
                rigidbody.angularVelocity = -m_velocityTracking.angularVelocitySmoothed;
            }
        }

        // Remove this behavior(script) from the object
        Destroy(this);
    }

}
