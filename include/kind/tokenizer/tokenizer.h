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
        protected:
            Token readIntLiteral (int firstChar);
            bool isWhitespace(int ch) { 
                return ch <= ' ' && (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n');
            }
        };
        
        void printVersion (std::ostream & out);
    }
}
