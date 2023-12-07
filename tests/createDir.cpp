#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

int main() {
    std::string directory_name = "../logs";

    if (!fs::exists(directory_name)) {
        if (fs::create_directory(directory_name)) {
            std::cout << "Directory created successfully: " << directory_name << std::endl;
        } else {
            std::cerr << "Failed to create directory!" << std::endl;
            return 1; // Return an error code
        }
    } else {
        std::cout << "Directory already exists: " << directory_name << std::endl;
    }

    return 0; // Return success
}
