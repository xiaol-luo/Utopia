xxxx = AABB2:new()
print("AABB", xxxx)

local lua_object = {}
lua_object.__index = lua_object

local base = inherit_from(lua_object)

function base.init(self, weight)
    self.weight = weight
end

b1 = base(10)
b2 = base:new(20)
print("b", b1.weight, b2.weight)

local derive = inherit_from(base)

function derive.init(self, weight, height)
    base.init(self, weight)
    self.height = height
end

d1 = derive(100, 10)
d2 = derive:new(200, 20)
print("d", d1.weight, d1.height, d2.weight, d2.height)


local es = effect_script.effect_script_demo:new(1, 2)
print("es", es)