
json_configs.scene = rapidjson.load("json_config/skill_editor/scene_config.json")
print("json config scene")
print(serpent.block(json_configs.scene))

json_configs.scene_unit = rapidjson.load("json_config/skill_editor/scene_unit_config.json")
print("json config scene_unit")
print(serpent.block(json_configs.scene_unit))


json_configs.skill = rapidjson.load("json_config/skill_editor/skill_config.json")
print("json config skill")
print(serpent.block(json_configs.skill))
