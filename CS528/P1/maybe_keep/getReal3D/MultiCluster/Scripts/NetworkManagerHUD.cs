using System;
using System.Text.RegularExpressions;
using UnityEngine;
using getReal3D.MultiCluster;

/// <summary>
/// 2D GUI used to connect or disconnect MultiCluster.
/// </summary>
/// <remarks>
/// This script also handles automatic connection via the command line. As opposed to
/// HMDConnectionHUD, this script only supports getReal3D.
/// </remarks>
[RequireComponent(typeof(NetworkManager))]
public class NetworkManagerHUD : MonoBehaviour, INetworkErrorListener {
    protected string m_serverAddress = "127.0.0.1";
    protected NetworkManager m_networkManager;

    class Options {
        public bool doHost = false;
        public bool doJoin = false;
        public bool forceAntiAliasing = false;
        public int antiAliasingValue = 0;
        public string hostname = "";

        public void Parse(string[] args)
        {
            for(int i = 0; i < args.Length; i++) {
                if(args[i] == "-host" || args[i] == "--host") {
                    doHost = true;
                }
                else if(i != args.Length - 1 && (args[i] == "-join" || args[i] == "--join")) {
                    doJoin = true;
                    hostname = args[++i];
                }
            }
        }
    }

    private string m_errors;

    protected string errors {
        get { return m_errors; }
    }

    protected virtual void Start()
    {
        m_serverAddress = PlayerPrefs.GetString("server_address", m_serverAddress);
        m_networkManager = GetComponent<NetworkManager>();

        Options options = new Options();
        options.Parse(System.Environment.GetCommandLineArgs());

        if(options.forceAntiAliasing) {
            QualitySettings.antiAliasing = options.antiAliasingValue;
        }

        if(options.doHost) {
            StartHost();
        }
        else if(options.doJoin) {
            StartClient(options.hostname);
        }
    }

    public virtual void OnGUI()
    {

        GUILayout.BeginArea(new Rect(0, 0, 200, 300));
        GUILayout.FlexibleSpace();
        GUILayout.BeginVertical("Network", UnityEngine.GUI.skin.window);

        bool connected = m_networkManager.isNetworkActive;

        if(connected) {
            bool disconnect = GUILayout.Button("Disconnect");
            if(disconnect) {
                m_errors = "";
                m_networkManager.StopClient();
                m_networkManager.StopHost();
            }

            var connections = NetworkServer.connections;
            if(connections != null) {
                GUILayout.Space(20);
                GUILayout.Label("Clients:");
                foreach(var conn in NetworkServer.connections) {
                    GUILayout.Label(conn.address);
                }
            }
        }
        else {

            bool allowGetReal3D = Application.isEditor ||
                Environment.GetEnvironmentVariable("GETREAL_CONFIG") != null;

            if(!allowGetReal3D) {
                GUILayout.Label("Please run within getReal3D");
                if(GUILayout.Button("Quit")) {
                    Application.Quit();
                }
            }

            bool startHostingGetReal3D = allowGetReal3D && GUILayout.Button("Host");

            GUILayout.BeginHorizontal();
            bool joinMasterGetReal3D = allowGetReal3D && GUILayout.Button("Join");
            m_serverAddress = GUILayout.TextField(m_serverAddress);
            GUILayout.EndHorizontal();

            if(joinMasterGetReal3D) {
                m_errors = "";
                StartClient(m_serverAddress);
            }

            if(startHostingGetReal3D) {
                m_errors = "";
                StartHost();
            }
        }
        if(!string.IsNullOrEmpty(m_errors)) {
            GUILayout.Label(m_errors);
        }
        GUILayout.EndVertical();
        GUILayout.EndArea();
    }

    private void StartClient(string serverAddress)
    {
        m_serverAddress = serverAddress;
        PlayerPrefs.SetString("server_address", serverAddress);
        PlayerPrefs.Save();
        m_networkManager.networkAddress = serverAddress;
        m_networkManager.StartClient();
    }

    private void StartHost()
    {
        m_networkManager.StartHost();
    }

    void INetworkErrorListener.OnClientError(NetworkConnection conn, int errorCode)
    {
        if(conn != null) {
            AddError("MultiCluster error from server " + conn.address + ". " +
                GetErrorString(errorCode) + ".");
        }
        else {
            AddError("MultiCluster error. " + GetErrorString(errorCode) + ".");
        }
    }

    void INetworkErrorListener.OnServerError(NetworkConnection conn, int errorCode)
    {
        if(conn != null) {
            AddError("MultiCluster error on client " + conn.address + ". " +
                GetErrorString(errorCode) + ".");
        }
        else {
            AddError("MultiCluster error. " + GetErrorString(errorCode) + ".");
        }
    }

    private void AddError(string errorMessage)
    {
        if(!string.IsNullOrEmpty(m_errors)) {
            m_errors += "\n";
        }
        m_errors += errorMessage;
    }

    private static string GetErrorString(int errorCode)
    {
        switch(errorCode) {
        case (int) NetworkError.Ok: return "No error";
        case (int) NetworkError.ConnectionLost: return "Connection lost";
        case (int) NetworkError.ConnectionFailure: return "Connection failed";
        case (int) NetworkError.LicenseError: return "License error";
        }
        return "Unknown error";
    }
}
