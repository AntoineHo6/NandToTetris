#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest.hpp"
#include "../include/Parser.hpp"
#include <fstream>

// Helper to write a temporary test file
void createTestFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    file << content;
}

TEST_CASE("Testing Parser::advance()") {
    SUBCASE("Advances through asm instructions") {
        std::string testPath = "test_standard.asm";
        createTestFile(testPath, "@10\nD=M\n@20\n");

        Parser parser(testPath);

        parser.advance();
        CHECK(parser.getInstr() == "@10");
    };

    SUBCASE("Trims whitespace and removes inline comments around asm instructions") {
        std::string testPath = "test_whitespace_inline_comments.asm";
        createTestFile(testPath, "   @10\nD=M // poopi\n@20   ");

        Parser parser(testPath);

        parser.advance();
        CHECK(parser.getInstr() == "@10");

        parser.advance();
        CHECK(parser.getInstr() == "D=M");

        parser.advance();
        CHECK(parser.getInstr() == "@20");
    }

    SUBCASE("Skips empty lines and comments automatically") {
        std::string testPath = "test_comments.asm";
        // File containing empty lines, whitespace, and comments
        std::string content = 
            "// Initial Comment\n"
            "\n"
            "   \n"
            "@100\n"
            "// Inline comment\n"
            "D=A\n";
            
        createTestFile(testPath, content);

        Parser parser(testPath);

        // advance() should skip comments and blank lines to land on "@100"
        parser.advance();
        CHECK(parser.getInstr() == "@100");

        // Next advance should skip the comment and land on "D=A"
        parser.advance();
        CHECK(parser.getInstr() == "D=A");
    }
};

TEST_CASE("Testing Parser::instructionType()") {
    SUBCASE("Extracts symbol from A_INSTRUCTION (@xxx)") {
        
    };
};

TEST_CASE("Testing Parser::symbol()") {
    SUBCASE("Extracts symbol from A_INSTRUCTION (@xxx)") {
        std::string testPath = "test_symbol.asm";
        createTestFile(testPath, "   @10\n(LOOP)");

        Parser parser(testPath);

        parser.advance();
        CHECK(parser.symbol() == "10");

        parser.advance();
        CHECK(parser.symbol() == "LOOP");
    };
};