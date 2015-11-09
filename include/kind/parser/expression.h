#ifndef _KIND_PARSER_EXPRESSION
#define _KIND_PARSER_EXPRESSION

#include "kind/parser/type.h"
#include "kind/tokenizer/token.h"

#include <memory>
#include <vector>
#include <string>

namespace kind
{
	namespace parser
	{   
		using kind::tokenizer::Token;
		
	    class Expression
	    {
	    public:
	        enum Type {
	            EXPR_NULL,
	            EXPR_TYPE_VARREF,
	            EXPR_TYPE_BINOP,
	            EXPR_TYPE_UNOP
	        };
	        
            virtual Type type () const = 0;
	    };
	    
	    class NullExpression : public Expression
	    {
	    public:
	    	static std::shared_ptr<NullExpression> INSTANCE;
	    	
	    	virtual Type type() const { return EXPR_NULL; }
	    	
	    };
	    
	    class VariableReferenceExpression : public Expression
	    {
	    private:
	    	std::string variableName_;
	    public:  
	    	VariableReferenceExpression(std::string variableName)
	    		: variableName_(variableName)
	    	{
	    	}
	        virtual Type type () const { return EXPR_TYPE_VARREF; }
	        std::string variableName() const { return variableName_; }
	    };
	    
	    class BinaryOperationExpression : public Expression
	    {
	    private:
	    	std::shared_ptr<Expression> left_, right_;
			Token::Type op_;  	
	    public:
			BinaryOperationExpression(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right, Token::Type op) 
				: left_(std::move(left)), right_(std::move(right)), op_(op)
			{
			}
			virtual Type type () const { return EXPR_TYPE_BINOP; }
			std::shared_ptr<Expression> left() { return left_; }
			std::shared_ptr<Expression> right() { return right_; }
			Token::Type op() { return op_; }
	    };
	    
	    class UnaryOperationExpression : public Expression
	    {
    	private:
    		std::shared_ptr<Expression> sub_;
    		Token::Type op_;
    	public:
    		UnaryOperationExpression(std::shared_ptr<Expression> sub, Token::Type op) : sub_(sub), op_(op)
    		{
    		}
			virtual Type type () const { return EXPR_TYPE_UNOP; }
			std::shared_ptr<Expression> sub() { return sub_; }
			Token::Type op() { return op_; }
	    };
	}
}

#endif