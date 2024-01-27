import os
import re
from generate_mods_file import get_mods_settings

def get_hook(directory = "."):
    hooks = {}
    for root, dirs, files in os.walk(directory):
        for file in files:
            if file.endswith(".c"):
                hooks.update(get_hook_file(os.path.join(root, file)))
    return hooks

def get_hook_file(file):
    with open(file, "r") as f:
        hook = {}
        for line in f.readlines():
            if line.startswith("HOOK("):
                funct, placement, priority, name = re.findall(r"HOOK\((\w+) *, *(\w+), *(\d+)\)\n.* (\w+)\(", line)[0]
                if funct not in hook:
                    hook[funct] = []
                hook[funct] += [{"placement": placement, "priority": priority, "name": name}]
    return hook

def detect_make_hook(file, hooks):
    modify = False
    lines = []
    with open(file, "r") as f:
        for line in f.readlines():
            for func_name in hooks:
                if func_name in line:
                    modify = True
                    lines+=apply_hook(line, hooks[func_name], func_name)
                else:
                    lines.append(line)

def apply_hook(line, hook, func_name):
    hook_start = [func for func in hook if func["placement"] == "START"]
    hook_start.sort(key=lambda x: x["priority"])
    hook_end = [func for func in hook if func["placement"] == "END"]
    hook_end.sort(key=lambda x: x["priority"])

    lines_out = []
    type_, args = re.findall(r"(\w+) (\w+)\((.*)\)", line)[0]

def generate_file_hook(directory = "mods", out="generate_file"):
    print("Generating hook file...")
    if not os.path.isdir(out):
        os.mkdir(out)
    mods_settings = get_mods_settings()
    hooks = {}
    for mod in os.listdir(directory):
        if mod in mods_settings["disabled"]:
            continue

        hooks.update(get_hook(directory+"/"+mod))
    hook_files = []
    for root, dirs, files in os.walk("vanilla"):
        for file in files:
            if file.endswith(".c"):
                