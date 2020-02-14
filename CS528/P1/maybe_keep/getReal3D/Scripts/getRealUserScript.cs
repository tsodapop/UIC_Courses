using UnityEngine;

public class getRealUserScript : MonoBehaviour {

    private getRealUser m_getRealUser = null;

    public uint userId()
    {
        findGetRealUser();
        return m_getRealUser == null ? 0 : m_getRealUser.userId;
    }

    public getRealUser user()
    {
        findGetRealUser();
        return m_getRealUser;
    }

    public getReal3D.Sensor getHead()
    {
        return getReal3D.Input.headForUser(userId());
    }

    public getReal3D.Sensor getWand()
    {
        return getReal3D.Input.wandForUser(userId());
    }

    private void findGetRealUser()
    {
        if (m_getRealUser) { return; }
        m_getRealUser = GetComponentInParent<getRealUser>();
        if(!m_getRealUser) {
            getRealUser anyUser = Object.FindObjectOfType<getRealUser>();
            if(anyUser) {
                getReal3D.Plugin.error("Unable to find a getRealUser in any of my parents but" +
                    " there are users in the scene. If you are building a multi users game," +
                    " please add a getRealUser script to all users.");
                m_getRealUser = anyUser;
            }
            else {
                m_getRealUser = transform.root.gameObject.AddComponent<getRealUser>();
            }
        }
    }
}
