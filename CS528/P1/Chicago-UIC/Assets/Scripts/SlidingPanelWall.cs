using UnityEngine;
using System.Collections;

public class SlidingPanelWall : MonoBehaviour {

	public bool open = false;
	public float speed = 1;

	public Transform[] panels;

	public float progress;

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		if(open && progress < 1){
			progress += Time.deltaTime * speed;
		}
		else if(open && progress > 1){
			progress = 1;
		}
		else if(!open && progress > 0){
			progress -= Time.deltaTime * speed;
		}
		else if(!open && progress < 0){
			progress = 0;
		}

		foreach( Transform t in panels )
		{
			t.localPosition = Vector3.Lerp( new Vector3(0,0,1), new Vector3(0,0,0), progress );
		}
	}
}
