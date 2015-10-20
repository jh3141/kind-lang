#include <functional>
#include "kind/parser/expressionparser.h"

namespace kind
{
    namespace parser
    {
        using namespace kind::tokenizer;
        
        /*
         * To parse expressions we use a top-down operator precendence parser,
         * aka Pratt parser.  See http://journal.stuffwithstuff.com/2011/03/19/pratt-parsers-expression-parsing-made-easy/
         * for the clearest explanation I've found of how these work.
         */
         
        /*
         * ============================================================================================================================
         * Types used by the parser functions.  We use function objects for convenience of implementation.  Need to check performance
         * implications of this!
         * ============================================================================================================================
         */
        struct ParseContext {
            Parser & parser;
            ExpressionParser & expressionParser;
        };
        typedef std::function<std::shared_ptr<Expression>(ParseContext & context, TokenStream::Iterator & current)> PrefixParser;
        typedef std::function<std::shared_ptr<Expression>(ParseContext & context, std::shared_ptr<Expression> left, TokenStream::Iterator & current)> InfixParser;
        
        
        /*
         * ============================================================================================================================
         * Token type table
         * ============================================================================================================================
         */
          
        /*
         * ============================================================================================================================
         * Main parser function
         * ============================================================================================================================
         */
        
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