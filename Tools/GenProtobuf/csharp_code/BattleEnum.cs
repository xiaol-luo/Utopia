// <auto-generated>
//     Generated by the protocol buffer compiler.  DO NOT EDIT!
//     source: BattleEnum.proto
// </auto-generated>
#pragma warning disable 1591, 0612, 3021
#region Designer generated code

using pb = global::Google.Protobuf;
using pbc = global::Google.Protobuf.Collections;
using pbr = global::Google.Protobuf.Reflection;
using scg = global::System.Collections.Generic;
namespace NetProto {

  /// <summary>Holder for reflection information generated from BattleEnum.proto</summary>
  public static partial class BattleEnumReflection {

    #region Descriptor
    /// <summary>File descriptor for BattleEnum.proto</summary>
    public static pbr::FileDescriptor Descriptor {
      get { return descriptor; }
    }
    private static pbr::FileDescriptor descriptor;

    static BattleEnumReflection() {
      byte[] descriptorData = global::System.Convert.FromBase64String(
          string.Concat(
            "ChBCYXR0bGVFbnVtLnByb3RvEghOZXRQcm90byo1CglFVW5pdFR5cGUSDAoI",
            "QnVpbGRpbmcQABIICgRIZXJvEAESBwoDTnBjEAISBwoDTUFYEAMq4AEKD0VN",
            "b3ZlQWdlbnRTdGF0ZRIYChRFTW92ZUFnZW50U3RhdGVfSWRsZRAAEh0KGUVN",
            "b3ZlQWdlbnRTdGF0ZV9Nb3ZlVG9Qb3MQARIdChlFTW92ZUFnZW50U3RhdGVf",
            "TW92ZVRvRGlyEAISHwobRU1vdmVBZ2VudFN0YXRlX0ltbW9iaWxpemVkEAMS",
            "HQoZRU1vdmVBZ2VudFN0YXRlX0ZvcmNlTGluZRAEEhwKGEVNb3ZlQWdlbnRT",
            "dGF0ZV9Gb3JjZVBvcxAFEhcKE0VNb3ZlQWdlbnRTdGF0ZV9NYXgQBipsCgpF",
            "TW92ZVN0YXRlEhMKD0VNb3ZlU3RhdGVfSWRsZRAAEhMKD0VNb3ZlU3RhdGVf",
            "TW92ZRABEhoKFkVNb3ZlU3RhdGVfSW1tb2JpbGl6ZWQQAhIYChRFTW92ZVN0",
            "YXRlX0ZvcmNlTW92ZRADKp4BCgxFUGxheWVyT3BlcmESDwoLRVBPX0ludmFs",
            "aWQQABIMCghFUE9fU3RvcBABEgwKCEVQT19Nb3ZlEAISDgoKRVBPX0ZvbGxv",
            "dxADEgwKCEVQT19IdW50EAQSEQoNRVBPX0Nhc3RTa2lsbBAFEg8KC0VQT19V",
            "c2VJdGVtEAYSDQoJRVBPX1RyYWNlEAcSEAoMRUJPX01heENvdW50ECAq5AIK",
            "C0VGaWdodFBhcmFtEgwKCEVGUF9Ob25lEAASCgoGRUZQX0hQEAESCgoGRUZQ",
            "X01QEAISDQoJRUZQX01heEhQEAkSDQoJRUZQX01heE1QEAoSEQoNRUZQX01v",
            "dmVTcGVlZBALEhIKDkVGUF9BdHRhY2tEaXN0EAwSEwoPRUZQX0F0dGFja1Nw",
            "ZWVkEA0SEQoNRUZQX1BoeUF0dGFjaxAOEhMKD0VGUF9NYWdpY0F0dGFjaxAP",
            "Eg8KC0VGUF9QaHlIdXJ0EBASEQoNRUZQX01hZ2ljSHVydBAREhIKDkVGUF9Q",
            "aHlEZWZlbnNlEBISFAoQRUZQX01hZ2ljRGVmZW5zZRATEg0KCUVGUF9EaXp6",
            "eRAUEg8KC0VGUF9TaWxlbmNlEBUSDQoJRUZQX0JsaW5kEBYSEwoPRUZQX0lt",
            "bW9iaWxpemVkEBcSDAoIRUZQX0RlYWQQGBINCglFRlBfQ09VTlQQICryAQoK",
            "RVNraWxsU2xvdBINCglFU1NfUVNsb3QQABINCglFU1NfV1Nsb3QQARINCglF",
            "U1NfRVNsb3QQAhINCglFU1NfUlNsb3QQAxINCglFU1NfRlNsb3QQBBINCglF",
            "U1NfR1Nsb3QQBRINCglFU1NfUFNsb3QQBhIPCgtFU1NfT25lU2xvdBALEg8K",
            "C0VTU19Ud29TbG90EAwSEQoNRVNTX1RocmVlU2xvdBANEhAKDEVTU19Gb3Vy",
            "U2xvdBAOEhAKDEVTU19GaXZlU2xvdBAPEg8KC0VTU19TaXhTbG90EBASEQoN",
            "RVNTX1NldmVuU2xvdBARKjcKCUVTa2lsbEJhchIVChFFU2tpbGxCYXJfRGVm",
            "YXVsdBAAEhMKD0VTa2lsbEJhcl9FeHRyYRABKnMKC0VTa2lsbFN0YXRlEg8K",
            "C0VTU19SZWFkeUdvEAASEQoNRVNTX1ByZXBhcmluZxABEhEKDUVTU19SZWxl",
            "YXNpbmcQAhIPCgtFU1NfR3VpZGluZxADEg8KC0VTU19MYXN0aW5nEAQSCwoH",
            "RVNTX0VuZBAFKn0KDEVTa2lsbFVzZVdheRIaChZFU2tpbGxVc2VXYXlfU2Nl",
            "bmVVbml0EAASGgoWRVNraWxsVXNlV2F5X0RpcmVjdGlvbhABEhkKFUVTa2ls",
            "bFVzZVdheV9Qb3NpdGlvbhACEhoKFkVTa2lsbFVzZVdheV9Qb3NBbmREaXIQ",
            "AyqLAQoSRVNjZW5lVW5pdFJlbGF0aW9uEhsKF0VTY2VuZVVuaXRSZWxhdGlv",
            "bl9Ob25lEAASGwoXRVNjZW5lVW5pdFJlbGF0aW9uX1NlbGYQARIdChlFU2Nl",
            "bmVVbml0UmVsYXRpb25fRnJpZW5kEAISHAoYRVNjZW5lVW5pdFJlbGF0aW9u",
            "X0VuZW15EAMqeQoORVNjZW5lVW5pdENhbXASFgoSRVNjZW5lVW5pdENhbXBf",
            "UmVkEAASFwoTRVNjZW5lVW5pdENhbXBfQmx1ZRABEhoKFkVTY2VuZVVuaXRD",
            "YW1wX01vbnN0ZXIQAhIaChZFU2NlbmVVbml0Q2FtcF9OZXV0cmFsEAMqtQEK",
            "DkVTY2VuZVVuaXRUeXBlEhoKFkVzY2VuZVVuaXRUeXBlX1Vua25vd24QABIX",
            "ChNFc2NlbmVVbml0VHlwZV9IZXJvEAESGgoWRXNjZW5lVW5pdFR5cGVfU29s",
            "ZGllchACEhoKFkVzY2VuZVVuaXRUeXBlX01vbnN0ZXIQAxIbChdFc2NlbmVV",
            "bml0VHlwZV9CdWlsZGluZxAEEhkKFUVzY2VuZVVuaXRUeXBlX0VmZmVjdBAF",
            "QgP4AQFiBnByb3RvMw=="));
      descriptor = pbr::FileDescriptor.FromGeneratedCode(descriptorData,
          new pbr::FileDescriptor[] { },
          new pbr::GeneratedClrTypeInfo(new[] {typeof(global::NetProto.EUnitType), typeof(global::NetProto.EMoveAgentState), typeof(global::NetProto.EMoveState), typeof(global::NetProto.EPlayerOpera), typeof(global::NetProto.EFightParam), typeof(global::NetProto.ESkillSlot), typeof(global::NetProto.ESkillBar), typeof(global::NetProto.ESkillState), typeof(global::NetProto.ESkillUseWay), typeof(global::NetProto.ESceneUnitRelation), typeof(global::NetProto.ESceneUnitCamp), typeof(global::NetProto.ESceneUnitType), }, null));
    }
    #endregion

  }
  #region Enums
  public enum EUnitType {
    [pbr::OriginalName("Building")] Building = 0,
    [pbr::OriginalName("Hero")] Hero = 1,
    [pbr::OriginalName("Npc")] Npc = 2,
    [pbr::OriginalName("MAX")] Max = 3,
  }

