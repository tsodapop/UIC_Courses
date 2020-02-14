using UnityEngine;
using System.Collections;
using getReal3D;

/// <summary>
/// This script update the position and rotation of the attached object according to a
/// getReal3D sensor.
/// </summary>
public class getRealSensorUpdater : MonoBehaviour
{
    [Tooltip("The getReal3D sensor name.")]
    public string sensorName;

    [Tooltip("Disable the attached object if the sensor doesn't exist.")]
    public bool disableIfNotFound = false;

    private bool m_sensorFound;

    void OnEnable()
    {
        m_sensorFound = System.Array.IndexOf(getReal3D.Input.sensorsName(), sensorName) >= 0;
        if(disableIfNotFound && !m_sensorFound) {
            gameObject.SetActive(false);
        }
    }

    void Update()
    {
        if (m_sensorFound){
            getReal3D.Sensor sensor = getReal3D.Input.GetSensor(sensorName);
            transform.localPosition = sensor.position;
            transform.localRotation = sensor.rotation;
        }
    }

    void OnDrawGizmos()
    {
        Gizmos.matrix = transform.localToWorldMatrix;
        Gizmos.color = Color.red;
        Gizmos.DrawWireCube(new Vector3(0,0,0), new Vector3(0.1f, 0.1f, 0.15f));
    }
}
