"""post-build hook script"""
import argparse

def get_config(file:str):
    """Get hook config"""
    hook_file = []
    with open(file, "r") as f:
        for line in f.read().split("\n"):
            if line == "":
                continue
            hook_file.append(line.split(","))
    return hook_file

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('input', default='mods/hook.txt', help='input file')
    parser.add_argument('output', default='build/us/mk64.ld', help='output file')
    args = parser.parse_args()
    
    hook_file = get_config(args.input)
    with open(args.output, "r") as f:
        ld_file = f.read()

    for hook in hook_file:
        ld_file = ld_file.replace("build/us/"+hook[0], "build/us/"+hook[1])
    
    with open(args.output, "w") as f:
        f.write(ld_file)
    