#ifndef _KIND_PARSER_FUNCTIONPARSER
#define _KIND_PARSER_FUNCTIONPARSER

#include <memory>
#include "kind/parser/parserutil.h"
#include "kind/parser/parsetree.h"
#include "kind/tokenizer/tokenstream.h"

namespace kind
{
    namespace parser
    {
        using namespace kind::tokenizer;
        
		class FunctionParser : ParserUtil
		{
		private:
			ParseTree & result;
		public:
			FunctionParser (std::string filename, ErrorHandler & errorHandler, ParseTree & result) :
				ParserUtil(filename, errorHandler), result(result)
			{
			}
			
			void parse (TokenStream::Iterator & current, TokenStream::Iterator end);
		};
    }		
}

#endif
