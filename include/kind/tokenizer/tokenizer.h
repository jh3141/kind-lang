#ifndef _KIND_TOKENIZER_TOKENIZER
#define _KIND_TOKENIZER_TOKENIZER

#include <iostream>
#include <deque>
#include <cctype>

#include "kind/tokenizer/token.h"
#include "kind/tokenizer/fileposition.h"

namespace kind
{
    namespace tokenizer
    {
        class Tokenizer
        {
        private:
            std::istream & in;
            FilePosition current;
        public:
            Tokenizer(std::istream & in);
            Token nextToken ();
        protected:
            Token readIntLiteral (int firstChar, FilePosition start);
            bool isWhitespace(int ch) { 
                return ch <= ' ' && (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n');
            }
            bool isIdStart (int ch) {
                return std::isalpha (ch) || ch == '_' || ch == '$';
            }
            bool isIdContinuation (int ch) {
                return std::isalnum (ch) || ch == '_' || ch == '$';
            }
            Token readIdOrKeyword(int firstChar, FilePosition start);
			Token readString (int firstChart, FilePosition start);
            int nextChar () { 
                int ch = in.get (); 
                current.advance(ch);
                return ch;
            }
            int peekChar () { return in.peek (); }
            void prevChar () { 
                in.unget (); 
                current.retreat();
            }
        };
        
        void printVersion (std::ostream & out);
    }
}

#endif
