#include "kind/parser/parser.h"

namespace kind
{
	namespace parser
	{
	
		Parser::Parser(TokenStream & tokens)
		{
			
		}
		
		std::unique_ptr<ParseTree> kind::parser::Parser::parse()
		{
			return std::unique_ptr<ParseTree> (new ParseTree);
		}
		
	}
}
