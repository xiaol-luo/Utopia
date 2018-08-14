
local scene_json = rapidjson.load("json_config/skill_editor/scene_config.json")
json_configs.scene = scene_json.cfgs
print("json config scene")
print(serpent.block(json_configs.scene))

local su_json = rapidjson.load("json_config/skill_editor/scene_unit_config.json")
json_configs.scene_unit = su_json.cfgs
print("json config scene_unit")
print(serpent.block(json_configs.scene_unit))


local skill_json = rapidjson.load("json_config/skill_editor/skill_config.json")
json_configs.skill = skill_json.cfgs
print("json config skill")
print(serpent.block(json_configs.skill))


function json_configs.get_scene(key)
    local ret = nil
    for i, v in ipairs(json_configs.scene) do
        if v.name == key then 
            ret = v
            break
        end
    end
    return  ret
end

function json_configs.get_su(id)
    local ret = nil
    for i, v in ipairs(json_configs.scene_unit) do
        if v.id == id then 
            ret = v
            break
        end
    end
    return  ret
end

function json_configs.get_skill(id)
    local ret = nil
    for i, v in ipairs(json_configs.skill) do
        if v.id == id then 
            ret = v
            break
        end
    end
    return ret
end