  public enum EMoveAgentState {
    [pbr::OriginalName("EMoveAgentState_Idle")] Idle = 0,
    [pbr::OriginalName("EMoveAgentState_MoveToPos")] MoveToPos = 1,
    [pbr::OriginalName("EMoveAgentState_MoveToDir")] MoveToDir = 2,
    [pbr::OriginalName("EMoveAgentState_Immobilized")] Immobilized = 3,
    [pbr::OriginalName("EMoveAgentState_ForceLine")] ForceLine = 4,
    [pbr::OriginalName("EMoveAgentState_ForcePos")] ForcePos = 5,
    [pbr::OriginalName("EMoveAgentState_Max")] Max = 6,
  }

  public enum EMoveState {
    [pbr::OriginalName("EMoveState_Idle")] Idle = 0,
    [pbr::OriginalName("EMoveState_Move")] Move = 1,
    [pbr::OriginalName("EMoveState_Immobilized")] Immobilized = 2,
    [pbr::OriginalName("EMoveState_ForceMove")] ForceMove = 3,
  }

  public enum EPlayerOpera {
    [pbr::OriginalName("EPO_Invalid")] EpoInvalid = 0,
    [pbr::OriginalName("EPO_Stop")] EpoStop = 1,
    [pbr::OriginalName("EPO_Move")] EpoMove = 2,
    [pbr::OriginalName("EPO_Follow")] EpoFollow = 3,
    [pbr::OriginalName("EPO_Hunt")] EpoHunt = 4,
    [pbr::OriginalName("EPO_CastSkill")] EpoCastSkill = 5,
    [pbr::OriginalName("EPO_UseItem")] EpoUseItem = 6,
    [pbr::OriginalName("EPO_Trace")] EpoTrace = 7,
    [pbr::OriginalName("EBO_MaxCount")] EboMaxCount = 32,
  }

