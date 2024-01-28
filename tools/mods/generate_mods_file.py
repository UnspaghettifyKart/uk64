import os
from utils import get_c_file_list, get_mods_settings, gen_header

def generate_file_mods(directory = "mods", out="generate_file"):
    """Generate mods.c file who have include all mods c files"""
    if not os.path.isdir(out):
        os.mkdir(out)
    mods_settings = get_mods_settings()
    c_file_list = []
    for mod in os.listdir(directory):
        if mod in mods_settings["disabled"]:
            continue

        c_file_list += get_c_file_list(directory+"/"+mod)
    with open(out+'/mods.c', "w") as f:
        for file in c_file_list:
            f.write(gen_header(file))