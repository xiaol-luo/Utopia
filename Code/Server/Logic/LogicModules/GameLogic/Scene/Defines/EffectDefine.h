#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include "Common/Geometry/Vector2.h"
#include "Common/Geometry/Vector3.h"
#include <limits.h>
#include "Utils/ConfigUtil.h"

namespace GameLogic
{
	class SkillBase;
	class SceneUnit;
	class EffectBase;

	struct UseSkillParam
	{
		void Reset()
		{
			target_suid = 0;				// 技能目标
			target_su.reset();
			pos = Vector2::zero;			// 技能目标点
			dir = Vector2::zero;			// 技能方向
			cast_face_dir = Vector2::zero;	// 技能开始施放时的朝向
			cast_pos = Vector2::zero;		// 技能开始施放时位置	
		}

		uint64_t target_suid = 0;
		std::weak_ptr<SceneUnit> target_su;
		Vector2 pos;
		Vector2 dir;
		Vector2 cast_face_dir;
		Vector2 cast_pos;
	};

	struct UseEffectParam
	{
		void Reset()
		{
			skill = nullptr;
			target_suid = 0;
			pos = Vector2::zero;
			dir = Vector2::zero;
		}

		std::shared_ptr<SkillBase> skill;
		uint64_t target_suid = 0;
		Vector2 pos;
		Vector2 dir;
	};

	enum EEffectEndCase
	{
		EEffectEndCase_Both = 0,
		EEffectEndCase_Done,
		EEffectEndCase_Break,
	};

	using EffectIdVec = std::vector<int>;

	struct EndEffectId
	{
		EEffectEndCase end_case = EEffectEndCase_Both;
		int id = 0;

		static bool Generate(EndEffectId &out_ret, const std::vector<int> &input_vals);
	};
	using EndEffectIdVec = std::vector<EndEffectId>;
	bool GenerateEndEffectIdVec(std::vector<EndEffectId> &out_ret, const std::vector<std::vector<int>> &input_vals);

	struct TimeLineEffectId
	{
		int id = 0;
		int wait_ms = 0;
		static bool Generate(TimeLineEffectId &out_ret, const std::vector<int> &input_vals);
	};
	using TimeLineEffectIdVec = std::vector<TimeLineEffectId>;
	struct TimeLineEffectIdsConfig
	{
		TimeLineEffectIdVec effect_ids;
		int min_wait_ms = -1;
		int max_wait_ms = -1;

		static bool Generate(TimeLineEffectIdsConfig &out_ret, const std::vector<std::vector<int>> &input_vals);
	};

	enum EEffectStage
	{
		EEffectStage_Wait = 0,
		EEffectStage_Begin,
		EEffectStage_Loop,
		EEffectStage_End,
	};

	enum EEffectType
	{
		EEffectType_Hurt,
		EEffectType_Heal,
		EEffectType_Attr,
		EEffectType_ForceMove,
	};

	enum EEffectFilterAnchor
	{
		EEffectFilterAnchor_Caster,
		EEffectFilterAnchor_CastPos,
		EEffectFilterAnchor_TargetPos,
		EEffectFilterAnchor_TargetUnit,
		EEffectFilterAnchor_EffectTargetUnit,
		EEffectFilterAnchor_EffectTargetPos,
	};
	EEffectFilterAnchor StrToEffectFilterAnchor(const std::string &str);

	enum EEffectFilterShape
	{
		EEffectFilterShape_None = 0,
		EEffectFilterShape_Circle,
		EEffectFilterShape_Rect,
		EEffectFilterShape_Sector,
	};

	union EffectFilterShapeParam
	{
		EffectFilterShapeParam() {}
		 struct
		 {
			 float radius = 0;
		 } circle;

		 struct
		 {
			 float x_size = 0;
			 float y_size = 0;
		 } rect;

		 struct
		 {
			 float radius = 0;
			 float angle = 0;
		 } sector;
	};

	struct EffectFilterShape 
	{
		Vector2 pos;
		Vector2 dir;
		EEffectFilterShape shape = EEffectFilterShape_None;
		EffectFilterShapeParam shape_param;
	};

	enum EEffectFilterLimitNumPriority
	{
		EEffectFilterLimitNumPriority_None = 0,
		EEffectFilterLimitNumPriority_NearCaster,
		EEffectFilterLimitNumPriority_AwayCaster,
		EEffectFilterLimitNumPriority_NearTarget,
		EEffectFilterLimitNumPriority_AwayTarget,
	};

	const static int SELECT_SELF_FILTER_CONFIG_ID = -1; // 选择自己的过滤器配置id
	const static int SELECT_TARGET_FILTER_CONFIG_ID = 0; // 选择目标的过滤器配置id

	enum EForceMoveAnchor
	{
		EForceMoveAnchor_Caster,
		EForceMoveAnchor_CastPos,
		EForceMoveAnchor_TargetPos,
		EForceMoveAnchor_TargetUnit,
		EForceMoveAnchor_EffectTargetUnit,
		EForceMoveAnchor_EffectTargetPos,
		EForceMoveAnchor_EffectDir,
		EForceMoveAnchor_SkillDir,
		EForceMoveAnchor_CastFaceDir,
	};
	EForceMoveAnchor StrToForceMoveAnchor(const std::string &str);
	bool CalForceMoveDir(const std::shared_ptr<EffectBase> effect_base, EForceMoveAnchor anchor, float deg, Vector2 *out_dir);
}
