using UnityEngine;
using System.Collections;

public class ToggleModel : MonoBehaviour {

    public GameObject targetGameobject;

    public bool showGameObject = true;

	// Use this for initialization
	void Start () {
        targetGameobject.SetActive(showGameObject);

    }
	
	public void ToggleGameObject() {
        showGameObject = !showGameObject;
        targetGameobject.SetActive(showGameObject);
    }
}
