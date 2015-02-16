#include "catch.hpp"
#include "kind/tokenizer/tokenizer.h"

#include <string>
#include <sstream>

using namespace kind::tokenizer;
using namespace std;

TEST_CASE("Tokenizer returns end of file marker", "[tokenizer]")
{
    string input = "";
    stringstream inputStream (input);
    Tokenizer sut (inputStream);
    
    REQUIRE(sut.nextToken().tokenType() == Token::Type::T_EOF);
}
