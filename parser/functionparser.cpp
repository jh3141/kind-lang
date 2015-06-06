#include "kind/parser/parser.h"

namespace kind
{
    namespace parser
    {
        using namespace kind::tokenizer;
        
        std::unique_ptr<LambdaExpression> LambdaExpressionParser::parse(
            TokenStream::Iterator & current, TokenStream::Iterator end, Parser & parser)
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
                current ++; // skip rparen
            }
            else
            {
                unexpectedTokenError (current, "function parameter list");
                return result;
            }

            result->addCase (guard, parser.statementBlockParser.parse (current, end, parser));
            
			return result;
        }
        
		void FunctionParser::parse (TokenStream::Iterator & current, TokenStream::Iterator end, ParseTree & result, Parser & parser)
		{
		    auto declaration = std::make_shared<Declaration>(current->text());
		    current++;
		    declaration->makeLambda(lambdaParser.parse(current, end, parser));
			result.declarations().push_back(declaration);
		}
    }
}
