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
                T_EOF,
        		T_ID,
                T_INTLITERAL,
				T_STRINGLITERAL,
                T_COMMA,
            	T_EXCL,
        		T_MOD,
        		T_XOR,
        		T_AND,
        		T_OR,
        		T_STAR,
        		T_LPAREN,
        		T_RPAREN,
        		T_LBRACKET,
        		T_RBRACKET,
        		T_LBRACE,
        		T_RBRACE,
        		T_APOS,
        		T_TILDE,
        		T_SEMI,
        		T_SLASH,
        		T_QUERY,
        		T_COLON,
        		T_LT,
        		T_GT,
        		T_DOT,
        		T_MINUS,
        		T_PLUS,
        		T_EQ,
        		T_LXOR,
        		T_LAND,
        		T_LOR,
        		T_SCOPE,
        		T_PLUS_EQ,
        		T_MINUS_EQ,
        		T_STAR_EQ,
        		T_SLASH_EQ,
        		T_MOD_EQ,
        		T_XOR_EQ,
        		T_AND_EQ,
        		T_OR_EQ,
        		T_DOUBLEMINUS,
        		T_DOUBLEPLUS,
        		T_ARROW,
        		T_LTE,
        		T_GTE,
        		T_LSH,
        		T_RSH,
        		T_NEQ,
				T_IMPORT,
				T_VAR,
				T_CLASS,
				T_PRIVATE,
				T_RETURN,
				T_NEW,
				T_WHILE,
				T_IF,
				T_UNTERMINATEDSTRING
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
        };
        
    }
}

#endif
