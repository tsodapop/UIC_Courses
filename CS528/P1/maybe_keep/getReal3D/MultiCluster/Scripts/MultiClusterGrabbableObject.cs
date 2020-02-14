using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using getReal3D.MultiCluster;
using System;

/// <summary>
/// Script that must be present on objects that can be grabbed.
/// </summary>
[AddComponentMenu("getReal3D/Multi Cluster/Grabbable Object")]
[RequireComponent(typeof(VelocityTracking))]
public class MultiClusterGrabbableObject : NetworkBehaviour {
    private VelocityTracking m_velocityTracking;
    private Transform m_originalParent = null;
    private bool m_wasKinematic = false;

    public void Awake()
    {
        m_velocityTracking = GetComponent<VelocityTracking>();
        m_originalParent = transform.parent;
    }

    public void DoRelease()
    {
        Debug.Assert(isClient);
        transform.parent = m_originalParent;
        // Re-enable physics on the object and initialize its velocity
        Rigidbody rigidbody = GetComponent<Rigidbody>();
        if(rigidbody) {
            rigidbody.isKinematic = m_wasKinematic;
            if(!m_wasKinematic) {
                rigidbody.velocity = m_velocityTracking.velocitySmoothed;
                rigidbody.angularVelocity = -m_velocityTracking.angularVelocitySmoothed;
            }
        }

        NetworkTransform networkTransform = GetComponent<NetworkTransform>();
        if(networkTransform) {
            networkTransform.enabled = true;
        }
    }

    public void DoGrab(MultiClusterGrabbingWand grabbingScript)
    {
        Debug.Assert(grabbingScript != null);
        Debug.Assert(grabbingScript.ReparentTransform != null, "Missing ReparentTransform.");
        transform.parent = grabbingScript.ReparentTransform;
        m_velocityTracking.ResetVelocity();
        Rigidbody rigidbody = GetComponent<Rigidbody>();
        if(rigidbody) {
            m_wasKinematic = rigidbody.isKinematic;
            rigidbody.isKinematic = true;
        }

        NetworkTransform networkTransform = GetComponent<NetworkTransform>();
        if(networkTransform) {
            networkTransform.enabled = false;
        }
    }

}
