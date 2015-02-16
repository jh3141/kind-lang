#include <iostream>
#include <deque>

#include "kind/tokenizer/token.h"

namespace kind
{
    namespace tokenizer
    {
        class Tokenizer
        {
        private:
            std::istream & in;
        public:
            Tokenizer(std::istream & in);
            
        };
        
        void printVersion (std::ostream & out);
    }
}
