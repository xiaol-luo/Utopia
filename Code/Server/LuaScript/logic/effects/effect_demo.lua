

effect_script.effect_demo = inherit_from(effect_script.effect_base)
local effect_demo = effect_script.effect_demo

local function OnTestEventCallback(self, ...)
    print(self, ...)
end

function effect_demo.init(self, effect, cfg)
    effect_script.effect_base.init(self, effect, cfg)

    self.loop_times = 0

    self.scene_events = 
    {
        --function(std::shared_ptr<SceneUnit> su, bool is_fix, NetProto::EFightParam efp, int new_value, int old_value)
        OnSceneUnitFightParamChange = OnTestEventCallback, 
        --function(std::shared_ptr<SceneUnit> su, bool is_attached)
        OnImmobilizedChange = OnTestEventCallback,
        --function(std::shared_ptr<SceneUnit> su, bool is_attached)
        OnBlindChange = OnTestEventCallback,
        --function(std::shared_ptr<SceneUnit> su, bool is_attached)
        OnSilenceChange = OnTestEventCallback,
        --function(std::shared_ptr<SceneUnit> su, bool is_attached)
        OnDeadChange = OnTestEventCallback,
        --function(std::shared_ptr<SceneUnit> su, bool is_attached)
        OnDizzinessChange = OnTestEventCallback,
        --function(std::shared_ptr<SceneUnit> su, int now_val, int old_val, int delta_val, EffectBase *effect)
        OnHpChange = OnTestEventCallback,
        --function(std::shared_ptr<SceneUnit> su, int now_val, int old_val, int delta_val, EffectBase *effect)
        OnMpChange = OnTestEventCallback,
        --function(std::shared_ptr<SceneUnit> su, Vector3 now_pos, Vector3 old_pos)
        OnPosChange = OnTestEventCallback,
        --function(std::shared_ptr<SceneUnit> su, EMoveAgentState now_state, EMoveAgentState old_state)
        OnMoveStateChange = OnTestEventCallback,
        --function(std::shared_ptr<SceneUnit> su, Vector3 new_v, Vector3 old_v)
        OnVolecityChange = OnTestEventCallback, 
        --function(std::shared_ptr<SceneUnit> su)
        OnEnterScene = OnTestEventCallback,
        --function(std::shared_ptr<SceneUnit> su)
        OnLeaveScene = OnTestEventCallback,

        HodePosition = nil
    }
end

local function CreateOnSceneUnitFightParamChange(param)
    local OnSceneUnitFightParamChange = function(self, p1, p2, p3, p4, p5, lua_param)
        print("OnSceneUnitFightParamChange")
        print(self, p1, p2, p3, p4, p5, lua_param)
        print(serpent.block(lua_param)) 
    end
    local ret_fn = function(self, p1, p2, p3, p4, p5)
        OnSceneUnitFightParamChange(self, p1, p2, p3, p4, p5, param)
    end
    return ret_fn
end
function effect_demo.on_late_begin(self)
    print("effect_demo.on_begin")
    local param = GameLogic.GuidedMissileParam.new()
    param.target_type = GameLogic.GuidedMissileParam.TargetType.TargetType_Pos
    param.move_speed = 5
    param.max_alive_sec  = 10000
    param.effect_ids:add(7000005)
    param.use_effect_param = self.effect:GetUseEffectParam()
	param.target_pos.x = param.use_effect_param.pos.x
	param.target_pos.z = param.use_effect_param.pos.y
	local start_pos = self.effect:GetSkill():GetCaster():GetTransform():GetPos():XZ()
    local gm = GameLogic.AddGuidedMissileToScene(start_pos, param.use_effect_param.dir, param)

    self.effect:SubscribeSuEvent(self.effect:GetSkill():GetCaster(), ESUEventId.ESU_FightParamChange, CreateOnSceneUnitFightParamChange({12, 34}))
end

function effect_demo.on_late_end(self)
    print("effect_demo.on_end")
end

function effect_demo.on_late_loop(self, now_ms, delta_ms)
    self.loop_times = self.loop_times + 1
    if self.loop_times > 10 then 
        self.is_done = true
    end
end



