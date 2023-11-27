MODULES = $(wildcard ./src/modules/*.cpp)

build:
	g++ -Wall -Werror -Wpedantic -std=c++17 ./src/main.cpp $(MODULES) -o ./build/CandyLand

run: build
	ifeq ($(OS),Windows_NT)
		./build/CandyLand.exe
	else
		./build/CandyLand
	endif

clean:
	rm -rf ./build

.PHONY: all clean