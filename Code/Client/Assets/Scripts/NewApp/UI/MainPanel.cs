using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using Utopia;

public class MainPanel : MonoBehaviour {

    [SerializeField]
    Button connectBtn;

    [SerializeField]
    Button disconnectBtn;

    [SerializeField]
    InputField ipTxt;

    [SerializeField]
    InputField portTxt;

    void Start() {
        connectBtn.onClick.AddListener(() => {
            NewApp.instance.netModule.gameSrv.Connect(ipTxt.text, int.Parse(portTxt.text));
        });

        disconnectBtn.onClick.AddListener(() => {
            NewApp.instance.netModule.gameSrv.Close();
        });

    }
}
