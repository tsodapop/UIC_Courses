using UnityEngine;
using UnityEngine.UI;
using System.Collections;

/// <summary>
/// Script used to handle the lights menu.
/// </summary>
public class MultiClusterLightsMenu : MonoBehaviour {

    public GameObject m_lightTogglePrefab;
    public MenuColors m_changeColors;

    private Light[] m_lights;
    private Toggle[] m_lightsToggle;
    private bool[] m_wasOn;

    void Start()
    {
        m_lights = FindObjectsOfType(typeof(Light)) as Light[];
        m_lightsToggle = new Toggle[m_lights.Length];
        m_wasOn = new bool[m_lights.Length];
        for(int i = 0; i < m_lights.Length; ++i) {
            Light light = m_lights[i];
            GameObject lightToggle = GameObject.Instantiate(m_lightTogglePrefab) as GameObject;
            lightToggle.transform.SetParent(transform, false);
            Text label = lightToggle.GetComponentInChildren<Text>() as Text;
            label.text = light.name;
            m_lightsToggle[i] = lightToggle.GetComponent<Toggle>() as Toggle;
            m_wasOn[i] = m_lightsToggle[i].isOn;
        }
        if(m_changeColors) {
            m_changeColors.handleGameObject(gameObject);
        }
    }

    void Update()
    {
        for(int i = 0; i < m_lights.Length; ++i) {
            if(m_wasOn[i] != m_lightsToggle[i].isOn) {
                m_wasOn[i] = m_lightsToggle[i].isOn;
                ToggleCallback(m_lights[i], m_lightsToggle[i].isOn);
            }
            if(m_lights[i].enabled != m_lightsToggle[i].isOn) {
                m_lightsToggle[i].isOn = m_lights[i].enabled;
                m_wasOn[i] = m_lights[i].enabled;
            }
        }
    }

    void ToggleCallback(Light light, bool e)
    {
        var lightHandler = GetComponentInParent<LightHandler>();
        if(lightHandler) {
            lightHandler.EnableLight(light, e);
        }
    }

}
