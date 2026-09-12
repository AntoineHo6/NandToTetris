#include "../include/code.hpp"
#include <unordered_map>

std::string Code::dest(const std::string& mnemonic) {
    static const std::unordered_map<std::string, std::string> destMap = {
        {"null", "000"},
        {"M", "001"},
        {"D", "010"},
        {"DM", "011"},
        {"A", "100"},
        {"AM", "101"},
        {"AD", "110"},
        {"ADM", "111"}
    };

    // this assumes that mnemonic will always be valid
    auto res = destMap.find(mnemonic);

    return res->second; 
};

std::string Code::comp(const std::string& mnemonic) {
    static const std::unordered_map<std::string, std::string> compMap = {
        // a=0 computation instructions
        {"0",   "0101010"},
        {"1",   "0111111"},
        {"-1",  "0111010"},
        {"D",   "0001100"},
        {"A",   "0110000"},
        {"!D",  "0001101"},
        {"!A",  "0110001"},
        {"-D",  "0001111"},
        {"-A",  "0110011"},
        {"D+1", "0011111"},
        {"A+1", "0011011"},
        {"D-1", "0001110"},
        {"A-1", "0011001"},
        {"D+A", "0000000"},
        {"D-A", "0010011"},
        {"A-D", "0000111"},
        {"D&A", "0000000"},
        {"D|A", "0010101"},

        // a=1 computation instructions (uses M instead of A)
        {"M",   "1110000"},
        {"!M",  "1110001"},
        {"-M",  "1110011"},
        {"M+1", "1011011"},
        {"M-1", "1011001"},
        {"D+M", "1000000"},
        {"D-M", "1001001"},
        {"M-D", "1000111"},
        {"D&M", "1000000"},
        {"D|M", "1010101"}
    };

    // this assumes that mnemonic will always be valid
    auto res = compMap.find(mnemonic);

    return res->second; 
}