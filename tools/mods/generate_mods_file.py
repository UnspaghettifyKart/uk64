import os
import re
import toml # not the default toml package because ubuntu use old version of python

def get_mods_settings(file = "mods/mods.toml"):
    with open(file, "r") as f:
        return toml.load(f)

def get_c_file_list(directory = "."):
    c_file_list = []
    for root, dirs, files in os.walk(directory):
        for file in files:
            if file.endswith(".c"):
                c_file_list.append(os.path.join(root, file))
    return c_file_list

def generate_file_mods(directory = "mods", out="generate_file"):
    if not os.path.isdir(out):
        os.mkdir(out)
    mods_settings = get_mods_settings()
    for mod in os.listdir(directory):
        if mod in mods_settings["disabled"]:
            continue

        c_file_list = get_c_file_list(directory+"/"+mod)
        with open(out+'/mods.c', "w") as f:
            for file in c_file_list:
                f.write("#include \""+file+"\"\n")