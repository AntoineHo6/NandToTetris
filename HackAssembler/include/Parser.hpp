#pragma once
#include <fstream>
#include <string>

enum class InstructionType {
    A_INSTRUCTION, // @xxx
    C_INSTRUCTION, // dest=comp;jump
    L_INSTRUCTION  // (xxx)
};

class Parser {
    public:
        explicit Parser(const std::string& filepath);

        bool hasMoreLines();
        void advance();
        
        InstructionType instructionType() const;
        std::string symbol() const;
        std::string des() const;
        std::string comp() const;
        std::string jump() const;

    private:
        std::ifstream file;
        std::string inst;
};