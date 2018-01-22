

local scene = TryUserType.Scene.new()


local loop = 0
game_exit = false

function MainTick()
    if game_exit then 
        return
    end

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