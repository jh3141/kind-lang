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
        
        void printVersion (std::ostream & out)
        {
            out << "Kind Tokenizer build " __DATE__ " " __TIME__ << std::endl;
        }
    }
}
