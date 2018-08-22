

effect_script.effect_bullet = inherit_from(effect_script.effect_base)
local effect_bullet = effect_script.effect_bullet

function effect_bullet.init(self, effect, cfg)
    effect_script.effect_base.init(self, effect, cfg)
    --[[
    self.cfg = json_configs.get_effect_bullet(cfg:GetIntParam())
    if nil == self.cfg then
        self.is_done = true
    end
    ]]
end

function effect_bullet.bullet_hit_action(self, hit_sus)
    print("effect_bullet.bullet_hit_action")
end

function effect_bullet.bullet_done_action(self)
    self.is_done = true
    print("effect_bullet.bullet_done_action")
end

local function create_bullet_action(self, wrap_fn)
    local ret_fn = function (...)
        wrap_fn(self, ...)
    end
    return ret_fn
end 


function effect_bullet.on_late_begin(self)
    print("effect_bullet.on_begin")
    if nil == self.cfg then 
        print("effect_bullet cfg is null")
        -- return
    end
--[[
    local target_su = self.effect:GetSu(self.cfg.target_id)
    local param = GameLogic.BulletParam.new()
    param.target_type = GameLogic.EBulletTarget.EBulletTarget_SceneUnit
    param.target_su = target_su
    param.max_alive_sec = self.cfg.max_alive_sec
    param.move_speed = self.cfg.move_speed
    param.use_effect_param = self.effect:GetUseEffectParam()
    param.calibre = self.cfg.calibre
    param.hit_filter_id = self.cfg.hit_filter_id
    param.model_id = self.cfg.model_id
    param.body_radius = self.cfg.body_radius
    param.hit_action = create_bullet_action(self, effect_bullet.bullet_hit_action)
    param.done_action = create_bullet_action(self,effect_bullet.bullet_done_action)
	local start_pos = self.effect:GetSkill():GetCaster():GetTransform():GetPos()
    local gm = GameLogic.AddBulletToScene(start_pos, param.use_effect_param.dir, param)
]]
    local use_effect_param = self.effect:GetUseEffectParam()
    local target_su = self.effect:GetSu(use_effect_param.target_suid)
    local param = GameLogic.BulletParam.new()
    param.target_type = GameLogic.EBulletTarget.EBulletTarget_SceneUnit
    param.target_su = target_su
    param.max_alive_sec = 10
    param.move_speed = 15
    param.use_effect_param = use_effect_param
    param.calibre = 6
    param.hit_filter_id = 20
    param.model_id = 1
    param.body_radius = 1
    param.hit_action = create_bullet_action(self, effect_bullet.bullet_hit_action)
    param.done_action = create_bullet_action(self,effect_bullet.bullet_done_action)
    local start_pos = self.effect:GetSkill():GetCaster():GetTransform():GetPos()
    local gm = GameLogic.AddBulletToScene(start_pos, param.use_effect_param.dir, param)
    -- self.effect:SubscribeSuEvent(target_su, ESUEventId.ESU_FightParamChange, CreateOnSceneUnitFightParamChange({12, 34}))
end

function effect_bullet.on_late_end(self)
    print("effect_demo.on_late_end")
end

function effect_bullet.on_late_loop(self, now_ms, delta_ms)

end



