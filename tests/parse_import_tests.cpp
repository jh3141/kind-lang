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

#define decl_sut(str) \
    string input = str; \
    stringstream inputStream (input); \
    Tokenizer tok (inputStream); \
	TokenStream ts (tok); \
	ErrorStorageHandler errors; \
	Parser sut ("test.k", ts, errors)
	
TEST_CASE("Parsing empty string produces empty parse tree", "[parser]")
{
	decl_sut("");
	std::unique_ptr<ParseTree> pt = sut.parse ();
	REQUIRE (pt->elementCount() == 0);
}

TEST_CASE("Can parse import declaration", "[parser]")
{
	decl_sut("import id1::id2;");
	std::unique_ptr<ParseTree> pt = sut.parse ();
	REQUIRE (pt->elementCount() == 1);
	REQUIRE (pt->imports().size() == 1);
	REQUIRE (pt->imports()[0].path().size() == 2);
	REQUIRE (pt->imports()[0].path()[0] == "id1");
	REQUIRE (pt->imports()[0].path()[1] == "id2");
}

TEST_CASE("Can parse import declaration with many components", "[parser]")
{
	decl_sut("import id1::id2::id3::id4;");
	std::unique_ptr<ParseTree> pt = sut.parse ();
	REQUIRE (pt->imports().size() == 1);
	REQUIRE (pt->imports()[0].path().size() == 4);
	REQUIRE (pt->imports()[0].path()[0] == "id1");
	REQUIRE (pt->imports()[0].path()[1] == "id2");
	REQUIRE (pt->imports()[0].path()[2] == "id3");
	REQUIRE (pt->imports()[0].path()[3] == "id4");
}

TEST_CASE("Can parse whole-namespace import", "[parser]")
{
	decl_sut("import id1::*;");
	std::unique_ptr<ParseTree> pt = sut.parse ();
	REQUIRE (pt->imports().size() == 1);
	REQUIRE (pt->imports()[0].path().size() == 1);
	REQUIRE (pt->imports()[0].path()[0] == "id1");
	REQUIRE (pt->imports()[0].isWildcard ());
}

TEST_CASE("Error if import not followed by id", "[parser][errors]")
{
	decl_sut("import 2;");
	sut.parse ();

	REQUIRE (errors.getErrors().size() == 1);
	Error error = errors.getErrors()[0];
	REQUIRE (error.filename == "test.k");
	REQUIRE (error.position.lineNumber() == 1);
	REQUIRE (error.position.columnNumber() == 8);
	REQUIRE (error.code == Error::ErrorCode::E_UNEXPECTEDTOKEN);
	REQUIRE (error.firstParameter == "integer literal");
	REQUIRE (error.secondParameter == "identifier");
}
TEST_CASE ("Error if EOF after import", "[parser][errors]")
{
	decl_sut("import");
	sut.parse ();
	REQUIRE (errors.getErrors().size() == 1);
	Error error = errors.getErrors()[0];
	REQUIRE (error.code == Error::ErrorCode::E_UNEXPECTEDEOF);
}
TEST_CASE ("Error if EOF after import id", "[parser][errors]")
{
	decl_sut ("import a");
	sut.parse ();
	REQUIRE (errors.getErrors().size() == 1);
	Error error = errors.getErrors()[0];
	REQUIRE (error.code == Error::ErrorCode::E_UNEXPECTEDEOF);
}
