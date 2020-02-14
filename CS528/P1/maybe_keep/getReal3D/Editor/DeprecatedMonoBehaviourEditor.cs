using UnityEditor;
using UnityEngine;

namespace getReal3D
{
    [CanEditMultipleObjects]
    class DeprecatedEditor : UnityEditor.Editor
    {
        public override void OnInspectorGUI()
        {
            EditorGUILayout.HelpBox("This script is deprecated.", MessageType.Warning, true);
            base.OnInspectorGUI();
        }
    }

    [CustomEditor(typeof(DeprecatedGetRealUserScript), true)]
    class DeprecatedGetRealUserScriptEditor : DeprecatedEditor { }

    [CustomEditor(typeof(DeprecatedMonoBehaviour), true)]
    class DeprecatedMonoBehaviourEditor : DeprecatedEditor { }
}