  public enum EFightParam {
    [pbr::OriginalName("EFP_None")] EfpNone = 0,
    /// <summary>
    /// 当前血量
    /// </summary>
    [pbr::OriginalName("EFP_HP")] EfpHp = 1,
    /// <summary>
    /// 当前魔法
    /// </summary>
    [pbr::OriginalName("EFP_MP")] EfpMp = 2,
    /// <summary>
    /// 最大血量			
    /// </summary>
    [pbr::OriginalName("EFP_MaxHP")] EfpMaxHp = 9,
    /// <summary>
    /// 最大魔法
    /// </summary>
    [pbr::OriginalName("EFP_MaxMP")] EfpMaxMp = 10,
    /// <summary>
    /// 移动速度
    /// </summary>
    [pbr::OriginalName("EFP_MoveSpeed")] EfpMoveSpeed = 11,
    /// <summary>
    /// 射程
    /// </summary>
    [pbr::OriginalName("EFP_AttackDist")] EfpAttackDist = 12,
    /// <summary>
    /// 攻击速度
    /// </summary>
    [pbr::OriginalName("EFP_AttackSpeed")] EfpAttackSpeed = 13,
    /// <summary>
    /// 物理攻击
    /// </summary>
    [pbr::OriginalName("EFP_PhyAttack")] EfpPhyAttack = 14,
    /// <summary>
    /// 法术攻击	
    /// </summary>
    [pbr::OriginalName("EFP_MagicAttack")] EfpMagicAttack = 15,
    /// <summary>
    /// 物强
    /// </summary>
    [pbr::OriginalName("EFP_PhyHurt")] EfpPhyHurt = 16,
    /// <summary>
    /// 法强
    /// </summary>
    [pbr::OriginalName("EFP_MagicHurt")] EfpMagicHurt = 17,
    /// <summary>
    /// 物抗
    /// </summary>
    [pbr::OriginalName("EFP_PhyDefense")] EfpPhyDefense = 18,
    /// <summary>
    /// 魔抗
    /// </summary>
    [pbr::OriginalName("EFP_MagicDefense")] EfpMagicDefense = 19,
    /// <summary>
    /// 眩晕
    /// </summary>
    [pbr::OriginalName("EFP_Dizzy")] EfpDizzy = 20,
    /// <summary>
    /// 沉默
    /// </summary>
    [pbr::OriginalName("EFP_Silence")] EfpSilence = 21,
    /// <summary>
    /// 致盲
    /// </summary>
    [pbr::OriginalName("EFP_Blind")] EfpBlind = 22,
    /// <summary>
    /// 定身
    /// </summary>
    [pbr::OriginalName("EFP_Immobilized")] EfpImmobilized = 23,
    /// <summary>
    /// 死亡
    /// </summary>
    [pbr::OriginalName("EFP_Dead")] EfpDead = 24,
    [pbr::OriginalName("EFP_COUNT")] EfpCount = 32,
  }

