#include "catch.hpp"
#include "kind/tokenizer/tokenizer.h"
#include "kind/tokenizer/tokenstream.h"
#include "kind/parser/parser.h"

#include <string>
#include <sstream>
#include <memory>

using namespace kind::tokenizer;
using namespace kind::parser;
using namespace std;

#define decl_sut(str) \
    string input = str; \
    stringstream inputStream (input); \
    Tokenizer tok (inputStream); \
	TokenStream ts (tok); \
	Parser sut (ts)
	
TEST_CASE("Parsing empty string produces empty parse tree", "[parser]")
{
	decl_sut("");
	std::unique_ptr<ParseTree> pt = sut.parse ();
	REQUIRE (pt->elementCount() == 0);
}
