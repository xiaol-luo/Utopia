# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: Battle.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf.internal import enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='Battle.proto',
  package='NetProto',
  syntax='proto3',
  serialized_pb=_b('\n\x0c\x42\x61ttle.proto\x12\x08NetProto\"8\n\x0bRspFreeHero\x12\x13\n\x0bred_hero_id\x18\x01 \x01(\x04\x12\x14\n\x0c\x62lue_hero_id\x18\x02 \x01(\x04\" \n\rSelectHeroReq\x12\x0f\n\x07hero_id\x18\x01 \x01(\x04\"1\n\rSelectHeroRsp\x12\x0f\n\x07hero_id\x18\x01 \x01(\x04\x12\x0f\n\x07is_succ\x18\x02 \x01(\x08\"[\n\x0bSceneObject\x12\r\n\x05objid\x18\x01 \x01(\x04\x12+\n\x08obj_type\x18\x02 \x01(\x0e\x32\x19.NetProto.SceneObjectType\x12\x10\n\x08model_id\x18\x03 \x01(\x05\"5\n\x0e\x41llSceneObject\x12#\n\x04objs\x18\x01 \x03(\x0b\x32\x15.NetProto.SceneObject*;\n\x0fSceneObjectType\x12\x0c\n\x08\x42uilding\x10\x00\x12\x08\n\x04Hero\x10\x01\x12\x07\n\x03Npc\x10\x02\x12\x07\n\x03MAX\x10\x03\x42\x03\xf8\x01\x01\x62\x06proto3')
)

_SCENEOBJECTTYPE = _descriptor.EnumDescriptor(
  name='SceneObjectType',
  full_name='NetProto.SceneObjectType',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='Building', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='Hero', index=1, number=1,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='Npc', index=2, number=2,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MAX', index=3, number=3,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=317,
  serialized_end=376,
)
_sym_db.RegisterEnumDescriptor(_SCENEOBJECTTYPE)

SceneObjectType = enum_type_wrapper.EnumTypeWrapper(_SCENEOBJECTTYPE)
Building = 0
Hero = 1
Npc = 2
MAX = 3



_RSPFREEHERO = _descriptor.Descriptor(
  name='RspFreeHero',
  full_name='NetProto.RspFreeHero',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='red_hero_id', full_name='NetProto.RspFreeHero.red_hero_id', index=0,
      number=1, type=4, cpp_type=4, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='blue_hero_id', full_name='NetProto.RspFreeHero.blue_hero_id', index=1,
      number=2, type=4, cpp_type=4, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=26,
  serialized_end=82,
)


_SELECTHEROREQ = _descriptor.Descriptor(
  name='SelectHeroReq',
  full_name='NetProto.SelectHeroReq',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='hero_id', full_name='NetProto.SelectHeroReq.hero_id', index=0,
      number=1, type=4, cpp_type=4, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=84,
  serialized_end=116,
)


_SELECTHERORSP = _descriptor.Descriptor(
  name='SelectHeroRsp',
  full_name='NetProto.SelectHeroRsp',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='hero_id', full_name='NetProto.SelectHeroRsp.hero_id', index=0,
      number=1, type=4, cpp_type=4, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='is_succ', full_name='NetProto.SelectHeroRsp.is_succ', index=1,
      number=2, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=118,
  serialized_end=167,
)


_SCENEOBJECT = _descriptor.Descriptor(
  name='SceneObject',
  full_name='NetProto.SceneObject',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='objid', full_name='NetProto.SceneObject.objid', index=0,
      number=1, type=4, cpp_type=4, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='obj_type', full_name='NetProto.SceneObject.obj_type', index=1,
      number=2, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='model_id', full_name='NetProto.SceneObject.model_id', index=2,
      number=3, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=169,
  serialized_end=260,
)


_ALLSCENEOBJECT = _descriptor.Descriptor(
  name='AllSceneObject',
  full_name='NetProto.AllSceneObject',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='objs', full_name='NetProto.AllSceneObject.objs', index=0,
      number=1, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=262,
  serialized_end=315,
)

_SCENEOBJECT.fields_by_name['obj_type'].enum_type = _SCENEOBJECTTYPE
_ALLSCENEOBJECT.fields_by_name['objs'].message_type = _SCENEOBJECT
DESCRIPTOR.message_types_by_name['RspFreeHero'] = _RSPFREEHERO
DESCRIPTOR.message_types_by_name['SelectHeroReq'] = _SELECTHEROREQ
DESCRIPTOR.message_types_by_name['SelectHeroRsp'] = _SELECTHERORSP
DESCRIPTOR.message_types_by_name['SceneObject'] = _SCENEOBJECT
DESCRIPTOR.message_types_by_name['AllSceneObject'] = _ALLSCENEOBJECT
DESCRIPTOR.enum_types_by_name['SceneObjectType'] = _SCENEOBJECTTYPE
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

RspFreeHero = _reflection.GeneratedProtocolMessageType('RspFreeHero', (_message.Message,), dict(
  DESCRIPTOR = _RSPFREEHERO,
  __module__ = 'Battle_pb2'
  # @@protoc_insertion_point(class_scope:NetProto.RspFreeHero)
  ))
_sym_db.RegisterMessage(RspFreeHero)

SelectHeroReq = _reflection.GeneratedProtocolMessageType('SelectHeroReq', (_message.Message,), dict(
  DESCRIPTOR = _SELECTHEROREQ,
  __module__ = 'Battle_pb2'
  # @@protoc_insertion_point(class_scope:NetProto.SelectHeroReq)
  ))
_sym_db.RegisterMessage(SelectHeroReq)

SelectHeroRsp = _reflection.GeneratedProtocolMessageType('SelectHeroRsp', (_message.Message,), dict(
  DESCRIPTOR = _SELECTHERORSP,
  __module__ = 'Battle_pb2'
  # @@protoc_insertion_point(class_scope:NetProto.SelectHeroRsp)
  ))
_sym_db.RegisterMessage(SelectHeroRsp)

SceneObject = _reflection.GeneratedProtocolMessageType('SceneObject', (_message.Message,), dict(
  DESCRIPTOR = _SCENEOBJECT,
  __module__ = 'Battle_pb2'
  # @@protoc_insertion_point(class_scope:NetProto.SceneObject)
  ))
_sym_db.RegisterMessage(SceneObject)

AllSceneObject = _reflection.GeneratedProtocolMessageType('AllSceneObject', (_message.Message,), dict(
  DESCRIPTOR = _ALLSCENEOBJECT,
  __module__ = 'Battle_pb2'
  # @@protoc_insertion_point(class_scope:NetProto.AllSceneObject)
  ))
_sym_db.RegisterMessage(AllSceneObject)


DESCRIPTOR.has_options = True
DESCRIPTOR._options = _descriptor._ParseOptions(descriptor_pb2.FileOptions(), _b('\370\001\001'))
# @@protoc_insertion_point(module_scope)