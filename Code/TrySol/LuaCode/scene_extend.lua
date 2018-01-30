
local ClassName = "Scene"
TryUserType[ClassName]["LuaTick"] = function (self) 
    self.params.sheep:Run()
    self.params.wolf:Run()
    for i = 1, #self.params.plants do 
        self.params.sheep:TryEatPlant(self.params.plants[i])
    end
    self.params.wolf:TryBite(self.params.sheep)
	self.params.wolf:ExTryBite(self.params.sheep)

    if self.params.sheep.is_dead then 
        self.is_done = true
        return
    end

    if (self.params.wolf.energy <= 0) then 
        self.is_done = true
        print("wolf is lose");
        return
    end

    print("Scene LuaTick end")
end

TryUserType[ClassName]["LuaStart"] = function (self) 
    print("Scene LuaStart")
    local wolf = TryUserType.Wolf.new("wolf", 10, 100, 100, 10, 10, 10)
    local sheep = TryUserType.Sheep.new("sheep", 10, 1000, 10, 10, 10)

    self.params.wolf = wolf
    self.params.sheep = sheep
    self.params.plants = {}

    for i = 1, 5 do 
        local plant = TryUserType.Plant.new("plant", i * 10, 100, 100)
        table.insert(self.params.plants, plant)
    end
    print("Scene LuaStart end")
end

print("scene_extend.lua load done !")