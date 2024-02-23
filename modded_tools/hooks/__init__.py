import os
import re
from typing import Any, Generator
from utils import get_mods_settings, gen_header, remove_non_letter, Path

def get_hook(directory:Path) -> dict[str, list[dict]]:
    """Get all hook in directory"""
    hooks = {}
    for file in directory.all_file_end(".c"):
        hooks.update(get_hook_file(file))
    return hooks

def get_hook_file(file:Path) -> dict[str, list[dict]]:
    """Get all hook from file"""
    hooks:dict[str, list[dict]] = {}

    with file.open("r") as f:
        lines:list[str] = f.readlines()

    i = 0
    while i < len(lines):
        if lines[i].startswith("HOOK("):
            list_hook = []
            while lines[i].startswith("HOOK("):
                funct, placement, priority = re.findall(r"HOOK\((\w+) *, *(\w+) *, *(\d+)\)", lines[i])[0]
                list_hook.append((funct, placement, priority))
                i += 1
            name = re.findall(r".* (\w+)\(", lines[i])[0]
            for funct, placement, priority in list_hook:
                if funct not in hooks:
                    hooks[funct] = []

                assert placement in ["START", "END"], "HOOK placement should be either START or END"
                assert funct != name, "HOOK function name should not be the same as the original function name"

                hooks[funct].append({"placement": placement, "priority": int(priority), "name": name, "header": file.with_suffix(".h"), "pattern": re.compile(r".+ +"+funct+r"\(.*\) *{")})
        i += 1
    return hooks

def detect_matching_hook(file:Path, hooks:dict[str, list[dict]], lines_:list[str]) -> Generator[tuple[str, str], Any, None]:
    """Detect matching hook"""
    with file.open("r", encoding="utf-8") as f:
        lines = f.readlines()
        for line in lines:
            for func_name in hooks:
                if hooks[func_name][0]["pattern"].match(line):
                    yield func_name, line
                    break
            else:
                lines_.append(line)

def detect_make_hook(file:Path, hooks:dict[str, list[dict]], out:Path) -> bool:
    """Detect if hook is needed and apply it"""
    modify = False
    lines = []

    for func_name, line in detect_matching_hook(file, hooks, lines):
        modify = True
        lines+=apply_hook(line, hooks[func_name], func_name)
    file_out:Path = out/file
    if modify:
        file_out.parent().mkdir(exist_ok=True)
        with file_out.open("w", encoding="utf-8") as f:
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
        lines_out.append(gen_header(str(hook_["header"])))
    lines_out.append("\n")

    type_, args = re.findall(r"(.+) +\w+\((.*)\)", line)[0]
    args_without_type = ", ".join([remove_non_letter(arg.split(" ")[-1]) for arg in args.split(",")])

    if args_without_type == "void":
        args_without_type = ""

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
        lines_out.append("    {}{}(&cancel{});\n".format(prefix, hook["name"], ", "+args_without_type if args_without_type != "" else ""))
        lines_out.append("    if (cancel) { return "+out+"; }\n")

    lines_out.append("    {}original_{}({});\n".format(prefix,func_name, args_without_type))

    for hook in hook_end:
        lines_out.append("    {}{}({}{});\n".format(prefix, hook["name"], ret_args, args_without_type))

    if type_ != "void":
        lines_out.append("    return ret;\n")

    lines_out.append("}\n\n")

    lines_out.append(type_+" original_"+func_name+"("+args+") {\n")    
    return lines_out

def mod_file_hook(directory:Path = Path("mods"), out:Path = Path("mod_file")):
    """Generate hook file"""    
    mods_settings = get_mods_settings()
    hooks = {}
    
    for mod in directory.iterdir():
        if mod.name() in mods_settings["disabled"]:
            continue
        hooks.update(get_hook(mod))
    
    hook_files = []
    
    for file in Path("src").all_file_end(".c"):
        if detect_make_hook(file, hooks, out):
            hook_files.append((file.with_suffix(".o"), out/file.with_suffix(".o")))

    with (directory/'hook.txt').open("w") as f:
        for file in hook_files:
            print(str(file[0])+","+str(file[1])+"\n")
            f.write(str(file[0])+","+str(file[1])+"\n")