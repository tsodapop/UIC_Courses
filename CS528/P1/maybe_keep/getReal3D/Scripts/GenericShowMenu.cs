using System.Collections.Generic;
using System.Linq;
using UnityEngine;

/// <summary>
/// By implementing this interface and registering to the GenericShowMenu script, it is possible to
/// prevent showing the getReal3D menu. Typical usage is to use other in game menus.
/// See the PreventsShowMenu script for an example usage.
/// </summary>
public interface PreventShowMenuCallback
{
    bool preventsShowMenu(Transform wandObject);
}

/// <summary>
/// Script used to toggle on or off the 3D menu.
/// </summary>
[RequireComponent(typeof(MenuSettings))]
[RequireComponent(typeof(PlayerInputs))]
public class GenericShowMenu : MonoBehaviour, MenuClickedOustideCallback
{
    [Tooltip("The menu to show.")]
    public Transform m_menuObject;

    [Tooltip("The reference transform used when spawning the menu.")]
    public Transform m_menuSpawnReference;

    [Tooltip("The wand object. This script is only working when that object is activated.")]
    public Transform m_wandObject;

    [Tooltip("When spawned, the menu is placed at the given distance from the reference transform.")]
    public float m_defaultDistance = 1.0f;

    private List<PreventShowMenuCallback> m_preventsShowMenu = new List<PreventShowMenuCallback>();
    private PlayerInputs m_playerInputs;
    private GenericWandEventModule m_wandEventModule;

    void Awake()
    {
        m_playerInputs = GetComponent<PlayerInputs>();
        m_wandEventModule = GameObject.FindObjectOfType<GenericWandEventModule>();
    }

    void Start()
    {
        MenuSettings ms = GetComponentInParent<MenuSettings>() as MenuSettings;
        if(ms && ms.depth.HasValue) {
            m_defaultDistance = ms.depth.Value;
        }
    }

    void Update()
    {
        if(m_menuObject &&
            m_wandObject && m_wandObject.gameObject.activeInHierarchy) {
            if(m_playerInputs.WandButtonDown && !m_menuObject.gameObject.activeSelf &&
                !m_preventsShowMenu.Any(p => p.preventsShowMenu(m_wandObject))) {
                if(m_wandEventModule) {
                    m_wandEventModule.playerInputs = m_playerInputs;
                    m_wandEventModule.cursor = transform.Find("Menu/Panel/Pointer")
                        as RectTransform;
                }
                foreach(var menuDrag in
                    m_menuObject.GetComponentsInChildren<GenericMenuDrag>()) {
                    menuDrag.m_showMenu = this;
                    menuDrag.m_inputs = m_playerInputs;
                }
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

    public void setDefaultPosition()
    {
        if(m_menuObject && m_menuSpawnReference) {
            m_menuObject.transform.position = m_menuSpawnReference.position + m_defaultDistance *
                (m_menuSpawnReference.rotation * Vector3.forward);
            Vector3 euler = new Vector3(0, m_menuSpawnReference.rotation.eulerAngles[1], 0);
            m_menuObject.transform.rotation = Quaternion.Euler(euler);
        }
    }

    public void Register(PreventShowMenuCallback callback)
    {
        m_preventsShowMenu.Add(callback);
    }

    public void Deregister(PreventShowMenuCallback callback)
    {
        m_preventsShowMenu.Remove(callback);
    }
}
