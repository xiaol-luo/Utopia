using NetProto;
using UnityEngine;
using Utopia;

namespace Utopia
{
    public partial class Scene
    {
        int m_clickBtnTiems = 0;
        void CheckPlayerInput()
        {
            const int Mouse_Left_Click = 0;
            const int Mouse_Right_Click = 1;

            if (Input.anyKey)
            {

            }

            if (Input.GetKeyDown(KeyCode.S))
            {
                this.StopAction();
            }

            if (Input.GetKeyDown(KeyCode.Q))
            {
                Vector3 hitGound = Vector3.zero;
                bool isOk = SceneUtils.ScreenToGround(sceneCamera.camera, Input.mousePosition, ref hitGound);
                if (isOk)
                {
                    this.CastSkill(ESkillSlot.EssQslot, targetSuid, hitGound);
                }
            }
            if (Input.GetKeyDown(KeyCode.W))
            {
                ++m_clickBtnTiems;
                Core.instance.log.LogDebug("CheckPlayerInput {0}", m_clickBtnTiems);

                Vector3 hitGound = Vector3.zero;
                bool isOk = SceneUtils.ScreenToGround(sceneCamera.camera, Input.mousePosition, ref hitGound);
                if (isOk)
                {
                    this.CastSkill(ESkillSlot.EssWslot, targetSuid, hitGound);
                }
            }
            if (Input.GetKeyDown(KeyCode.F))
            {
                this.TraceUnit(targetSuid);
            }
            if (Input.GetKeyDown(KeyCode.R))
            {
                ReloadLuaScripts msg = new ReloadLuaScripts();
                msg.Scripts.Add("_load_files_effect_script");
                App.instance.net.gameSrv.Send(PID.ReloadLuaScripts, msg);
            }

        }
    }
}
