using UnityEngine;
using getReal3D;

/// <summary>
/// Script used to update a camera position, rotation and projection.
/// </summary>
[RequireComponent(typeof(Camera))]
[AddComponentMenu("getReal3D/Updater/Camera Updater")]
[ExecuteInEditMode]
public class getRealCameraUpdater
    : getRealUserScript, CameraUpdaterInterface
{

    public CameraUpdaterHelper updater {
        get { return m_cameraUpdaterHelper; }
        set { m_cameraUpdaterHelper = value; }
    }

    public MonoBehaviour behaviour {
        get { return this; }
    }

    [SerializeField]
    public CameraPreviewData m_cameraPreviewData;

    public CameraPreviewData cameraPreviewData {
        get { return m_cameraPreviewData; }
        set { m_cameraPreviewData = value; }
    }

    private CameraUpdaterHelper m_cameraUpdaterHelper;

    void OnEnable()
    {
        CameraUpdaterHelper.CreateCamerasForUserIfNeeded(GetComponent<Camera>(), userId());
    }

    public bool m_updateTrackingPosition = true;
    void OnPreCull()
    {
        if(m_cameraUpdaterHelper != null && m_updateTrackingPosition) {
            m_cameraUpdaterHelper.UpdateCamera();
        }
    }

    void OnPreRender()
    {
        if(m_cameraUpdaterHelper != null) {
            m_cameraUpdaterHelper.PreRender();
        }
    }

    void OnPostRender()
    {
        if(m_cameraUpdaterHelper != null) {
            m_cameraUpdaterHelper.PostRender();
        }
    }

    void OnDestroy()
    {
        if(m_cameraUpdaterHelper != null) {
            m_cameraUpdaterHelper.Destroyed();
        }
    }

    void OnDisable()
    {
        if(m_cameraUpdaterHelper != null) {
            m_cameraUpdaterHelper.Disabled();
        }
    }

    void OnRenderImage(RenderTexture src, RenderTexture dst)
    {
        if(m_cameraUpdaterHelper != null) {
            m_cameraUpdaterHelper.OnRenderImage(src, dst);
        }
        else {
            Graphics.Blit(src, dst);
        }
    }
}