  public enum ESkillSlot {
    [pbr::OriginalName("ESS_QSlot")] EssQslot = 0,
    [pbr::OriginalName("ESS_WSlot")] EssWslot = 1,
    [pbr::OriginalName("ESS_ESlot")] EssEslot = 2,
    [pbr::OriginalName("ESS_RSlot")] EssRslot = 3,
    /// <summary>
    /// 召唤师技能1
    /// </summary>
    [pbr::OriginalName("ESS_FSlot")] EssFslot = 4,
    /// <summary>
    /// 召唤师技能2
    /// </summary>
    [pbr::OriginalName("ESS_GSlot")] EssGslot = 5,
    /// <summary>
    /// 被动
    /// </summary>
    [pbr::OriginalName("ESS_PSlot")] EssPslot = 6,
    [pbr::OriginalName("ESS_OneSlot")] EssOneSlot = 11,
    [pbr::OriginalName("ESS_TwoSlot")] EssTwoSlot = 12,
    [pbr::OriginalName("ESS_ThreeSlot")] EssThreeSlot = 13,
    [pbr::OriginalName("ESS_FourSlot")] EssFourSlot = 14,
    [pbr::OriginalName("ESS_FiveSlot")] EssFiveSlot = 15,
    [pbr::OriginalName("ESS_SixSlot")] EssSixSlot = 16,
    [pbr::OriginalName("ESS_SevenSlot")] EssSevenSlot = 17,
  }

  public enum ESkillBar {
    [pbr::OriginalName("ESkillBar_Default")] Default = 0,
    [pbr::OriginalName("ESkillBar_Extra")] Extra = 1,
  }

  public enum ESkillState {
    /// <summary>
    /// 准备好释放
    /// </summary>
    [pbr::OriginalName("ESS_ReadyGo")] EssReadyGo = 0,
    /// <summary>
    /// 吟唱
    /// </summary>
    [pbr::OriginalName("ESS_Preparing")] EssPreparing = 1,
    /// <summary>
    /// 前摇
    /// </summary>
    [pbr::OriginalName("ESS_Releasing")] EssReleasing = 2,
    /// <summary>
    /// 引导
    /// </summary>
    [pbr::OriginalName("ESS_Guiding")] EssGuiding = 3,
    /// <summary>
    /// 后摇
    /// </summary>
    [pbr::OriginalName("ESS_Lasting")] EssLasting = 4,
    /// <summary>
    /// 结束
    /// </summary>
    [pbr::OriginalName("ESS_End")] EssEnd = 5,
  }

  public enum ESkillUseWay {
    [pbr::OriginalName("ESkillUseWay_SceneUnit")] SceneUnit = 0,
    [pbr::OriginalName("ESkillUseWay_Direction")] Direction = 1,
    [pbr::OriginalName("ESkillUseWay_Position")] Position = 2,
    [pbr::OriginalName("ESkillUseWay_PosAndDir")] PosAndDir = 3,
  }

  public enum ESceneUnitRelation {
    [pbr::OriginalName("ESceneUnitRelation_None")] None = 0,
    [pbr::OriginalName("ESceneUnitRelation_Self")] Self = 1,
    [pbr::OriginalName("ESceneUnitRelation_Friend")] Friend = 2,
    [pbr::OriginalName("ESceneUnitRelation_Enemy")] Enemy = 3,
  }

  public enum ESceneUnitCamp {
    [pbr::OriginalName("ESceneUnitCamp_Red")] Red = 0,
    [pbr::OriginalName("ESceneUnitCamp_Blue")] Blue = 1,
    [pbr::OriginalName("ESceneUnitCamp_Monster")] Monster = 2,
    /// <summary>
    /// 中立的
    /// </summary>
    [pbr::OriginalName("ESceneUnitCamp_Neutral")] Neutral = 3,
  }

  public enum ESceneUnitType {
    [pbr::OriginalName("EsceneUnitType_Unknown")] Unknown = 0,
    [pbr::OriginalName("EsceneUnitType_Hero")] Hero = 1,
    [pbr::OriginalName("EsceneUnitType_Soldier")] Soldier = 2,
    [pbr::OriginalName("EsceneUnitType_Monster")] Monster = 3,
    [pbr::OriginalName("EsceneUnitType_Building")] Building = 4,
    /// <summary>
    /// 用于展示effect效果的，比如子弹、技能预警
    /// </summary>
    [pbr::OriginalName("EsceneUnitType_Effect")] Effect = 5,
  }

  #endregion

}

#endregion Designer generated code
