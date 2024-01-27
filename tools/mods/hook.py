import os

def get_hook(directory = "."):
    hook = {}
    for root, dirs, files in os.walk(directory):
        for file in files:
            if file.endswith(".c"):
                hook.update(get_hook_file(os.path.join(root, file)))
    return hook

def get_hook_file(file):
    print("Generating hook file...")
    if not os.path.isdir(out):
        os.mkdir(out)
    c_file_list = get_hook(directory)
    with open(out+'/hook.c', "w") as f:
        for file in c_file_list:
            f.write("#include \""+file+"\"\n")
    print("Done!")