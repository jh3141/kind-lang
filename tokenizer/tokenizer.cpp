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
            if (std::isdigit (in.peek()))
                return readIntLiteral ();
            else
                return Token(Token::Type::T_EOF);
        }

        Token Tokenizer::readIntLiteral ()
        {
            while (std::isdigit(in.get()))
                ;
            return Token (Token::Type::T_INTLITERAL);
        }
    }
}
