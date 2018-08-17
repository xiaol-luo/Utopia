
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
