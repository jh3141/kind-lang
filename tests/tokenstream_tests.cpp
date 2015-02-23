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
}

