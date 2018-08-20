

effect_script.effect_trace_bullet = inherit_from(effect_script.effect_base)
local effect_trace_bullet = effect_script.effect_trace_bullet

function effect_trace_bullet.init(self, effect, cfg)
    effect_script.effect_base.init(self, effect, cfg)
    self.cfg = json_configs.get_effect_trace_bulletget_effect_trace_bullet(cfg:GetIntParam())
    if nil == self.cfg then
        self.is_done = true
    end
end

function effect_trace_bullet.on_late_begin(self)
    print("effect_trace_bullet.on_begin")
    if nil == self.cfg then 
        print("effect_trace_bullet cfg is null")
        return
    end

    local param = GameLogic.GuidedMissileParam.new()
    param.target_type = GameLogic.GuidedMissileParam.TargetType.TargetType_SceneUnit
    param.move_speed = self.cfg.move_speed
    param.max_alive_sec  = self.cfg.max_alive_sec
    param.effect_ids:add(self.cfg.effect_id)
    param.use_effect_param = self.effect:GetUseEffectParam()
	param.target_pos.x = param.use_effect_param.pos.x
    param.target_pos.z = param.use_effect_param.pos.y
    param.target_su = self.effect:GetSu(self.cfg.target_id)
	local start_pos = self.effect:GetSkill():GetCaster():GetTransform():GetPos():XZ()
    local gm = GameLogic.AddGuidedMissileToScene(start_pos, param.use_effect_param.dir, param)

    self.effect:SubscribeSuEvent(self.effect:GetSkill():GetCaster(), ESUEventId.ESU_FightParamChange, CreateOnSceneUnitFightParamChange({12, 34}))
end

function effect_demo.on_late_end(self)
    print("effect_demo.on_end")
end

function effect_demo.on_late_loop(self, now_ms, delta_ms)
    self.loop_times = self.loop_times + 1
    if self.loop_times > 100 then 
        self.is_done = true
    end
end



