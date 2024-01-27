import generate_vanilla_file
import generate_mods_file
import time

if __name__ == "__main__":
    generate_vanilla_file.generate_file_vanilla("vanilla", "generate_file")
    generate_mods_file.generate_file_mods("mods", "generate_file")