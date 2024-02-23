from __future__ import annotations
import os
from typing import IO, Any, Generator
import toml # not the default toml package because ubuntu use old version of python
import re

class Path:
    def __init__(self, path:str):
        self.path = path
    
    def __str__(self) -> str:
        return self.path
    
    def __truediv__(self, other:str|Path) -> Path:
        if isinstance(other, Path):
            other = other.path
        return Path(self.path+"/"+other)
    
    def mkdir(self, exist_ok:bool = False) -> None: 
        os.makedirs(self.path, exist_ok=exist_ok)

    def iterdir(self) -> Generator[Path]:
        for file in os.listdir(self.path):
            yield Path(self.path+"/"+file)
    
    def all_file_end(self, end:str) -> Generator[Path, Any, None]:
        for root, _, files in os.walk(self.path):
            root = root.replace("\\", "/")
            for file in files:
                if file.endswith(end):
                    yield Path(root+"/"+file)

    def is_dir(self) -> bool:
        return os.path.isdir(self.path)
    
    def open(self, mode:str, encoding=None) -> IO:
        return open(self.path, mode, encoding=encoding)
    
    def with_suffix(self, suffix:str) -> Path:
        return Path("".join(self.path.split(".")[:-1])+suffix)
    
    def parent(self) -> Path:
        return Path(os.path.dirname(self.path))
    
    def name(self) -> str:
        return os.path.basename(self.path)

def gen_header(file:str) -> str:
    """Generate header for file"""
    return "#include \""+file+"\"\n"

def get_c_file_list(directory:Path) -> list[str]:
    """Get all c files in directory"""
    c_file_list:list[Path] = []
    for file in directory.all_file_end(".c"):
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
    