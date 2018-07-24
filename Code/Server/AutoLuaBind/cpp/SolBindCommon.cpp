#include <sol.hpp>

namespace SolLuaBind 
{
        extern void LuaBind_(lua_State *L);
        extern void LuaBind_Vector2(lua_State *L);
        extern void LuaBind_Vector3(lua_State *L);
        extern void LuaBind_Ticker(lua_State *L);
        extern void LuaBind_Axis2(lua_State *L);
        extern void LuaBind_AABB2(lua_State *L);
        extern void LuaBind_OBB2(lua_State *L);
        extern void LuaBind_Circle(lua_State *L);
        extern void LuaBind_Sector(lua_State *L);
        extern void LuaBind_LineSegment(lua_State *L);
        extern void LuaBind_MemoryUtil(lua_State *L);
        extern void LuaBind_EventDispacher(lua_State *L);
        extern void LuaBind_FastLZCompressor(lua_State *L);
        extern void LuaBind_LinearAllocator(lua_State *L);
        extern void LuaBind_MeshProcess(lua_State *L);
        extern void LuaBind_EventDispacherProxy(lua_State *L);
        extern void LuaBind_IAutoReleaseObject(lua_State *L);
        extern void LuaBind_AutoReleaseUtil(lua_State *L);
        extern void LuaBind_ESUEventId(lua_State *L);
        extern void LuaBind_SamplePolyAreas(lua_State *L);
        extern void LuaBind_SamplePolyFlags(lua_State *L);
        extern void LuaBind_SamplePartitionType(lua_State *L);
        extern void LuaBind_GameLogic(lua_State *L);
        extern void LuaBind_LuaUtils(lua_State *L);
        extern void LuaBind_Config(lua_State *L);
        extern void LuaBind_Net(lua_State *L);
        extern void LuaBind_LuaNet(lua_State *L);
        extern void LuaBind_std(lua_State *L);
        extern void LuaBind_Tuple(lua_State *L);
        extern void LuaBind_NumUtil(lua_State *L);
        extern void LuaBind_GeometryUtils(lua_State *L);
        extern void LuaBind_LuaDyCast(lua_State *L);
        extern void LuaBind_NetProto(lua_State *L);
        extern void LuaBind_GameLogic_SceneUnitMoveState(lua_State *L);
        extern void LuaBind_GameLogic_SceneUnitMoveIdleState(lua_State *L);
        extern void LuaBind_GameLogic_UseSkillParam(lua_State *L);
        extern void LuaBind_GameLogic_UseEffectParam(lua_State *L);
        extern void LuaBind_GameLogic_EndEffectId(lua_State *L);
        extern void LuaBind_GameLogic_TimeLineEffectId(lua_State *L);
        extern void LuaBind_GameLogic_TimeLineEffectIdsConfig(lua_State *L);
        extern void LuaBind_GameLogic_EffectFilterShape(lua_State *L);
        extern void LuaBind_GameLogic_EffectConfigBase(lua_State *L);
        extern void LuaBind_GameLogic_EffectConfigMgr(lua_State *L);
        extern void LuaBind_GameLogic_EffectBase(lua_State *L);
        extern void LuaBind_GameLogic_EffectForceMove(lua_State *L);
        extern void LuaBind_GameLogic_EffectScriptConfig(lua_State *L);
        extern void LuaBind_GameLogic_SkillConfigBase(lua_State *L);
        extern void LuaBind_GameLogic_NavAgent(lua_State *L);
        extern void LuaBind_GameLogic_SceneAllConfig(lua_State *L);
        extern void LuaBind_GameLogic_EffectHurtConfig(lua_State *L);
        extern void LuaBind_GameLogic_SceneUnitMoveToPosState(lua_State *L);
        extern void LuaBind_GameLogic_SyncClientMsg(lua_State *L);
        extern void LuaBind_GameLogic_SceneUnit(lua_State *L);
        extern void LuaBind_GameLogic_SceneUnitModule(lua_State *L);
        extern void LuaBind_GameLogic_SceneUnitMissile(lua_State *L);
        extern void LuaBind_GameLogic_SceneUnitBomb(lua_State *L);
        extern void LuaBind_GameLogic_ViewSnapshotDifference(lua_State *L);
        extern void LuaBind_GameLogic_ViewSnapshot(lua_State *L);
        extern void LuaBind_GameLogic_SceneModule(lua_State *L);
        extern void LuaBind_GameLogic_SceneEffects(lua_State *L);
        extern void LuaBind_GameLogic_EffectGroupConfig(lua_State *L);
        extern void LuaBind_GameLogic_EffectFilterConfig(lua_State *L);
        extern void LuaBind_GameLogic_EffectFilterParams(lua_State *L);
        extern void LuaBind_GameLogic_EffectFilterConfigMgr(lua_State *L);
        extern void LuaBind_GameLogic_EffectForceMoveConfig(lua_State *L);
        extern void LuaBind_GameLogic_EffectHurt(lua_State *L);
        extern void LuaBind_GameLogic_SceneUnitMove(lua_State *L);
        extern void LuaBind_GameLogic_SceneUnitQTreeNodeUnit(lua_State *L);
        extern void LuaBind_GameLogic_SceneUnitQTreeNode(lua_State *L);
        extern void LuaBind_GameLogic_SceneUnitQTree(lua_State *L);
        extern void LuaBind_GameLogic_ViewGrid(lua_State *L);
        extern void LuaBind_GameLogic_SkillBase(lua_State *L);
        extern void LuaBind_GameLogic_Skill(lua_State *L);
        extern void LuaBind_GameLogic_SceneUnitSight(lua_State *L);
        extern void LuaBind_GameLogic_SceneUnitExample(lua_State *L);
        extern void LuaBind_GameLogic_SceneUnitTransform(lua_State *L);
        extern void LuaBind_GameLogic_Player(lua_State *L);
        extern void LuaBind_GameLogic_SceneUnitBody(lua_State *L);
        extern void LuaBind_GameLogic_SkillLevelConfig(lua_State *L);
        extern void LuaBind_GameLogic_SkillConfig(lua_State *L);
        extern void LuaBind_GameLogic_SkillConfigSet(lua_State *L);
        extern void LuaBind_GameLogic_GuidedMissileParam(lua_State *L);
        extern void LuaBind_GameLogic_SceneUnitGuidedMissile(lua_State *L);
        extern void LuaBind_GameLogic_ESceneUnitFilterWayParams(lua_State *L);
        extern void LuaBind_GameLogic_SceneUnitFilter(lua_State *L);
        extern void LuaBind_GameLogic_FightParam(lua_State *L);
        extern void LuaBind_GameLogic_SceneUnitBullet(lua_State *L);
        extern void LuaBind_GameLogic_FightParamKV(lua_State *L);
        extern void LuaBind_GameLogic_FightParamKVs(lua_State *L);
        extern void LuaBind_GameLogic_EffectAttrsConfig(lua_State *L);
        extern void LuaBind_GameLogic_SceneView(lua_State *L);
        extern void LuaBind_GameLogic_SceneUnitFightParam(lua_State *L);
        extern void LuaBind_GameLogic_EffectGroup(lua_State *L);
        extern void LuaBind_GameLogic_EffectUtil(lua_State *L);
        extern void LuaBind_GameLogic_NavMesh(lua_State *L);
        extern void LuaBind_GameLogic_SceneUnitMoveImmobilizedState(lua_State *L);
        extern void LuaBind_GameLogic_NewScene(lua_State *L);
        extern void LuaBind_GameLogic_SceneUnitMoveForceLineState(lua_State *L);
        extern void LuaBind_GameLogic_PlayerMgr(lua_State *L);
        extern void LuaBind_GameLogic_EffectSearcher(lua_State *L);
        extern void LuaBind_GameLogic_EffectSearcherConfig(lua_State *L);
        extern void LuaBind_GameLogic_EffectAttrs(lua_State *L);
        extern void LuaBind_GameLogic_SceneUnitSkills(lua_State *L);
        extern void LuaBind_GameLogic_SceneMove(lua_State *L);
        extern void LuaBind_GameLogic_SceneUnitEventProxy(lua_State *L);
        extern void LuaBind_GameLogic_TestScene(lua_State *L);
        extern void LuaBind_GameLogic_SceneHeroAction(lua_State *L);
        extern void LuaBind_GameLogic_SceneUnitMoveForcePosState(lua_State *L);
        extern void LuaBind_GameLogic_SceneNavMesh(lua_State *L);
        extern void LuaBind_GameLogic_SceneUnitMoveToDirState(lua_State *L);
        extern void LuaBind_GameLogic_EffectScript(lua_State *L);
        extern void LuaBind_GameLogic_EEffectEndCase(lua_State *L);
        extern void LuaBind_GameLogic_EEffectStage(lua_State *L);
        extern void LuaBind_GameLogic_EEffectType(lua_State *L);
        extern void LuaBind_GameLogic_EEffectFilterAnchor(lua_State *L);
        extern void LuaBind_GameLogic_EEffectFilterShape(lua_State *L);
        extern void LuaBind_GameLogic_EEffectFilterLimitNumPriority(lua_State *L);
        extern void LuaBind_GameLogic_EForceMoveAnchor(lua_State *L);
        extern void LuaBind_GameLogic_EViewCamp(lua_State *L);
        extern void LuaBind_GameLogic_EViewGridType(lua_State *L);
        extern void LuaBind_GameLogic_ESceneObjectShape(lua_State *L);
        extern void LuaBind_GameLogic_ESceneModule(lua_State *L);
        extern void LuaBind_GameLogic_ESceneUnitModule(lua_State *L);
        extern void LuaBind_GameLogic_ESUAction(lua_State *L);
        extern void LuaBind_GameLogic_ESUFaceDir(lua_State *L);
        extern void LuaBind_GameLogic_GuidedMissileState(lua_State *L);
        extern void LuaBind_GameLogic_ESceneUnitFilterWay(lua_State *L);
        extern void LuaBind_GameLogic_FightParamAddType(lua_State *L);
        extern void LuaBind_Config_CsvEffectForceMoveConfig(lua_State *L);
        extern void LuaBind_Config_CsvEffectForceMoveConfigSet(lua_State *L);
        extern void LuaBind_Config_CsvEffectSearcherConfig(lua_State *L);
        extern void LuaBind_Config_CsvEffectSearcherConfigSet(lua_State *L);
        extern void LuaBind_Config_CsvEffectHealConfig(lua_State *L);
        extern void LuaBind_Config_CsvEffectHealConfigSet(lua_State *L);
        extern void LuaBind_Config_CsvEffectFilterConfig(lua_State *L);
        extern void LuaBind_Config_CsvEffectFilterConfigSet(lua_State *L);
        extern void LuaBind_Config_CsvEffectGroupConfig(lua_State *L);
        extern void LuaBind_Config_CsvEffectGroupConfigSet(lua_State *L);
        extern void LuaBind_Config_CsvLogConfig(lua_State *L);
        extern void LuaBind_Config_CsvLogConfigSet(lua_State *L);
        extern void LuaBind_Config_CsvEffectScriptConfig(lua_State *L);
        extern void LuaBind_Config_CsvEffectScriptConfigSet(lua_State *L);
        extern void LuaBind_Config_CsvEffectAttrsConfig(lua_State *L);
        extern void LuaBind_Config_CsvEffectAttrsConfigSet(lua_State *L);
        extern void LuaBind_Config_CsvSceneConfig(lua_State *L);
        extern void LuaBind_Config_CsvSceneConfigSet(lua_State *L);
        extern void LuaBind_Config_CsvSkillLevelConfig(lua_State *L);
        extern void LuaBind_Config_CsvSkillLevelConfigSet(lua_State *L);
        extern void LuaBind_Config_CsvSkillConfig(lua_State *L);
        extern void LuaBind_Config_CsvSkillConfigSet(lua_State *L);
        extern void LuaBind_Config_CsvEffectHurtConfig(lua_State *L);
        extern void LuaBind_Config_CsvEffectHurtConfigSet(lua_State *L);
        extern void LuaBind_Config_CsvConfigSets(lua_State *L);
        extern void LuaBind_NumUtil_ECalculateStrategy(lua_State *L);
        extern void LuaBind_GameLogic_NavAgent_EMoveType(lua_State *L);
        extern void LuaBind_GameLogic_SceneUnitQTreeNode_EChild(lua_State *L);
        extern void LuaBind_GameLogic_GuidedMissileParam_TargetType(lua_State *L);
        extern void LuaBind_GameLogic_ESceneUnitFilterWayParams__exclude_suids(lua_State *L);
        extern void LuaBind_GameLogic_ESceneUnitFilterWayParams__relations(lua_State *L);
        extern void LuaBind_GameLogic_ESceneUnitFilterWayParams__shape_obb2(lua_State *L);
        extern void LuaBind_GameLogic_ESceneUnitFilterWayParams__shape_circle(lua_State *L);
        extern void LuaBind_GameLogic_ESceneUnitFilterWayParams__shape_sector(lua_State *L);
        extern void LuaBind_GameLogic_ESceneUnitFilterWayParams__limit_num(lua_State *L);
        extern void LuaBind_GameLogic_ESceneUnitFilterWayParams__unit_type(lua_State *L);

