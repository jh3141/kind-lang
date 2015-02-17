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
                T_INTLITERAL,
                T_COMMA,
            	T_EXCL,
        		T_QUOTE,
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
        		T_EQ
            };
            
        private:
            Type type;
            
        public:
            Token (Type type)
                : type(type)
            {
            }
            
            Type tokenType() { return type; }
        };
        
    }
}