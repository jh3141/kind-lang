#include <iostream>
#include "kind/tokenizer/tokenizer.h"

namespace kind
{
    namespace tokenizer
    {
        void printVersion (std::ostream & out)
        {
            out << "Kind Tokenizer build " __DATE__ " " __TIME__ << std::endl;
        }
    }
}
