using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UIConnectServer : MonoBehaviour
{
    [SerializeField]
    protected Button commitBtn;
    [SerializeField]
    protected InputField ipTxt;
    [SerializeField]
    protected InputField portTxt;
    [SerializeField]
    protected Text errMsgTxt;  

    public string ip
    {
        get { return ipTxt.text; }
        set { ipTxt.text = value; }
    }
    public string port
    {
        get { return portTxt.text; }
        set { portTxt.text = value; }
    }
    public string errMsg
    {
        get { return errMsgTxt.text; }
        set { errMsgTxt.text = value; }
    }

    void Start ()
    {
        commitBtn.onClick.AddListener(this.OnClickBtn);
    }
	
	// Update is called once per frame
	void Update ()
    {
		
	}

    void OnClickBtn()
    {
        int port = int.Parse(portTxt.text);
        App.my.gameNetwork.Connect(ipTxt.text, port);
    }
}
