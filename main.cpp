#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

const std::string cmakeTemplateTop = "cmake_minimum_required(VERSION 3.10) \n\nproject(";
const std::string cmakeTemplateBottom = ")\n\nset(CMAKE_CXX_STANDARD 20)\nset(CMAKE_CXX_STANDARD_REQUIRED True)\n\nadd_executable(";
const std::string cmakeTemplateEnd = " main.cpp)\n";

const std::string cppContent = R"(#include <iostream>

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
)";

bool writeFile(const std::string &path, const std::string &content) {
    std::ofstream file(path);
    if (!file) {
        return false;
    }
    file << content;
    file.close();
    return true;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Please provide the project name." << std::endl;
        return 1;
    }

    std::string projectName = argv[1];
    std::filesystem::path projectDir = projectName;

    // Create directory with the project name
    if (!std::filesystem::create_directory(projectDir)) {
        std::cerr << "Error creating project directory." << std::endl;
        return 1;
    }

    // Create CMakeLists.txt content
    std::string cmakeContent = cmakeTemplateTop + projectName + cmakeTemplateBottom + projectName + cmakeTemplateEnd;

    // Write CMakeLists.txt
    if (!writeFile((projectDir / "CMakeLists.txt").string(), cmakeContent)) {
        std::cerr << "Error writing CMakeLists.txt." << std::endl;
        return 1;
    }

    // Write main.cpp
    if (!writeFile((projectDir / "main.cpp").string(), cppContent)) {
        std::cerr << "Error writing main.cpp." << std::endl;
        return 1;
    }

    std::cout << "Project successfully created." << std::endl;
    return 0;
}
