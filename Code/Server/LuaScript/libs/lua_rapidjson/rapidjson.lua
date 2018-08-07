
rapidjson = require("rapidjson")

local x = rapidjson.encode('{"a":3}')
print(x)

local t = {}
t.a = 1
x = rapidjson.encode('{"a":3}')

t = rapidjson.decode(x)
print(t)