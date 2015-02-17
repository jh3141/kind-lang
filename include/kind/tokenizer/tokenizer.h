#include <iostream>
#include <deque>
#include <cctype>

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
            bool isIdStart (int ch) {
                return std::isalpha (ch) || ch == '_' || ch == '$';
            }
            bool isIdContinuation (int ch) {
                return std::isalnum (ch) || ch == '_' || ch == '$';
            }
            Token readIdOrKeyword(int firstChar);
        };
        
        void printVersion (std::ostream & out);
    }
}
