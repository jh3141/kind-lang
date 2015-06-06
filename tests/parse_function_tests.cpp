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
	ModuleParser sut ("test.k", ts, kind_test_verbose ? (ErrorHandler&)errorMultiplexer : (ErrorHandler&)errors)
	
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
	REQUIRE(lambda->caseCount() == 1);
	REQUIRE(lambda->pattern(0)->matches(std::make_shared<TupleType>(0)));
}
TEST_CASE("Empty function does not cause error", "[parser][errors]")
{
	decl_sut("testFunction(){}");
	sut.parse();
	REQUIRE (errors.getErrors().size() == 0);	
}
TEST_CASE("Function with parameter does not match empty tuple argument", "[parser]")
{
	decl_sut("testFunction(a){}");
	std::unique_ptr<ParseTree> result = sut.parse();	
	REQUIRE(result->declarations()[0]->type() == Declaration::DECL_TYPE_LAMBDA);
	std::shared_ptr<LambdaExpression> lambda = result->declarations()[0]->lambda();
	REQUIRE(lambda->caseCount() == 1);
	REQUIRE(! lambda->pattern(0)->matches(std::make_shared<TupleType>(0)));
}
TEST_CASE("Function without bracket raises error", "[parser][errors]")
{
	decl_sut("testFunction 3 {}");
	sut.parse();
	REQUIRE (errors.getErrors().size() == 1);
	Error error = errors.getErrors()[0];
	REQUIRE (error.code == Error::ErrorCode::E_UNEXPECTEDTOKEN);
	REQUIRE (error.firstParameter == "integer literal");
	REQUIRE (error.secondParameter == "function parameter list");
}
TEST_CASE("Non-identifier in argument list raises error", "[parser][errors]")
{
	decl_sut("testFunction(+){}");
	sut.parse();
	REQUIRE (errors.getErrors().size() == 1);
	Error error = errors.getErrors()[0];
	REQUIRE (error.code == Error::ErrorCode::E_UNEXPECTEDTOKEN);
	REQUIRE (error.firstParameter == "'+'");
	REQUIRE (error.secondParameter == "identifier");
}
TEST_CASE("Multiple parameters separated by commas recognised", "[parser]")
{
	decl_sut("testFunction(a,b,c){}");
	std::unique_ptr<ParseTree> result = sut.parse();	
	REQUIRE (errors.getErrors().size() == 0);	
	REQUIRE(result->declarations()[0]->type() == Declaration::DECL_TYPE_LAMBDA);
	std::shared_ptr<LambdaExpression> lambda = result->declarations()[0]->lambda();
	REQUIRE(lambda->caseCount() == 1);
	REQUIRE(lambda->pattern(0)->matches(std::make_shared<TupleType>(3)));
}
TEST_CASE("Missing comma in argument list raises error", "[parser][errors]")
{
	decl_sut("testFunction(a b){}");
	sut.parse();
	REQUIRE (errors.getErrors().size() == 1);
	Error error = errors.getErrors()[0];
	REQUIRE (error.code == Error::ErrorCode::E_UNEXPECTEDTOKEN);
	REQUIRE (error.firstParameter == "identifier");
	REQUIRE (error.secondParameter == "',' or ')'");
}
TEST_CASE("Functions contain expressions", "[parser]")
{
	decl_sut("identity(a){return a;}");
	std::unique_ptr<ParseTree> result = sut.parse();	
	std::shared_ptr<LambdaExpression> lambda = result->declarations()[0]->lambda();
	std::shared_ptr<Block> block = lambda->block(0);
	REQUIRE(block->expressions().size() == 1);
	std::shared_ptr<Expression> expr = block->expressions()[0];
	REQUIRE(expr->type() == Expression::EXPR_TYPE_VARREF);
}
