using UnityEngine;
using System.Collections.Generic;

public class getRealUser : MonoBehaviour {
    public uint userId = 0;

    private static List<getRealUser> s_users = new List<getRealUser>();

    public static List<getRealUser> users {
        get { return s_users; }
    }

    void OnEnable()
    {
        s_users.Add(this);
    }

    void OnDisable()
    {
        s_users.Remove(this);
    }
}
