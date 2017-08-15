import os
import sys
import configparser
import re
import logging
import subprocess
import shlex
import jinja2
from auto_config import *

log = logging

def run(cfg_path):
    template_env = jinja2.Environment(loader=jinja2.ChoiceLoader([
        #jinja2.FileSystemLoader(cfg_list_desc.template_dir),
        jinja2.PackageLoader('auto_config', 'templates')
    ]))
    if not template_env:
        return False
    cfg_list_desc = ConfigListDescript.load(cfg_path)  
    for excel2csv_desc in cfg_list_desc.excel2csv_descs:
        if not CsvGenerator.gen(excel2csv_desc, log):
            log.error("CsvGenerator gen fail, file %s:%s->%s", excel2csv_desc.file_path, 
                excel2csv_desc.sheet_name, excel2csv_desc.out_csv_file_path)
            return False
        if not CppGenerator.gen(excel2csv_desc, template_env, log):
            log.error("CppGenerator gen fail, file %s:%s->%s", excel2csv_desc.file_path, 
                excel2csv_desc.sheet_name, excel2csv_desc.out_csv_file_path)
            return False
    if not CppLoaderGenerator.gen(cfg_list_desc, template_env, log):
        log.error("CppLoaderGenerator.load fail")
        return False
    return True

if __name__ == "__main__":
    log.basicConfig(level=logging.DEBUG)
    if len(sys.argv) < 2:
        sys.exit(1)
    if not run(os.path.abspath(sys.argv[1])):
        sys.exit(2)
    log.info("all ok")
