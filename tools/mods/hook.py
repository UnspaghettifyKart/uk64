import os
import re
from utils import get_mods_settings, enumerate_c_files, gen_header, remove_non_letter

def get_hook(directory:str) -> dict[str, list[dict]]:
    """Get all hook in directory"""
    hooks = {}
    for root, file in enumerate_c_files(directory):
        hooks.update(get_hook_file(os.path.join(root, file)))
    return hooks

def get_hook_file(file:str) -> dict[str, list[dict]]:
    """Get all hook from file"""
    hooks:dict[str, list[dict]] = {}

    with open(file, "r") as f:
        lines = f.readlines()

    i = 0
    for line in lines:
        if line.startswith("HOOK("):
            funct, placement, priority = re.findall(r"HOOK\((\w+) *, *(\w+) *, *(\d+)\)", line)[0]
            name = re.findall(r".* (\w+)\(", lines[i+1])[0]
            if funct not in hooks:
                hooks[funct] = []

            assert placement in ["START", "END"], "HOOK placement should be either START or END"
            assert funct != name, "HOOK function name should not be the same as the original function name"

            hooks[funct].append({"placement": placement, "priority": int(priority), "name": name, "header": file.replace(".c", ".h")})
        i += 1
    return hooks

def detect_matching_hook(file:str, hooks:dict[str, list[dict]], lines:list[str]) -> tuple[str, str]:
    """Detect matching hook"""
    with open(file, "r") as f:
        for line in f.readlines():
            for func_name in hooks:
                if re.match(r".+ +"+func_name+r"\(.*\) *{", line):
                    yield func_name, line
                    break
            else:
                lines.append(line)

def detect_make_hook(file:str, hooks:dict[str, list[dict]]) -> bool:
    """Detect if hook is needed and apply it"""
    modify = False
    lines = []

    for func_name, line in detect_matching_hook(file, hooks, lines):
        modify = True
        lines+=apply_hook(line, hooks[func_name], func_name)
            
    if modify:
        with open("generate_file/"+file.split("/")[-1], "w") as f:
            f.writelines(lines)

    return modify

def split_hook(hook:list[dict]) -> tuple[list[dict], list[dict]]:
    """Split hook by placement and sort by priority"""
    hook_start = [func for func in hook if func["placement"] == "START"]
    hook_start.sort(key=lambda x: x["priority"])
    hook_end = [func for func in hook if func["placement"] == "END"]
    hook_end.sort(key=lambda x: x["priority"])
    return hook_start, hook_end

def apply_hook(line:str, hook:list[dict], func_name:str) -> list[str]:
    """Apply hook by inserting code in the file"""
    hook_start, hook_end = split_hook(hook)

    lines_out = []
    for hook_ in hook:
        lines_out.append(gen_header(hook_["header"]))
    lines_out.append("\n")

    type_, args = re.findall(r"(.+) +\w+\((.*)\)", line)[0]
    args_without_type = ", ".join([remove_non_letter(arg.split(" ")[-1]) for arg in args.split(",")])

    lines_out.append(type_+" original_"+func_name+"("+args+");\n\n")

    lines_out.append(type_+" "+func_name+"("+args+") {\n")
    lines_out.append("    bool cancel = FALSE;\n")

    prefix = ""
    out = ""
    ret_args = ""

    if type_ != "void":
        lines_out.append("    {} ret;\n".format(type_))
        prefix = "ret = "
        out = "ret"
        ret_args = "&ret, "

    for hook in hook_start:
        lines_out.append("    {}{}(&cancel, {});\n".format(prefix, hook["name"], args_without_type))
        lines_out.append("    if (cancel) { return "+out+"; }\n")

    lines_out.append("    {}original_{}({});\n".format(prefix,func_name, args_without_type))

    for hook in hook_end:
        lines_out.append("    {}{}({}{});\n".format(prefix, hook["name"], ret_args, args_without_type))

    if type_ != "void":
        lines_out.append("    return ret;\n")

    lines_out.append("}\n\n")

    lines_out.append(type_+" original_"+func_name+"("+args+") {\n")    
    return lines_out

def generate_file_hook(directory:str = "mods", out:str = "generate_file"):
    """Generate hook file"""
    if not os.path.isdir(out):
        os.mkdir(out)
    
    mods_settings = get_mods_settings()
    hooks = {}
    
    for mod in os.listdir(directory):
        if mod in mods_settings["disabled"]:
            continue
        hooks.update(get_hook(directory+"/"+mod))
    
    hook_files = []
    
    for root, file in enumerate_c_files("src"):
        if detect_make_hook(os.path.join(root, file), hooks):
            hook_files.append((os.path.join(root, file).replace(".c", ".o"), os.path.join(out, file.replace(".c", ".o"))))

    with open(directory+'/hook.txt', "w") as f:
        for file in hook_files:
            f.write(file[0]+","+file[1]+"\n")