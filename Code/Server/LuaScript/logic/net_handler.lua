net_handler = net_handler or {}

function net_handler.OnPlayerMsg(proto_id, msg_buf, player)
    print("net_handler.OnPlayerMsg " .. proto_id)
    
    if #msg_buf > 0 then
        print("net_handler.OnPlayerMsg  3 " .. msg_buf)
        local tb =pb.decode("NetProto.SelectHeroReq", msg_buf)
        print(serpent.block(tb)) 

        local try_item = {
            xxx = "hello world",
            red_hero_id = 20000,
            blue_hero_id = 11000,
        }
        net.send_pb(player:GetNetId(), 101, "NetProto.RspFreeHero", try_item)

        return true
    end
    return false
end