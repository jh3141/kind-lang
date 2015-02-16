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
            Token nextToken ();
        };
        
        void printVersion (std::ostream & out);
    }
}
