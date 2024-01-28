import os
from utils import get_c_file_list, gen_header

def generate_file_vanilla(directory = "vanilla", out="generate_file"):
    """Generate vanilla.c file who have include all vanilla c files"""
    
    if not os.path.isdir(out):
        os.mkdir(out)
    c_file_list = get_c_file_list(directory)
    with open(out+'/vanilla.c', "w") as f:
        for file in c_file_list:
            f.write(gen_header(file))