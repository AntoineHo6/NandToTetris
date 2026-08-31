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
    while (std::getline(file, inst)) {
        size_t posFirstChar = inst.find_first_not_of(" \t\r\n"); 
        
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

InstrType Parser::instructionType() const {
    size_t posFirstChar = inst.find_first_not_of(" \t\r\n");

    // Safety guard:
    if (posFirstChar == std::string::npos) {
        std::cerr << "Fatal Error: Attempted to parse an empty or invalid instruction line." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    if (inst[posFirstChar] == '@') {
        return InstrType::A_INSTRUCTION;
    }
    else if (inst[posFirstChar] == '(') {
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
    InstrType instrType = instructionType();

    if (instructionType() == InstrType::A_INSTRUCTION || instructionType() == InstrType::L_INSTRUCTION) {
        // 1. Find the first non-whitespace character (where '@' or '(' is located)
        size_t startPos = inst.find_first_not_of(" \t\r\n");

        // 2. Extract the substring starting right after '@' or '(' (index startPos + 1)
        std::string symbolStr = inst.substr(startPos + 1);

        // 3. Trim any trailing inline comments (e.g., "@100 // comment") or whitespace
        size_t commentPos = symbolStr.find("//");
        if (commentPos != std::string::npos) {
            symbolStr = symbolStr.substr(0, commentPos);
        }

        size_t endPos = symbolStr.find_last_not_of(" \t\r\n");
        if (endPos != std::string::npos) {
            symbolStr = symbolStr.substr(0, endPos + 1);
        }

        return symbolStr;
    }
    
    std::cerr << "Fatal Error: Attempted extract symbol from an instruction that is not an A or a L instruction" << std::endl;
    std::exit(EXIT_FAILURE);
};

