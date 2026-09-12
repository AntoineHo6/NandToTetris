#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest.hpp"
#include "../include/code.hpp"
#include "../include/parser.hpp"

// Helper to write a temporary test file
void createTestFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    file << content;
}

TEST_CASE("Testing Code::dest()") {
    SUBCASE("Extracts dest mnemonic into it's binary equivalent") {
        std::string testPath = "test_standard.asm";
        createTestFile(testPath, "DM=A+1\n");

        Parser parser(testPath);

        parser.advance();

        CHECK(Code::dest(parser.dest()) == "011");
    };
};