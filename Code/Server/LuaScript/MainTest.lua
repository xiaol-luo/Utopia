
LuaObject = {}

local Base = {}
local Base_mt = { __index = Base }
-- setmetatable(Base, LuaObject)

function Base.new(weight)
    local ret = setmetatable({}, Base_mt)
    ret.weight = weight
    return ret
end

function Base.SetWeight(self, weight)
    self.weight = weight
end

function Base.GetWeight(self)
    print("Base.GetWeight")
    return self.weight
end

local Derivied = {}
local Derivied_mt = { __index = Derivied }
setmetatable(Derivied, { __index = Base })

Derivied.height = 1000

function Derivied.new(weight, height)
    local ret = setmetatable(Base.new(weight), Derivied_mt)
    -- ret.height = height
    return ret
end

function Derivied.SetHeight(self, height)
    self.height = height
end

function Derivied.GetHeight(self)
    return self.height
end

print("classes", Base, Base_mt, Derivied, Derivied_mt)

local t1 = Base.new(10)
local t3 = Derivied.new(10, 20)

print("instance", t1, t3)
mt_t1 = getmetatable(t1)
mt_t3 = getmetatable(t3)
print("meta t1", mt_t1, mt_t1.__index, mt_t1.__newindex)
print("meta t2", mt_t3, mt_t3.__index, mt_t3.__newindex)

print("before set weight",  t3.height, mt_t3.__index.height)
t3.height = 100
print("after set weight",  t3.height, mt_t3.__index.height)