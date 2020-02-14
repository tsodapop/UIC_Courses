using UnityEngine;
using System.Collections;
using getReal3D;

// This class is deprecated. GenericHeadUpdater should be used instead.
public class getRealHeadUpdater
    : DeprecatedGetRealUserScript
{
    private Transform m_transform;

    void Awake()
    {
        m_transform = transform;
    }

    void Update()
    {
        getReal3D.Sensor headSensor = getHead();
        m_transform.localPosition = headSensor.position;
        m_transform.localRotation = headSensor.rotation;
    }

    void OnDrawGizmos()
    {
        Gizmos.matrix = transform.localToWorldMatrix * Matrix4x4.Scale(new Vector3(0.1f, 0.2f, 0.1f));
        Gizmos.color = Color.yellow;
        Gizmos.DrawWireSphere(new Vector3(0,0,0), 1);
    }
}
