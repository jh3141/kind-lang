#include "kind/parser/parser.h"
#include "kind/parser/importparser.h"
#include "kind/parser/functionparser.h"

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
			FunctionParser functionParser (filename, errorHandler, *result);
			
			while (current < end)
			{
				switch (current->tokenType())
				{
				case Token::Type::T_IMPORT:
					importParser.parse (current, end);
					break;
				case Token::Type::T_ID:
					functionParser.parse (current, end);
					break;
					
				default:
					unexpectedTokenError (current, "start of top level declaration");
					skipToSyncPoint (current, end);
				}
			}
			return std::move(result);
		}
	}
}