	void SolLuaBind(lua_State *L)
	{
            LuaBind_(L);
            LuaBind_Vector2(L);
            LuaBind_Vector3(L);
            LuaBind_Ticker(L);
            LuaBind_Axis2(L);
            LuaBind_AABB2(L);
            LuaBind_OBB2(L);
            LuaBind_Circle(L);
            LuaBind_Sector(L);
            LuaBind_LineSegment(L);
            LuaBind_MemoryUtil(L);
            LuaBind_EventDispacher(L);
            LuaBind_FastLZCompressor(L);
            LuaBind_LinearAllocator(L);
            LuaBind_MeshProcess(L);
            LuaBind_EventDispacherProxy(L);
            LuaBind_IAutoReleaseObject(L);
            LuaBind_AutoReleaseUtil(L);
            LuaBind_ESUEventId(L);
            LuaBind_SamplePolyAreas(L);
            LuaBind_SamplePolyFlags(L);
            LuaBind_SamplePartitionType(L);
            LuaBind_GameLogic(L);
            LuaBind_LuaUtils(L);
            LuaBind_Config(L);
            LuaBind_Net(L);
            LuaBind_LuaNet(L);
            LuaBind_std(L);
            LuaBind_Tuple(L);
            LuaBind_NumUtil(L);
            LuaBind_GeometryUtils(L);
            LuaBind_LuaDyCast(L);
            LuaBind_NetProto(L);
            LuaBind_GameLogic_SceneUnitMoveState(L);
            LuaBind_GameLogic_SceneUnitMoveIdleState(L);
            LuaBind_GameLogic_UseSkillParam(L);
            LuaBind_GameLogic_UseEffectParam(L);
            LuaBind_GameLogic_EndEffectId(L);
            LuaBind_GameLogic_TimeLineEffectId(L);
            LuaBind_GameLogic_TimeLineEffectIdsConfig(L);
            LuaBind_GameLogic_EffectFilterShape(L);
            LuaBind_GameLogic_EffectConfigBase(L);
            LuaBind_GameLogic_EffectConfigMgr(L);
            LuaBind_GameLogic_EffectBase(L);
            LuaBind_GameLogic_EffectForceMove(L);
            LuaBind_GameLogic_EffectScriptConfig(L);
            LuaBind_GameLogic_SkillConfigBase(L);
            LuaBind_GameLogic_NavAgent(L);
            LuaBind_GameLogic_SceneAllConfig(L);
            LuaBind_GameLogic_EffectHurtConfig(L);
            LuaBind_GameLogic_SceneUnitMoveToPosState(L);
            LuaBind_GameLogic_SyncClientMsg(L);
            LuaBind_GameLogic_SceneUnit(L);
            LuaBind_GameLogic_SceneUnitModule(L);
            LuaBind_GameLogic_SceneUnitMissile(L);
            LuaBind_GameLogic_SceneUnitBomb(L);
            LuaBind_GameLogic_ViewSnapshotDifference(L);
            LuaBind_GameLogic_ViewSnapshot(L);
            LuaBind_GameLogic_SceneModule(L);
            LuaBind_GameLogic_SceneEffects(L);
            LuaBind_GameLogic_EffectGroupConfig(L);
            LuaBind_GameLogic_EffectFilterConfig(L);
            LuaBind_GameLogic_EffectFilterParams(L);
            LuaBind_GameLogic_EffectFilterConfigMgr(L);
            LuaBind_GameLogic_EffectForceMoveConfig(L);
            LuaBind_GameLogic_EffectHurt(L);
            LuaBind_GameLogic_SceneUnitMove(L);
            LuaBind_GameLogic_SceneUnitQTreeNodeUnit(L);
            LuaBind_GameLogic_SceneUnitQTreeNode(L);
            LuaBind_GameLogic_SceneUnitQTree(L);
            LuaBind_GameLogic_ViewGrid(L);
            LuaBind_GameLogic_SkillBase(L);
            LuaBind_GameLogic_Skill(L);
            LuaBind_GameLogic_SceneUnitSight(L);
            LuaBind_GameLogic_SceneUnitExample(L);
            LuaBind_GameLogic_SceneUnitTransform(L);
            LuaBind_GameLogic_Player(L);
            LuaBind_GameLogic_SceneUnitBody(L);
            LuaBind_GameLogic_SkillLevelConfig(L);
            LuaBind_GameLogic_SkillConfig(L);
            LuaBind_GameLogic_SkillConfigSet(L);
            LuaBind_GameLogic_GuidedMissileParam(L);
            LuaBind_GameLogic_SceneUnitGuidedMissile(L);
            LuaBind_GameLogic_ESceneUnitFilterWayParams(L);
            LuaBind_GameLogic_SceneUnitFilter(L);
            LuaBind_GameLogic_FightParam(L);
            LuaBind_GameLogic_SceneUnitBullet(L);
            LuaBind_GameLogic_FightParamKV(L);
            LuaBind_GameLogic_FightParamKVs(L);
            LuaBind_GameLogic_EffectAttrsConfig(L);
            LuaBind_GameLogic_SceneView(L);
            LuaBind_GameLogic_SceneUnitFightParam(L);
            LuaBind_GameLogic_EffectGroup(L);
            LuaBind_GameLogic_EffectUtil(L);
            LuaBind_GameLogic_NavMesh(L);
            LuaBind_GameLogic_SceneUnitMoveImmobilizedState(L);
            LuaBind_GameLogic_NewScene(L);
            LuaBind_GameLogic_SceneUnitMoveForceLineState(L);
            LuaBind_GameLogic_PlayerMgr(L);
            LuaBind_GameLogic_EffectSearcher(L);
            LuaBind_GameLogic_EffectSearcherConfig(L);
            LuaBind_GameLogic_EffectAttrs(L);
            LuaBind_GameLogic_SceneUnitSkills(L);
            LuaBind_GameLogic_SceneMove(L);
            LuaBind_GameLogic_SceneUnitEventProxy(L);
            LuaBind_GameLogic_TestScene(L);
            LuaBind_GameLogic_SceneHeroAction(L);
            LuaBind_GameLogic_SceneUnitMoveForcePosState(L);
            LuaBind_GameLogic_SceneNavMesh(L);
            LuaBind_GameLogic_SceneUnitMoveToDirState(L);
            LuaBind_GameLogic_EffectScript(L);
            LuaBind_GameLogic_EEffectEndCase(L);
            LuaBind_GameLogic_EEffectStage(L);
            LuaBind_GameLogic_EEffectType(L);
            LuaBind_GameLogic_EEffectFilterAnchor(L);
            LuaBind_GameLogic_EEffectFilterShape(L);
            LuaBind_GameLogic_EEffectFilterLimitNumPriority(L);
            LuaBind_GameLogic_EForceMoveAnchor(L);
            LuaBind_GameLogic_EViewCamp(L);
            LuaBind_GameLogic_EViewGridType(L);
            LuaBind_GameLogic_ESceneObjectShape(L);
            LuaBind_GameLogic_ESceneModule(L);
            LuaBind_GameLogic_ESceneUnitModule(L);
            LuaBind_GameLogic_ESUAction(L);
            LuaBind_GameLogic_ESUFaceDir(L);
            LuaBind_GameLogic_GuidedMissileState(L);
            LuaBind_GameLogic_ESceneUnitFilterWay(L);
            LuaBind_GameLogic_FightParamAddType(L);
            LuaBind_Config_CsvEffectForceMoveConfig(L);
            LuaBind_Config_CsvEffectForceMoveConfigSet(L);
            LuaBind_Config_CsvEffectSearcherConfig(L);
            LuaBind_Config_CsvEffectSearcherConfigSet(L);
            LuaBind_Config_CsvEffectHealConfig(L);
            LuaBind_Config_CsvEffectHealConfigSet(L);
            LuaBind_Config_CsvEffectFilterConfig(L);
            LuaBind_Config_CsvEffectFilterConfigSet(L);
            LuaBind_Config_CsvEffectGroupConfig(L);
            LuaBind_Config_CsvEffectGroupConfigSet(L);
            LuaBind_Config_CsvLogConfig(L);
            LuaBind_Config_CsvLogConfigSet(L);
            LuaBind_Config_CsvEffectScriptConfig(L);
            LuaBind_Config_CsvEffectScriptConfigSet(L);
            LuaBind_Config_CsvEffectAttrsConfig(L);
            LuaBind_Config_CsvEffectAttrsConfigSet(L);
            LuaBind_Config_CsvSceneConfig(L);
            LuaBind_Config_CsvSceneConfigSet(L);
            LuaBind_Config_CsvSkillLevelConfig(L);
            LuaBind_Config_CsvSkillLevelConfigSet(L);
            LuaBind_Config_CsvSkillConfig(L);
            LuaBind_Config_CsvSkillConfigSet(L);
            LuaBind_Config_CsvEffectHurtConfig(L);
            LuaBind_Config_CsvEffectHurtConfigSet(L);
            LuaBind_Config_CsvConfigSets(L);
            LuaBind_NumUtil_ECalculateStrategy(L);
            LuaBind_GameLogic_NavAgent_EMoveType(L);
            LuaBind_GameLogic_SceneUnitQTreeNode_EChild(L);
            LuaBind_GameLogic_GuidedMissileParam_TargetType(L);
            LuaBind_GameLogic_ESceneUnitFilterWayParams__exclude_suids(L);
            LuaBind_GameLogic_ESceneUnitFilterWayParams__relations(L);
            LuaBind_GameLogic_ESceneUnitFilterWayParams__shape_obb2(L);
            LuaBind_GameLogic_ESceneUnitFilterWayParams__shape_circle(L);
            LuaBind_GameLogic_ESceneUnitFilterWayParams__shape_sector(L);
            LuaBind_GameLogic_ESceneUnitFilterWayParams__limit_num(L);
            LuaBind_GameLogic_ESceneUnitFilterWayParams__unit_type(L);
	}
}