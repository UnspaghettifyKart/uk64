import os
import toml # not the default toml package because ubuntu use old version of python
import re
from pathlib import Path

def gen_header(file:str) -> str:
    """Generate header for file"""
    return "#include \""+file+"\"\n"

def get_c_file_list(directory:Path) -> list[str]:
    """Get all c files in directory"""
    c_file_list:list[Path] = []
    for file in directory.glob("**/*.c"):
        c_file_list.append(file)
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