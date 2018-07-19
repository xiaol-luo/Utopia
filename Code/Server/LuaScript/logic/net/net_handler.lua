net_handler = net_handler or {}

function net_handler.OnPlayerMsg(pid, msg_buf, player)
    print("net_handler.OnPlayerMsg " .. pid)
    local handle_item = msg_handlers.handler_map[pid]
    if not handle_item then
        print("net_handler.OnPlayerMsg 1 " .. pid)
        return false
    end
    local fn = handle_item[msg_handlers.HANDLE_FN]
    if not fn then 
        print("net_handler.OnPlayerMsg 2 " .. pid)
        return false
    end
    print("net_handler.OnPlayerMsg 3 " .. pid)
    local pb_msg = nil
    local pb_name = handle_item[msg_handlers.PB_NAME]
    if pb_name then
        pb_msg = pb.decode(pb_name, msg_buf)
        if pb_msg then
            print("net_handler.OnPlayerMsg 4 " .. pid)
            local default_msg = pb.defaults(pb_name)
            setmetatable(pb_msg, { __index = default_msg })
        else
            print("net_handler.OnPlayerMsg 5 " .. pid)
            return false
        end
    end
    print("net_handler.OnPlayerMsg 6 " .. pid)
    fn(player, pid, pb_msg)
    return true
end