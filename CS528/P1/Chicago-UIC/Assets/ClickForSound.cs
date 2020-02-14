using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ClickForSound : CAVE2Interactable
{

    AudioSource my_Audio;

    [SerializeField]
    CAVE2.Button clickButton = CAVE2.Button.Button3;

    private void Start()
    {
        my_Audio = GetComponent<AudioSource>();
    }

    void Update()
    {
        UpdateWandOverTimer();
    }

    new void OnWandButtonDown(CAVE2.WandEvent evt)
    {
        if (evt.button == clickButton)
        {
                my_Audio.Play();
        }
    }


}
