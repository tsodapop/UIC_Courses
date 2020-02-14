using System;
using UnityEditor;
using UnityEngine;

namespace getReal3D {

    class NavigationHelperEditor {

        SerializedProperty navigationMethod;
        SerializedProperty TranslationSpeed;
        SerializedProperty RotationSpeed;
        SerializedProperty WandLookDeadZone;
        SerializedProperty navFollows;
        SerializedProperty navReference;
        SerializedProperty rotationAround;
        SerializedProperty rotationAroundReference;
        SerializedProperty rotationFollows;
        SerializedProperty rotationFollowsReference;
        SerializedProperty joylookRotationAxes;
        SerializedProperty wandlookRotation;
        SerializedProperty wandLookContinuousDrive;

        public void OnEnable(SerializedObject serializedObject)
        {
            navigationMethod =
                serializedObject.FindProperty("m_navigationHelper.m_navigationMethod");
            TranslationSpeed = serializedObject.FindProperty("m_navigationHelper.TranslationSpeed");
            RotationSpeed = serializedObject.FindProperty("m_navigationHelper.RotationSpeed");
            WandLookDeadZone = serializedObject.FindProperty("m_navigationHelper.WandLookDeadZone");
            navFollows = serializedObject.FindProperty("m_navigationHelper.navFollows");
            navReference = serializedObject.FindProperty("m_navigationHelper.navReference");
            rotationAround = serializedObject.FindProperty("m_navigationHelper.rotationAround");
            rotationAroundReference = serializedObject.FindProperty
                ("m_navigationHelper.rotationAroundReference");
            rotationFollows = serializedObject.FindProperty("m_navigationHelper.rotationFollows");
            rotationFollowsReference = serializedObject.FindProperty
                ("m_navigationHelper.rotationFollowsReference");
            joylookRotationAxes = serializedObject.FindProperty
                ("m_navigationHelper.joylookRotationAxes");
            wandlookRotation = serializedObject.FindProperty("m_navigationHelper.wandlookRotation");
            wandLookContinuousDrive = serializedObject.FindProperty
                ("m_navigationHelper.wandLookContinuousDrive");
        }
        public void OnInspectorGUI(SerializedObject serializedObject)
        {
            EditorGUILayout.Space();

            EditorGUILayout.LabelField("Navigation Settings", EditorStyles.boldLabel);
            PropertyField("Type", navigationMethod);
            EditorGUILayout.Space();

            EditorGUILayout.LabelField("Navigation Settings", EditorStyles.boldLabel);
            EditorGUILayout.PropertyField(TranslationSpeed);
            EditorGUILayout.PropertyField(navFollows);
            if(navFollows.enumValueIndex == (int) NavigationHelper.NavFollows.Reference) {
                EditorGUILayout.PropertyField(navReference);
            }
            EditorGUILayout.Space();

            EditorGUILayout.LabelField("Look Settings", EditorStyles.boldLabel);
            EditorGUILayout.PropertyField(RotationSpeed);
            EditorGUILayout.PropertyField(WandLookDeadZone);
            EditorGUILayout.PropertyField(rotationAround);
            if(rotationAround.enumValueIndex == (int) NavigationHelper.NavFollows.Reference) {
                EditorGUILayout.PropertyField(rotationAroundReference);
            }
            EditorGUILayout.PropertyField(rotationFollows);
            if(rotationFollows.enumValueIndex == (int) NavigationHelper.NavFollows.Reference) {
                EditorGUILayout.PropertyField(rotationFollowsReference);
            }
            EditorGUILayout.PropertyField(joylookRotationAxes);
            EditorGUILayout.PropertyField(wandlookRotation);
            EditorGUILayout.PropertyField(wandLookContinuousDrive);
        }

        private void PropertyField(string label, SerializedProperty property)
        {
            GUILayout.BeginHorizontal();
            EditorGUILayout.PropertyField(property, new GUIContent(label));
            GUILayout.EndHorizontal();
        }
    }
}
