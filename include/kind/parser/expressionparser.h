#ifndef _KIND_PARSER_EXPRESSIONPARSER
#define _KIND_PARSER_EXPRESSIONPARSER

#include <memory>
#include "kind/parser/parserutil.h"
#include "kind/parser/parsetree.h"
#include "kind/tokenizer/tokenstream.h"
#include "kind/parser/expression.h"

namespace kind
{
    namespace parser
    {
        using namespace kind::tokenizer;
        
        class Parser;
        
        class ExpressionParser : ParserUtil
        {
        public:
            ExpressionParser (std::string filename, ErrorHandler & errorHandler) :
                ParserUtil (filename, errorHandler)
            {
            }
            
            std::shared_ptr<Expression> parse (TokenStream::Iterator & current, TokenStream::Iterator end, Parser & parser);
        };
    }
}

#endif