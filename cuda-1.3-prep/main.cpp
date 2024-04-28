#include "module.h"

int main() {
    std::fstream file("source.cpp", std::ios_base::in);

    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::string buf;
    std::string line;
    while (std::getline(file, line)) {
        buf += line + "\n"; // Preserve the newline character
    }

    // original
    
    char* _str = nullptr;
    cudaMallocManaged(&_str, buf.size() + 1);
    memcpy(_str, buf.data(), buf.size());

    std::cout << _str << std::endl;

    cu_toupper(_str);

    // after
    std::cout << _str << std::endl;
    
    return 0;
}