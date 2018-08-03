# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: Gm.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='Gm.proto',
  package='NetProto',
  syntax='proto3',
  serialized_options=_b('\370\001\001'),
  serialized_pb=_b('\n\x08Gm.proto\x12\x08NetProto\"#\n\x10ReloadLuaScripts\x12\x0f\n\x07scripts\x18\x01 \x03(\t\"&\n\x10RecreateSceneReq\x12\x12\n\nscene_name\x18\x01 \x01(\t\"#\n\x10RecreateSceneRsp\x12\x0f\n\x07is_succ\x18\x01 \x01(\x08\x42\x03\xf8\x01\x01\x62\x06proto3')
)




_RELOADLUASCRIPTS = _descriptor.Descriptor(
  name='ReloadLuaScripts',
  full_name='NetProto.ReloadLuaScripts',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='scripts', full_name='NetProto.ReloadLuaScripts.scripts', index=0,
      number=1, type=9, cpp_type=9, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=22,
  serialized_end=57,
)


_RECREATESCENEREQ = _descriptor.Descriptor(
  name='RecreateSceneReq',
  full_name='NetProto.RecreateSceneReq',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='scene_name', full_name='NetProto.RecreateSceneReq.scene_name', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=59,
  serialized_end=97,
)


_RECREATESCENERSP = _descriptor.Descriptor(
  name='RecreateSceneRsp',
  full_name='NetProto.RecreateSceneRsp',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='is_succ', full_name='NetProto.RecreateSceneRsp.is_succ', index=0,
      number=1, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=99,
  serialized_end=134,
)

DESCRIPTOR.message_types_by_name['ReloadLuaScripts'] = _RELOADLUASCRIPTS
DESCRIPTOR.message_types_by_name['RecreateSceneReq'] = _RECREATESCENEREQ
DESCRIPTOR.message_types_by_name['RecreateSceneRsp'] = _RECREATESCENERSP
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

ReloadLuaScripts = _reflection.GeneratedProtocolMessageType('ReloadLuaScripts', (_message.Message,), dict(
  DESCRIPTOR = _RELOADLUASCRIPTS,
  __module__ = 'Gm_pb2'
  # @@protoc_insertion_point(class_scope:NetProto.ReloadLuaScripts)
  ))
_sym_db.RegisterMessage(ReloadLuaScripts)

RecreateSceneReq = _reflection.GeneratedProtocolMessageType('RecreateSceneReq', (_message.Message,), dict(
  DESCRIPTOR = _RECREATESCENEREQ,
  __module__ = 'Gm_pb2'
  # @@protoc_insertion_point(class_scope:NetProto.RecreateSceneReq)
  ))
_sym_db.RegisterMessage(RecreateSceneReq)

RecreateSceneRsp = _reflection.GeneratedProtocolMessageType('RecreateSceneRsp', (_message.Message,), dict(
  DESCRIPTOR = _RECREATESCENERSP,
  __module__ = 'Gm_pb2'
  # @@protoc_insertion_point(class_scope:NetProto.RecreateSceneRsp)
  ))
_sym_db.RegisterMessage(RecreateSceneRsp)


DESCRIPTOR._options = None
# @@protoc_insertion_point(module_scope)
