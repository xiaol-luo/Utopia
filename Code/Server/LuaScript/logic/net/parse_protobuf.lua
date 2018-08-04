local pb = pb
local protoc = pb.protoc

local proto_files = {
	"Battle.proto",
	"BattleEnum.proto",
	"Common.proto",
	"Empty.proto",
	"Gm.proto",
	"msg.proto",
	"PID.proto",
	"test.proto",
	"try.proto",
}

local p = protoc:new()
p:addpath("Proto")
for i, v in ipairs(proto_files) do
    p:loadfile(v)
end

for name, basename, type in pb.types() do
    -- print(name, basename, type)
end
