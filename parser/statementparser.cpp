#include "kind/parser/parser.h"
#include "kind/parser/statementparser.h"

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
                
			while (current < end && current->tokenType() != Token::T_RBRACE) {
			    result->append (parser.expressionParser.parse(current, end, parser));
			    if (current->tokenType() != Token::T_SEMI)
			    {
			        unexpectedTokenError (current, "';'");
			    }
			    else
			    {
			        current ++;
			    }
			}
			    
			current ++; // skip close brace
			
            return result;
        }
        
        std::shared_ptr<Expression> ExpressionParser::parse(TokenStream::Iterator & current, TokenStream::Iterator end, Parser & parser)
        {
            std::string text = current->text ();
            switch (current->tokenType())
            {
                case Token::T_ID:
                    current ++;
                    return std::make_shared<VariableReferenceExpression> (text);
                default:
                    unexpectedTokenError (current, "start of expression");
                    current ++;
                    return NullExpression::INSTANCE;
            }
        }
    }
}

        
