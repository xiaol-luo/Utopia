import os
import subprocess
import shlex

subprocess.call(
    shlex.split("protoc.exe --proto_path=./proto  --cpp_out=./cpp_protobuf msg.proto test.proto"), shell=True)