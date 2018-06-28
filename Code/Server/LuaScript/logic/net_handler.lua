net_handler = net_handler or {}

function net_handler.OnPlayerMsg(proto_id, msg_buf, player, msg_name)
    print("net_handler.OnPlayerMsg " .. msg_name .. " " .. proto_id)

    print("net_handler.OnPlayerMsg  2 " .. #msg_name)
    
    if #msg_name > 0 then
        print("net_handler.OnPlayerMsg  3 " .. msg_buf)
        local tb =pb.decode(msg_name, msg_buf)
        print(serpent.block(tb)) 
    end
end