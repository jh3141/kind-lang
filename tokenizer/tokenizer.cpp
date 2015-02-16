#include "kind/tokenizer/tokenizer.h"
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
            return Token(Token::Type::T_EOF);
        }
        
    }
}
