#include <iostream>

#include "Parser.cpp"

int main() {
    Parser parser("../asm/mult.asm");
    
    while (true) {
        if (!parser.hasMoreLines()) {
            return 0;
        }
        
        parser.advance();
        std::string test = parser.symbol();
        std::cout << "HELLO WORLD";
    }

    return 0;
}