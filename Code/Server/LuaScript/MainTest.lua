local pb = pb
local protoc = pb.protoc

assert(protoc:load [[
   message Phone {
      optional string name        = 1;
      optional int64  phonenumber = 2;
   }
   message Person {
      optional string name     = 1;
      optional int32  age      = 2;
      optional string address  = 3;
      repeated Phone  contacts = 4;
   } ]])

local data = {
   name = "ilse",
   age  = 18,
   contacts = {
      { name = "alice", phonenumber = 12312341234 },
      { name = "bob",   phonenumber = 45645674567 }
   }
}

for name, basename, type in pb.types() do
    --print(name, basename, type)
  end

local bytes = assert(pb.encode("Person", data))
print(pb.tohex(bytes))

local data2 = assert(pb.decode("Person", bytes))
serpent.block(data2)

local p = protoc:new()
p:addpath("Proto")

p:loadfile("Battle.proto")
p:loadfile("BattleEnum.proto")

local proto_files = {
    "msg.proto",
	"test.proto",
	"Battle.proto",
	"ProtoId.proto",
	"Common.proto",
	"Empty.proto",
	"BattleEnum.proto",
	"try.proto",
	"Instruction.proto"
}

for i, v in ipairs(proto_files) do
    p:loadfile(v)
end

for name, basename, type in pb.types() do
    --print(name, basename, type)
end

function pb_test()
    local try_item = {
        id = 1,
        name = "hello"
    }
    serpent.dump(try_item)
    print("xxxxxxxxxxxxx")
    serpent.line(try_item)
    local item_bytes = assert(pb.encode("NetProto.TryItem", try_item))

    net.send_pb(0, 0, "NetProto.TryItem", try_item)
    net.send_buf(0, 0, item_bytes)

    return item_bytes
end


pb_test()
