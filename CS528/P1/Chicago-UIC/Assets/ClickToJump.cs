using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ClickToJump : CAVE2Interactable
{

    Animator ani;

    [SerializeField]
    CAVE2.Button clickButton = CAVE2.Button.Button3;

    private void Start()
    {
        ani = GetComponent<Animator>();
    }

    void Update()
    {
        UpdateWandOverTimer();
    }

    new void OnWandButtonDown(CAVE2.WandEvent evt)
    {
        if (evt.button == clickButton)
        {
            //ani.SetTrigger("Active");
            ani.Play("jump-up",0);
        }
    }


}
