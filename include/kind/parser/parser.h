#ifndef _KIND_PARSER_PARSER
#define _KIND_PARSER_PARSER

#include <string>
#include <memory>

#include "kind/tokenizer/tokenstream.h"
#include "kind/tokenizer/token.h"
#include "kind/parser/parsetree.h"
#include "kind/parser/errorhandler.h"
#include "kind/parser/parserutil.h"
#include "kind/parser/functionparser.h"
#include "kind/parser/statementparser.h"
#include "kind/parser/importparser.h"

using namespace kind::tokenizer;

namespace kind
{
	namespace parser
	{
		class Parser;
		
		class ModuleParser : ParserUtil
		{
		private:
			std::string filename;
			TokenStream & tokens;
			ErrorHandler & errorHandler;
			std::unique_ptr<ParseTree> result;
			
		public:
			ModuleParser (std::string filename, TokenStream & tokens, ErrorHandler & errorHandler);
			
			std::unique_ptr<ParseTree> parse (Parser & parser);
			
		};

		class Parser
		{
		public:
			ModuleParser moduleParser;
			StatementBlockParser statementBlockParser;
			ImportParser importParser;
			FunctionParser functionParser;
			
			Parser (std::string filename, TokenStream & tokens, ErrorHandler & errorHandler)
				: moduleParser (filename, tokens, errorHandler),
				  statementBlockParser (filename, errorHandler),
				  importParser (filename, errorHandler),
				  functionParser (filename, errorHandler)
			{
			}
			
			
			std::unique_ptr<ParseTree> parse ()
			{
				return moduleParser.parse(*this);
			}
		};
	}
}
#endif
