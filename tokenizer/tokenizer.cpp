#include "kind/tokenizer/tokenizer.h"
#include <cctype>

namespace kind
{
    namespace tokenizer
    {
        Tokenizer::Tokenizer(std::istream & in)
            : in(in)
        {
        }
        
        Token Tokenizer::nextToken()
        {
            int ch = in.get();
            while (isWhitespace(ch))
            {
                ch = in.get ();
            }
            
            if (std::isdigit (ch))
                return readIntLiteral (ch);
            else if (ch == ',')
                return Token(Token::Type::T_COMMA);
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
