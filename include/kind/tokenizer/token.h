#ifndef _KIND_TOKENIZER_TOKEN
#define _KIND_TOKENIZER_TOKEN

#include <string>
#include "kind/tokenizer/fileposition.h"

namespace kind
{
    namespace tokenizer
    {
        class Token
        {
        public:
            enum Type
            {
                T_EOF,                  // 0
        		T_ID,                   // 1
                T_INTLITERAL,           // 2    
				T_STRINGLITERAL,        // 3
                T_COMMA,                // 4
            	T_EXCL,                 // 5
        		T_MOD,                  // 6
        		T_XOR,                  // 7
        		T_AND,                  // 8
        		T_OR,                   // 9
        		T_STAR,                 // 10
        		T_LPAREN,               // 11
        		T_RPAREN,               // 12
        		T_LBRACKET,             // 13
        		T_RBRACKET,             // 14
        		T_LBRACE,               // 15
        		T_RBRACE,               // 16
        		T_APOS,                 // 17
        		T_TILDE,                // 18
        		T_SEMI,                 // 19
        		T_SLASH,                // 20
        		T_QUERY,                // 21
        		T_COLON,                // 22
        		T_LT,                   // 23
        		T_GT,                   // 24
        		T_DOT,                  // 25
        		T_MINUS,                // 26
        		T_PLUS,                 // 27
        		T_EQ,                   // 28
        		T_LXOR,                 // 29
        		T_LAND,                 // 30
        		T_LOR,                  // 31
        		T_SCOPE,                // 32
        		T_PLUS_EQ,              // 33
        		T_MINUS_EQ,             // 34
        		T_STAR_EQ,              // 35
        		T_SLASH_EQ,             // 36
        		T_MOD_EQ,               // 37
        		T_XOR_EQ,               // 38
        		T_AND_EQ,               // 39
        		T_OR_EQ,                // 40
        		T_DOUBLEMINUS,          // 41
        		T_DOUBLEPLUS,           // 42
        		T_ARROW,                // 43
        		T_LTE,                  // 44
        		T_GTE,                  // 45
        		T_LSH,                  // 46
        		T_RSH,                  // 47
        		T_NEQ,                  // 48
        		T_DOUBLEEQ,             // 49
				T_IMPORT,               // 50
				T_VAR,                  // 51
				T_CLASS,                // 52
				T_PRIVATE,              // 53
				T_RETURN,               // 54
				T_NEW,                  // 55
				T_WHILE,                // 56
				T_IF,                   // 57
				T_UNTERMINATEDSTRING,   // 58
				T_MAX
            };
            
        private:
            Type type;
            FilePosition start, end;
            std::string textVal;
            
        public:
            Token (Type type, FilePosition start, FilePosition end)
                : type(type), start(start), end(end), textVal(/*empty*/)
            {
            }
            Token (Type type, FilePosition start, FilePosition end, std::string textVal)
                : type(type), start(start), end(end), textVal(textVal)
            {
            }
            
            Type tokenType() { return type; }
            FilePosition startPos () { return start; }
            FilePosition endPos () { return end; }
            std::string & text () { return textVal; }
            std::string typeName ();
        };
        
    }
}

#endif
