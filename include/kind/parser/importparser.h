#ifndef _KIND_PARSER_IMPORTPARSER
#define _KIND_PARSER_IMPORTPARSER

#include "kind/parser/parserutil.h"
#include "kind/parser/parsetree.h"

namespace kind
{
    namespace parser
    {
        class ImportParser : ParserUtil
        {
        public:
            ImportParser(std::string filename, ErrorHandler & errorHandler) : 
                ParserUtil(filename, errorHandler)
            {
            }
            
            void parse (TokenStream::Iterator& current, TokenStream::Iterator end, ParseTree & result);
        };
    }
}
#endif