using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ClickForSoundCanPause : CAVE2Interactable

{
    AudioSource my_Audio;

    bool hasStarted;
    bool isPlaying;

    [SerializeField]
    CAVE2.Button click_and_pause_Button = CAVE2.Button.Button3;

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
        if (evt.button == click_and_pause_Button && !hasStarted)
        {
            my_Audio.Play();
            isPlaying = true;
            hasStarted = true;
        }
        else if (evt.button == click_and_pause_Button && isPlaying)
        {
            my_Audio.Pause();
            isPlaying = false;
            //hasStarted = false;
        }
        else if (evt.button == click_and_pause_Button && !isPlaying && hasStarted)
        {
            my_Audio.UnPause();
            isPlaying = true;
            //hasStarted = false;
        }
    }
}
