import os
import sys

args = sys.argv
file_path = os.path.abspath(__file__)
valid = {
    "--run": "-r",
    "--help": "-h", 
}
shorthand = ["-r", "-h"]
validarr = list(valid.keys()) + shorthand

run = False
if len(args)>1:
    args = args[1:]
    if not args[0] in validarr:
        print(f"sorry, the argument {args[0]} is not supprted")
        args[0] = "-h"
    arg = valid.get(args[0]) if valid.get(args[0])!=None else args[0]
    if arg == "-h":
        print("""the only supported args are -r, --run, -h, --help
-r/--run is used to run the executable after compilation
-h/--help is used to show this menu""")
        exit(1)
    if arg == "-r":
        run = True
    

module_files = [os.path.join("./src/modules", file) for file in os.listdir('./src/modules') if file.endswith(".cpp")]

compile_command = f"g++ -Wall -Werror -Wpedantic -std=c++17 ./src/main.cpp {' '.join(module_files)} -o ./build/CandyLand"
os.system(compile_command)
if run:
    if os.name == "nt":
        os.system(r".\build\CandyLand.exe")
    else:
        os.system("./build/CandyLand")