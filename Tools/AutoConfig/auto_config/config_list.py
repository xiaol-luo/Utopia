import configparser
import re
import os
from .define import STRING_EMPTY
from .excel_list import ExcelDescript

class Excel2CsvDescript(object):
    def __init__(self, owner, **kwargs):
        self._owner = owner
        self.file_path = STRING_EMPTY
        self.sheet_name = STRING_EMPTY
        self.original_out_csv_file_path = STRING_EMPTY
        self.out_csv_file_path = STRING_EMPTY
        self.class_name = STRING_EMPTY
        self.out_cs_file_path = STRING_EMPTY
        self.out_cpp_file_path = STRING_EMPTY
        self.original_out_cpp_file_path = STRING_EMPTY
        self.out_lua_file_path = STRING_EMPTY
        self.excel_desc = None
        return super().__init__(**kwargs)
   
    @staticmethod
    def _build_path(dir_path, file_path):
        ret = None
        if file_path:
            if os.path.isabs(file_path): ret = file_path
            else: ret = os.path.join(dir_path, file_path)
        return os.path.abspath(ret) 
     
    CPP_CODE_PREFIX = "Cpp"
    LUA_CODE_PREFIX = "Lua"
    CSHARP_CODE_PREFIX = "CSharp"


    def init(self, cfg_section):
        self.file_path = Excel2CsvDescript._build_path(self._owner.excel_dir, cfg_section["file_path"])
        self.sheet_name = cfg_section["sheet_name"]
        self.original_out_csv_file_path = cfg_section["out_csv_file_path"]
        self.out_csv_file_path = self._build_path(self._owner.out_config_dir, cfg_section["out_csv_file_path"])
        self.class_name = cfg_section["class_name"]
        self.out_cs_file_path = Excel2CsvDescript._build_path(\
               os.path.join(self._owner.out_code_dir, Excel2CsvDescript.CSHARP_CODE_PREFIX), cfg_section["out_cs_file_path"])
        self.original_out_cpp_file_path = cfg_section["out_cpp_file_path"]
        self.out_cpp_file_path = Excel2CsvDescript._build_path(\
                os.path.join(self._owner.out_code_dir, Excel2CsvDescript.CPP_CODE_PREFIX), cfg_section["out_cpp_file_path"])
        self.out_lua_file_path = Excel2CsvDescript._build_path(\
                os.path.join(self._owner.out_code_dir, Excel2CsvDescript.LUA_CODE_PREFIX), cfg_section["out_lua_file_path"])
        self.excel_desc = ExcelDescript.load(self.file_path, self.sheet_name)
        return self.excel_desc != None


class ConfigListDescript(object):
    ENV_SECTION = "env"
    EXCEL2CSV_REGEX_PATTERN = r'^excel2csv-.*'

    def __init__(self, **kwargs):
        self.data_dir = STRING_EMPTY
        self.excel_dir = STRING_EMPTY
        self.out_config_dir = STRING_EMPTY
        self.out_code_dir = STRING_EMPTY
        self.excel2csv_descs = []
        return super().__init__(**kwargs)

    def init(self, cfg_praser):
        if not cfg_praser.has_section(ConfigListDescript.ENV_SECTION):
            return False
        env_section = cfg_praser[ConfigListDescript.ENV_SECTION]
        self.data_dir = os.path.abspath(env_section["data_dir"])
        self.excel_dir = os.path.join(self.data_dir, env_section["excel_dir"])
        self.out_config_dir = os.path.join(self.data_dir, env_section["out_config_dir"])
        self.out_code_dir = os.path.join(self.data_dir, env_section["out_code_dir"])
        self.excel2csv_descs = []
        for section_name in cfg_praser.sections():
            if not re.match(ConfigListDescript.EXCEL2CSV_REGEX_PATTERN, section_name):
                continue
            excel2csv_desc = Excel2CsvDescript(self)
            if not excel2csv_desc.init(cfg_praser[section_name]):
                print("cfg_path - {0} error".format(section_name))
            else:
                self.excel2csv_descs.append(excel2csv_desc)
        return True

    @staticmethod
    def load(file_path):
        env_desc = None
        if os.path.exists(file_path) and os.path.isfile(file_path): 
            with open(file_path, "r") as f:
                cfg_praser = configparser.ConfigParser()
                cfg_praser.read_file(f)
                env_desc = ConfigListDescript()
                if not env_desc.init(cfg_praser):
                    env_desc = None
        return env_desc