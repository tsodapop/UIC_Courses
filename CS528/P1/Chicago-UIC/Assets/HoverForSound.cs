using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HoverForSound : CAVE2Interactable
{

    AudioSource m_MyAudioSource;

    //bool hasSound = false;
 

    // Start is called before the first frame update
    void Start()
    {
        m_MyAudioSource = GetComponent<AudioSource>();
    }

    // Update is called once per frame
    void Update()
    {
        UpdateWandOverTimer();


        //if (wandPointing && !hasSound)
        if (wandPointing)
        {
            m_MyAudioSource.Play();
            //hasSound = true;
        }

    }
}
