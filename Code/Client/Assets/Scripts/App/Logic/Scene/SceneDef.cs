using UnityEngine;
using UnityEditor;

namespace Utopia
{
    public class SceneDef
    {
        public const int InLogic_GameFrame = 30;
        public const int InBattle_GameFrame = -1;
    }

    public class SceneEventDef
    {
        public const string MouseHitGround = "MouseHitGround";
    }

    public class SuEventDef
    {
        public const string MsgSceneUnitMove = "MsgSceneUnitMove";
        public const string MsgSceneUnitSkillAction = "MsgSceneUnitSkillAction";
        public const string MsgSceneUnitTransform = "MsgSceneUnitTransform";

        public const string MsgBulletState = "MsgBulletTargetPos";
        public const string MsgBulletTargetPos = "MsgBulletTargetPos";
    }
}
