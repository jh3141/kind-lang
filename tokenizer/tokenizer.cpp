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
            int peek = in.peek();
            while (isWhitespace(peek))
            {
                in.get();
                peek = in.peek ();
            }
            if (std::isdigit (peek))
                return readIntLiteral ();
            else if (peek == ',')
            {
                in.get ();
                return Token(Token::Type::T_COMMA);
            }
            else
                return Token(Token::Type::T_EOF);
        }

        Token Tokenizer::readIntLiteral ()
        {
            int read;
            while (std::isdigit(read = in.get()))
                ;
            in.unget ();
            return Token (Token::Type::T_INTLITERAL);
        }
    }
}
