
effect_script.effect_base = {}
local effect_base = effect_script.effect_base

function effect_base.init(self, effect, cfg)
    self.effect = effect
    self.script_cfg = cfg
    self.json_cfg = json_configs.get_effect_script(cfg:GetId())
    self.is_done = false

    self.scene_events = 
    {
        --function(std::shared_ptr<SceneUnit> su, bool is_fix, NetProto::EFightParam efp, int new_value, int old_value)
        OnSceneUnitFightParamChange = nil, 
        --function(std::shared_ptr<SceneUnit> su, bool is_attached)
        OnImmobilizedChange = nil,
        --function(std::shared_ptr<SceneUnit> su, bool is_attached)
        OnBlindChange = nil,
        --function(std::shared_ptr<SceneUnit> su, bool is_attached)
        OnSilenceChange = nil,
        --function(std::shared_ptr<SceneUnit> su, bool is_attached)
        OnDeadChange = nil,
        --function(std::shared_ptr<SceneUnit> su, bool is_attached)
        OnDizzinessChange = nil,
        --function(std::shared_ptr<SceneUnit> su, int now_val, int old_val, int delta_val, EffectBase *effect)
        OnHpChange = nil,
        --function(std::shared_ptr<SceneUnit> su, int now_val, int old_val, int delta_val, EffectBase *effect)
        OnMpChange = nil,
        --function(std::shared_ptr<SceneUnit> su, Vector3 now_pos, Vector3 old_pos)
        OnPosChange = nil,
        --function(std::shared_ptr<SceneUnit> su, EMoveAgentState now_state, EMoveAgentState old_state)
        OnMoveStateChange = nil,
        --function(std::shared_ptr<SceneUnit> su, Vector3 new_v, Vector3 old_v)
        OnVolecityChange = nil, 
        --function(std::shared_ptr<SceneUnit> su)
        OnEnterScene = nil,
        --function(std::shared_ptr<SceneUnit> su)
        OnLeaveScene = nil,

        HodePosition = nil
    }
end

function effect_base.on_late_begin(self)
end

function effect_base.on_late_end(self)
end

function effect_base.on_late_loop(self, now_ms, delta_ms)
end