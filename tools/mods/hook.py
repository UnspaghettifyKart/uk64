import os
import re
from utils import get_mods_settings, enumerate_c_files

def get_hook(directory = "."):
    hooks = {}
    for root, file in enumerate_c_files(directory):
        hooks.update(get_hook_file(os.path.join(root, file)))
    return hooks

def get_hook_file(file:str):
    with open(file, "r") as f:
        hook = {}
        lines = f.readlines()

    i = 0
    for line in lines:
        if line.startswith("HOOK("):
            funct, placement, priority = re.findall(r"HOOK\((\w+) *, *(\w+), *(\d+)\)", line)[0]
            name = re.findall(r".* (\w+)\(", lines[i+1])[0]
            if funct not in hook:
                hook[funct] = []
            hook[funct] += [{"placement": placement, "priority": priority, "name": name, "header": file.replace(".c", ".h")}]
        i += 1
    return hook

def detect_make_hook(file:str, hooks:dict):
    modify = False
    lines = []
    with open(file, "r") as f:
        for line in f.readlines():
            for func_name in hooks:
                if re.match(r".+ +"+func_name+r"\(.*\) *{", line):
                    modify = True
                    lines+=apply_hook(line, hooks[func_name], func_name)
                    break
            else:
                lines.append(line)
    if modify:
        with open("generate_file/"+file.split("/")[-1], "w") as f:
            f.writelines(lines)
    return modify

def apply_hook(line, hook, func_name):
    hook_start = [func for func in hook if func["placement"] == "START"]
    hook_start.sort(key=lambda x: x["priority"])
    hook_end = [func for func in hook if func["placement"] == "END"]
    hook_end.sort(key=lambda x: x["priority"])

    lines_out = []
    for hook_ in hook:
        lines_out.append("#include \""+hook_["header"]+"\"\n")

    lines_out.append("\n")

    type_, args = re.findall(r"(.+) +\w+\((.*\))", line)[0]
    args_without_type = ", ".join(re.findall(r"([\w\d_]+) *[,)]", args))
    lines_out.append(type_+" original_"+func_name+"("+args+";\n")
    lines_out.append(type_+" "+func_name+"("+args+" {\n")
    lines_out.append("    bool cancel = FALSE;\n")
    if type_ != "void":
        lines_out.append("    {} ret;\n".format(type_))
        for hook in hook_start:
            lines_out.append("    ret = {}(&cancel, {});\n".format(hook["name"], args_without_type))
            lines_out.append("    if (cancel) { return ret; }\n")
        lines_out.append("    ret = original_{}({});\n".format(func_name, args_without_type))
        for hook in hook_end:
            lines_out.append("    ret = {}({},ret);\n".format(hook["name"], args_without_type))
        lines_out.append("    return ret;\n")
    else:
        for hook in hook_start:
            lines_out.append("    {}(&cancel, {});\n".format(hook["name"], args_without_type))
            lines_out.append("    if (cancel) { return; }\n")
        lines_out.append("    original_{}({});\n".format(func_name, args_without_type))
        for hook in hook_end:
            lines_out.append("    {}({});\n".format(hook["name"], args_without_type))
    lines_out.append("}\n")
    lines_out.append("\n")

    lines_out.append(type_+" original_"+func_name+"("+args+" {\n")    
    return lines_out

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
    print(hooks)
    hook_files = []
    for root, dirs, files in os.walk("src"):
        for file in files:
            if file.endswith(".c"):
                if detect_make_hook(os.path.join(root, file), hooks):
                    hook_files.append((os.path.join(root, file).replace(".c", ".o"), os.path.join(out, file.replace(".c", ".o"))))
    with open(directory+'/hook.txt', "w") as f:
        for file in hook_files:
            f.write(file[0]+","+file[1]+"\n")