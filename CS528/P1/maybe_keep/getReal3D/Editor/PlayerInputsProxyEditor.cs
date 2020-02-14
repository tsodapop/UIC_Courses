using UnityEditor;
using UnityEngine;

namespace getReal3D
{
    [CustomEditor(typeof(PlayerInputsProxy))]
    [CanEditMultipleObjects]
    class PlayerInputsProxyEditor : UnityEditor.Editor
    {

        SerializedProperty m_initializationMode;
        SerializedProperty m_searchInThisObject;

        public void OnEnable()
        {
            m_initializationMode = serializedObject.FindProperty("initializationMode");
            m_searchInThisObject = serializedObject.FindProperty("searchInThisObject");
        }

        public override void OnInspectorGUI()
        {
            serializedObject.Update();
            var target = (PlayerInputsProxy)serializedObject.targetObject;

            PropertyField("Initialization", m_initializationMode);

            if(target.initializationMode == PlayerInputsProxy.InitializationMode.SearchInObject) {
                PropertyField("Target object", m_searchInThisObject);
                if(target.searchInThisObject == null) {
                    EditorGUILayout.HelpBox("Target object not set.", MessageType.Warning, true);
                }
            }

            if(EditorApplication.isPlaying && target.target == null) {
                EditorGUILayout.HelpBox("Target not found.", MessageType.Warning, true);
            }

            if(target.target != null) {
                EditorGUILayout.ObjectField("Target", target.target.behaviour, typeof(GameObject), true);
            }

            serializedObject.ApplyModifiedProperties();
        }

        private void PropertyField(string label, SerializedProperty property)
        {
            GUILayout.BeginHorizontal();
            EditorGUILayout.PropertyField(property, new GUIContent(label));
            GUILayout.EndHorizontal();
        }
    }
}
