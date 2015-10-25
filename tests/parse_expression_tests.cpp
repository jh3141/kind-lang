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

#define decl_parse_expr(str) \
	decl_sut(str); \
	std::unique_ptr<ParseTree> result = sut.parse();	\
	std::shared_ptr<LambdaExpression> lambda = result->declarations()[0]->lambda(); \
	std::shared_ptr<Block> block = lambda->block(0); \
	REQUIRE(block->expressions().size() == 1); \
	std::shared_ptr<Expression> expr = block->expressions()[0]
	
TEST_CASE("Variable references know the name of the variable they reference", "[parser]")
{
	decl_parse_expr("simple(a){a;}");
	REQUIRE(expr->type() == Expression::EXPR_TYPE_VARREF);
	std::shared_ptr<VariableReferenceExpression> varref = std::dynamic_pointer_cast<VariableReferenceExpression>(expr);
	REQUIRE(varref->variableName() == "a");
}
TEST_CASE("Infix operators can be used", "[parser]")
{
	decl_parse_expr("simple(a,b){a + b;}");
	REQUIRE(expr->type() == Expression::EXPR_TYPE_BINOP);
}
TEST_CASE("Invalid expression start error correct", "[parser][errors]")
{
	decl_sut("testFunction(a){/;}");
	sut.parse();
	REQUIRE (errors.getErrors().size() == 1);
	Error error = errors.getErrors()[0];
	REQUIRE (error.code == Error::ErrorCode::E_UNEXPECTEDTOKEN);
	REQUIRE (error.firstParameter == "'/'");
	REQUIRE (error.secondParameter == "start of expression");
}
TEST_CASE("Infix operators left associative", "[parser]")
{
	decl_parse_expr("simple(a,b,c){a + b + c;}");
	REQUIRE(expr->type() == Expression::EXPR_TYPE_BINOP);
	REQUIRE(std::dynamic_pointer_cast<BinaryOperationExpression>(expr)->left()->type() == Expression::EXPR_TYPE_BINOP);
	REQUIRE(std::dynamic_pointer_cast<BinaryOperationExpression>(expr)->right()->type() == Expression::EXPR_TYPE_VARREF);
}
TEST_CASE("Multiple precedence levels handled appropriately", "[parser]")
{
	decl_parse_expr("simple(a,b,c){a + b * c;}");
	REQUIRE(expr->type() == Expression::EXPR_TYPE_BINOP);
	REQUIRE(std::dynamic_pointer_cast<BinaryOperationExpression>(expr)->left()->type() == Expression::EXPR_TYPE_VARREF);
	REQUIRE(std::dynamic_pointer_cast<BinaryOperationExpression>(expr)->right()->type() == Expression::EXPR_TYPE_BINOP);
}