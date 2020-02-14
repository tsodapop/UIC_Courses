using UnityEngine;
using System.Collections;

public class LightWandController : MonoBehaviour {


    Light l;
	// Use this for initialization
	void Start () {
        l = GetComponent<Light>();

    }
	
	// Update is called once per frame
	void Update () {
	    if(CAVE2.GetButtonDown(1, CAVE2.Button.ButtonUp))
        {
            if(l.shadows == LightShadows.Hard)
            {
                l.shadows = LightShadows.Soft;
            }
            else if (l.shadows == LightShadows.Soft)
            {
                l.shadows = LightShadows.None;
            }
            else if (l.shadows == LightShadows.None)
            {
                l.shadows = LightShadows.Hard;
            }
        }
	}
}
