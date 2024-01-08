import os, re, sys, json, shutil, tomllib, math

if not os.path.isfile("config/common_grand_prix_human_item_curve.json"):
    open("config/common_grand_prix_human_item_curve.json", "w").write(json.dumps([
        {
            "banana": 30,
            "banana_bunch": 5,
            "green_shell": 30,
            "triple_green_shell": 5,
            "red_shell": 5,
            "fake_item_box": 10,
            "boo": 5,
            "mushroom": 10
        },
        {
            "banana_bunch": 5,
            "green_shell": 5,
            "triple_green_shell": 10,
            "red_shell": 15,
            "triple_red_shell": 20,
            "thunderbolt": 5,
            "fake_item_box": 5,
            "star": 5,
            "boo": 5,
            "mushroom": 5,
            "triple_mushroom": 15,
            "super_mushroom": 5
        },
        {
            "triple_green_shell": 10,
            "red_shell": 20,
            "triple_red_shell": 20,
            "thunderbolt": 5,
            "star": 10,
            "mushroom": 5,
            "triple_mushroom": 20,
            "super_mushroom": 10
        },
        {
            "red_shell": 15,
            "triple_red_shell": 20,
            "blue_spiny_shell": 5,
            "thunderbolt": 10,
            "star": 15,
            "mushroom": 5,
            "triple_mushroom": 20,
            "super_mushroom": 10
        },
        {
            "red_shell": 10,
            "triple_red_shell": 20,
            "blue_spiny_shell": 5,
            "thunderbolt": 10,
            "star": 15,
            "mushroom": 5,
            "triple_mushroom": 25,
            "super_mushroom": 10
        },
        {
            "triple_red_shell": 20,
            "blue_spiny_shell": 10,
            "thunderbolt": 15,
            "star": 20,
            "triple_mushroom": 25,
            "super_mushroom": 10
        },
        {
            "triple_red_shell": 20,
            "blue_spiny_shell": 10,
            "thunderbolt": 20,
            "star": 30,
            "triple_mushroom": 10,
            "super_mushroom": 10
        },
        {
            "triple_red_shell": 20,
            "blue_spiny_shell": 15,
            "thunderbolt": 20,
            "star": 30,
            "triple_mushroom": 5,
            "super_mushroom": 10
        }
    ], indent=4))

if not os.path.isfile("config/common_grand_prix_CPU_item_curve.json"):
    open("config/common_grand_prix_CPU_item_curve.json", "w").write(json.dumps([
        {
            "banana": 60,
            "green_shell": 25,
            "fake_item_box": 10,
            "boo": 5
        },
        {
            "banana": 50,
            "green_shell": 25,
            "triple_green_shell": 5,
            "fake_item_box": 10,
            "boo": 5,
            "mushroom": 5
        },
        {
            "banana": 40,
            "green_shell": 25,
            "triple_green_shell": 10,
            "fake_item_box": 10,
            "boo": 5,
            "mushroom": 10
        },
        {
            "banana": 35,
            "green_shell": 25,
            "triple_green_shell": 15,
            "fake_item_box": 10,
            "boo": 5,
            "mushroom": 10
        },
        {
            "banana": 30,
            "green_shell": 20,
            "triple_green_shell": 20,
            "fake_item_box": 5,
            "star": 5,
            "mushroom": 20
        },
        {
            "banana": 30,
            "green_shell": 20,
            "triple_green_shell": 20,
            "fake_item_box": 5,
            "star": 5,
            "mushroom": 20
        },
        {
            "banana": 30,
            "green_shell": 20,
            "triple_green_shell": 20,
            "star": 10,
            "mushroom": 20
        },
        {
            "banana": 25,
            "green_shell": 20,
            "triple_green_shell": 20,
            "thunderbolt": 1,
            "star": 10,
            "mushroom": 24
        }
    ], indent=4))

if not os.path.isfile("config/common_versus_2_player_item_curve.json"):
    open("config/common_versus_2_player_item_curve.json", "w").write(json.dumps([
        {
            "banana": 25,
            "boo": 5,
            "banana_bunch": 10,
            "green_shell": 30,
            "triple_green_shell": 5,
            "red_shell": 5,
            "fake_item_box": 10,
            "mushroom": 10
        },
        {
            "triple_mushroom": 15,
            "banana_bunch": 5,
            "triple_green_shell": 5,
            "red_shell": 5,
            "blue_spiny_shell": 5,
            "super_mushroom": 20,
            "thunderbolt": 15,
            "triple_red_shell": 15,
            "star": 15
        }
    ], indent=4))

