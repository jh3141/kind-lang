#include "kind/parser/parser.h"

namespace kind
{
    namespace parser
    {
        using namespace kind::tokenizer;
        
        std::shared_ptr<NullExpression> NullExpression::INSTANCE = std::make_shared<NullExpression> ();
        
        std::shared_ptr<Block> StatementBlockParser::parse(TokenStream::Iterator & current, TokenStream::Iterator end, Parser & parser)
        {
            auto result = std::make_shared<Block> ();
            
            if (current->tokenType() != Token::T_LBRACE)
            {
                unexpectedTokenError (current, "'{'");
            }
            else
                current ++; // skip '{' (FIXME: error if not present)
                
			while (current < end && current->tokenType() != Token::T_RBRACE) 
			{
			    // at present, the only type of statement we support is an expression:
			    result->append (parser.expressionParser.parse(current, end, parser));
			    // expressions should be semicolon-terminated.
			    if (current->tokenType() != Token::T_SEMI)
			    {
			        unexpectedTokenError (current, "';'");
			    }
			    else
			    {
			        current ++;
			    }
			    
			    // FIXME check for other statement types
			}
			    
			current ++; // skip close brace
			
            return result;
        }
        
    }
}

        
