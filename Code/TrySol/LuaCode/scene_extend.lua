
local ClassName = "Scene"
TryUserType[ClassName]["LuaTick"] = function (self) 
    print("Scene LuaTick ")
    self.is_done = true
end

TryUserType[ClassName]["LuaStart"] = function (self) 
    print("Scene LuaStart")
end

print("scene_extend.lua load done !")