using UnityEngine;
using UnityEngine.UI;
using System.Collections;

/// <summary>
/// This class is used by the pointer UI in order to ignore any raycast it to itself.
/// </summary>
public class IgnoreRaycast : MonoBehaviour, ICanvasRaycastFilter
{
    public bool IsRaycastLocationValid(Vector2 sp, Camera eventCamera)
    {
        return false;
    }
}
