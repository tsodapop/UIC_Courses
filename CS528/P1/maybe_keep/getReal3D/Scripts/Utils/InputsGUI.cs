using System;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(PlayerInputs))]
public class InputsGUI : MonoBehaviour
{
    private PlayerInputs m_playerInputs;
    private Dictionary<string, float> m_pushedTimestamp = new Dictionary<string, float>();
    private Dictionary<string, float> m_releasedTimestamp = new Dictionary<string, float>();
    private float fadeOutTime = 0.5f;
    private GUIStyle m_buttonsStyle;

    void Start()
    {
        m_playerInputs = GetComponent<PlayerInputs>();
    }

    void OnGUI()
    {
        if(!getReal3D.GUI.BeginGUI()) return;

        int w = 300;
        int h = 400;
        int x = Screen.width / 2 - w / 2;
        int y = Screen.height / 2 - h / 2;

        GUILayout.BeginArea(new Rect(x, y, w, h));
        GUILayout.BeginVertical("Inputs", GUI.skin.window);

        ShowAxis("YawAxis", m_playerInputs.YawAxis);
        ShowAxis("PitchAxis", m_playerInputs.PitchAxis);
        ShowAxis("StrafeAxis", m_playerInputs.StrafeAxis);
        ShowAxis("ForwardAxis", m_playerInputs.ForwardAxis);

        ShowButton("WandLookButton", m_playerInputs.WandLookButton,
            m_playerInputs.WandLookButtonDown, m_playerInputs.WandLookButtonUp);

        ShowButton("WandDriveButton", m_playerInputs.WandDriveButton,
            m_playerInputs.WandDriveButtonDown, m_playerInputs.WandDriveButtonUp);

        ShowButton("NavSpeedButton", m_playerInputs.NavSpeedButton,
            m_playerInputs.NavSpeedButtonDown, m_playerInputs.NavSpeedButtonUp);

        ShowButton("JumpButton", m_playerInputs.JumpButton,
            m_playerInputs.JumpButtonDown, m_playerInputs.JumpButtonUp);

        ShowButton("WandButton", m_playerInputs.WandButton,
            m_playerInputs.WandButtonDown, m_playerInputs.WandButtonUp);

        ShowButton("ChangeWandButton", m_playerInputs.ChangeWandButton,
            m_playerInputs.ChangeWandButtonDown, m_playerInputs.ChangeWandButtonUp);

        ShowButton("ResetButton", m_playerInputs.ResetButton,
            m_playerInputs.ResetButtonDown, m_playerInputs.ResetButtonUp);

        GUILayout.EndVertical();
        GUILayout.EndArea();
        getReal3D.GUI.EndGUI();
    }

    private GUIStyle getStyle(float timeElapsed)
    {
        if(m_buttonsStyle == null) {
            m_buttonsStyle = new GUIStyle(GUI.skin.label);
        }
        var fade = 1 - timeElapsed / fadeOutTime;
        m_buttonsStyle.normal.textColor = new Color(1, 1, 1, fade);
        m_buttonsStyle.fixedWidth = 20f;
        return m_buttonsStyle;
    }

    private float getFadeOutTime(string label, Dictionary<string, float> elapsed)
    {
        float val;
        if(elapsed.TryGetValue(label, out val)) {
            return Mathf.Min(Time.time - val, fadeOutTime);
        }
        return fadeOutTime;
    }

    private void ShowButton(string label, bool isDown, bool wasPushedDown, bool wasReleased)
    {
        if(wasPushedDown) {
            m_pushedTimestamp[label] = Time.time;
        }
        if(wasReleased) {
            m_releasedTimestamp[label] = Time.time;
        }
        GUILayout.BeginHorizontal();
        GUILayout.Label(label);
        GUILayout.FlexibleSpace();
        GUILayout.TextField("X", getStyle(isDown?0:fadeOutTime));
        GUILayout.Space(20);
        GUILayout.TextField("X", getStyle(getFadeOutTime(label, m_pushedTimestamp)));
        GUILayout.Space(20);
        GUILayout.TextField("X", getStyle(getFadeOutTime(label, m_releasedTimestamp)));
        GUILayout.EndHorizontal();
    }

    private void ShowAxis(string label, float axis)
    {
        GUILayout.BeginHorizontal();
        GUILayout.Label(label);
        GUILayout.FlexibleSpace();
        GUILayout.TextField(axis.ToString("##0.000"));
        GUILayout.EndHorizontal();
    }

}
