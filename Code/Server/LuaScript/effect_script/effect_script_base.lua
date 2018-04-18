
effect_script.effect_script_base = {}
local effect_script_base = effect_script.effect_script_base
effect_script_base.__index = effect_script_base

function effect_script_base.init(self, effect, param)
    self.effect = effect
    self.param = param
    self.is_done = false
end

function effect_script_base.on_late_begin(self)
end

function effect_script_base.on_late_end(self)
end

function effect_script_base.on_late_loop(self, now_ms, delta_ms)
end