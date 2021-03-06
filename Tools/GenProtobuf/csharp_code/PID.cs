// <auto-generated>
//     Generated by the protocol buffer compiler.  DO NOT EDIT!
//     source: PID.proto
// </auto-generated>
#pragma warning disable 1591, 0612, 3021
#region Designer generated code

using pb = global::Google.Protobuf;
using pbc = global::Google.Protobuf.Collections;
using pbr = global::Google.Protobuf.Reflection;
using scg = global::System.Collections.Generic;
namespace NetProto {

  /// <summary>Holder for reflection information generated from PID.proto</summary>
  public static partial class PIDReflection {

    #region Descriptor
    /// <summary>File descriptor for PID.proto</summary>
    public static pbr::FileDescriptor Descriptor {
      get { return descriptor; }
    }
    private static pbr::FileDescriptor descriptor;

    static PIDReflection() {
      byte[] descriptorData = global::System.Convert.FromBase64String(
          string.Concat(
            "CglQSUQucHJvdG8SCE5ldFByb3RvKqkFCgNQSUQSCwoHUElEX01pbhAAEgwK",
            "CFBJRF9QaW5nEAESDAoIUElEX1BvbmcQAhIVChFQSURfUXVlcnlGcmVlSGVy",
            "bxBkEhMKD1BJRF9Sc3BGcmVlSGVybxBlEhUKEVBJRF9TZWxlY3RIZXJvUmVx",
            "EGYSFQoRUElEX1NlbGVjdEhlcm9Sc3AQZxIZChVQSURfTG9hZFNjZW5lQ29t",
            "cGxldGUQaBISCg5QSURfTGVhdmVTY2VuZRBpEh0KGFBJRF9TY2VuZU9iamVj",
            "dERpc2FwcGVhchDyBxISCg1QSURfTW92ZVRvUG9zEPwHEhEKDFBJRF9TdG9w",
            "TW92ZRCGCBIXChJQSURfQmF0dGxlT3BlcmFSZXEQzAgSFQoQUElEX1ZpZXdT",
            "bmFwc2hvdBDWCBIVChBQSURfVmlld0FsbEdyaWRzENcIEhkKFFBJRF9WaWV3",
            "U25hcHNob3REaWZmENgIEhcKElBJRF9TY2VuZVVuaXRTdGF0ZRCwCRIbChZQ",
            "SURfU2NlbmVVbml0VHJhbnNmb3JtELEJEhYKEVBJRF9TY2VuZVVuaXRNb3Zl",
            "ELIJEh0KGFBJRF9TY2VuZVVuaXRTa2lsbEFjdGlvbhCzCRIUCg9QSURfQnVs",
            "bGV0U3RhdGUQtAkSGAoTUElEX0J1bGxldFRhcmdldFBvcxC1CRIZChRQSURf",
            "UmVsb2FkTHVhU2NyaXB0cxChHxIZChRQSURfUmVjcmVhdGVTY2VuZVJlcRCi",
            "HxIZChRQSURfUmVjcmVhdGVTY2VuZVJzcBCjHxIYChNQSURfUmVsb2FkQ29u",
            "ZmlnUmVxEKQfEhgKE1BJRF9TY2VuZVRpbWVTeW5SZXEQpR8SGAoTUElEX1Nj",
            "ZW5lVGltZVN5blJzcBCmHxIMCgdQSURfTWF4EIAoQgP4AQFiBnByb3RvMw=="));
      descriptor = pbr::FileDescriptor.FromGeneratedCode(descriptorData,
          new pbr::FileDescriptor[] { },
          new pbr::GeneratedClrTypeInfo(new[] {typeof(global::NetProto.PID), }, null));
    }
    #endregion

  }
  #region Enums
  public enum PID {
    [pbr::OriginalName("PID_Min")] Min = 0,
    [pbr::OriginalName("PID_Ping")] Ping = 1,
    [pbr::OriginalName("PID_Pong")] Pong = 2,
    [pbr::OriginalName("PID_QueryFreeHero")] QueryFreeHero = 100,
    [pbr::OriginalName("PID_RspFreeHero")] RspFreeHero = 101,
    [pbr::OriginalName("PID_SelectHeroReq")] SelectHeroReq = 102,
    [pbr::OriginalName("PID_SelectHeroRsp")] SelectHeroRsp = 103,
    [pbr::OriginalName("PID_LoadSceneComplete")] LoadSceneComplete = 104,
    [pbr::OriginalName("PID_LeaveScene")] LeaveScene = 105,
    [pbr::OriginalName("PID_SceneObjectDisappear")] SceneObjectDisappear = 1010,
    [pbr::OriginalName("PID_MoveToPos")] MoveToPos = 1020,
    [pbr::OriginalName("PID_StopMove")] StopMove = 1030,
    [pbr::OriginalName("PID_BattleOperaReq")] BattleOperaReq = 1100,
    [pbr::OriginalName("PID_ViewSnapshot")] ViewSnapshot = 1110,
    [pbr::OriginalName("PID_ViewAllGrids")] ViewAllGrids = 1111,
    [pbr::OriginalName("PID_ViewSnapshotDiff")] ViewSnapshotDiff = 1112,
    [pbr::OriginalName("PID_SceneUnitState")] SceneUnitState = 1200,
    [pbr::OriginalName("PID_SceneUnitTransform")] SceneUnitTransform = 1201,
    [pbr::OriginalName("PID_SceneUnitMove")] SceneUnitMove = 1202,
    [pbr::OriginalName("PID_SceneUnitSkillAction")] SceneUnitSkillAction = 1203,
    [pbr::OriginalName("PID_BulletState")] BulletState = 1204,
    [pbr::OriginalName("PID_BulletTargetPos")] BulletTargetPos = 1205,
    [pbr::OriginalName("PID_ReloadLuaScripts")] ReloadLuaScripts = 4001,
    [pbr::OriginalName("PID_RecreateSceneReq")] RecreateSceneReq = 4002,
    [pbr::OriginalName("PID_RecreateSceneRsp")] RecreateSceneRsp = 4003,
    [pbr::OriginalName("PID_ReloadConfigReq")] ReloadConfigReq = 4004,
    [pbr::OriginalName("PID_SceneTimeSynReq")] SceneTimeSynReq = 4005,
    [pbr::OriginalName("PID_SceneTimeSynRsp")] SceneTimeSynRsp = 4006,
    [pbr::OriginalName("PID_Max")] Max = 5120,
  }

  #endregion

}

#endregion Designer generated code
