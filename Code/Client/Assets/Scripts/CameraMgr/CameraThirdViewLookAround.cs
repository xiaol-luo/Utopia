using UnityEngine;

class CameraThirdViewLookAround : MonoBehaviour
{
    private Camera m_camera = null;
    public float moveSpeed = 300.0f;
    public float angel = 60.0f;
    public float height = 200.0f;
    public float edgeThick = 20.0f;
    void Start()
    {
        Vector3 cameraPos = m_camera.transform.position;
        m_camera.transform.position = new Vector3(cameraPos.x, height, cameraPos.z);
    }
    private void Awake()
    {
        m_camera = this.GetComponent<Camera>();
    }

    const int MOVE_LEFT = -1;
    const int MOVE_RIGHT = 1;
    const int MOVE_UP = 1;
    const int MOVE_BUTTOM = -1;

    public bool isDisableMouse = true;

    private void Update()
    {
    }
    void LateUpdate()
    {
        Vector3 mousePos = Input.mousePosition;
        // Debug.Log(string.Format("mouse pos {0} : sceen{1}:{2}", mousePos, Screen.width, Screen.height));

        if (Input.GetKeyDown(KeyCode.Z))
            isDisableMouse = !isDisableMouse;

        int move_hor = 0;
        int move_veg = 0;

        bool isMoved = false;
        if (!isMoved)
        {
            if (Input.GetKey(KeyCode.LeftArrow))
                move_hor = MOVE_LEFT;
            if (Input.GetKey(KeyCode.RightArrow))
                move_hor = MOVE_RIGHT;
            if (Input.GetKey(KeyCode.DownArrow))
                move_veg = MOVE_BUTTOM;
            if (Input.GetKey(KeyCode.UpArrow))
                move_veg = MOVE_UP;
            isMoved = this.DoMoveCamera(move_hor, move_veg);
        }
        if (!isDisableMouse && !isMoved)
        {
            if (mousePos.x < edgeThick)
                move_hor = MOVE_LEFT;
            if (mousePos.x > Screen.width - edgeThick)
                move_hor = MOVE_RIGHT;
            if (mousePos.y < edgeThick)
                move_veg = MOVE_BUTTOM;
            if (mousePos.y > Screen.height - edgeThick)
                move_veg = MOVE_UP;
            isMoved = this.DoMoveCamera(move_hor, move_veg);
        }
    }

    void FixedUpdate()
    {
        
    }

    bool DoMoveCamera(int move_hor, int move_veg)
    {
        bool isMoved = false;
        if (0 != move_hor || 0 != move_veg)
        {
            float sideMoveSpeed = moveSpeed / (System.Math.Abs(move_hor) + System.Math.Abs(move_veg));
            float move_x = sideMoveSpeed * move_hor * Time.deltaTime;
            float move_y = sideMoveSpeed * move_veg * Time.deltaTime;
            m_camera.transform.eulerAngles = new Vector3(angel, 0, 0);
            Vector3 cameraPos = m_camera.transform.position;
            m_camera.transform.position = new Vector3(cameraPos.x + move_x, height, cameraPos.z + move_y);
            isMoved = true;
        }
        return isMoved;
    }
}
