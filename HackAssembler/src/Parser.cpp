#include "../include/Parser.hpp"
#include <fstream>
#include <iostream>

Parser::Parser(const std::string& filepath): file(filepath) {
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filepath << std::endl;
    }
}

bool Parser::hasMoreLines() {
    return file.peek() != EOF;
};

void Parser::advance() {
    size_t posFirstChar = inst.find_first_not_of(" \t\r\n"); 

    while (std::getline(file, inst)) {
        // skip empty lines
        if (posFirstChar == std::string::npos) {
            continue;
        }

        // skip comment lines
        if (inst.compare(posFirstChar, 2, "//") == 0) {
            continue;
        }

        break;
    }
};

InstructionType Parser::instructionType() const {
    size_t posFirstChar = inst.find_first_not_of(" \t\r\n");

    // Safety guard:
    if (posFirstChar == std::string::npos) {
        std::cerr << "Fatal Error: Attempted to parse an empty or invalid instruction line." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    if (inst[posFirstChar] == '@') {
        return InstructionType::A_INSTRUCTION;
    }
    else if (inst[posFirstChar] == '(') {
        return InstructionType::L_INSTRUCTION;
    }
    else {
        return InstructionType::C_INSTRUCTION;
    }
};