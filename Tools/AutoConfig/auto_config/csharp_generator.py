import jinja2
import os
from .excel_list import EnumFieldType
from .config_list import Excel2CsvDescript

class _CSharpExtraField(object):
    def __init__(self, field_desc, **kwargs):
        self._field_desc = field_desc
        return super().__init__(**kwargs)

    @property
    def field_type(self):
        return ".".join(self._field_desc.field_type)

    @property
    def field_name(self):
        return self._field_desc.field_name


class _CSharpField(object):
    Base_Type_Strs = {
        EnumFieldType.Min: "",
        EnumFieldType.Bool: "bool",
        EnumFieldType.Int: "int",
        EnumFieldType.Long: "long",
        EnumFieldType.Float: "float",
        EnumFieldType.String: "string"
    } 

    Collect_Type_Str_Format = {
        EnumFieldType.Vec: "List<{0}{1}>",
        EnumFieldType.Map: "Dictionary<{0}, {1}>",
        EnumFieldType.VecVec: "List<List<{0}{1}>>",
        EnumFieldType.MapVec: "Dictionary<{0}, List<{1}>>"
    }

    Convert_Function_Strs = {
        EnumFieldType.Min: "",
        EnumFieldType.Bool: "ConfigUtil.Str2BaseValue",
        EnumFieldType.Int: "ConfigUtil.Str2BaseValue",
        EnumFieldType.Long: "ConfigUtil.Str2BaseValue",
        EnumFieldType.Float: "ConfigUtil.Str2BaseValue",
        EnumFieldType.String: "ConfigUtil.Str2Str",
        EnumFieldType.Vec: "ConfigUtil.Str2Vec",
        EnumFieldType.Map: "ConfigUtil.Str2Map",
        EnumFieldType.VecVec: "ConfigUtil.Str2VecVec",
        EnumFieldType.MapVec: "ConfigUtil.Str2MapVec"
    }

    def __init__(self, field_desc, class_name, **kwargs):
        self._field_desc = field_desc
        self._class_name = class_name
        return super().__init__(**kwargs)
        
    @property
    def field_type(self):
        field_type = self._field_desc.type_desc.field_type
        key_type = self._field_desc.type_desc.field_key_type
        val_type = self._field_desc.type_desc.field_val_type
        if EnumFieldType.is_base_type(field_type) or EnumFieldType.String == field_type:
            return _CSharpField.Base_Type_Strs[field_type]
        if EnumFieldType.is_collection_type(field_type):
            return _CSharpField.Collect_Type_Str_Format[field_type].format(
                    _CSharpField.Base_Type_Strs[key_type],
                    _CSharpField.Base_Type_Strs[val_type])
        return ""

    @property
    def field_name(self):
        return self._field_desc.name_desc.name

    @property 
    def default_value(self):
        field_type = self._field_desc.type_desc.field_type
        if EnumFieldType.String == field_type:
            return "string.Empty"
        if EnumFieldType.is_collection_type(field_type):
            return "new {0}()".format(self.field_type)
        return ""

    @property 
    def has_key_set(self):
        return self._field_desc.type_desc.is_key

    @property
    def has_group_set(self):
        return self._field_desc.type_desc.is_group

    @property
    def key_set_type(self):
        if self.has_key_set:
            return "Dictionary<{0}, {1}>".format(
                self.field_type, self._class_name)
        return ""
    
    @property 
    def key_set_name(self):
        if self.has_key_set:
            return "{0}_to_key".format(self.field_name)
        return ""

    @property
    def group_set_type(self):
        if self.has_group_set:
            return "Dictionary<{0}, List<{1}>>".format(
                self.field_type, self._class_name)
        return ""
    
    @property 
    def group_set_name(self):
        if self.has_group_set:
            return "{0}_to_group".format(self.field_name)
        return ""

    @property
    def column_name_tag(self):
        return "Field_Name_{0}".format(self.field_name)

    @property
    def convert_func(self):
        field_type = self._field_desc.type_desc.field_type
        if EnumFieldType.is_base_type(field_type) or EnumFieldType.is_complex_type(field_type):
            return _CSharpField.Convert_Function_Strs[field_type]
        return ""

