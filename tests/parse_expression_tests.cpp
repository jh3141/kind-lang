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
	
TEST_CASE("Variable references know the name of the variable they reference", "[parser]")
{
	decl_sut("simple(a){a;}");
	std::unique_ptr<ParseTree> result = sut.parse();	
	std::shared_ptr<LambdaExpression> lambda = result->declarations()[0]->lambda();
	std::shared_ptr<Block> block = lambda->block(0);
	REQUIRE(block->expressions().size() == 1);
	std::shared_ptr<Expression> expr = block->expressions()[0];
	REQUIRE(expr->type() == Expression::EXPR_TYPE_VARREF);
	std::shared_ptr<VariableReferenceExpression> varref = std::dynamic_pointer_cast<VariableReferenceExpression>(expr);
	REQUIRE(varref->variableName() == "a");
}