if not os.path.isfile("config/common_versus_3_player_item_curve.json"):
    open("config/common_versus_3_player_item_curve.json", "w").write(json.dumps([
        {
            "banana": 35,
            "banana_bunch": 5,
            "green_shell": 30,
            "red_shell": 5,
            "fake_item_box": 10,
            "boo": 5,
            "mushroom": 10
        },
        {
            "banana": 5,
            "banana_bunch": 5,
            "triple_green_shell": 10,
            "red_shell": 15,
            "triple_red_shell": 15,
            "thunderbolt": 5,
            "fake_item_box": 5,
            "star": 5,
            "boo": 5,
            "mushroom": 5,
            "triple_mushroom": 20,
            "super_mushroom": 5
        },
        {
            "red_shell": 10,
            "triple_red_shell": 20,
            "blue_spiny_shell": 10,
            "thunderbolt": 15,
            "star": 15,
            "triple_mushroom": 20,
            "super_mushroom": 10
        }
    ], indent=4))

if not os.path.isfile("config/common_versus_4_player_item_curve.json"):
    open("config/common_versus_4_player_item_curve.json", "w").write(json.dumps([
        {
            "banana": 35,
            "banana_bunch": 5,
            "green_shell": 30,
            "red_shell": 5,
            "fake_item_box": 10,
            "boo": 5,
            "mushroom": 10
        },
        {
            "banana": 5,
            "banana_bunch": 5,
            "green_shell": 5,
            "triple_green_shell": 10,
            "red_shell": 15,
            "triple_red_shell": 15,
            "fake_item_box": 5,
            "star": 5,
            "boo": 5,
            "mushroom": 5,
            "triple_mushroom": 25
        },
        {
            "banana_bunch": 5,
            "triple_green_shell": 5,
            "red_shell": 10,
            "triple_red_shell": 15,
            "blue_spiny_shell": 5,
            "thunderbolt": 10,
            "fake_item_box": 5,
            "star": 10,
            "mushroom": 5,
            "triple_mushroom": 25,
            "super_mushroom": 5
        },
        {
            "triple_red_shell": 20,
            "blue_spiny_shell": 10,
            "thunderbolt": 15,
            "star": 20,
            "triple_mushroom": 25,
            "super_mushroom": 10
        }
    ], indent=4))

if not os.path.isfile("config/common_battle_item_curve.json"):
    open("config/common_battle_item_curve.json", "w").write(json.dumps([
        {
            "banana": 10,
            "banana_bunch": 5,
            "green_shell": 5,
            "triple_green_shell": 20,
            "red_shell": 20,
            "fake_item_box": 15,
            "star": 20,
            "boo": 5
        }
    ], indent=4))

def convert_to_array_C(item_curve:list[dict]) -> str:
    out = "{\n"
    for i in range(len(item_curve)):
        total_weight = 0
        for item in item_curve[i]:
            total_weight += item_curve[i][item]

        out += "    {\n"
        float_part = 0.0
        for item in item_curve[i]:
            n = item_curve[i][item]/total_weight*100
            float_part += (n - math.floor(n))
            if float_part >= 1:
                float_part -= 1
                n = math.ceil(n)
            else:
                n = math.floor(n)
            out += f"ITEM_{item.upper()},"*n
            out += "\n"
        out += "    },\n"
    out += "}"
    return out
            

files = [
    "config/common_grand_prix_human_item_curve.json",
    "config/common_grand_prix_CPU_item_curve.json",
    "config/common_versus_2_player_item_curve.json",
    "config/common_versus_3_player_item_curve.json",
    "config/common_versus_4_player_item_curve.json",
    "config/common_battle_item_curve.json"
]
out_file = "#ifndef CONFIG_JSON_H\n#define CONFIG_JSON_H\n\n"
for file in files:
    item_curve = json.loads(open(file, "r").read())
    out = convert_to_array_C(item_curve)
    out_file += f"#define CONFIG_{file.split('/')[1].split('.')[0].upper()}_ITEM_CURVE {out.replace("\n", "\\\n")}\n\n"

out_file += "#endif"
open("include/config_json.h", "w").write(out_file)