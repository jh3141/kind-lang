#include "kind/parser/functionparser.h"

namespace kind
{
    namespace parser
    {
        using namespace kind::tokenizer;
        
		void FunctionParser::parse (TokenStream::Iterator & current, TokenStream::Iterator end)
		{
			result.declarations().push_back(std::make_shared<Declaration>());
			while (current < end && current->tokenType() != Token::T_RBRACE) current ++;
		}
    }
}
