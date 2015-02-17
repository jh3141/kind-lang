#include "kind/tokenizer/tokenizer.h"
#include <cctype>
#include <map>

namespace kind
{
    namespace tokenizer
    {
        static std::map<char,Token::Type> punctuation;
        static bool punctuationInitialized = false;
        static void initPunctuation ()
        {
            punctuation[','] = Token::Type::T_COMMA;
            punctuation['!'] = Token::Type::T_EXCL;
            punctuation['"'] = Token::Type::T_QUOTE;
            punctuation['%'] = Token::Type::T_MOD;
            punctuation['^'] = Token::Type::T_XOR;
            punctuation['&'] = Token::Type::T_AND;
            punctuation['|'] = Token::Type::T_OR;
            punctuation['*'] = Token::Type::T_STAR;
            punctuation['('] = Token::Type::T_LPAREN;
            punctuation[')'] = Token::Type::T_RPAREN;
            punctuation['['] = Token::Type::T_LBRACKET;
            punctuation[']'] = Token::Type::T_RBRACKET;
            punctuation['{'] = Token::Type::T_LBRACE;
            punctuation['}'] = Token::Type::T_RBRACE;
            punctuation['\''] = Token::Type::T_APOS;
            punctuation['~'] = Token::Type::T_TILDE;
            punctuation[';'] = Token::Type::T_SEMI;
            punctuation['/'] = Token::Type::T_SLASH;
            punctuation['?'] = Token::Type::T_QUERY;
            punctuation[':'] = Token::Type::T_COLON;
            punctuation['<'] = Token::Type::T_LT;
            punctuation['>'] = Token::Type::T_GT;
            punctuation['.'] = Token::Type::T_DOT;
            punctuation['-'] = Token::Type::T_MINUS;
            punctuation['+'] = Token::Type::T_PLUS;
            punctuation['='] = Token::Type::T_EQ;
        }
        
        Tokenizer::Tokenizer(std::istream & in)
            : in(in)
        {
            if (!punctuationInitialized) initPunctuation ();
        }
        
        Token Tokenizer::nextToken()
        {
            int ch = in.get();
            
            while (isWhitespace(ch))
            {
                ch = in.get ();
            }
            
            std::map<char,Token::Type>::iterator foundPunctuation;
            
            if (std::isdigit (ch))
                return readIntLiteral (ch);
            else if ((foundPunctuation = punctuation.find(ch)) != punctuation.end())
                return Token(foundPunctuation->second);
            else
                return Token(Token::Type::T_EOF);
        }

        Token Tokenizer::readIntLiteral (int firstChar)
        {
            int read;
            while (std::isdigit(read = in.get()))
                ;
            in.unget ();
            return Token (Token::Type::T_INTLITERAL);
        }
    }
}
