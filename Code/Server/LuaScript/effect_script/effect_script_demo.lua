

effect_script.effect_script_demo = inherit_from(effect_script.effect_script_base)
local effect_script_demo = effect_script.effect_script_demo
effect_script_demo.__index = effect_script_demo

function effect_script_demo.init(self, effect, param)
    effect_script.effect_script_base.init(self, effect, param)
    self.loop_times = 0
end

function effect_script_demo.on_late_begin(self)
    print("effect_script_demo.on_begin")
end

function effect_script_demo.on_late_end(self)
    print("effect_script_demo.on_end")
end

function effect_script_demo.on_late_loop(self, now_ms, delta_ms)
    self.loop_times = self.loop_times + 1
    if self.loop_times > 10 then 
        self.is_done = true
    end
    print("effect_script_demo.on_loop")
    local key = self.effect:GetKey()
    local cfg = self.effect:GetCfg()
    print("loop key", key, cfg)
    print("loop cfg id", cfg:GetId())
    cfg = LuaDyCast.ToEffectScriptConfig(cfg)
    local class_name = cfg:GetClassName(cfg)
    print("loop cfg className", class_name)
end



