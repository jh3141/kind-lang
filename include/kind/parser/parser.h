#ifndef _KIND_PARSER_PARSER
#define _KIND_PARSER_PARSER

#include <string>
#include <memory>

#include "kind/tokenizer/tokenstream.h"
#include "kind/tokenizer/token.h"
#include "kind/parser/parsetree.h"
#include "kind/parser/errorhandler.h"
#include "kind/parser/parserutil.h"

using namespace kind::tokenizer;

namespace kind
{
	namespace parser
	{
		class Parser : ParserUtil
		{
		private:
			std::string filename;
			TokenStream & tokens;
			ErrorHandler & errorHandler;
			std::unique_ptr<ParseTree> result;
			
		public:
			Parser (std::string filename, TokenStream & tokens, ErrorHandler & errorHandler);
			
			std::unique_ptr<ParseTree> parse ();
			
		protected:
			void parseImport (TokenStream::Iterator& current, TokenStream::Iterator end);
		
		};
	}
}
#endif
