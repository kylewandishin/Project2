import os

module_files = [f"./src/modules/{file}" for file in os.listdir('./src/modules') if file.endswith(".cpp")]

compile_command = f"g++ -Wall -Werror -Wpedantic -std=c++17 ./src/main.cpp {' '.join(module_files)}"

os.system(compile_command)
os.system("./a.out")