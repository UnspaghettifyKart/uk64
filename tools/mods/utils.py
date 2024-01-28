import os
import toml # not the default toml package because ubuntu use old version of python
import re

def enumerate_c_files(directory:str) -> tuple[str, str]:
    """Enumerate all c files in directory"""
    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith(".c"):
                yield root, file

def gen_header(file:str) -> str:
    """Generate header for file"""
    return "#include \""+file+"\"\n"

def get_c_file_list(directory:str) -> list[str]:
    """Get all c files in directory"""
    c_file_list:list[str] = []
    for root, file in enumerate_c_files(directory):
        c_file_list.append(os.path.join(root, file))
    return c_file_list

def get_mods_settings(file:str = "mods/mods.toml") -> dict:
    """Get mods settings"""
    if not os.path.isfile(file):
        with open(file, "w") as f:
            f.write("[disabled]\n")
        return {"disabled": []}

    with open(file, "r") as f:
        return toml.load(f)

def remove_non_letter(string:str) -> str:
    """Remove non letter from string"""
    return re.sub(r"[^a-zA-Z0-9_]", "", string)