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
            TokenStream::Iterator & current;
            TokenStream::Iterator end;
            std::function<void(TokenStream::Iterator,std::string)> unexpectedTokenError;
            
            std::shared_ptr<Expression> parse ();
        };
        typedef std::function<std::shared_ptr<Expression>(ParseContext & context)> PrefixParser;
        typedef std::function<std::shared_ptr<Expression>(ParseContext & context, std::shared_ptr<Expression> left)> InfixParser;
        
        
        /*
         * ============================================================================================================================
         * Token type table
         * ============================================================================================================================
         */
        class ExpressionParserTables
        {
        public:
            std::array<PrefixParser, Token::Type::T_MAX> prefix;
            std::array<InfixParser, Token::Type::T_MAX> infix;
            std::array<int, Token::Type::T_MAX> precedence;
            
            ExpressionParserTables ()
            {
                addPrefix (Token::T_ID, [] (ParseContext & context) { 
                    auto text = context.current->text();
                    context.current ++;
                    return std::make_shared<VariableReferenceExpression> (text); 
                });
                addInfix (Token::T_PLUS, [] (ParseContext & context, std::shared_ptr<Expression> left) { 
                    context.current ++;
                    return std::make_shared<BinaryOperationExpression> (left, context.parse(), Token::T_PLUS);
                });
            }
            
            void addPrefix (int id, PrefixParser parser) { prefix[id] = parser; }
            void addInfix (int id, InfixParser parser) { infix[id] = parser; }
            
        };
        
        ExpressionParserTables eptabs;
        
        /*
         * ============================================================================================================================
         * Main parser function
         * ============================================================================================================================
         */

        std::shared_ptr<Expression> ParseContext::parse ()
        {
            Token::Type ttype = current->tokenType ();
            
            if (! eptabs.prefix[ttype])
            {
                unexpectedTokenError (current, "start of expression");
                current ++;
                return NullExpression::INSTANCE;
            }
            std::shared_ptr<Expression> left = eptabs.prefix[ttype] (*this);
            
            while (current < end)  // note that both prefix and infix parsers should advance the tokenizer
            {
                ttype = current->tokenType ();
                if (! eptabs.infix[ttype]) break;
                left = eptabs.infix[ttype] (*this, left);
            }
            
            return left;
        }
        std::shared_ptr<Expression> ExpressionParser::parse(TokenStream::Iterator & current, TokenStream::Iterator end, Parser & parser)
        {
            using namespace std::placeholders;
            ParseContext context = { parser, *this, current, end, std::bind(&ParserUtil::unexpectedTokenError, (ParserUtil *)this, _1, _2) };
            return context.parse ();
        }
   }
}