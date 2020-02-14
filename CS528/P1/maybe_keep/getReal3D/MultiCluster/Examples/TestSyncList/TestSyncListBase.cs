//using getReal3D.MultiCluster;
using UnityEngine;
using System.Linq;
//using UnityEngine.Networking;
using System.Collections.Generic;
using getReal3D.MultiCluster;
using System;

/// <summary>
/// This example shows how to use SyncLists. For ease of use, this example is using the 2D UI.
/// This will prevent this example to work on multiple instances, on the server side.
/// </summary>
public abstract class TestSyncListBase<T> : NetworkBehaviour {

    public SyncList<T> m_syncList = CreateSyncList();

    private static SyncList<T> CreateSyncList()
    {
        if(typeof(bool) == typeof(T))
            return (SyncList<T>) (object) new SyncListBool();
        else if(typeof(float) == typeof(T))
            return (SyncList<T>) (object) new SyncListFloat();
        else if(typeof(int) == typeof(T))
            return (SyncList<T>) (object) new SyncListInt();
        else if(typeof(string) == typeof(T))
            return (SyncList<T>) (object) new SyncListString();
        else if(typeof(uint) == typeof(T))
            return (SyncList<T>) (object) new SyncListUInt();
        else if(typeof(MyStruct) == typeof(T))
            return (SyncList<T>) (object) new SyncListStruct<MyStruct>();
        else if(typeof(Vector3) == typeof(T))
            return (SyncList<T>) (object) new SyncListStruct<Vector3>();
        return null;
    }

    private readonly int m_maxMessage = 10;
    private LinkedList<string> m_messages = new LinkedList<string>();
    private string m_message;

    public int m_x = 0;
    public int m_width = 230;

    private void OnIntChanged(SyncList<T>.Operation op, int index)
    {
        addLog(op + " index: " + index + "\n");
    }

    private void addLog(string msg)
    {
        m_messages.AddLast(msg);
        while(m_messages.Count > m_maxMessage) {
            m_messages.RemoveFirst();
        }
        m_message = string.Empty;
        foreach(var m in m_messages) {
            m_message += m;
        }
    }

    public override void OnStartServer()
    {
        m_syncList.Add(GetRandom());
        m_syncList.Add(GetRandom());
        m_syncList.Add(GetRandom());
        m_syncList.Add(GetRandom());
    }

    public void Awake()
    {
        m_syncList.Callback = OnIntChanged;
    }

    void OnGUI()
    {
        GUI.Box(new Rect(m_x, 0, m_width, Screen.height), "");
        GUILayout.BeginArea(new Rect(m_x, 0, m_width, Screen.height));

        T toDelete = default(T);
        bool hasValueToDelete = false;
        int? toDeleteIndex = new int?();

        if(GUILayout.Button("Clear")) {
            m_syncList.Clear();
        }

        if(GUILayout.Button("Add")) {
            m_syncList.Add(GetRandom());
        }

        for(int i = 0; i < m_syncList.Count(); ++i) {
            var item = m_syncList[i];

            GUILayout.BeginHorizontal();
            GUILayout.Label(string.Format("{0}: {1}", i, item));
            if(GUILayout.Button("RAT")) {
                toDeleteIndex = i;
            }
            if(GUILayout.Button("S")) {
                m_syncList[i] = GetRandom();
            }
            if(GUILayout.Button("D")) {
                m_syncList.Dirty(i);
            }
            if(GUILayout.Button("I")) {
                m_syncList.Insert(i, GetRandom());
            }
            if(GUILayout.Button("R")) {
                toDelete = m_syncList[i];
                hasValueToDelete = true;
            }
            GUILayout.EndHorizontal();
        }

        GUILayout.Label(m_message);

        GUILayout.EndArea();

        if(hasValueToDelete) {
            m_syncList.Remove(toDelete);
        }

        if(toDeleteIndex.HasValue) {
            m_syncList.RemoveAt(toDeleteIndex.Value);
        }
    }

    virtual protected T GetRandom()
    {
        if(typeof(bool) == typeof(T))
            return (T) (object) (UnityEngine.Random.value > 0.5);
        else if(typeof(float) == typeof(T))
            return (T) (object) UnityEngine.Random.Range(0f, 1f);
        else if(typeof(int) == typeof(T))
            return (T) (object) UnityEngine.Random.Range(0, 42);
        else if(typeof(string) == typeof(T))
            return (T) (object) (System.Guid.NewGuid().ToString().Substring(0, 4));
        else if(typeof(uint) == typeof(T))
            return (T) (object) UnityEngine.Random.Range(0, 42);
        else if(typeof(Vector3) == typeof(T))
            return (T) (object) UnityEngine.Random.onUnitSphere;
        else if(typeof(Quaternion) == typeof(T))
            return (T) (object) UnityEngine.Random.rotation;
        else
            return default(T);
    }
}
