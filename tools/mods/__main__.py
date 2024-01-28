from generate_vanilla_file import generate_file_vanilla
from generate_mods_file import generate_file_mods
from hook import generate_file_hook
import time

if __name__ == "__main__":
    generate_file_vanilla("vanilla", "generate_file")
    generate_file_mods("mods", "generate_file")
    generate_file_hook("mods", "generate_file")
    print("Done!")