﻿// -------------------------------------------------------------------------------
// THIS FILE IS ORIGINALLY GENERATED BY THE DESIGNER.
// YOU ARE ONLY ALLOWED TO MODIFY CODE BETWEEN '///<<< BEGIN' AND '///<<< END'.
// PLEASE MODIFY AND REGENERETE IT IN THE DESIGNER FOR CLASS/MEMBERS/METHODS, ETC.
// -------------------------------------------------------------------------------

#include "AISceneUnitHero.h"

///<<< BEGIN WRITING YOUR CODE FILE_INIT

#include "GameLogic/Scene/SceneUnitModules/SceneUnitAction/SceneHeroAction.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitSkills/SceneUnitSkills.h"
#include "GameLogic/Scene/Skills/Skill.h"

///<<< END WRITING YOUR CODE

AISceneUnitHero::AISceneUnitHero()
{
	hero = 0;
	skill_keyid = 0;
///<<< BEGIN WRITING YOUR CODE CONSTRUCTOR

///<<< END WRITING YOUR CODE
}

AISceneUnitHero::~AISceneUnitHero()
{
///<<< BEGIN WRITING YOUR CODE DESTRUCTOR

///<<< END WRITING YOUR CODE
}

void AISceneUnitHero::Init(long long param)
{
///<<< BEGIN WRITING YOUR CODE Init
	m_su_action = (GameLogic::SceneHeroAction *)param;
	m_su = m_su_action->GetOwner();
	m_skills = m_su->GetModule<GameLogic::SceneUnitSkills>().get();
///<<< END WRITING YOUR CODE
}

bool AISceneUnitHero::IsActive()
{
///<<< BEGIN WRITING YOUR CODE IsActive
	if (nullptr == m_su)
		return false;
	if (0 != m_su->GetPlayerId())
		return false;
	return true;
///<<< END WRITING YOUR CODE
}

void AISceneUnitHero::PickSkill()
{
///<<< BEGIN WRITING YOUR CODE PickSkill
	auto fn = [this](std::shared_ptr<GameLogic::Skill> skill, void *param) {
		if (!skill->InCd())
		{
			GameLogic::Skill** out_skill_id = (GameLogic::Skill**)param;
			*out_skill_id = skill.get();
		}
	};
	GameLogic::Skill *ret_skill = nullptr;
	m_skills->ForeachSkill(fn, &ret_skill);
	if (nullptr != ret_skill)
		skill_keyid = ret_skill->GetSkillKey();

///<<< END WRITING YOUR CODE
}

void AISceneUnitHero::CaskSkill()
{
///<<< BEGIN WRITING YOUR CODE CaskSkill

	auto skill = m_skills->GetSkill(skill_keyid);
	if (nullptr != skill)
	{
		auto cfg = skill->GetCfg();
	}

	this->ResetData();

///<<< END WRITING YOUR CODE
}


///<<< BEGIN WRITING YOUR CODE FILE_UNINIT

void AISceneUnitHero::ResetData()
{
	skill_keyid = 0;
}
///<<< END WRITING YOUR CODE
