
TmpSeceneTable = {}

local ClassName = "Scene"
TryUserType[ClassName]["LuaTick"] = function (self) 
    TmpSeceneTable.sheep:Run()
    TmpSeceneTable.wolf:Run()
    for i = 1, #TmpSeceneTable.plants do 
        TmpSeceneTable.sheep:TryEatPlant(TmpSeceneTable.plants[i])
    end
    TmpSeceneTable.wolf:TryBite(TmpSeceneTable.sheep)

    if TmpSeceneTable.sheep.is_dead then 
        self.is_done = true
        return
    end

    if (TmpSeceneTable.wolf.energy <= 0) then 
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

    self.params.

    TmpSeceneTable.wolf = wolf
    TmpSeceneTable.sheep = sheep
    TmpSeceneTable.plants = {}

    for i = 1, 5 do 
        local plant = TryUserType.Plant.new("plant", i * 10, 100, 100)
        table.insert(TmpSeceneTable.plants, plant)
    end
    print("Scene LuaStart end")
end

print("scene_extend.lua load done !")