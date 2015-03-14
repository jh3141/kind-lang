#ifndef _KIND_PARSER_PARSERUTIL
#define _KIND_PARSER_PARSERUTIL

#include <string>

#include "kind/tokenizer/tokenstream.h"
#include "kind/tokenizer/token.h"
#include "kind/parser/errorhandler.h"


namespace kind
{
    namespace parser
    {
        using namespace kind::tokenizer;
        
        class ParserUtil
        {
        private:
            std::string filename;
            ErrorHandler & errorHandler;    
        public:
            ParserUtil(std::string filename, ErrorHandler & errorHandler) : 
                filename(filename), errorHandler(errorHandler) 
            { 
            }
            
			void errorSync (TokenStream::Iterator& current, TokenStream::Iterator end, Error::ErrorCode, std::string first = "", std::string second = "");
			void unexpectedTokenError (TokenStream::Iterator token, std::string expected);
			bool advanceAndTestEOF (TokenStream::Iterator& i, TokenStream::Iterator end);
			void skipToSyncPoint (TokenStream::Iterator & i, TokenStream::Iterator end);
        };
    }
}

#endif
