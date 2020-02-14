using UnityEditor;

namespace getReal3D {
    [CustomEditor(typeof(MultiClusterNavigation))]
    [CanEditMultipleObjects]
    class MultiClusterNavigationEditor : UnityEditor.Editor {
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
