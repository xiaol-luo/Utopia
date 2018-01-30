import os
import sys
import subprocess
import shlex
import logging as log
log.basicConfig(level=log.DEBUG)

proto_files = [
	"msg.proto",
	"test.proto",
	"Battle.proto",
	"ProtoId.proto",
	"Common.proto",
	"Empty.proto",
	"BattleEnum.proto",
	"try.proto",
]

out_options = [
	"--cpp_out=./cpp_code",
	"--csharp_out=./csharp_code",
	"--python_out=./python_code"
]

for out_opt in out_options:
	cmd_format = "protoc.exe --proto_path=./proto {0} {1}"
	p = subprocess.Popen(shlex.split(cmd_format.format(out_opt, " ".join(proto_files))), shell=True, \
			stdout=subprocess.PIPE, stdin=subprocess.PIPE, universal_newlines=True)
	(std_out, std_err) = p.communicate()
	if p.returncode:
		log.error("{0}\n {1}".format(std_out, std_err))
 