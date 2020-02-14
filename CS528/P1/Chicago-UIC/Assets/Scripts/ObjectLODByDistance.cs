using UnityEngine;
using System.Collections;

[ExecuteInEditMode]
public class ObjectLODByDistance : LODByDistance
{

    [SerializeField]
    GameObject[] highLODObject;

    [SerializeField]
    GameObject[] lowLODObject;

    override public void ShowHighLOD()
    {
        foreach (GameObject g in highLODObject)
        {
            g.SetActive(true);
        }
        foreach (GameObject g in lowLODObject)
        {
            g.SetActive(false);
        }
    }

    override public void ShowLowLOD()
    {
        foreach (GameObject g in highLODObject)
        {
            g.SetActive(false);
        }
        foreach (GameObject g in lowLODObject)
        {
            g.SetActive(true);
        }
    }
}
