#ifndef _KIND_PARSER_PARSER
#define _KIND_PARSER_PARSER

#include <memory>

#include "kind/tokenizer/tokenstream.h"
#include "kind/tokenizer/token.h"
#include "kind/parser/parsetree.h"

using namespace kind::tokenizer;

namespace kind
{
	namespace parser
	{
		class Parser
		{
		private:
		public:
			Parser (TokenStream & tokens);
			
			std::unique_ptr<ParseTree> parse ();
		};
	}
}
#endif
