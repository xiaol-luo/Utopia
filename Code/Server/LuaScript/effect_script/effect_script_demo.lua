

effect_script.effect_script_demo = inherit_from(effect_script.effect_script_base)
local effect_script_demo = effect_script.effect_script_demo
effect_script_demo.__index = effect_script_demo

function effect_script_demo.init(self, effect, param)
    effect_script.effect_script_base.init(self, effect, param)
    self.loop_times = 0
end

function effect_script_demo.on_late_begin(self)
    print("effect_script_demo.on_begin")
    local param = GameLogic.GuidedMissileParam.new()
    param.target_type = GameLogic.GuidedMissileParam.TargetType.TargetType_Pos
    param.target_pos.x = 60
    param.target_pos.y = 0
    param.target_pos.z = 60
    param.move_speed = 5
    param.max_alive_sec  = 10000
    param.effect_ids:add(7000005)
    param.use_effect_param = self.effect:GetUseEffectParam()
    local gm = GameLogic.AddGuidedMissileToScene(param.use_effect_param.pos, param.use_effect_param.dir, param)
end

function effect_script_demo.on_late_end(self)
    print("effect_script_demo.on_end")
end

function effect_script_demo.on_late_loop(self, now_ms, delta_ms)
    self.loop_times = self.loop_times + 1
    if self.loop_times > 10 then 
        self.is_done = true
    end


end



