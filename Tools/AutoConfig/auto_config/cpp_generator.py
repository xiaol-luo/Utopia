import jinja2
import os
from .excel_list import EnumFieldType

class _CppExtraField(object):
    def __init__(self, field_desc, **kwargs):
        self._field_desc = field_desc
        return super().__init__(**kwargs)

    @property
    def head_file(self):
        return "{0}.h".format("/".join(self._field_desc.field_type))

    @property
    def field_type(self):
        return "::".join(self._field_desc.field_type)

    @property
    def field_name(self):
        return self._field_desc.field_name


class _CppField(object):
    Base_Type_Strs = {
        EnumFieldType.Min: "",
        EnumFieldType.Bool: "bool",
        EnumFieldType.Int: "int",
        EnumFieldType.Long: "long",
        EnumFieldType.Float: "float",
        EnumFieldType.String: "std::string"
    } 

    Collect_Type_Str_Format = {
        EnumFieldType.Vec: "std::vector<{0}{1}>",
        EnumFieldType.Map: "std::map<{0}, {1}>",
        EnumFieldType.VecVec: "std::vector<std::vector<{0}{1}>>",
        EnumFieldType.MapVec: "std::map<{0}, std::vector<{1}>>"
    }

    Convert_Function_Strs = {
        EnumFieldType.Min: "",
        EnumFieldType.Bool: "ConfigUtil::Str2BaseValue",
        EnumFieldType.Int: "ConfigUtil::Str2BaseValue",
        EnumFieldType.Long: "ConfigUtil::Str2BaseValue",
        EnumFieldType.Float: "ConfigUtil::Str2BaseValue",
        EnumFieldType.String: "ConfigUtil::Str2Str",
        EnumFieldType.Vec: "ConfigUtil::Str2Vec",
        EnumFieldType.Map: "ConfigUtil::Str2Map",
        EnumFieldType.VecVec: "ConfigUtil::Str2VecVec",
        EnumFieldType.MapVec: "ConfigUtil::Str2MapVec"
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
            return _CppField.Base_Type_Strs[field_type]
        if EnumFieldType.is_collection_type(field_type):
            return _CppField.Collect_Type_Str_Format[field_type].format(
                    _CppField.Base_Type_Strs[key_type],
                    _CppField.Base_Type_Strs[val_type])
        return ""

    @property
    def field_name(self):
        return self._field_desc.name_desc.name

    @property 
    def default_value(self):
        if EnumFieldType.is_base_type(self._field_desc.type_desc.field_type):
            return "0"
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
            return "std::map<{0}, {1} *>".format(
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
            return "std::map<{0}, std::vector<{1} *>>".format(
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
            return _CppField.Convert_Function_Strs[field_type]
        return ""

class CppGenerator(object):
    Cpp_Template_File = 'cpp_code/cpp_template.tt'
    H_Template_File = 'cpp_code/h_template.tt'

    def __init__(self, excel2csv_desc, template_evn, **kwargs):
        self._excel2csv_desc = excel2csv_desc
        self._template_evn = template_evn
        self.code_content = None
        return super().__init__(**kwargs)

    def gen_file(self, log=None):
        h_code, cpp_code = self.gen_code(log)
        if not h_code or not cpp_code:
            return False
        out_h_file_path = "{0}.h".format(self._excel2csv_desc.out_cpp_file_path)
        out_cpp_file_path = "{0}.cpp".format(self._excel2csv_desc.out_cpp_file_path)
        file_paths = [out_h_file_path, out_cpp_file_path]
        codes = [h_code, cpp_code]
        for i in range(0, len(file_paths)):
            code = codes[i]
            file_path = file_paths[i]
            if os.path.exists(file_path) and os.path.isfile(file_path):
                os.remove(file_path)
            if not os.path.exists(os.path.dirname(file_path)):
                os.makedirs(os.path.dirname(file_path))
            with open(file_path, 'a') as f:
                f.write(code)
        return True

    def gen_code(self, log=None):
        cpp_template = self._template_evn.get_template(CppGenerator.Cpp_Template_File)
        h_template = self._template_evn.get_template(CppGenerator.H_Template_File)
        if not cpp_template or not h_template:
            return None, None
        extra_fields = [_CppExtraField(field) for field in self._excel2csv_desc.excel_desc.extra_field_descs]
        fields = [_CppField(field, self._excel2csv_desc.class_name) for field in self._excel2csv_desc.excel_desc.field_descs]
        head_file_path = self._excel2csv_desc.original_out_cpp_file_path.replace('\\', '/').strip('./')
        render_dict = {
            "class_name":  self._excel2csv_desc.class_name,
            "fields": fields,
            "extra_fields": extra_fields,
            "head_file_path": head_file_path
        }
        h_ret = h_template.render(render_dict)
        cpp_ret = cpp_template.render(render_dict)
        return h_ret, cpp_ret

    @staticmethod
    def gen(excel2csv_desc, template_env, log=None):
        generator = CppGenerator(excel2csv_desc, template_env)
        return generator.gen_file(log)

class _CppLoadInfo(object):
    def __init__(self, type_name, field_name, head_file_path, csv_file_path, **kwargs):
        self.type_name = type_name
        self.field_name = field_name
        self.head_file_path = head_file_path
        self.csv_file_path = csv_file_path
        return super().__init__(**kwargs)

class CppLoaderGenerator(object):
    Cpp_Template_File = 'cpp_code/cpp_loader.tt'
    H_Template_File = 'cpp_code/h_loader.tt'
    Save_File_Name = 'CsvConfigSets'
    
    def __init__(self, cfg_list, template_evn, **kwargs):
        self._cfg_list = cfg_list
        self._template_evn = template_evn
        self.code_content = None
        return super().__init__(**kwargs)

    def gen_code(self, log=None):
        cpp_template = self._template_evn.get_template(CppLoaderGenerator.Cpp_Template_File)
        h_template = self._template_evn.get_template(CppLoaderGenerator.H_Template_File)
        if not cpp_template or not h_template:
            return None, None
        load_infos = []
        for excel2csv_desc in self._cfg_list.excel2csv_descs:
            type_name = "{0}Set".format(excel2csv_desc.class_name)
            field_name =  "csv_{0}".format(type_name)
            head_file_path = "{0}.h".format(
                excel2csv_desc.original_out_cpp_file_path.replace('\\', '/').strip('./'))
            csv_file_path = excel2csv_desc.original_out_csv_file_path.replace('\\', '/').strip('./')
            load_infos.append(_CppLoadInfo(type_name, field_name, head_file_path, csv_file_path))
        render_dict = {
            "load_infos": load_infos,
            "save_file_name": CppLoaderGenerator.Save_File_Name
        }
        h_ret = h_template.render(render_dict)
        cpp_ret = cpp_template.render(render_dict)
        return h_ret, cpp_ret

    def gen_file(self, log=None):
        h_code, cpp_code = self.gen_code(log)
        if not h_code or not cpp_code:
            return False
        out_h_file_path = os.path.join(
            self._cfg_list.out_code_dir, "{0}.h".format(CppLoaderGenerator.Save_File_Name))
        out_cpp_file_path = os.path.join(
            self._cfg_list.out_code_dir, "{0}.cpp".format(CppLoaderGenerator.Save_File_Name))
        file_paths = [out_h_file_path, out_cpp_file_path]
        codes = [h_code, cpp_code]
        for i in range(0, len(file_paths)):
            code = codes[i]
            file_path = file_paths[i]
            if os.path.exists(file_path) and os.path.isfile(file_path):
                os.remove(file_path)
            if not os.path.exists(os.path.dirname(file_path)):
                os.makedirs(os.path.dirname(file_path))
            with open(file_path, 'a') as f:
                f.write(code)
        return True

    @staticmethod
    def gen(cfg_list, template_env, log=None):
        generator = CppLoaderGenerator(cfg_list, template_env)
        return generator.gen_file(log)