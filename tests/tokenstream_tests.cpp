#include "catch.hpp"
#include "kind/tokenizer/tokenizer.h"
#include "kind/tokenizer/tokenstream.h"

#include <string>
#include <sstream>

using namespace kind::tokenizer;
using namespace std;

#define decl_sut(str) \
    string input = str; \
    stringstream inputStream (input); \
    Tokenizer tokenizer (inputStream); \
	TokenStream sut (tokenizer)

TEST_CASE("Token stream returns empty stream for empty string", "[tokenizer]")
{
	decl_sut("");

	REQUIRE(sut.begin() == sut.end ());
	REQUIRE(!(sut.begin() < sut.end()));
}

TEST_CASE("Token stream returns single token", "[tokenizer]")
{
	decl_sut("1");

	TokenStream::Iterator i = sut.begin();
	REQUIRE(!(i == sut.end()));
	REQUIRE(i < sut.end ());
	REQUIRE(i->tokenType() == Token::T_INTLITERAL);
	i ++;
	REQUIRE(i == sut.end());
}

TEST_CASE("Token stream returns multiple tokens", "[tokenizer]")
{
	decl_sut("1 2 3");
	
	TokenStream::Iterator i = sut.begin();
	REQUIRE(!(i == sut.end()));
	REQUIRE(i < sut.end ());
	REQUIRE(i->tokenType() == Token::T_INTLITERAL);
	i ++;
	REQUIRE(i < sut.end ());
	REQUIRE(i->tokenType() == Token::T_INTLITERAL);
	i ++;
	REQUIRE(i < sut.end ());
	REQUIRE(i->tokenType() == Token::T_INTLITERAL);
	i ++;
	REQUIRE(i == sut.end());
}

TEST_CASE("Token stream can go back to previous tokens", "[tokenizer]")
{
	decl_sut("1,x");
	
	TokenStream::Iterator i = sut.begin();
	REQUIRE(!(i == sut.end()));
	REQUIRE(i < sut.end ());
	REQUIRE(i->tokenType() == Token::T_INTLITERAL);
	i ++;
	REQUIRE(i < sut.end ());
	REQUIRE(i->tokenType() == Token::T_COMMA);
	i --;
	REQUIRE(i < sut.end ());
	REQUIRE(i->tokenType() == Token::T_INTLITERAL);
}

TEST_CASE("Can use prefix increment/decrement operators on token stream iterator", "[tokenizer]")
{
	decl_sut("1,x");
	
	TokenStream::Iterator i = sut.begin();
	REQUIRE(!(i == sut.end()));
	REQUIRE(i < sut.end ());
	REQUIRE(i->tokenType() == Token::T_INTLITERAL);
	++ i;
	REQUIRE(i < sut.end ());
	REQUIRE(i->tokenType() == Token::T_COMMA);
	-- i;
	REQUIRE(i < sut.end ());
	REQUIRE(i->tokenType() == Token::T_INTLITERAL);	
}

TEST_CASE("Iterator at end of token stream returns EOF token", "[tokenizer]")
{
	decl_sut("a");
	TokenStream::Iterator i = sut.begin();
	i ++;
	REQUIRE(i == sut.end());
	REQUIRE(i->tokenType() == Token::T_EOF);
}
