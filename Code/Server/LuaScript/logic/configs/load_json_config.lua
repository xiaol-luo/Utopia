
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


local su_filter_json = rapidjson.load("json_config/skill_editor/filter_config.json")
json_configs.su_filter = su_filter_json.cfgs
print("json config su_filter_json")
print(serpent.block(json_configs.su_filter_json))


local effect_group = rapidjson.load("json_config/skill_editor/effect/effect_group_config.json")
json_configs.effect_group = effect_group.cfgs
print("json config effect_group")
print(serpent.block(json_configs.effect_group))

local effect_hurt = rapidjson.load("json_config/skill_editor/effect/hurt_effect.json")
json_configs.effect_hurt = effect_hurt.cfgs
print("json config effect_hurt")
print(serpent.block(json_configs.effect_hurt))

local effect_heal = rapidjson.load("json_config/skill_editor/effect/heal_effect.json")
json_configs.effect_heal = effect_heal.cfgs
print("json config effect_heal")
print(serpent.block(json_configs.effect_heal))

local effect_seacher = rapidjson.load("json_config/skill_editor/effect/searcher_effect.json")
json_configs.effect_seacher = effect_seacher.cfgs
print("json config effect_seacher")
print(serpent.block(json_configs.effect_seacher))

local effect_attrs = rapidjson.load("json_config/skill_editor/effect/attrs_effect.json")
json_configs.effect_attrs = effect_attrs.cfgs
print("json config effect_attrs")
print(serpent.block(json_configs.effect_attrs))

local effect_force_move = rapidjson.load("json_config/skill_editor/effect/force_move_effect.json")
json_configs.effect_force_move = effect_force_move.cfgs
print("json config effect_force_move")
print(serpent.block(json_configs.effect_force_move))

local effect_script = rapidjson.load("json_config/skill_editor/effect/script_effect.json")
json_configs.effect_script = effect_script.cfgs
print("json config effect_script")
print(serpent.block(json_configs.effect_script))

for i, v in pairs(json_configs.effect_script) do
    v.json_cfg = rapidjson.decode(v.json_param)
    print(serpent.block(v.json_cfg))
end
