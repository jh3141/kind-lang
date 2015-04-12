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
            result->addCase(GuardPattern());
            
			while (current < end && current->tokenType() != Token::T_RBRACE) current ++;
			
			return result;
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
