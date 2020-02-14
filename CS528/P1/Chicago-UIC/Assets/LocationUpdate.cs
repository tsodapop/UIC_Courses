using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LocationUpdate : CAVE2Interactable
{
    //Camera main_camera;
    //GameObject pcontroller;
    Transform coordinates;

    Vector3 default_pos = new Vector3(129, 13, 243);

    Vector3 jukebox = new Vector3(100,9,250);
    Vector3 benches = new Vector3(125, 9, 255);


    Vector3 stalls_pos = new Vector3(98,10,257);


    // Start is called before the first frame update
    void Start()
    {
        //main_camera = GetComponent<Camera>();
        coordinates = GetComponent<Transform>();
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void moveJukebox()
    {
        coordinates.transform.position = jukebox;
        coordinates.transform.rotation = Quaternion.Euler(0, -28, 0);
    }

    public void moveBenches()
    {
        coordinates.transform.position = benches;
        coordinates.transform.rotation = Quaternion.Euler(0, -28, 0);
    }

    public void moveStalls()
    {
        coordinates.transform.position = stalls_pos;
        coordinates.transform.rotation = Quaternion.Euler(0,-180,0);
    }

    public void moveDefault()
    {
        coordinates.transform.position = default_pos;
        coordinates.transform.rotation = Quaternion.Euler(0, -28, 0);
    }
}
