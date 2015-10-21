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
        class ExpressionParserTables
        {
        public:
            std::array<PrefixParser, Token::Type::T_MAX> prefix;
            std::array<InfixParser, Token::Type::T_MAX> infix;
            std::array<int, Token::Type::T_MAX> precedence;
            
            ExpressionParserTables ()
            {
                addPrefix (Token::T_ID, [] (ParseContext & context, TokenStream::Iterator & current) { return std::make_shared<VariableReferenceExpression> (current->text()); });
            }
            
            void addPrefix (int id, PrefixParser parser) { prefix[id] = parser; }
            
        };
        
        ExpressionParserTables eptabs;
        
        /*
         * ============================================================================================================================
         * Main parser function
         * ============================================================================================================================
         */
        
        std::shared_ptr<Expression> ExpressionParser::parse(TokenStream::Iterator & current, TokenStream::Iterator end, Parser & parser)
        {
            ParseContext context = { parser, *this };
            Token::Type ttype = current->tokenType ();
            
            if (eptabs.prefix[ttype])
            {
                 std::shared_ptr<Expression> e = eptabs.prefix[ttype] (context, current);
                 current ++;
                 return e;
            }
            else            
            {
                unexpectedTokenError (current, "start of expression");
                current ++;
                return NullExpression::INSTANCE;
            }
        }
    }
}