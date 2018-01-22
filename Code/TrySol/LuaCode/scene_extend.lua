
local ClassName = "Scene"
TryUserType[ClassName]["LuaTick"] = function (self) 
    print("Scene LuaTick")
    self.sheep:Run()
    self.wolf:Run()
    print("Scene LuaTick 2")
    for i = 1, #self.plants do 
        self.sheep:TryEatPlant(self.plants[i])
    end
    self.wolf:TryBite(self.sheep)

    if self.sheep.is_dead then 
        self.is_done = true
        print("sheep is lost")
        return
    end

    if (self.wolf.energy <= 0) then 
        self.is_done = true
        print("wolf is lose");
        return
    end
end

TryUserType[ClassName]["LuaStart"] = function (self) 
    print("Scene LuaStart")
    local wolf = TryUserType.Wolf.new("wolf", 10, 100, 100, 10, 10, 10)
    local sheep = TryUserType.Sheep.new("sheep", 10, 1000, 10, 10, 10)

    self.wolf = wolf;
    self.sheep = sheep
    self.plants = {}
    
    for i = 1, 5 do 
        local plant = TryUserType.Plant.new("plant", i * 10, 100, 100)
        table.insert(self.plants, plant)
    end

end

print("scene_extend.lua load done !")