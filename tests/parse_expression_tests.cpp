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
	
#define BOP(x) std::dynamic_pointer_cast<BinaryOperationExpression>(x)

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
	REQUIRE(BOP(expr)->left()->type() == Expression::EXPR_TYPE_BINOP);
	REQUIRE(BOP(expr)->right()->type() == Expression::EXPR_TYPE_VARREF);
}
TEST_CASE("Multiple precedence levels handled appropriately", "[parser]")
{
	decl_parse_expr("simple(a,b,c){a + b * c;}");
	REQUIRE(expr->type() == Expression::EXPR_TYPE_BINOP);
	REQUIRE(BOP(expr)->left()->type() == Expression::EXPR_TYPE_VARREF);
	REQUIRE(BOP(expr)->right()->type() == Expression::EXPR_TYPE_BINOP);
}
TEST_CASE("Bracketed expressions handled correctly", "[parser]")
{
	decl_parse_expr("simple(a,b,c){a * (b + c);}");
	REQUIRE(expr->type() == Expression::EXPR_TYPE_BINOP);
	REQUIRE(BOP(expr)->op() == Token::T_STAR);
	REQUIRE(BOP(expr)->right()->type() == Expression::EXPR_TYPE_BINOP);
}
TEST_CASE("Bracket with missing close bracket", "[parser][errors]")
{
	decl_sut("testFunction(a,b){(a+b;}");
	sut.parse();
	REQUIRE (errors.getErrors().size() == 1);
	Error error = errors.getErrors()[0];
	REQUIRE (error.code == Error::ErrorCode::E_UNEXPECTEDTOKEN);
	REQUIRE (error.firstParameter == "';'");
	REQUIRE (error.secondParameter == "')' or operator");
}
std::string dump_postfix (std::shared_ptr<Expression> expr)
{
	switch (expr->type())
	{
		case Expression::EXPR_TYPE_VARREF: 
			return std::dynamic_pointer_cast<VariableReferenceExpression>(expr)->variableName();
		case Expression::EXPR_TYPE_BINOP: 
			return  dump_postfix(BOP(expr)->left()) + " " + 
					dump_postfix(BOP(expr)->right()) + " [" + 
					std::to_string(BOP(expr)->op()) + "]";
	}
	return std::string("(unknown expression type ") + to_string(expr->type()) + ")";
}

TEST_CASE("Complex bracketed expression", "[parser]")
{
	decl_parse_expr("complex(a,b,c,d,e) {" 
			        "  (a * b) + (c * d + e) * a + (d * (a + b));"
			        "}");
			        
	REQUIRE (dump_postfix (expr) == "a b [10] c d [10] e [27] a [10] [27] d a b [27] [10] [27]");
}

TEST_CASE("Negation as a prefix expression", "[parser]")
{
	decl_parse_expr("simple(a) { -a; }");
	
	REQUIRE (expr->type() == Expression::EXPR_TYPE_UNOP);
	REQUIRE (std::dynamic_pointer_cast<UnaryOperationExpression>(expr)->op () == Token::T_MINUS);
}

TEST_CASE("Function call operator works", "[parser]")
{
	decl_parse_expr("fncall(a) { a(); }");
	
	REQUIRE (expr->type() == Expression::EXPR_TYPE_FNCALL);
	auto fn = std::dynamic_pointer_cast<FunctionCallExpression>(expr);
	REQUIRE ("a" == dump_postfix (fn->function()));
	REQUIRE (0 == fn->args().size());
}

TEST_CASE("Function call allows a single parameter", "[parser]")
{
	decl_parse_expr("fncall(a,b) { a(b); }");
	
	REQUIRE (expr->type() == Expression::EXPR_TYPE_FNCALL);
	auto fn = std::dynamic_pointer_cast<FunctionCallExpression>(expr);
	REQUIRE ("a" == dump_postfix (fn->function()));
	REQUIRE (1 == fn->args().size());
	REQUIRE ("b" == dump_postfix (fn->args()[0]));
}

TEST_CASE("Function call with multiple parameters", "[parser]")
{
	decl_parse_expr("fncall(a,b,c,d) { a(b,c,d); }");

	REQUIRE (expr->type() == Expression::EXPR_TYPE_FNCALL);
	auto fn = std::dynamic_pointer_cast<FunctionCallExpression>(expr);
	REQUIRE ("a" == dump_postfix (fn->function()));
	REQUIRE (3 == fn->args().size());
	REQUIRE ("b" == dump_postfix (fn->args()[0]));
	REQUIRE ("c" == dump_postfix (fn->args()[1]));
	REQUIRE ("d" == dump_postfix (fn->args()[2]));
}

TEST_CASE("Function call with missing close paren at start", "[parser][errors]")
{
	decl_sut("testFunction(a){a(;}");
	sut.parse();
	REQUIRE (errors.getErrors().size() == 1);
	Error error = errors.getErrors()[0];
	REQUIRE (error.code == Error::ErrorCode::E_UNEXPECTEDTOKEN);
	REQUIRE (error.firstParameter == "';'");
	REQUIRE (error.secondParameter == "')' or start of expression");
}

TEST_CASE("Function call with missing close paren after args", "[parser][errors]")
{
	decl_sut("testFunction(a,b){a(b;}");
	sut.parse();
	REQUIRE (errors.getErrors().size() == 1);
	Error error = errors.getErrors()[0];
	REQUIRE (error.code == Error::ErrorCode::E_UNEXPECTEDTOKEN);
	REQUIRE (error.firstParameter == "';'");
	REQUIRE (error.secondParameter == "')', ',' or operator");
}