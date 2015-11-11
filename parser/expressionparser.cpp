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
            
            std::shared_ptr<Expression> parse (int precedence = 0);
        };
        typedef std::function<std::shared_ptr<Expression>(ParseContext & context)> PrefixParser;
        typedef std::function<std::shared_ptr<Expression>(ParseContext & context, std::shared_ptr<Expression> left)> InfixParser;
        
        /*
         * Precedence level descriptions, based on C++ precedence levels
         */
        #define PREC_ALL 0         // include as much as possibility
        #define PREC_COMMA 10      // ,
        #define PREC_ASSIGN 20     // assignents, throw, ?:
        #define PREC_LOGOR 30
        #define PREC_LOGAND 40
        #define PREC_BITOR 50
        #define PREC_BITXOR 60
        #define PREC_BITAND 70
        #define PREC_EQUAL 80      // == and !=
        #define PREC_COMPARE 90
        #define PREC_BITSHIFT 100
        #define PREC_ADDSUB 110
        #define PREC_MULDIV 120
        #define PREC_PTRMEMBER 130 // may not be required in this language
        #define PREC_PREFIX 140    // various prefix operators
        #define PREC_BIND 150      // misc hard binders (member extraction, function call, etc)
        #define PREC_SCOPE 160
        
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
                addPrefix (Token::T_INTLITERAL, [] (ParseContext & context) {
                    auto text = context.current->text();
                    context.current ++;
                    return std::make_shared<IntegerLiteralExpression> (text); 
                });
                addPrefix (Token::T_ID, [] (ParseContext & context) { 
                    auto text = context.current->text();
                    context.current ++;
                    return std::make_shared<VariableReferenceExpression> (text); 
                });
                addPrefix (Token::T_LPAREN, [] (ParseContext & context) {
                    context.current ++;
                    auto result = context.parse(0);
                    if (context.current->tokenType() != Token::T_RPAREN)
                    {
                        context.unexpectedTokenError(context.current, "')' or operator");
                    }
                    else
                    {
                        context.current ++;
                    }
                    return result;
                });
                addPrefixOp (Token::T_MINUS, PREC_PREFIX);
                addPrefixOp (Token::T_TILDE, PREC_PREFIX);
                addPrefixOp (Token::T_EXCL, PREC_PREFIX);
                
                addBinOp (Token::T_LSH, PREC_BITSHIFT);
                addBinOp (Token::T_RSH, PREC_BITSHIFT);
                
                addBinOp (Token::T_AND, PREC_BITAND);
                addBinOp (Token::T_OR, PREC_BITOR);
                addBinOp (Token::T_LAND, PREC_LOGAND);
                addBinOp (Token::T_LOR, PREC_LOGOR);
                addBinOp (Token::T_LXOR, PREC_LOGOR);
                
                addBinOp (Token::T_DOUBLEEQ, PREC_COMPARE);
                addBinOp (Token::T_NEQ, PREC_COMPARE);
                addBinOp (Token::T_LT, PREC_COMPARE);
                addBinOp (Token::T_LTE, PREC_COMPARE);
                addBinOp (Token::T_GT, PREC_COMPARE);
                addBinOp (Token::T_GTE, PREC_COMPARE);
                
                addBinOp (Token::T_PLUS, PREC_ADDSUB);
                addBinOp (Token::T_MINUS, PREC_ADDSUB);
                
                addBinOp (Token::T_STAR, PREC_MULDIV);
                addBinOp (Token::T_SLASH, PREC_MULDIV);
                addBinOp (Token::T_MOD, PREC_MULDIV);
                
                addInfix (Token::T_LPAREN, PREC_BIND, [this] (ParseContext & context, std::shared_ptr<Expression> left) {
                    std::shared_ptr<FunctionCallExpression> result = std::make_shared<FunctionCallExpression>(left);
                    context.current ++;
                   
                    if (isStartOfExpr(context.current->tokenType())) // has arguments
                    {
                        result->addArgument (context.parse(PREC_COMMA));
                        while (context.current->tokenType() == Token::T_COMMA)
                        {
                            context.current ++;
                            result->addArgument (context.parse(PREC_COMMA));
                        }
                        if (context.current->tokenType() != Token::T_RPAREN)
                        {
                            context.unexpectedTokenError(context.current, "')', ',' or operator");
                            return result;
                        }
                    }
                    else if (context.current->tokenType() != Token::T_RPAREN)
                    {
                        context.unexpectedTokenError(context.current, "')' or start of expression");
                        return result;
                    }
                    context.current ++;
                    return result;
                });
                addInfix(Token::T_DOT, PREC_BIND, [] (ParseContext & context, std::shared_ptr<Expression> left) {
                    context.current ++;
                    if (context.current->tokenType() != Token::T_ID)
                    {
                        context.unexpectedTokenError(context.current, "identifier");
                        context.current ++;
                        return left;
                    }
                    std::shared_ptr<Expression> result = std::make_shared<MemberSelectionExpression> (left, context.current->text());
                    context.current ++;
                    return result;
                });
            }
            
            void addPrefix (int id, PrefixParser parser) { prefix[id] = parser; }
            void addPrefixOp (Token::Type id, int tokenPrecedence) {
                addPrefix (id, [id, tokenPrecedence] (ParseContext & context) {
                    context.current ++;
                    return std::make_shared<UnaryOperationExpression> (context.parse(tokenPrecedence), id);
                });
            }
            void addInfix (int id, int tokenPrecedence, InfixParser parser) { 
                infix[id] = parser;
                precedence[id] = tokenPrecedence;
            }
            void addBinOp (Token::Type id, int tokenPrecedence) {
                addInfix (id, tokenPrecedence, [id, tokenPrecedence] (ParseContext & context, std::shared_ptr<Expression> left) { 
                    context.current ++;
                    return std::make_shared<BinaryOperationExpression> (left, context.parse(tokenPrecedence), id);
                });
            }
            bool isStartOfExpr (Token::Type ttype) { return (bool)prefix[ttype]; } 
        };
        
        ExpressionParserTables eptabs;
        
        /*
         * ============================================================================================================================
         * Main parser function
         * ============================================================================================================================
         */

        std::shared_ptr<Expression> ParseContext::parse (int precedence)
        {
            Token::Type ttype = current->tokenType ();
            
            if (! eptabs.isStartOfExpr(ttype))
            {
                unexpectedTokenError (current, "start of expression");
                current ++;
                return NullExpression::INSTANCE;
            }
            std::shared_ptr<Expression> left = eptabs.prefix[ttype] (*this);
            
            while (current < end)  // note that both prefix and infix parsers should advance the tokenizer
            {
                ttype = current->tokenType ();
                if (! eptabs.infix[ttype]) break;                   // no operator matching token
                if (eptabs.precedence[ttype] <= precedence) break;  // operator has lower precedence than the outer token we're binding our result to
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