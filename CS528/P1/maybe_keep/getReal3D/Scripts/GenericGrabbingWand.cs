using UnityEngine;

using getReal3D;

/// <summary>
/// This script handles grabbing objects with a wand.
/// </summary>
[RequireComponent(typeof(PlayerInputs))]
public class GenericGrabbingWand
 : MonoBehaviour
{
    private GameObject grabObject = null;
    private PlayerInputs m_playerInputs;

    [Tooltip("The raycast layer used for object to grab.")]
    public LayerMask grabLayerMask = -1;

    [Tooltip("If stealing an object is allowed.")]
    public bool allowGrabSteal = false;

    [Tooltip("The wand transform.")]
    public Transform Wand;

    [Tooltip("The parent used to hold the object.")]
    public Transform ReparentTransform;

    void Awake()
    {
        m_playerInputs = GetComponent<PlayerInputs>();
    }

    void OnDisable()
    {
        DropObject();
    }

    void DropObject()
    {
        if(grabObject != null) {
            // If the object has the GrabbedObject behavior, tell it to drop
            GrabbedObject grabbedObject = grabObject.GetComponent<GrabbedObject>();
            if(grabbedObject)
                grabbedObject.dropObject(ReparentTransform);

            grabObject = null;
        }
    }

    void Update()
    {
        if(!Wand || !Wand.gameObject.activeInHierarchy) {
            return;
        }

        Debug.DrawRay(Wand.parent.position, Wand.parent.forward * 2f, Color.yellow);

        // If the wand button is released, drop the object
        if(m_playerInputs.WandButtonUp) {
            DropObject();
        }
        // If the wand button was pressed and we're not already grabbing something, test for objects to grab
        else if(grabObject == null && m_playerInputs.WandButtonDown) {
            // Raycast test for objects to grab
            RaycastHit hit = new RaycastHit();
            bool hitTest = Physics.Raycast(Wand.parent.position, Wand.parent.forward, out hit, 2.0f, grabLayerMask);
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

                grabObject = rb.gameObject;

                // Add the GrabbedObject behavior(script) to the object if it hasn't already been grabbed by someone else
                GrabbedObject grabbedObject = grabObject.GetComponent<GrabbedObject>();
                if(!grabbedObject) {
                    grabbedObject = grabObject.AddComponent<GrabbedObject>();
                }

                // Grab the object
                grabbedObject.grabObject(ReparentTransform, allowGrabSteal);
            }
        }
    }
}
