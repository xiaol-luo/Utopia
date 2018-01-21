


local unit = TryUserType.Unit.new(1, 1, 1)
local scene = TryUserType.Scene.new()

local loop = 0
game_exit = false

function MainTick()
    if game_exit then 
        return
    end

    loop = loop + 1
    print("Lua Main Tick loop " .. loop)

    if (loop >= 20) then 
        game_exit = true
    end
end

print("main.lua load done !")