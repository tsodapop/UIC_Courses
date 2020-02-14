using UnityEditor;

namespace getReal3D
{
    [CustomEditor(typeof(Navigation))]
    [CanEditMultipleObjects]
    class NavigationEditor : UnityEditor.Editor
    {
        private NavigationHelperEditor navigationHelperEditor = new NavigationHelperEditor();
        void OnEnable()
        {
            navigationHelperEditor.OnEnable(serializedObject);
        }

        public override void OnInspectorGUI()
        {
            serializedObject.Update();
            navigationHelperEditor.OnInspectorGUI(serializedObject);
            serializedObject.ApplyModifiedProperties();
        }
    }
}
