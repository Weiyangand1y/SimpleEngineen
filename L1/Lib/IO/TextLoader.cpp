#include "textLoader.h"
std::string loadTextFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        std::string script;
        while (std::getline(file, line)) {
            script += line + "\n";
        }
        return script;
        file.close();
    } else {
        std::cout << "Error: Unable to open file" << std::endl;
        return "";
    }
}