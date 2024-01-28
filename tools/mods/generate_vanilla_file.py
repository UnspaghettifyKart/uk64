import os
from utils import get_c_file_list

def generate_file_vanilla(directory = "vanilla", out="generate_file"):
    print("Generating vanilla file...")
    if not os.path.isdir(out):
        os.mkdir(out)
    c_file_list = get_c_file_list(directory)
    with open(out+'/vanilla.c', "w") as f:
        for file in c_file_list:
            f.write("#include \""+file+"\"\n")
    print("Done!")