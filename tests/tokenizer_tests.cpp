#include "catch.hpp"
#include "kind/tokenizer/tokenizer.h"

#include <string>
#include <sstream>

using namespace kind::tokenizer;
using namespace std;

TEST_CASE("Tokenizer returns end of file marker", "[tokenizer]")
{
    string input = "";
    stringstream inputStream (input);
    Tokenizer sut (inputStream);
    
    REQUIRE(sut.nextToken().tokenType() == Token::Type::T_EOF);
}

TEST_CASE("Tokenizer parses single digit", "[tokenizer]")
{
    string input = "1";
    stringstream inputStream (input);
    Tokenizer sut (inputStream);
    
    REQUIRE(sut.nextToken().tokenType() == Token::Type::T_INTLITERAL);
    REQUIRE(sut.nextToken().tokenType() == Token::Type::T_EOF);
}

TEST_CASE("Tokenizer parses multiple digits", "[tokenizer]")
{
    string input = "1234";
    stringstream inputStream (input);
    Tokenizer sut (inputStream);
    
    REQUIRE(sut.nextToken().tokenType() == Token::Type::T_INTLITERAL);
    REQUIRE(sut.nextToken().tokenType() == Token::Type::T_EOF);
}

TEST_CASE("Tokenizer ignores whitespace", "[tokenizer]")
{
    string input = "  \t\r\n 1234";
    stringstream inputStream (input);
    Tokenizer sut (inputStream);
    
    REQUIRE(sut.nextToken().tokenType() == Token::Type::T_INTLITERAL);
    REQUIRE(sut.nextToken().tokenType() == Token::Type::T_EOF);
}

TEST_CASE("Can parse multiple tokens", "[tokenizer]")
{
    string input = "1234 5678";
    stringstream inputStream (input);
    Tokenizer sut (inputStream);
    
    REQUIRE(sut.nextToken().tokenType() == Token::Type::T_INTLITERAL);
    REQUIRE(sut.nextToken().tokenType() == Token::Type::T_INTLITERAL);
    REQUIRE(sut.nextToken().tokenType() == Token::Type::T_EOF);
}

TEST_CASE("Integer literal terminated by punctuation correctly", "[tokenizer]")
{
    string input = "1234,";
    stringstream inputStream (input);
    Tokenizer sut (inputStream);
    
    REQUIRE(sut.nextToken().tokenType() == Token::Type::T_INTLITERAL);
    REQUIRE(sut.nextToken().tokenType() == Token::Type::T_COMMA);
    REQUIRE(sut.nextToken().tokenType() == Token::Type::T_EOF);
}
