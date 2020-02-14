using UnityEngine;
using System.Collections;

//[ExecuteInEditMode]
public class POIJump : MonoBehaviour {

	public GameObject player;

	public Transform[] poiLocations;
	public bool warp = false;
	public int warpID = 0;

	// Update is called once per frame
	void Update () {

		if (warp && warpID < poiLocations.Length) {
			player.transform.position = poiLocations[warpID].position;
			player.transform.rotation = poiLocations[warpID].rotation;
			warp = false;
		}
        /*
		if (CAVE2.GetButtonDown(1, CAVE2.Button.ButtonLeft))
		{
			warpID--;
			WarpTo(warpID);
			//getReal3D.RpcManager.call("WarpTo", warpID);
		}
		if (CAVE2.GetButtonDown(1, CAVE2.Button.ButtonRight))
		{
			warpID++;
			WarpTo(warpID);
			//getReal3D.RpcManager.call("WarpTo", warpID);
		}
        if (CAVE2.GetButtonDown(1, CAVE2.Button.ButtonUp))
        {
            //player.GetComponent<OmicronPlayerController>().flyMovementScale *= 10;
        }
        if (CAVE2.GetButtonDown(1, CAVE2.Button.ButtonDown))
        {
            //player.GetComponent<OmicronPlayerController>().flyMovementScale *= 0.1f;
        }
        */
    }

	//[getReal3D.RPC]
	public void WarpTo( int id )
	{
		if (id >= poiLocations.Length ) {
			id  = 0;
			warpID = 0;
		}
        else if (id < 0)
        {
            id = poiLocations.Length - 1;
            warpID = poiLocations.Length - 1;
        }

        if (id < poiLocations.Length) {
			player.transform.position = poiLocations[id].position;
			player.transform.rotation = poiLocations[id].rotation;
		}
	}
}
