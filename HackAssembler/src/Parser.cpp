#include "../include/Parser.hpp"
#include <fstream>
#include <iostream>

Parser::Parser(const std::string& filepath): file(filepath) {
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filepath << std::endl;
    }
}

std::string Parser::getInstr() const {
    return instr;
};

bool Parser::hasMoreLines() {
    return file.peek() != EOF;
};

void Parser::advance() {
    std::string line;
    while (std::getline(file, line)) {
        size_t posFirstChar = line.find_first_not_of(" \t\r\n"); 
        
        // #1: skip empty lines
        if (posFirstChar == std::string::npos) {
            continue;
        }

        // #2: skip comment lines
        if (line.compare(posFirstChar, 2, "//") == 0) {
            continue;
        }

        // #3: If asm line, do the following:
        // Trim whitespace left
        line.erase(0, posFirstChar);

        // Trim trailing inline comments ("@100 // comment")
        size_t commentPos = line.find("//");
        if (commentPos != std::string::npos) {
            line = line.substr(0, commentPos);
        }

        // Trim trailing whitespace ("@100 ")
        size_t endPos = line.find_last_not_of(" \t\r\n");
        if (endPos != std::string::npos) {
            line = line.substr(0, endPos + 1);
        }

        instr = line;
        break;
    }
};

InstrType Parser::instructionType() const {
    size_t posFirstChar = instr.find_first_not_of(" \t\r\n");

    if (instr[posFirstChar] == '@') {
        return InstrType::A_INSTRUCTION;
    }
    else if (instr[posFirstChar] == '(') {
        return InstrType::L_INSTRUCTION;
    }
    else {
        return InstrType::C_INSTRUCTION;
    }
};

/*
    A_INSTRUCTION: @xxx
    L_INSTRUCTION: (xxx)
*/
std::string Parser::symbol() const {
    // Skip the first char as it can only be @ or (
    std::string symbolStr = instr.substr(0 + 1);

    if (instructionType() == InstrType::A_INSTRUCTION) {
        return symbolStr;
    }
    else if (instructionType() == InstrType::L_INSTRUCTION) { // remove the ')'
        size_t endPos = symbolStr.find(")");

        return symbolStr.substr(0, endPos);
    }
};


std::string Parser::dest() const {
    size_t endPos = instr.find_first_of("=");

    if (endPos == std::string::npos) {
        return "";
    }

    return instr.substr(0, endPos);
}
