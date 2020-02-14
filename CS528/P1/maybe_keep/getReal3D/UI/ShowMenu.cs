using UnityEngine;
using System.Collections;

// This class is deprecated. GenericShowMenu should be used instead.
public class ShowMenu : getReal3D.DeprecatedMonoBehaviour {

    public Transform m_menuObject;
    public string m_wandButton = "WandButton";
    public float m_defaultDistance = 1.0f;

    void Start()
    {
        MenuSettings ms = GetComponentInParent<MenuSettings>() as MenuSettings;
        if(ms && ms.depth.HasValue) {
            m_defaultDistance = ms.depth.Value;
        }
        if(ms && ms.menuButton != null) {
            m_wandButton = ms.menuButton;
        }
        var wandEventModule = FindObjectOfType<WandEventModule>();
        if(!wandEventModule) {
            Debug.LogError("Unable to find getReal3D.WandEventModule object in scene. " +
                "Either use the GenericPlayer prefab or attach a WandEventModule to the " +
                "EventSystem object.", FindObjectOfType<UnityEngine.EventSystems.EventSystem>()
                );
        }
    }

    void Update () {
        if(m_menuObject) {
            if(getReal3D.Input.GetButtonDown(m_wandButton) && !m_menuObject.gameObject.activeSelf) {
                m_menuObject.gameObject.SetActive(true);
                setDefaultPosition();
            }
        }
    }

    public void clickOutside()
    {
        if(m_menuObject) {
            m_menuObject.gameObject.SetActive(false);
        }
    }

    private void setDefaultPosition()
    {
        if(m_menuObject) {
            Transform hand = transform.parent;
            m_menuObject.transform.position = hand.position + m_defaultDistance *
                (hand.rotation * Vector3.forward);
            Vector3 euler = new Vector3(0,hand.rotation.eulerAngles[1],0);
            m_menuObject.transform.rotation = Quaternion.Euler(euler);
        }
    }
}
