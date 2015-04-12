#include "catch.hpp"
#include "kind/tokenizer/tokenizer.h"
#include "kind/tokenizer/tokenstream.h"
#include "kind/parser/parser.h"
#include "kind/parser/errorhandler.h"

#include <string>
#include <sstream>
#include <memory>


using namespace kind::tokenizer;
using namespace kind::parser;
using namespace std;

extern bool kind_test_verbose;

#define decl_sut(str) \
    string input = str; \
    stringstream inputStream (input); \
    Tokenizer tok (inputStream); \
	TokenStream ts (tok); \
	ErrorStorageHandler errors; \
	DefaultErrorPrinter errorPrinter; \
	ErrorHandlerMultiplexer errorMultiplexer { &errors, &errorPrinter }; \
	Parser sut ("test.k", ts, kind_test_verbose ? (ErrorHandler&)errorMultiplexer : (ErrorHandler&)errors)
	
TEST_CASE("Can parse empty function declaration", "[parser]")
{
	decl_sut("testFunction(){}");
	std::unique_ptr<ParseTree> result = sut.parse();
	
	REQUIRE(result->declarations().size() == 1);
}
TEST_CASE("Function name is stored in declaration", "[parser]")
{
	decl_sut("testFunction(){}");
	std::unique_ptr<ParseTree> result = sut.parse();	
	REQUIRE(result->declarations()[0]->id() == "testFunction");
}
TEST_CASE("Empty function contains a lambda definition with an empty tuple argument", "[parser]")
{
	decl_sut("testFunction(){}");
	std::unique_ptr<ParseTree> result = sut.parse();	
	REQUIRE(result->declarations()[0]->type() == Declaration::DECL_TYPE_LAMBDA);
	std::shared_ptr<LambdaExpression> lambda = result->declarations()[0]->lambda();
	REQUIRE(lambda->patterns().size() == 1);
	REQUIRE(lambda->patterns()[0].matches(Tuple(0)));
}
