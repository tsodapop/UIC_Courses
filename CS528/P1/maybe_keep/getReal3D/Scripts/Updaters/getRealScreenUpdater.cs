using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// This script updates the attached game object transform to match a screen position, rotation and
/// size.
/// </summary>
public class getRealScreenUpdater : MonoBehaviour
{
    private string m_screenName;
    private bool m_screenDirty = true;
    public bool alwaysUpdate = false;

    /// <summary>
    /// Set the screen name. This is how a screen is identified within the display system.
    /// </summary>
    public string screenName {
        get {
            return m_screenName;
        }
        set {
            m_screenName = value;
            m_screenDirty = true;
        }
    }

    private void Update()
    {
        if (m_screenDirty || alwaysUpdate)
        {
            UpdateScreen();
        }
    }

    private void UpdateScreen()
    {
        var corners = getReal3D.Plugin.getScreenCoordinatesByName(m_screenName);
        var center = 0.5f * (corners[0] + corners[2]);
        var u = corners[1] - corners[0];
        var v = corners[3] - corners[0];
        var n = Vector3.Cross(u, v);

        transform.localPosition = center;
        transform.localScale = new Vector3(u.magnitude, v.magnitude, 1);
        transform.localRotation = Quaternion.LookRotation(n, v);

        m_screenDirty = false;
    }
}
