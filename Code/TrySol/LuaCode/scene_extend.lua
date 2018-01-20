

TryUserType["Scene"]["LuaTick"] = function (self) 
    print("Scene LuaTick ")
    self.is_done = true
end

TryUserType["Scene"]["LuaStart"] = function (self) 
    print("Scene LuaStart")
end

unit = Unit.new(1, 1, 1)
unit.TestProperty = 100
unit.TestProperty2 = 1024
xxx = unit.TestProperty

print("scene_extend.lua load done !")