#include "Parser.hpp";
#include <fstream>;
#include <iostream>;

Parser::Parser(const std::string& filepath): file(filepath) {
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filepath << std::endl;
    }
}

bool Parser::hasMoreLines() const {
    return file.peek() != EOF;
};