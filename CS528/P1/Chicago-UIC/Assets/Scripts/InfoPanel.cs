using UnityEngine;
using System.Collections;

public class InfoPanel : MonoBehaviour {

	public bool showPanel = false;
	public float scaleProgress = 0;
	public float scaleSpeed = 2;

	public float playerMinDistance = 10;
	
	public float playerDistance;
	public bool lookAtPlayer = true;

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		playerDistance = Vector3.Distance (GameObject.FindGameObjectWithTag("Player").transform.position, transform.position);
		if ( playerDistance <= playerMinDistance) {
			showPanel = true;
		} else {
			showPanel = false;
		}

		if (showPanel && scaleProgress < 1) {
			scaleProgress += Time.deltaTime * scaleSpeed;
		} else if (showPanel && scaleProgress > 1) {
			scaleProgress = 1;
		} else if (!showPanel && scaleProgress > 0) {
			scaleProgress -= Time.deltaTime * scaleSpeed;
		} else if (!showPanel && scaleProgress < 0) {
			scaleProgress = 0;
		}

		transform.localScale = Vector3.Lerp( new Vector3(1,0,1), Vector3.one, scaleProgress );

		if( lookAtPlayer )
		{
			transform.LookAt (Camera.main.transform.position);
			transform.eulerAngles = new Vector3 (0, transform.eulerAngles.y + 180, 0);
		}
	}
}
