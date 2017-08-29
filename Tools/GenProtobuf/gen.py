import os
import sys
import subprocess
import shlex

proto_files = [
	"msg.proto",
	"test.proto"
]
proto_files_str = " ".join(proto_files)
cpp_out = "--cpp_out=./cpp_code"
python_out = "--python_out=./python_code"
csharp_out = "--csharp_out=./csharp_code"
cmd_format = "protoc.exe --proto_path=./proto {0} {1}"

subprocess.call(shlex.split(cmd_format.format(cpp_out, proto_files_str)), shell=True)
subprocess.call(shlex.split(cmd_format.format(python_out, proto_files_str)), shell=True)
 