

local scene = TryUserType.Scene.new()


local loop = 0
game_exit = false

function MainTick()
    if game_exit then
        return
    end

	local a
	local zz
	a = NetProto.TryItem.new()
	a.id = 10
	zz = a.id
	a.name = "1234"
	zz = a.name
	
	a = NetProto.TryMsg.new()
	a.int_val = 10
	zz = a.int_val
	a.str_val = "224"
	zz = a.str_val
	a.nest_enum_val = NetProto.TryMsg.TryNestEnum.a
    zz = a.nest_enum_val
    -- a.nest_enum_array[5] = 2456
    zz = a.nest_enum_array
    a.nest_enum_array[2] = 777
    cc = a.nest_enum_array[-1]
    a.nest_enum_array[-1] = 888
	zz[1] = 2345
	len = #zz
	-- zz = a.nest_enum_array[1]
	
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