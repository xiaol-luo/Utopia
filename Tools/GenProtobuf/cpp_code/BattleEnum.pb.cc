// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: BattleEnum.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "BattleEnum.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace NetProto {

namespace protobuf_BattleEnum_2eproto {


namespace {

const ::google::protobuf::EnumDescriptor* file_level_enum_descriptors[10];

}  // namespace

PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::ParseTableField
    const TableStruct::entries[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  {0, 0, 0, ::google::protobuf::internal::kInvalidMask, 0, 0},
};

PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::AuxillaryParseTableField
    const TableStruct::aux[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  ::google::protobuf::internal::AuxillaryParseTableField(),
};
PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::ParseTable const
    TableStruct::schema[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { NULL, NULL, 0, -1, -1, -1, -1, NULL, false },
};

const ::google::protobuf::uint32 TableStruct::offsets[1] = {};
static const ::google::protobuf::internal::MigrationSchema* schemas = NULL;
static const ::google::protobuf::Message* const* file_default_instances = NULL;
namespace {

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "BattleEnum.proto", schemas, file_default_instances, TableStruct::offsets, factory,
      NULL, file_level_enum_descriptors, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
}

}  // namespace
void TableStruct::InitDefaultsImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::internal::InitProtobufDefaults();
}

void InitDefaults() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &TableStruct::InitDefaultsImpl);
}
namespace {
void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n\020BattleEnum.proto\022\010NetProto*5\n\tEUnitTyp"
      "e\022\014\n\010Building\020\000\022\010\n\004Hero\020\001\022\007\n\003Npc\020\002\022\007\n\003MA"
      "X\020\003*\340\001\n\017EMoveAgentState\022\030\n\024EMoveAgentSta"
      "te_Idle\020\000\022\035\n\031EMoveAgentState_MoveToPos\020\001"
      "\022\035\n\031EMoveAgentState_MoveToDir\020\002\022\037\n\033EMove"
      "AgentState_Immobilized\020\003\022\035\n\031EMoveAgentSt"
      "ate_ForceLine\020\004\022\034\n\030EMoveAgentState_Force"
      "Pos\020\005\022\027\n\023EMoveAgentState_Max\020\006*l\n\nEMoveS"
      "tate\022\023\n\017EMoveState_Idle\020\000\022\023\n\017EMoveState_"
      "Move\020\001\022\032\n\026EMoveState_Immobilized\020\002\022\030\n\024EM"
      "oveState_ForceMove\020\003*\236\001\n\014EPlayerOpera\022\017\n"
      "\013EPO_Invalid\020\000\022\014\n\010EPO_Stop\020\001\022\014\n\010EPO_Move"
      "\020\002\022\016\n\nEPO_Follow\020\003\022\014\n\010EPO_Hunt\020\004\022\021\n\rEPO_"
      "CastSkill\020\005\022\017\n\013EPO_UseItem\020\006\022\r\n\tEPO_Trac"
      "e\020\007\022\020\n\014EBO_MaxCount\020 *\332\002\n\013EFightParam\022\014\n"
      "\010EFP_None\020\000\022\n\n\006EFP_HP\020\001\022\n\n\006EFP_MP\020\002\022\r\n\tE"
      "FP_MaxHP\020\t\022\r\n\tEFP_MaxMP\020\n\022\021\n\rEFP_MoveSpe"
      "ed\020\013\022\022\n\016EFP_AttackDist\020\014\022\023\n\017EFP_AttackSp"
      "eed\020\r\022\021\n\rEFP_PhyAttack\020\016\022\023\n\017EFP_MagicAtt"
      "ack\020\017\022\017\n\013EFP_PhyHurt\020\020\022\021\n\rEFP_MagicHurt\020"
      "\021\022\022\n\016EFP_PhyDefense\020\022\022\024\n\020EFP_MagicDefens"
      "e\020\023\022\021\n\rEFP_Dizziness\020\024\022\017\n\013EFP_Silence\020\025\022"
      "\r\n\tEFP_Blind\020\026\022\023\n\017EFP_Immobilized\020\027\022\r\n\tE"
      "FP_COUNT\020 *\362\001\n\nESkillSlot\022\r\n\tESS_QSlot\020\000"
      "\022\r\n\tESS_WSlot\020\001\022\r\n\tESS_ESlot\020\002\022\r\n\tESS_RS"
      "lot\020\003\022\r\n\tESS_FSlot\020\004\022\r\n\tESS_GSlot\020\005\022\r\n\tE"
      "SS_PSlot\020\006\022\017\n\013ESS_OneSlot\020\013\022\017\n\013ESS_TwoSl"
      "ot\020\014\022\021\n\rESS_ThreeSlot\020\r\022\020\n\014ESS_FourSlot\020"
      "\016\022\020\n\014ESS_FiveSlot\020\017\022\017\n\013ESS_SixSlot\020\020\022\021\n\r"
      "ESS_SevenSlot\020\021*7\n\tESkillBar\022\025\n\021ESkillBa"
      "r_Default\020\000\022\023\n\017ESkillBar_Extra\020\001*t\n\013ESki"
      "llState\022\017\n\013ESS_ReadyGo\020\000\022\021\n\rESS_Preparin"
      "g\020\001\022\021\n\rESS_Releasing\020\002\022\020\n\014ESS_Guilding\020\003"
      "\022\017\n\013ESS_Lasting\020\004\022\013\n\007ESS_End\020\005*^\n\014ESkill"
      "UseWay\022\027\n\023ESkillTarget_Target\020\000\022\032\n\026ESkil"
      "lTarget_Direction\020\001\022\031\n\025ESkillTarget_Posi"
      "tion\020\002*\355\001\n\020ESkillEffectCase\022\031\n\025ESkillTar"
      "getCase_Self\020\000\022\033\n\027ESkillTargetCase_Frien"
      "d\020\001\022\032\n\026ESkillTargetCase_Enemy\020\002\022\036\n\032ESkil"
      "lTargetCase_SelfEnemy\020\003\022&\n\"ESkillTargetC"
      "ase_FriendExcludeSelf\020\004\022#\n\037ESkillTargetC"
      "ase_AllExcludeSelf\020\005\022\030\n\024ESkillTargetCase"
      "_All\020\006B\003\370\001\001b\006proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 1699);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "BattleEnum.proto", &protobuf_RegisterTypes);
}
} // anonymous namespace

