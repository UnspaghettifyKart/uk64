import pathlib
import sys
sys.path.append(str(pathlib.Path(__file__).parent))
from utils import get_mods_settings, get_c_file_list, gen_header, Path
from hooks import mod_file_hook

if __name__ == "__main__":
    out = Path("mod_file")
    out.mkdir(exist_ok=True)

    mods_settings = get_mods_settings()
    c_file_list = []
    mod_directory = Path("mods")
    vanilla_directory = Path("vanilla")

    for mod in mod_directory.iterdir():
        if mod in mods_settings["disabled"] or not mod.is_dir():
            continue
        c_file_list += get_c_file_list(mod)
    
    c_file_list += get_c_file_list(vanilla_directory)
    mod_file_hook(mod_directory, out)

    with (out/'files.c').open("w") as f:
        for file in c_file_list:
            f.write(gen_header(str(file)))
    print("Done!")