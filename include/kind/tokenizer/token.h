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
        		T_EQ,
        		T_LXOR,
        		T_LAND,
        		T_LOR,
        		T_COMMENT_EOL,
        		T_COMMENT_BEGIN,
        		T_COMMENT_END,
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
        		T_NEQ
        		
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