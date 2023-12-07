cmake_minimum_required(VERSION 3.0)
project(CandyLand)

set(CMAKE_CXX_STANDARD 17)

# Define the source files
file(GLOB MODULE_SOURCES "src/modules/*.cpp")
set(MAIN_SOURCE "src/main.cpp")

# Create an executable from the sources
add_executable(CandyLandCMake ${MODULE_SOURCES} ${MAIN_SOURCE})

# Set the output directory for the executable
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/build")