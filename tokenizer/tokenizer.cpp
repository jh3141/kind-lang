#include "kind/tokenizer/tokenizer.h"
#include <cctype>
#include <map>

#if defined(__GNUC__)
// FIXME clang defines __GNUC__ but does it use the same multichar literal representation?
#define MK_MULTICHAR(first,second) (int)((((first)&0xFF) << 8)|((second)&0xFF))
#else
#error Cannot compile with unknown compiler as we use multichar literals, which are implementation defined.
#endif

namespace kind
{
    namespace tokenizer
    {
        static std::map<char,Token::Type> punctuation;
        static std::map<int,Token::Type> multiCharPunctuation;
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
            multiCharPunctuation['^^'] = Token::Type::T_LXOR;
            multiCharPunctuation['&&'] = Token::Type::T_LAND;
            multiCharPunctuation['||'] = Token::Type::T_LOR;
            multiCharPunctuation['//'] = Token::Type::T_COMMENT_EOL;
            multiCharPunctuation['/*'] = Token::Type::T_COMMENT_BEGIN;
            multiCharPunctuation['*/'] = Token::Type::T_COMMENT_END;
            multiCharPunctuation['::'] = Token::Type::T_SCOPE;
            multiCharPunctuation['+='] = Token::Type::T_PLUS_EQ;
            multiCharPunctuation['-='] = Token::Type::T_MINUS_EQ;
            multiCharPunctuation['*='] = Token::Type::T_STAR_EQ;
            multiCharPunctuation['/='] = Token::Type::T_SLASH_EQ;
            multiCharPunctuation['%='] = Token::Type::T_MOD_EQ;
            multiCharPunctuation['^='] = Token::Type::T_XOR_EQ;
            multiCharPunctuation['&='] = Token::Type::T_AND_EQ;
            multiCharPunctuation['|='] = Token::Type::T_OR_EQ;
            multiCharPunctuation['--'] = Token::Type::T_DOUBLEMINUS;
            multiCharPunctuation['++'] = Token::Type::T_DOUBLEPLUS;
            multiCharPunctuation['->'] = Token::Type::T_ARROW;
            multiCharPunctuation['<='] = Token::Type::T_LTE;
            multiCharPunctuation['>='] = Token::Type::T_GTE;
            multiCharPunctuation['<<'] = Token::Type::T_LSH;
            multiCharPunctuation['>>'] = Token::Type::T_RSH;
            multiCharPunctuation['!='] = Token::Type::T_NEQ;
        }
        
        Tokenizer::Tokenizer(std::istream & in)
            : in(in)
        {
            if (!punctuationInitialized) initPunctuation ();
        }
        
        Token Tokenizer::nextToken()
        {
            int ch = nextChar ();
            
            while (isWhitespace(ch))
            {
                ch = nextChar ();
            }
            
            std::map<char,Token::Type>::iterator foundPunctuation;
            std::map<int,Token::Type>::iterator foundMultiCharPunctuation;
            
            int multichar = MK_MULTICHAR(ch, peekChar ());
            
            if (std::isdigit (ch))
                return readIntLiteral (ch);
            else if (isIdStart (ch))
                return readIdOrKeyword (ch);
            else if ((foundMultiCharPunctuation = multiCharPunctuation.find(multichar)) != multiCharPunctuation.end())
            {
                nextChar ();
                return Token(foundMultiCharPunctuation->second);
            }
            else if ((foundPunctuation = punctuation.find(ch)) != punctuation.end())
                return Token(foundPunctuation->second);
            else
                return Token(Token::Type::T_EOF);
        }

        Token Tokenizer::readIntLiteral (int firstChar)
        {
            while (std::isdigit(nextChar()))
                ;
            prevChar ();
            return Token (Token::Type::T_INTLITERAL);
        }
        
        Token Tokenizer::readIdOrKeyword (int firstChar)
        {
            while (isIdContinuation(nextChar()))
                ;
            prevChar ();
            return Token (Token::Type::T_ID);
        }
    }
}
