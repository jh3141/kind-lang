namespace kind
{
    namespace tokenizer
    {
        class Token
        {
        public:
            enum Type
            {
                T_EOF
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