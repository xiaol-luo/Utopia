

effect_script.effect_bullet = inherit_from(effect_script.effect_base)
local effect_bullet = effect_script.effect_bullet

function effect_bullet.init(self, effect, cfg)
    effect_script.effect_base.init(self, effect, cfg)
    self.cfg = self.json_cfg
    self.hited_suids = {}
    if nil == self.cfg then
        self.is_done = true
    end
end

function effect_bullet.bullet_hit_action(self, bullet, hit_sus)
    print("effect_bullet.bullet_hit_action")
    print(serpent.block(hit_sus))

    for k, v in pairs(hit_sus) do
        if nil == self.hited_suids[k] then
            self.hited_suids[k] = true
            local hit_effect_id = 1000001
            local use_effect_param = self.effect:GetUseEffectParam()
            local scene_effects = self.effect:GetSceneEffects()
            local hit_effect = scene_effects:CreateEffect(hit_effect_id)
            use_effect_param.target_suid = k
            hit_effect:Begin(use_effect_param)
            bullet:SetDone()
        end
    end
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
        return
    end

    local use_effect_param = self.effect:GetUseEffectParam()
    local param = GameLogic.BulletParam.new()
    param.target_type = self.cfg.json_cfg.target_type
    param.target_pos.x = use_effect_param.pos.x
    param.target_pos.z = use_effect_param.pos.y
    if self.cfg.json_cfg.target_type == GameLogic.EBulletTarget.EBulletTarget_SceneUnit then
        local target_su = self.effect:GetSu(use_effect_param.target_suid)
        param.target_su = target_su
    end
    param.max_alive_sec = self.cfg.json_cfg.max_alive_sec
    param.move_speed = self.cfg.json_cfg.move_speed
    param.use_effect_param = use_effect_param
    param.calibre = self.cfg.json_cfg.calibre
    param.hit_filter_id = self.cfg.json_cfg.hit_filter_id
    param.model_id = self.cfg.json_cfg.model_id
    param.body_radius = self.cfg.json_cfg.body_radius
    param.hit_action = create_bullet_action(self, effect_bullet.bullet_hit_action)
    param.done_action = create_bullet_action(self,effect_bullet.bullet_done_action)
	local start_pos = self.effect:GetSkill():GetCaster():GetTransform():GetPos()
    local gm = GameLogic.AddBulletToScene(start_pos, param.use_effect_param.dir, param)
end

function effect_bullet.on_late_end(self)
    print("effect_demo.on_late_end")
end

function effect_bullet.on_late_loop(self, now_ms, delta_ms)

end



