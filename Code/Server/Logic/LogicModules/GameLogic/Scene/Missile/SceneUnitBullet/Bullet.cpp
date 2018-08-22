#include "Bullet.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"
#include "GameLogic/Scene/NewScene.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitTransform.h"
#include "GameLogic/Scene/Config/SceneAllConfig.h"
#include "GameLogic/Scene/SceneModule/SceneUnitFilter/SceneUnitFilter.h"
#include "GameLogic/Scene/Effects/EffectFilterConfig.h"
#include "GameLogic/Scene/Skills/Skill.h"
#include "GameLogic/Scene/SceneModule/SceneUnitFilter/SceneUnitFilter.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitBody.h"
#include "GameLogic/Scene/SceneModule/SceneView/SceneView.h"

namespace GameLogic
{
	Bullet::Bullet() : SceneUnitMissile()
	{

	}

	Bullet::~Bullet()
	{
	}

	bool Bullet::SetParam(const BulletParam &param)
	{
		if (EBulletState_None != m_curr_state)
			return false;
		m_param = param;
		m_curr_state = EBulletState_Ready;
		return true;
	}

	void Bullet::SetDone()
	{
		if (m_curr_state < EBulletState_Done)
			m_curr_state = EBulletState_Done;
	}

	void Bullet::OnEnterScene()
	{
		m_transform = this->GetModule<SceneUnitTransform>();
	}

	void Bullet::OnUpdate()
	{
		if (EBulletState_AllFinish == m_curr_state || EBulletState_None == m_curr_state)
			return;

		if (EBulletState_Ready == m_curr_state)
		{
			m_ticker.SetTimeFunc(std::bind(&NewScene::GetLogicSec, this->GetScene()));
			m_ticker.Restart(m_param.max_alive_sec);

			if (EBulletTarget_Pos == m_param.target_type)
			{
				Vector3 link_vec3 = m_param.target_pos - m_transform->GetPos();
				link_vec3.y = 0;
				m_velocity = Vector3::Normalize(link_vec3) * m_param.move_speed;
			}

			m_curr_state = EBulletState_Moving;
		}

		if (EBulletState_Moving == m_curr_state)
		{
			// 移动
			Vector3 target_pos = m_param.target_pos;
			if (EBulletTarget_SceneUnit == m_param.target_type)
			{
				target_pos = m_param.target_su->GetTransform()->GetPos();
				Vector3 linkVec3 = target_pos - m_transform->GetPos();
				linkVec3.y = 0;
				m_velocity = Vector3::Normalize(linkVec3) * m_param.move_speed;
			}

			float time_span = m_ticker.ElaspeTime() - m_last_elaspe_sec;
			if (!m_ticker.InCd())
				time_span = m_ticker.GetCd() - m_last_elaspe_sec;
			m_last_elaspe_sec = m_ticker.ElaspeTime();

			Vector3 move_distance = m_velocity * time_span;
			Vector3 ret_pos = m_transform->GetPos() + move_distance;
			
			bool isDone = false;
			{
				Vector3 nor1 = target_pos - m_transform->GetPos();
				Vector3 nor2 = ret_pos - target_pos;
				nor1.y = 0; nor2.y = 0;
				if (nor2.SqrMagnitude() > FLT_MIN)
				{
					nor1.Normalize(); nor2.Normalize();
					if (Vector3::Dot(nor1, nor2) > 0) // 夹角小于90度，也即ret_pos越过了target_pos
					{
						isDone = true;
					}
				}
				else
				{
					isDone = true;
				}
			}
			if (isDone)
			{
				ret_pos = target_pos;
			}

			Vector3 old_pos = m_transform->GetPos();
			m_transform->SetLocalPos(ret_pos);
			if (m_param.calibre > 0 && m_param.hit_filter_id > 0 && m_param.hit_action.valid())
			{
				NewScene *scene = this->GetScene();
				// 检查命中的目标
				 auto filter_cfg = scene->GetCfg()->effect_filter_cfg_mgr->GetCfg(m_param.hit_filter_id);
				 if (nullptr != filter_cfg)
				 {
					 SceneUnitFilterWayParams filter_way_param = filter_cfg->GenFilterWayParams();
					 filter_way_param.relations.caster = m_param.use_effect_param.skill->GetCaster();
					 EffectFilterShape &filter_shape = filter_way_param.shape;
					 filter_shape.shape = EEffectFilterShape_Rect;
					 filter_shape.pos = old_pos.XZ();
					 filter_shape.dir = Vector2::Normalize(m_velocity.XZ());
					 filter_shape.shape_param.rect.x_size = m_param.calibre;
					 filter_shape.shape_param.rect.y_size = (ret_pos - old_pos).Magnitude();
					 std::unordered_map<uint64_t, std::shared_ptr<SceneUnit>> ret_sus = scene->GetModule<SceneUnitFilter>()->FindSceneUnit(filter_way_param);
					 m_param.hit_action(this, ret_sus);
				 }
			}

			if (isDone)
			{
				m_curr_state = EBulletState_Done;
			}
		}

		if (EBulletState_Done == m_curr_state)
		{
			if (m_param.done_action.valid())
			{
				m_param.done_action(this);
			}
			m_curr_state = EBulletState_Destroying;
		}

		if (m_curr_state < EBulletState_Destroying && !m_ticker.InCd())
		{
			// 存活时间超过最大限制了，让它结束
			m_curr_state = EBulletState_Destroying;
		}
		if (EBulletState_Destroying == m_curr_state)
		{
			++m_wait_frame_for_destory;
			if (m_wait_frame_for_destory > 1)
			{
				m_curr_state = EBulletState_AllFinish;
				this->GetScene()->RemoveUnit(m_owner->GetId());
			}
		}
	}
	

	std::shared_ptr<SceneUnit> AddBulletToScene(const Vector3 & pos, const Vector2 & face_dir, const BulletParam & param)
	{
		auto su = std::make_shared<SceneUnit>();
		su->SetUnitType(NetProto::EsceneUnitType_Effect);
		su->SetModelId(param.model_id);

		auto scene = param.use_effect_param.skill->GetCaster()->GetScene();
		auto sugm = su->AddModule(std::make_shared<Bullet>());
		auto subd = su->AddModule(std::make_shared<SceneUnitBody>());
		subd->SetSceneView(scene->GetModule<SceneView>());
		subd->SetRadius(param.body_radius);

		sugm->SetParam(param);
		su->GetTransform()->SetLocalPos(pos);
		su->GetTransform()->SetFaceDir(face_dir, ESUFaceDir::ESUFaceDir_Move);
		scene->AddUnit(su);
		return su;
	}
}