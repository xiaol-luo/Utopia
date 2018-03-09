STRING_EMPTY = ""

excel_column_num_ascii_map = {
    0:"A", 1:"B", 2:"C", 3:"D", 4:"E", 5:"F", 6:"G", 7:"H", 
    8:"I", 9:"J", 10:"K", 11:"L", 12:"M", 13:"N", 14:"O", 15:"P",
    16:"Q", 17:"R", 18:"S", 19:"T", 20:"U", 21:"V", 22:"W", 23:"X", 24:"Y", 25:"Z"
}

excel_column_ascii_list = ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
                           "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"]

def excel_column(col_idx):
    scale = len(excel_column_ascii_list)
    tmp = int(col_idx - 1)
    ret = excel_column_ascii_list[int(tmp % scale)]
    tmp = int(tmp / scale)
    while tmp > 0:
        ret = "{0}{1}".format(excel_column_ascii_list[int(tmp % scale)], ret)
        tmp = int(tmp / scale)
    return ret

def excel_coordinate(row, col):
    ret = "{0}{1}".format(excel_column(col), row)
    return ret

        
