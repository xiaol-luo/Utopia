msg_handlers = msg_handlers or {}
msg_handlers.handler_map = msg_handlers.handler_map or {}
msg_handlers.PID = "PID_NAME"
msg_handlers.PB_NAME = "PB_NAME"
msg_handlers.HANDLE_FN = "HANDLE_FN"


msg_handlers.convert_pid = function(pid_name)
    return pb.enum("NetProto.PID", pid_name)
end

function msg_handlers.add_handler(pid, pb_name, fn)
    local item = {} 
    item[msg_handlers.PID] = pid
    item[msg_handlers.PB_NAME] = pb_name
    item[msg_handlers.HANDLE_FN] = fn
    msg_handlers.handler_map[pid] = item
end

local handle_pb_SelectHeroReq = function(player, pid, msg) 
    print("fn handle_pb_SelectHeroReq")
    print(msg.hero_id)
    print(serpent.block(msg)) 
end

msg_handlers.add_handler(
    msg_handlers.convert_pid("PID_SelectHeroReq"),
    "NetProto.SelectHeroReq",
    handle_pb_SelectHeroReq
)

local handle_PID_QueryFreeHero = function(player, pid) 
    print("fn handle_PID_QueryFreeHero")
end
msg_handlers.add_handler(
    msg_handlers.convert_pid("PID_QueryFreeHero"),
    nil,
    handle_PID_QueryFreeHero
)

local handle_pb_PrintPBContent = function(player, pid, msg)
    print("handle_pb_PrintPBContent " .. pid)
    print("table" .. serpent.block(msg))
    print("---------------end --------- \n")
end

msg_handlers.add_handler(
    msg_handlers.convert_pid("PID_BattleOperaReq"),
    "NetProto.BattleOperation",
    handle_pb_PrintPBContent
)