#include "kind/parser/parser.h"
#include "kind/parser/importparser.h"
#include "kind/parser/functionparser.h"

namespace kind
{
	namespace parser
	{
		using namespace kind::tokenizer;
		
		ModuleParser::ModuleParser(std::string filename, TokenStream & tokens, ErrorHandler & errorHandler) :
			ParserUtil(filename, errorHandler),
			filename(filename), tokens(tokens), errorHandler(errorHandler), result(new ParseTree)
		{
			
		}
		
		std::unique_ptr<ParseTree> kind::parser::ModuleParser::parse(Parser & parser)
		{
			auto current = tokens.begin ();
			auto end = tokens.end ();
			
			while (current < end)
			{
				switch (current->tokenType())
				{
				case Token::Type::T_IMPORT:
					parser.importParser.parse (current, end, *result);
					break;
				case Token::Type::T_ID:
					parser.functionParser.parse (current, end, *result);
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
