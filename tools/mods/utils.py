import os
import toml # not the default toml package because ubuntu use old version of python

def enumerate_c_files(directory = "."):
    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith(".c"):
                yield root, file

def get_c_file_list(directory = "."):
    c_file_list = []
    for root, file in enumerate_c_files(directory):
        c_file_list.append(os.path.join(root, file))
    return c_file_list

def get_mods_settings(file:str = "mods/mods.toml"):
    if not os.path.isfile(file):
        with open(file, "w") as f:
            f.write("[disabled]\n")
        return {"disabled": []}

    with open(file, "r") as f:
        return toml.load(f)
