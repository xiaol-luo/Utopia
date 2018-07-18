net_handler = net_handler or {}

function net_handler.OnPlayerMsg(proto_id, msg_buf, player)
    local msg_handler = msg_handlers[proto_id]
    if not msg_handler or not msg_handler.handle_fn then 
        return false
    end

    local pb_msg = nil
    if msg_handler.pb_name then
        pb_msg = pb.decode(msg_handler.pb_name, msg_buf)
        local default_msg = pb.defaults(msg_handler.pb_name)
        setmetatable(pb_msg, { __index = default_msg })
    end
    msg_handler.handle_fn(proto_id, pb_msg, player)
    return true
end