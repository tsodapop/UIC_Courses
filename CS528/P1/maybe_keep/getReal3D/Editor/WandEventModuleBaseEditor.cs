using UnityEditor;
using UnityEngine;

namespace getReal3D
{
    public class WandEventModuleBaseEditor : UnityEditor.Editor
    {
        SerializedProperty sendWandEvents;
        SerializedProperty cursor;
        SerializedProperty mouseInteractionMode;
        SerializedProperty mouseCamera;
        SerializedProperty inputActionsPerSecond;
        SerializedProperty repeatDelay;
        SerializedProperty sendMoveEvents;

        void OnEnable()
        {
            sendWandEvents = serializedObject.FindProperty("m_sendWandEvents");
            cursor = serializedObject.FindProperty("cursor");
            mouseInteractionMode = serializedObject.FindProperty("m_mouseInteractionMode");
            mouseCamera = serializedObject.FindProperty("m_mouseCamera");
            inputActionsPerSecond = serializedObject.FindProperty("m_inputActionsPerSecond");
            repeatDelay = serializedObject.FindProperty("m_repeatDelay");
            sendMoveEvents = serializedObject.FindProperty("m_sendMoveEvents");
        }

        public override void OnInspectorGUI()
        {
            serializedObject.Update();
            PropertyField("Send Wand events", sendWandEvents);
            if (sendWandEvents.boolValue) {
                PropertyField("Cursor to display", cursor);
            }
            PropertyField("Master mouse interaction", mouseInteractionMode);
            var interactionMode = (WandEventModuleBase.MouseInteractionMode)
                mouseInteractionMode.enumValueIndex;
            if (interactionMode == WandEventModuleBase.MouseInteractionMode.WorldOnly ||
                interactionMode == WandEventModuleBase.MouseInteractionMode.All)
            {
                PropertyField("Master camera", mouseCamera);
            }
            PropertyField("Send move events", sendMoveEvents);
            if (sendMoveEvents.boolValue)
            {
                EditorGUILayout.PropertyField(repeatDelay);
                EditorGUILayout.PropertyField(inputActionsPerSecond);
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

    [CustomEditor(typeof(GenericWandEventModule))]
    public class GenericWandEventModuleEditor : WandEventModuleBaseEditor { }

    [CustomEditor(typeof(WandEventModule))]
    public class WandEventModuleEditor : WandEventModuleBaseEditor { }

}
