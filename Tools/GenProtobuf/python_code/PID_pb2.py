# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: PID.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf.internal import enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='PID.proto',
  package='NetProto',
  syntax='proto3',
  serialized_options=_b('\370\001\001'),
  serialized_pb=_b('\n\tPID.proto\x12\x08NetProto*\xa9\x05\n\x03PID\x12\x0b\n\x07PID_Min\x10\x00\x12\x0c\n\x08PID_Ping\x10\x01\x12\x0c\n\x08PID_Pong\x10\x02\x12\x15\n\x11PID_QueryFreeHero\x10\x64\x12\x13\n\x0fPID_RspFreeHero\x10\x65\x12\x15\n\x11PID_SelectHeroReq\x10\x66\x12\x15\n\x11PID_SelectHeroRsp\x10g\x12\x19\n\x15PID_LoadSceneComplete\x10h\x12\x12\n\x0ePID_LeaveScene\x10i\x12\x1d\n\x18PID_SceneObjectDisappear\x10\xf2\x07\x12\x12\n\rPID_MoveToPos\x10\xfc\x07\x12\x11\n\x0cPID_StopMove\x10\x86\x08\x12\x17\n\x12PID_BattleOperaReq\x10\xcc\x08\x12\x15\n\x10PID_ViewSnapshot\x10\xd6\x08\x12\x15\n\x10PID_ViewAllGrids\x10\xd7\x08\x12\x19\n\x14PID_ViewSnapshotDiff\x10\xd8\x08\x12\x17\n\x12PID_SceneUnitState\x10\xb0\t\x12\x1b\n\x16PID_SceneUnitTransform\x10\xb1\t\x12\x16\n\x11PID_SceneUnitMove\x10\xb2\t\x12\x1d\n\x18PID_SceneUnitSkillAction\x10\xb3\t\x12\x14\n\x0fPID_BulletState\x10\xb4\t\x12\x18\n\x13PID_BulletTargetPos\x10\xb5\t\x12\x19\n\x14PID_ReloadLuaScripts\x10\xa1\x1f\x12\x19\n\x14PID_RecreateSceneReq\x10\xa2\x1f\x12\x19\n\x14PID_RecreateSceneRsp\x10\xa3\x1f\x12\x18\n\x13PID_ReloadConfigReq\x10\xa4\x1f\x12\x18\n\x13PID_SceneTimeSynReq\x10\xa5\x1f\x12\x18\n\x13PID_SceneTimeSynRsp\x10\xa6\x1f\x12\x0c\n\x07PID_Max\x10\x80(B\x03\xf8\x01\x01\x62\x06proto3')
)

_PID = _descriptor.EnumDescriptor(
  name='PID',
  full_name='NetProto.PID',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='PID_Min', index=0, number=0,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PID_Ping', index=1, number=1,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PID_Pong', index=2, number=2,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PID_QueryFreeHero', index=3, number=100,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PID_RspFreeHero', index=4, number=101,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PID_SelectHeroReq', index=5, number=102,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PID_SelectHeroRsp', index=6, number=103,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PID_LoadSceneComplete', index=7, number=104,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PID_LeaveScene', index=8, number=105,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PID_SceneObjectDisappear', index=9, number=1010,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PID_MoveToPos', index=10, number=1020,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PID_StopMove', index=11, number=1030,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PID_BattleOperaReq', index=12, number=1100,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PID_ViewSnapshot', index=13, number=1110,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PID_ViewAllGrids', index=14, number=1111,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PID_ViewSnapshotDiff', index=15, number=1112,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PID_SceneUnitState', index=16, number=1200,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PID_SceneUnitTransform', index=17, number=1201,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PID_SceneUnitMove', index=18, number=1202,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PID_SceneUnitSkillAction', index=19, number=1203,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PID_BulletState', index=20, number=1204,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PID_BulletTargetPos', index=21, number=1205,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PID_ReloadLuaScripts', index=22, number=4001,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PID_RecreateSceneReq', index=23, number=4002,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PID_RecreateSceneRsp', index=24, number=4003,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PID_ReloadConfigReq', index=25, number=4004,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PID_SceneTimeSynReq', index=26, number=4005,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PID_SceneTimeSynRsp', index=27, number=4006,
      serialized_options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PID_Max', index=28, number=5120,
      serialized_options=None,
      type=None),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=24,
  serialized_end=705,
)
_sym_db.RegisterEnumDescriptor(_PID)

PID = enum_type_wrapper.EnumTypeWrapper(_PID)
PID_Min = 0
PID_Ping = 1
PID_Pong = 2
PID_QueryFreeHero = 100
PID_RspFreeHero = 101
PID_SelectHeroReq = 102
PID_SelectHeroRsp = 103
PID_LoadSceneComplete = 104
PID_LeaveScene = 105
PID_SceneObjectDisappear = 1010
PID_MoveToPos = 1020
PID_StopMove = 1030
PID_BattleOperaReq = 1100
PID_ViewSnapshot = 1110
PID_ViewAllGrids = 1111
PID_ViewSnapshotDiff = 1112
PID_SceneUnitState = 1200
PID_SceneUnitTransform = 1201
PID_SceneUnitMove = 1202
PID_SceneUnitSkillAction = 1203
PID_BulletState = 1204
PID_BulletTargetPos = 1205
PID_ReloadLuaScripts = 4001
PID_RecreateSceneReq = 4002
PID_RecreateSceneRsp = 4003
PID_ReloadConfigReq = 4004
PID_SceneTimeSynReq = 4005
PID_SceneTimeSynRsp = 4006
PID_Max = 5120


DESCRIPTOR.enum_types_by_name['PID'] = _PID
_sym_db.RegisterFileDescriptor(DESCRIPTOR)


DESCRIPTOR._options = None
# @@protoc_insertion_point(module_scope)
