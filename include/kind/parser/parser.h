#ifndef _KIND_PARSER_PARSER
#define _KIND_PARSER_PARSER

#include <string>
#include <memory>

#include "kind/tokenizer/tokenstream.h"
#include "kind/tokenizer/token.h"
#include "kind/parser/parsetree.h"
#include "kind/parser/errorhandler.h"

using namespace kind::tokenizer;

namespace kind
{
	namespace parser
	{
		class Parser
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
			void unexpectedTokenError (TokenStream::Iterator token, std::string expected);
			void parseImport (TokenStream::Iterator& current, TokenStream::Iterator end);
			bool advanceAndTestEOF (TokenStream::Iterator& i, TokenStream::Iterator end);
			void skipToSyncPoint (TokenStream::Iterator & i, TokenStream::Iterator end);
		};
	}
}
#endif
