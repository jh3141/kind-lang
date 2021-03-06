#ifndef _KIND_PARSER_FUNCTIONPARSER
#define _KIND_PARSER_FUNCTIONPARSER

#include <memory>
#include "kind/parser/parserutil.h"
#include "kind/parser/parsetree.h"
#include "kind/parser/statementparser.h"
#include "kind/tokenizer/tokenstream.h"

namespace kind
{
    namespace parser
    {
        using namespace kind::tokenizer;
        
        class Parser;
        
        class GuardExpressionParser : ParserUtil
        {
        public:
			GuardExpressionParser (std::string filename, ErrorHandler & errorHandler) :
				ParserUtil(filename, errorHandler)
			{
			}
        	
        };
        
        class LambdaExpressionParser : ParserUtil
        {
        private:
        	GuardExpressionParser guardParser;
        public:
			LambdaExpressionParser (std::string filename, ErrorHandler & errorHandler) :
				ParserUtil(filename, errorHandler),
				guardParser(filename, errorHandler)
			{
			}
			
			std::unique_ptr<LambdaExpression> parse (TokenStream::Iterator & current, TokenStream::Iterator end, Parser & parser);
        };
        
		class FunctionParser : ParserUtil
		{
		private:
			LambdaExpressionParser lambdaParser;
		public:
			FunctionParser (std::string filename, ErrorHandler & errorHandler) :
				ParserUtil(filename, errorHandler), 
				lambdaParser(filename, errorHandler)
			{
			}
			
			void parse (TokenStream::Iterator & current, TokenStream::Iterator end, ParseTree & result, Parser & parser);
		};
    }		
}

#endif
