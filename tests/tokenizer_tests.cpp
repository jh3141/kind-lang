#include "catch.hpp"
#include "kind/tokenizer/tokenizer.h"

#include <string>
#include <sstream>

using namespace kind::tokenizer;
using namespace std;

#define decl_sut(str) \
    string input = str; \
    stringstream inputStream (input); \
    Tokenizer sut (inputStream)

TEST_CASE("Tokenizer returns end of file marker", "[tokenizer]")
{
    decl_sut("");
    
    REQUIRE(sut.nextToken().tokenType() == Token::Type::T_EOF);
}

TEST_CASE("Tokenizer parses single digit", "[tokenizer]")
{
    decl_sut("1");

    REQUIRE(sut.nextToken().tokenType() == Token::Type::T_INTLITERAL);
    REQUIRE(sut.nextToken().tokenType() == Token::Type::T_EOF);
}

TEST_CASE("Tokenizer parses multiple digits", "[tokenizer]")
{
    decl_sut("1234");
    
    REQUIRE(sut.nextToken().tokenType() == Token::Type::T_INTLITERAL);
    REQUIRE(sut.nextToken().tokenType() == Token::Type::T_EOF);
}

TEST_CASE("Tokenizer ignores whitespace", "[tokenizer]")
{
    decl_sut("  \t\r\n 1234");

    REQUIRE(sut.nextToken().tokenType() == Token::Type::T_INTLITERAL);
    REQUIRE(sut.nextToken().tokenType() == Token::Type::T_EOF);
}

TEST_CASE("Can parse multiple tokens", "[tokenizer]")
{
    decl_sut("1234 5678");

    REQUIRE(sut.nextToken().tokenType() == Token::Type::T_INTLITERAL);
    REQUIRE(sut.nextToken().tokenType() == Token::Type::T_INTLITERAL);
    REQUIRE(sut.nextToken().tokenType() == Token::Type::T_EOF);
}

TEST_CASE("Integer literal terminated by punctuation correctly", "[tokenizer]")
{
    decl_sut("1234,");

    REQUIRE(sut.nextToken().tokenType() == Token::Type::T_INTLITERAL);
    REQUIRE(sut.nextToken().tokenType() == Token::Type::T_COMMA);
    REQUIRE(sut.nextToken().tokenType() == Token::Type::T_EOF);
}

TEST_CASE("Various single-character punctuation identified", "[tokenizer]")
{
    decl_sut(",!\"%^&|*()[]{}'~;/?:<>.-+=")  ;
    
    Token::Type expected[] = {
        Token::Type::T_COMMA,
        Token::Type::T_EXCL,
        Token::Type::T_QUOTE,
        Token::Type::T_MOD,
        Token::Type::T_XOR,
        Token::Type::T_AND,
        Token::Type::T_OR,
        Token::Type::T_STAR,
        Token::Type::T_LPAREN,
        Token::Type::T_RPAREN,
        Token::Type::T_LBRACKET,
        Token::Type::T_RBRACKET,
        Token::Type::T_LBRACE,
        Token::Type::T_RBRACE,
        Token::Type::T_APOS,
        Token::Type::T_TILDE,
        Token::Type::T_SEMI,
        Token::Type::T_SLASH,
        Token::Type::T_QUERY,
        Token::Type::T_COLON,
        Token::Type::T_LT,
        Token::Type::T_GT,
        Token::Type::T_DOT,
        Token::Type::T_MINUS,
        Token::Type::T_PLUS,
        Token::Type::T_EQ,
    };
    int count = sizeof(expected)/sizeof(expected[0]);
    for (int i = 0; i < count; i ++)
        REQUIRE(sut.nextToken().tokenType() == expected[i]);
    REQUIRE(sut.nextToken().tokenType() == Token::Type::T_EOF);       
}