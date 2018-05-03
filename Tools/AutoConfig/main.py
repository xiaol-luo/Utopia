import os
import sys
import configparser
import re
import logging
import subprocess
import shlex
import jinja2
from auto_config import *
import auto_config.csharp_generator as csharp_generator
import argparse

log = logging

def run(args):
    template_env = jinja2.Environment(loader=jinja2.ChoiceLoader([
        #jinja2.FileSystemLoader(cfg_list_desc.template_dir),
        jinja2.PackageLoader('auto_config', 'templates')
    ]))
    if not template_env:
        return False
    cfg_list_desc = ConfigListDescript.load(args.config_dir)  
    for excel2csv_desc in cfg_list_desc.excel2csv_descs:
        if args.gen_file:
            if not CsvGenerator.gen(excel2csv_desc, log):
                log.error("CsvGenerator gen fail, file %s:%s->%s", excel2csv_desc.file_path, 
                    excel2csv_desc.sheet_name, excel2csv_desc.out_csv_file_path)
                return False
        if args.gen_code:
            if not CppGenerator.gen(excel2csv_desc, template_env, log):
                log.error("CppGenerator gen fail, file %s:%s->%s", excel2csv_desc.file_path, 
                    excel2csv_desc.sheet_name, excel2csv_desc.out_csv_file_path)
                return False
            if not CSharpGenerator.gen(excel2csv_desc, template_env, log):
                log.error("CSharpGenerator gen fail, file %s:%s->%s", excel2csv_desc.file_path, 
                    excel2csv_desc.sheet_name, excel2csv_desc.out_csv_file_path)
                return False
    if args.gen_code:
        if not CppLoaderGenerator.gen(cfg_list_desc, template_env, log):
            log.error("CppLoaderGenerator.load fail")
            return False
        if not CSharpLoaderGenerator.gen(cfg_list_desc, template_env, log):
            log.error("CSharpLoaderGenerator.load fail")
            return False
    return True

if __name__ == "__main__":
    log.basicConfig(level=logging.DEBUG)

    parser = argparse.ArgumentParser()
    parser.add_argument("-cd", '--config_dir',  help='config_dir')
    parser.add_argument("-gc", '--gen_code',  action='store_true', help='gen_code')
    parser.add_argument("-gf", '--gen_file',  action='store_true', help='gen_file')
    args = parser.parse_args()

    if not run(args):
        sys.exit(2)
    log.info("all ok")
