using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System;

/// <summary>
/// This class is a debugging tool displaying Unity messages on the screen space GUI.
/// </summary>
public class LogToScreen : MonoBehaviour {

    [Tooltip("Maximum number of messages to show.")]
    public int m_maxSize = 15;

    [Tooltip("How long to show messages before they are removed (in seconds).")]
    public float m_timeout = 2;

    public GUIStyle m_style = new GUIStyle();

    private struct Message {
        public Message(float timeIssued, string text)
        {
            this.timeIssued = timeIssued;
            this.text = text;
        }
        public float timeIssued;
        public string text;
    }

    LinkedList<Message> m_messages = new LinkedList<Message>();

    string myLog;

    void Start()
    {

    }

    void OnEnable()
    {
        Application.logMessageReceived += HandleLog;
    }

    void OnDisable()
    {
        Application.logMessageReceived -= HandleLog;
    }

    private void Update()
    {
        float removalTime = Time.time - m_timeout;
        bool changed = false;
        while(m_messages.Count > 0 && m_messages.Last.Value.timeIssued < removalTime) {
            m_messages.RemoveLast();
            changed = true;
        }
        if(changed) {
            BuildText();
        }
    }

    void HandleLog(string logString, string stackTrace, LogType type)
    {
        myLog = logString;
        string newString = "\n [" + type + "] : " + myLog;
        m_messages.AddFirst(new Message(Time.time, newString));
        if(type == LogType.Exception) {
            newString = "\n" + stackTrace;
            m_messages.AddFirst(new Message(Time.time, newString));
        }

        while(m_messages.Count > m_maxSize) {
            m_messages.RemoveLast();
        }

        BuildText();
    }

    private void BuildText()
    {
        myLog = string.Empty;
        foreach(Message msg in m_messages) {
            myLog += msg.text;
        }
    }

    void OnGUI()
    {
        GUILayout.Label(myLog, m_style);
    }
}
