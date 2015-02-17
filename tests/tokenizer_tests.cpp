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
    decl_sut(",!\"%^&|*()[]{}'~;/?:<>.=-+");
    
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_COMMA);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_EXCL);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_QUOTE);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_MOD);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_XOR);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_AND);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_OR);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_STAR);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_LPAREN);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_RPAREN);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_LBRACKET);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_RBRACKET);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_LBRACE);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_RBRACE);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_APOS);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_TILDE);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_SEMI);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_SLASH);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_QUERY);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_COLON);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_LT);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_GT);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_DOT);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_EQ);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_MINUS);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_PLUS);
    REQUIRE(sut.nextToken().tokenType() == Token::Type::T_EOF);       
}

TEST_CASE("Various double-character punctuation identified", "[tokenizer]")
{
    decl_sut("^^ && || // /* */ :: += -= *= /= %= ^= &= |= -- ++ -> <= >= << >> !=");
    
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_LXOR);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_LAND);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_LOR);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_COMMENT_EOL);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_COMMENT_BEGIN);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_COMMENT_END);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_SCOPE);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_PLUS_EQ);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_MINUS_EQ);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_STAR_EQ);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_SLASH_EQ);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_MOD_EQ);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_XOR_EQ);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_AND_EQ);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_OR_EQ);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_DOUBLEMINUS);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_DOUBLEPLUS);//ungood
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_ARROW);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_LTE);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_GTE);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_LSH);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_RSH);
	REQUIRE(sut.nextToken().tokenType() == Token::Type::T_NEQ);
    REQUIRE(sut.nextToken().tokenType() == Token::Type::T_EOF);       
}