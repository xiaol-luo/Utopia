
json_configs = {}

json_configs.scene = {}
json_configs.scene_unit = {}
json_configs.skill = {}
json_configs.effect_group = {}
json_configs.effect_hurt = {}
json_configs.effect_heal = {}
json_configs.effect_attrs = {}
json_configs.effect_force_move = {}
json_configs.effect_seacher = {}
json_configs.effect_trace_bullet = {}

local find = function (t, predit_fn, key)
    ret = nil
    for i, v in pairs(t) do
        if predit_fn(v,key) then 
            ret = v
            break
        end
    end
    return ret
end

local match_id = function (t, id)
    return t.id == id
end

local match_name = function (t, name)
    return t.name == name
end

json_configs.get_scene = function (name)
   return find(json_configs.scene, match_name, name)
end

json_configs.get_su = function (id)
    return find(json_configs.scene_unit, match_id, id)
end

json_configs.get_effect_trace_bullet = function (id)
    return find(json_configs.effect_trace_bullet, match_id, id) 
end
