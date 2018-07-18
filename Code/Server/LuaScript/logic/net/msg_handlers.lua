msg_handlers = msg_handlers or {}

local handle_pb_SelectHeroReq = function(pid, msg, player) 
    print("fn handle_pb_SelectHeroReq")
    print(msg.hero_id)
    print(serpent.block(msg)) 

    local try_item = {
        xxx = "hello world",
        red_hero_id = 20000,
        blue_hero_id = 11000,
    }
    net.send_pb(player:GetNetId(), 101, "NetProto.RspFreeHero", try_item)
end

msg_handlers[102] = {
    pb_name = "NetProto.SelectHeroReq",
    handle_fn = handle_pb_SelectHeroReq

}