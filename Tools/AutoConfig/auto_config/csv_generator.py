from .config_list import *
import os
import codecs
import csv

class CsvGenerator(object):
    def __init__(self, excel2csv_desc, **kwargs):
        self.excel2csv_desc = excel2csv_desc
        self.csv_rows = None
        return super().__init__(**kwargs)
    
    def gen_file(self, log=None):
        out_csv_file_path = self.excel2csv_desc.out_csv_file_path
        if os.path.exists(out_csv_file_path) and os.path.isfile(out_csv_file_path):
            os.remove(out_csv_file_path)
        if not os.path.exists(os.path.dirname(out_csv_file_path)):
            os.makedirs(os.path.dirname(out_csv_file_path))
        with open(out_csv_file_path, 'a', newline="") as csv_file:
            csv_writer = csv.writer(csv_file)
            if csv_writer:
                self.gen_content()
                for csv_row in self.csv_rows:
                    csv_writer.writerow(csv_row)    
        return True

    def gen_content(self, log=None):
        self.csv_rows = []
        excel_desc = self.excel2csv_desc.excel_desc
        csv_row = [field_desc.name_desc.orignal_str for field_desc in excel_desc.field_descs]
        self.csv_rows.append(csv_row)
        csv_row = [field_desc.type_desc.orignal_str for field_desc in excel_desc.field_descs]
        self.csv_rows.append(csv_row)
        for row in excel_desc.sheet_data.iter_rows(
            min_col=excel_desc.min_column, 
            max_col=excel_desc.max_column, 
            min_row=excel_desc.start_row + 2
            ):
            csv_row = [x.value for x in row]
            self.csv_rows.append(csv_row)

    @staticmethod
    def gen(excel2csv_desc, log=None):
        generator = CsvGenerator(excel2csv_desc)
        return generator.gen_file(log)
