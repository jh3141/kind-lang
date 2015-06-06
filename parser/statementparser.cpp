#include "kind/parser/statementparser.h"

namespace kind
{
    namespace parser
    {
        using namespace kind::tokenizer;
        
        std::shared_ptr<Block> StatementBlockParser::parse(TokenStream::Iterator & current, TokenStream::Iterator end, Parser & parser)
        {
            current ++; // skip '{' (FIXME: error if not present)
			while (current < end && current->tokenType() != Token::T_RBRACE) 
			    current ++;
			current ++; // skip close brace
            return std::make_shared<Block> ();
        }
        
        
    }
}

        