class CSharpGenerator(object):
    Csharp_Template_File = 'csharp_code/config_template.tt'

    def __init__(self, excel2csv_desc, template_evn, **kwargs):
        self._excel2csv_desc = excel2csv_desc
        self._template_evn = template_evn
        self.code_content = None
        return super().__init__(**kwargs)

    def gen_file(self, log=None):
        code_ctx = self.gen_code(log)
        if not code_ctx:
            return False
        out_file_path = self._excel2csv_desc.out_cs_file_path
        code = code_ctx
        file_path = out_file_path
        if os.path.exists(file_path) and os.path.isfile(file_path):
            os.remove(file_path)
        if not os.path.exists(os.path.dirname(file_path)):
            os.makedirs(os.path.dirname(file_path))
        with open(file_path, 'a') as f:
            f.write(code)
        return True

    def gen_code(self, log=None):
        code_template = self._template_evn.get_template(CSharpGenerator.Csharp_Template_File)
        if not code_template:
            return None
        extra_fields = [_CSharpExtraField(field) for field in self._excel2csv_desc.excel_desc.extra_field_descs]
        fields = [_CSharpField(field, self._excel2csv_desc.class_name) for field in self._excel2csv_desc.excel_desc.field_descs]
        render_dict = {
            "class_name":  self._excel2csv_desc.class_name,
            "fields": fields,
            "extra_fields": extra_fields
        }
        code_ctx = code_template.render(render_dict)
        return code_ctx

    @staticmethod
    def gen(excel2csv_desc, template_env, log=None):
        generator = CSharpGenerator(excel2csv_desc, template_env)
        return generator.gen_file(log)

class _CSharpLoadInfo(object):
    def __init__(self, type_name, field_name, csv_file_path, **kwargs):
        self.type_name = type_name
        self.field_name = field_name
        self.csv_file_path = csv_file_path
        return super().__init__(**kwargs)

class CSharpLoaderGenerator(object):
    Code_Template_File = 'csharp_code/loader_template.tt'
    Save_File_Name = 'CsvConfigSets'
    
    def __init__(self, cfg_list, template_evn, **kwargs):
        self._cfg_list = cfg_list
        self._template_evn = template_evn
        self.code_content = None
        return super().__init__(**kwargs)

    def gen_code(self, log=None):
        code_template = self._template_evn.get_template(CSharpLoaderGenerator.Code_Template_File)
        if not code_template:
            return None
        load_infos = []
        for excel2csv_desc in self._cfg_list.excel2csv_descs:
            type_name = "{0}Set".format(excel2csv_desc.class_name)
            field_name =  "csv_{0}".format(type_name)
            csv_file_path = excel2csv_desc.original_out_csv_file_path.replace('\\', '/').strip('./')
            load_infos.append(_CSharpLoadInfo(type_name, field_name, csv_file_path))
        render_dict = {
            "load_infos": load_infos,
            "save_file_name": CSharpLoaderGenerator.Save_File_Name
        }
        code_ctx = code_template.render(render_dict)
        return code_ctx

    def gen_file(self, log=None):
        code_ctx = self.gen_code(log)
        if not code_ctx:
            return False
        out_file_path = os.path.join(self._cfg_list.out_code_dir, \
            Excel2CsvDescript.CSHARP_CODE_PREFIX, "{0}.cs".format(CSharpLoaderGenerator.Save_File_Name))

        code = code_ctx
        file_path = out_file_path
        if os.path.exists(file_path) and os.path.isfile(file_path):
            os.remove(file_path)
        if not os.path.exists(os.path.dirname(file_path)):
            os.makedirs(os.path.dirname(file_path))
        with open(file_path, 'a') as f:
            f.write(code)
        return True

    @staticmethod
    def gen(cfg_list, template_env, log=None):
        generator = CSharpLoaderGenerator(cfg_list, template_env)
        return generator.gen_file(log)