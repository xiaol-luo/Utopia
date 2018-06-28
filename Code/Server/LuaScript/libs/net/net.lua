net = net or {}

function net.send_pb(netid, protoid, pb_name, pb_table)
    local pb_buf = assert(pb.encode(pb_name, pb_table))
    return net.send_buf(netid, protoid, pb_buf)
end

function net.send_buf(netid, protoid, buf)
    return LuaNet.SendBuffer(netid, protoid, buf)
end