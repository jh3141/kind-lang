#include "kind/parser/parserutil.h"
#include "kind/parser/errorhandler.h"

namespace kind
{
    namespace parser
    {
     
        using namespace kind::tokenizer;
        
		bool ParserUtil::advanceAndTestEOF(TokenStream::Iterator & i, TokenStream::Iterator end)
		{
			i++;
			if (i == end) 
			{
				errorSync (i, end, Error::ErrorCode::E_UNEXPECTEDEOF);
				return false;
			}			
			return true;
		}
		
		void ParserUtil::skipToSyncPoint (TokenStream::Iterator & i, TokenStream::Iterator end)
		{
			while (i < end && i->tokenType() != Token::T_SEMI) i++;
			i ++;	// skip over sync point
		}
		
		void ParserUtil::unexpectedTokenError (TokenStream::Iterator actual, std::string expected)
		{
			errorHandler.error(Error(
				filename, actual->startPos(), Error::E_UNEXPECTEDTOKEN,
				actual->typeName(),
				expected));
		}
		
		void ParserUtil::errorSync (TokenStream::Iterator & current, TokenStream::Iterator end, Error::ErrorCode code, std::string first, std::string second)
		{
			errorHandler.error(Error(filename, current->startPos(), code, first, second));
			skipToSyncPoint (current, end);			
		}
    }
}
