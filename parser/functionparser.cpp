#include "kind/parser/functionparser.h"

namespace kind
{
    namespace parser
    {
        using namespace kind::tokenizer;
        
        std::unique_ptr<LambdaExpression> LambdaExpressionParser::parse(
            TokenStream::Iterator & current, TokenStream::Iterator end)
        {
            std::unique_ptr<LambdaExpression> result (new LambdaExpression);
            std::shared_ptr<GuardPattern> guard;

            if (current->tokenType() == Token::T_LPAREN)    // start of parameter list
            {
                current ++;
                int tupleSize = 0;
                while (current < end && current->tokenType() != Token::T_RPAREN) {
                    if (current->tokenType() != Token::T_ID)
                    {
                        unexpectedTokenError (current, "identifier");
                        current ++;
                        continue;
                    }
                    else
                    {
                        current ++;
                        tupleSize ++;
                        switch (current->tokenType())
                        {
                            case Token::T_RPAREN: break;    // last entry in list
                            case Token::T_COMMA: 
                                current++;
                                break;     // separator for next entry
                            default:
                                unexpectedTokenError (current, "',' or ')'");
                        }
                    }
                }
                guard = std::make_shared<TupleGuardPattern>(tupleSize);
            }
            else
            {
                unexpectedTokenError (current, "function parameter list");
            }

            std::shared_ptr<Block> block = blockParser.parse (current, end);
            
			result->addCase(guard,block);
			return result;
        }
        
        std::shared_ptr<Block> StatementBlockParser::parse(TokenStream::Iterator & current, TokenStream::Iterator end)
        {
            current ++; // skip '{' (FIXME: error if not present)
			while (current < end && current->tokenType() != Token::T_RBRACE) 
			    current ++;
			current ++; // skip close brace
            return std::make_shared<Block> ();
        }
        
		void FunctionParser::parse (TokenStream::Iterator & current, TokenStream::Iterator end)
		{
		    auto declaration = std::make_shared<Declaration>(current->text());
		    current++;
		    declaration->makeLambda(lambdaParser.parse(current, end));
			result.declarations().push_back(declaration);
		}
    }
}
