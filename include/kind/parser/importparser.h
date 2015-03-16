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
        private:
            ParseTree & result;
        public:
            ImportParser(std::string filename, ErrorHandler & errorHandler, ParseTree & result) : 
                ParserUtil(filename, errorHandler), result(result)
            {
            }
            
            void parse (TokenStream::Iterator& current, TokenStream::Iterator end);
        };
    }
}
#endif