void AddDescriptors() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at dynamic initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;

}  // namespace protobuf_BattleEnum_2eproto

const ::google::protobuf::EnumDescriptor* EUnitType_descriptor() {
  protobuf_BattleEnum_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_BattleEnum_2eproto::file_level_enum_descriptors[0];
}
bool EUnitType_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
      return true;
    default:
      return false;
  }
}

const ::google::protobuf::EnumDescriptor* EMoveAgentState_descriptor() {
  protobuf_BattleEnum_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_BattleEnum_2eproto::file_level_enum_descriptors[1];
}
bool EMoveAgentState_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
      return true;
    default:
      return false;
  }
}

const ::google::protobuf::EnumDescriptor* EMoveState_descriptor() {
  protobuf_BattleEnum_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_BattleEnum_2eproto::file_level_enum_descriptors[2];
}
bool EMoveState_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
      return true;
    default:
      return false;
  }
}

const ::google::protobuf::EnumDescriptor* EPlayerOpera_descriptor() {
  protobuf_BattleEnum_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_BattleEnum_2eproto::file_level_enum_descriptors[3];
}
bool EPlayerOpera_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 32:
      return true;
    default:
      return false;
  }
}

const ::google::protobuf::EnumDescriptor* EFightParam_descriptor() {
  protobuf_BattleEnum_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_BattleEnum_2eproto::file_level_enum_descriptors[4];
}
bool EFightParam_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 32:
      return true;
    default:
      return false;
  }
}

const ::google::protobuf::EnumDescriptor* ESkillSlot_descriptor() {
  protobuf_BattleEnum_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_BattleEnum_2eproto::file_level_enum_descriptors[5];
}
bool ESkillSlot_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
      return true;
    default:
      return false;
  }
}

const ::google::protobuf::EnumDescriptor* ESkillBar_descriptor() {
  protobuf_BattleEnum_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_BattleEnum_2eproto::file_level_enum_descriptors[6];
}
bool ESkillBar_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
      return true;
    default:
      return false;
  }
}

const ::google::protobuf::EnumDescriptor* ESkillState_descriptor() {
  protobuf_BattleEnum_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_BattleEnum_2eproto::file_level_enum_descriptors[7];
}
bool ESkillState_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
      return true;
    default:
      return false;
  }
}

const ::google::protobuf::EnumDescriptor* ESkillUseWay_descriptor() {
  protobuf_BattleEnum_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_BattleEnum_2eproto::file_level_enum_descriptors[8];
}
bool ESkillUseWay_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
      return true;
    default:
      return false;
  }
}

const ::google::protobuf::EnumDescriptor* ESkillEffectCase_descriptor() {
  protobuf_BattleEnum_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_BattleEnum_2eproto::file_level_enum_descriptors[9];
}
bool ESkillEffectCase_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
      return true;
    default:
      return false;
  }
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace NetProto

// @@protoc_insertion_point(global_scope)
