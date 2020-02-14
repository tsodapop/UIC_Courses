using UnityEngine;
using System.Collections;

[ExecuteInEditMode]
public class MeshLODByDistance : LODByDistance {

    [SerializeField]
    Mesh highLODMesh;

    [SerializeField]
    Mesh lowLODMesh;

    override public void ShowHighLOD()
    {
        if( highLODMesh )
        {
            GetComponent<MeshFilter>().mesh = highLODMesh;
        }
    }

    override public void ShowLowLOD()
    {
        if (lowLODMesh)
        {
            GetComponent<MeshFilter>().mesh = lowLODMesh;
        }
    }
}
