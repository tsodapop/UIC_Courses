using UnityEngine;
using System.Collections;

public class WandMenu : MonoBehaviour
{

    public float timeSinceLastWandOver;

    public TextMesh[] textLines;

    int currentRow = 0;

    float hideAfterIdleTime = 0.25f;
    float showHideTimer;
    public bool hideGUI = true;

    public bool panelActive = false;

    public POIJump jumper;

    public Vector3 originalTextScale = Vector3.one;

    public Transform background;
    public Vector3 backgroundOrigScale;

    void ActivatePanel()
    {
        panelActive = true;
    }

    void DeactivatePanel()
    {
        panelActive = false;
    }

    void Start()
    {
        backgroundOrigScale = background.localScale;
        /*
        if (hideGUI)
        {
            foreach (TextMesh t in textLines)
            {
                t.transform.localScale = new Vector3(0.02599687f, 0, 0.02599687f);
            }
            showHideTimer = 1;
        }
        else
        {
            showHideTimer = 0;
            foreach (TextMesh t in textLines)
            {
                t.transform.localScale = new Vector3(0.02599687f, 0.07381471f, 0.02599687f);
            }
        }
         */
    }

    // Update is called once per frame
    void Update()
    {
        timeSinceLastWandOver += Time.deltaTime;

        if (!hideGUI && timeSinceLastWandOver >= hideAfterIdleTime)
        {
            showHideTimer += Time.deltaTime * 5;

            if (showHideTimer > 1)
            {
                showHideTimer = 1;
                hideGUI = true;
            }
            foreach (TextMesh t in textLines)
            {
                t.transform.localScale = new Vector3(originalTextScale.x, originalTextScale.y * (1 - showHideTimer), originalTextScale.z);
            }
            background.localScale = new Vector3(backgroundOrigScale.x, backgroundOrigScale.y * (1 - showHideTimer), backgroundOrigScale.z);
        }
        else if (!hideGUI && showHideTimer > 0)
        {
            showHideTimer -= Time.deltaTime * 5;

            if (showHideTimer < 0)
            {
                showHideTimer = 0;
            }
            foreach (TextMesh t in textLines)
            {
                t.transform.localScale = new Vector3(originalTextScale.x, originalTextScale.y * (1 - showHideTimer), originalTextScale.z);
            }
            background.localScale = new Vector3(backgroundOrigScale.x, backgroundOrigScale.y * (1 - showHideTimer), backgroundOrigScale.z);
        }

        if (currentRow >= 0 && currentRow < textLines.Length)
        {
            foreach (TextMesh t in textLines)
            {
                t.color = Color.white;
            }
            textLines[currentRow].color = Color.green;
        }
    }

    void OnWandButtonClick(CAVE2.Button button)
    {
        if (hideGUI)
            return;

        if (button == CAVE2.Button.ButtonDown)
            currentRow++;
        if (button == CAVE2.Button.ButtonUp)
            currentRow--;

        if (currentRow >= textLines.Length)
            currentRow = textLines.Length - 1;
        if (currentRow < 0)
            currentRow = 0;

        if (button == CAVE2.Button.ButtonLeft)
        {
            
        }
        else if (button == CAVE2.Button.ButtonRight)
        {
            
        }
        else if (button == CAVE2.Button.Button3)
        {
            jumper.WarpTo(currentRow);
        }

    }

    void OnWandOver()
    {
        if (panelActive)
        {
            timeSinceLastWandOver = 0;
            hideGUI = false;
        }
    }
}
