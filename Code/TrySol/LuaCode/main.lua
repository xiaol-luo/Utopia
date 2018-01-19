
local loop = 1
local scene = TryUserType.Scene.new()

function MainTick()
    loop = loop + 1
    print("Lua Main Tick loop " .. loop)
    scene:Tick()
end