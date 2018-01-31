# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: try.proto

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
  name='try.proto',
  package='NetProto',
  syntax='proto3',
  serialized_pb=_b('\n\ttry.proto\x12\x08NetProto\"#\n\x07TryItem\x12\n\n\x02id\x18\x01 \x01(\x05\x12\x0c\n\x04name\x18\x02 \x01(\t\"\xa2\x02\n\x06TryMsg\x12\x0f\n\x07int_val\x18\x01 \x01(\x05\x12\x0f\n\x07str_val\x18\x02 \x01(\t\x12\"\n\x07msg_val\x18\x03 \x01(\x0b\x32\x11.NetProto.TryItem\x12#\n\x08\x65num_val\x18\x04 \x01(\x0e\x32\x11.NetProto.TryEnum\x12\x33\n\rnest_enum_val\x18\x05 \x01(\x0e\x32\x1c.NetProto.TryMsg.TryNestEnum\x12$\n\tmsg_array\x18\x06 \x03(\x0b\x32\x11.NetProto.TryItem\x12\x35\n\x0fnest_enum_array\x18\x07 \x03(\x0e\x32\x1c.NetProto.TryMsg.TryNestEnum\"\x1b\n\x0bTryNestEnum\x12\x05\n\x01\x61\x10\x00\x12\x05\n\x01\x62\x10\x01*\x17\n\x07TryEnum\x12\x05\n\x01\x61\x10\x00\x12\x05\n\x01\x62\x10\x01\x42\x03\xf8\x01\x01\x62\x06proto3')
)

_TRYENUM = _descriptor.EnumDescriptor(
  name='TryEnum',
  full_name='NetProto.TryEnum',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='a', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='b', index=1, number=1,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=353,
  serialized_end=376,
)
_sym_db.RegisterEnumDescriptor(_TRYENUM)

TryEnum = enum_type_wrapper.EnumTypeWrapper(_TRYENUM)
a = 0
b = 1


_TRYMSG_TRYNESTENUM = _descriptor.EnumDescriptor(
  name='TryNestEnum',
  full_name='NetProto.TryMsg.TryNestEnum',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='a', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='b', index=1, number=1,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=324,
  serialized_end=351,
)
_sym_db.RegisterEnumDescriptor(_TRYMSG_TRYNESTENUM)


_TRYITEM = _descriptor.Descriptor(
  name='TryItem',
  full_name='NetProto.TryItem',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='id', full_name='NetProto.TryItem.id', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='name', full_name='NetProto.TryItem.name', index=1,
      number=2, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
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
  serialized_start=23,
  serialized_end=58,
)


_TRYMSG = _descriptor.Descriptor(
  name='TryMsg',
  full_name='NetProto.TryMsg',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='int_val', full_name='NetProto.TryMsg.int_val', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='str_val', full_name='NetProto.TryMsg.str_val', index=1,
      number=2, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='msg_val', full_name='NetProto.TryMsg.msg_val', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='enum_val', full_name='NetProto.TryMsg.enum_val', index=3,
      number=4, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='nest_enum_val', full_name='NetProto.TryMsg.nest_enum_val', index=4,
      number=5, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='msg_array', full_name='NetProto.TryMsg.msg_array', index=5,
      number=6, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='nest_enum_array', full_name='NetProto.TryMsg.nest_enum_array', index=6,
      number=7, type=14, cpp_type=8, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _TRYMSG_TRYNESTENUM,
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=61,
  serialized_end=351,
)

_TRYMSG.fields_by_name['msg_val'].message_type = _TRYITEM
_TRYMSG.fields_by_name['enum_val'].enum_type = _TRYENUM
_TRYMSG.fields_by_name['nest_enum_val'].enum_type = _TRYMSG_TRYNESTENUM
_TRYMSG.fields_by_name['msg_array'].message_type = _TRYITEM
_TRYMSG.fields_by_name['nest_enum_array'].enum_type = _TRYMSG_TRYNESTENUM
_TRYMSG_TRYNESTENUM.containing_type = _TRYMSG
DESCRIPTOR.message_types_by_name['TryItem'] = _TRYITEM
DESCRIPTOR.message_types_by_name['TryMsg'] = _TRYMSG
DESCRIPTOR.enum_types_by_name['TryEnum'] = _TRYENUM
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

TryItem = _reflection.GeneratedProtocolMessageType('TryItem', (_message.Message,), dict(
  DESCRIPTOR = _TRYITEM,
  __module__ = 'try_pb2'
  # @@protoc_insertion_point(class_scope:NetProto.TryItem)
  ))
_sym_db.RegisterMessage(TryItem)

TryMsg = _reflection.GeneratedProtocolMessageType('TryMsg', (_message.Message,), dict(
  DESCRIPTOR = _TRYMSG,
  __module__ = 'try_pb2'
  # @@protoc_insertion_point(class_scope:NetProto.TryMsg)
  ))
_sym_db.RegisterMessage(TryMsg)


DESCRIPTOR.has_options = True
DESCRIPTOR._options = _descriptor._ParseOptions(descriptor_pb2.FileOptions(), _b('\370\001\001'))
# @@protoc_insertion_point(module_scope)