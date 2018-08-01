

effect_script.effect_script_demo = inherit_from(effect_script.effect_script_base)
local effect_script_demo = effect_script.effect_script_demo
effect_script_demo.__index = effect_script_demo

local OnSceneUnitFightParamChange = function(self, p1, p2, p3, p4, p5, lua_param)
    print("OnSceneUnitFightParamChange")
    print(self, p1, p2, p3, p4, p5, lua_param)
    print(serpent.block(lua_param)) 
end

local function CreateOnSceneUnitFightParamChange(param)
    local function ret_fn(self, p1, p2, p3, p4, p5)
        OnSceneUnitFightParamChange(self, p1, p2, p3, p4, p5, param)
    end
    return ret_fn
end

function effect_script_demo.init(self, effect, param)
    effect_script.effect_script_base.init(self, effect, param)
    self.loop_times = 0
    self.scene_events.OnSceneUnitFightParamChange = OnSceneUnitFightParamChange
end

function effect_script_demo.on_late_begin(self)
    print("effect_script_demo.on_begin")
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
    self.effect:SubscribeSuEvent(self.effect:GetSkill():GetCaster(), ESUEventId.ESU_FightParamChange, CreateOnSceneUnitFightParamChange(nil))
    self.effect:SubscribeSuEvent(self.effect:GetSkill():GetCaster(), ESUEventId.ESU_FightParamChange, CreateOnSceneUnitFightParamChange(12345))
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



