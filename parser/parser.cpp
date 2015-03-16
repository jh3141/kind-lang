#include "kind/parser/parser.h"
#include "kind/parser/importparser.h"

namespace kind
{
	namespace parser
	{
		using namespace kind::tokenizer;
		
		Parser::Parser(std::string filename, TokenStream & tokens, ErrorHandler & errorHandler) :
			ParserUtil(filename, errorHandler),
			filename(filename), tokens(tokens), errorHandler(errorHandler), result(new ParseTree)
		{
			
		}
		
		std::unique_ptr<ParseTree> kind::parser::Parser::parse()
		{
			auto current = tokens.begin ();
			auto end = tokens.end ();
			
			ImportParser importParser (filename, errorHandler, *result);
			
			while (current < end)
			{
				if (current->tokenType() == Token::Type::T_IMPORT)
				{
					importParser.parse (current, end);
				}
				else
				{
					unexpectedTokenError (current, "start of top level declaration");
					skipToSyncPoint (current, end);
				}
			}
			return std::move(result);
		}
	}
}
