MODULES=$(wildcard ./src/modules/*.cpp)

builder:
	mkdir -p ./build
	g++ -Wall -Werror -Wpedantic -std=c++17 ./src/main.cpp $(MODULES) -o ./build/CandyLand

run: builder
	./build/CandyLand