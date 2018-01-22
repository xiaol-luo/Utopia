


local unit = TryUserType.Unit.new(1, 1, 1)
local scene = TryUserType.Scene.new()
local plant = TryUserType.Plant.new("plant", 10, 100, 100)
local wolf = TryUserType.Wolf.new("wolf", 10, 100, 100, 10, 10, 10)
local sheep = TryUserType.Sheep.new("sheep", 10, 1000, 10, 10, 10)

local loop = 0
game_exit = false

function MainTick()
    if game_exit then 
        return
    end

    loop = loop + 1
    print("Lua Main Tick loop " .. loop)

    sheep:Run()
    wolf:Run()
    sheep:TryAction()
    wolf:TryAction()
    wolf:TryBite(sheep)
    sheep.pos = 100
    
    sheep:TryEatPlant(plant)
    
    if (loop >= 20000) then 
        game_exit = true
    end
end

print("main.lua load done !")