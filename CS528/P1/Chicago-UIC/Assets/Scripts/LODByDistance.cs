using UnityEngine;
using System.Collections;

[ExecuteInEditMode]
public class LODByDistance : MonoBehaviour {

    [SerializeField]
    float cameraDistance;

    [SerializeField]
    float minimumDistance = 50;

    [SerializeField]
    bool alwaysShow = false;

    void Start()
    {
        StartCoroutine("CheckLODDistance");
    }

    IEnumerator CheckLODDistance() {
        cameraDistance = Vector3.Distance(transform.position, Camera.main.transform.position);

        if ((alwaysShow || cameraDistance <= minimumDistance))
        {
            ShowHighLOD();
        }
        else if (cameraDistance > minimumDistance)
        {
            ShowLowLOD();
        }

        yield return new WaitForSeconds(0.1f);
    }

    virtual public void ShowHighLOD()
    {
        gameObject.GetComponent<MeshRenderer>().enabled = true;
    }

    virtual public void ShowLowLOD()
    {
        gameObject.GetComponent<MeshRenderer>().enabled = false;
    }
}
