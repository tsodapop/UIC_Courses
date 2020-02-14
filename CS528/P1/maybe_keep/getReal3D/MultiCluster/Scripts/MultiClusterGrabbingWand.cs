using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using getReal3D.MultiCluster;
using System;

/// <summary>
/// This script handles grabbing objects with a wand.
/// </summary>
/// <remarks>
/// In order to grab an object, it must have a MultiClusterGrabbableObject and a RigidBody.
/// </remarks>
[AddComponentMenu("getReal3D/Multi Cluster/Grabbing Wand")]
[RequireComponent(typeof(PlayerInputs))]
public class MultiClusterGrabbingWand : NetworkBehaviour {

    [Tooltip("The wand transform.")]
    public Transform Wand;

    [Tooltip("The parent used to hold the object.")]
    public Transform ReparentTransform;

    [Tooltip("The raycast layer used for object to grab.")]
    public LayerMask grabLayerMask = -1;

    private MultiClusterGrabbableObject m_grabObject = null;
    private NetworkIdentity m_scriptIdentity;
    private PlayerInputs m_playerInputs;

    void Awake()
    {
        m_scriptIdentity = GetComponent<NetworkIdentity>();
        m_playerInputs = GetComponent<PlayerInputs>();
    }

    void Update()
    {
        if(!isLocalPlayer || !Wand || !Wand.gameObject.activeInHierarchy) {
            return;
        }

        Debug.DrawRay(Wand.parent.position, Wand.parent.forward * 2f, Color.yellow);

        // If the wand button is released, drop the object
        if(m_playerInputs.WandButtonUp && m_grabObject) {
            CmdDropObject();
        }
        // If the wand button was pressed and we're not already grabbing something,
        // test for objects to grab
        else if(m_grabObject == null && m_playerInputs.WandButtonDown) {
            // Raycast test for objects to grab
            RaycastHit hit = new RaycastHit();
            bool hitTest = Physics.Raycast(Wand.parent.position, Wand.parent.forward,
                out hit, 2.0f, grabLayerMask);
            if(hitTest) {
                Rigidbody rb = hit.rigidbody;
                Transform tf = hit.transform.parent;
                while(rb == null && tf && tf.parent != null) {
                    tf = tf.parent;
                    rb = tf.GetComponent<Rigidbody>();
                }

                // If the object doesn't have a rigidbody, don't do anything
                if(!rb)
                    return;

                var grabObject = rb.gameObject.GetComponent<MultiClusterGrabbableObject>();
                if(grabObject) {
                    CmdGrabObject(grabObject.GetComponent<NetworkIdentity>());
                }
            }
        }
    }

    private void DropObjectImpl()
    {
        Debug.Assert(isServer, "Should be a server.");
        if(m_grabObject == null) {
            return;
        }
        var identity = m_grabObject.GetComponent<NetworkIdentity>();
        Debug.Assert(identity.clientAuthorityOwner != null, "Client authority should be null");

        var grabbable = m_grabObject.GetComponent<MultiClusterGrabbableObject>();
        Debug.Assert(grabbable != null, "Grabbable not found.");

        identity.RemoveClientAuthority(identity.clientAuthorityOwner);
        RpcRestoreOriginalParent();
    }

    [Command]
    private void CmdDropObject()
    {
        DropObjectImpl();
    }

    private void RestoreOriginalParentImpl()
    {
        Debug.Assert(isClient, "Should be a client.");
        m_grabObject.DoRelease();
        m_grabObject = null;
    }

    [ClientRpc]
    private void RpcRestoreOriginalParent()
    {
        RestoreOriginalParentImpl();
    }

    private void GrabObjectImpl(NetworkIdentity target)
    {
        Debug.Assert(isServer, "Should be a server.");

        if(target.clientAuthorityOwner != null) {
            Debug.Log("Somebody is already handling that object.");
            return;
        }

        target.AssignClientAuthority(m_scriptIdentity.clientAuthorityOwner);
        RpcDoReparent(target);
    }

    [Command]
    private void CmdGrabObject(NetworkIdentity target)
    {
        GrabObjectImpl(target);
    }

    private void DoReparentImpl(NetworkIdentity target)
    {
        Debug.Assert(isClient, "Should be a client.");
        Debug.Assert(target != null, "Target is null!");
        m_grabObject = target.GetComponent<MultiClusterGrabbableObject>();
        Debug.Assert(m_grabObject != null, "No grabbable found on the target!");
        m_grabObject.DoGrab(this);
    }

    [ClientRpc]
    private void RpcDoReparent(NetworkIdentity target)
    {
        DoReparentImpl(target);
    }


}
