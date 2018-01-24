

local scene = TryUserType.Scene.new()


local loop = 0
game_exit = false

function MainTick()
    if game_exit then
        return
    end

    local enum_unknown = TryUserType.UnitType.UnitType_Unknown
    local enum_animal = TryUserType.UnitType.UnitType_Animal
    local enum_plant = TryUserType.UnitType.UnitType_Plant

    print("enum ", enum_unknown, enum_animal, enum_plant)

    loop = loop + 1
    print("Lua Main Tick loop " .. loop)

    if scene.is_done then
        scene:Start()
    end

    scene:Tick()
    if (loop >= 20000) then
        game_exit = true
    end
end

print("main.lua load done !")