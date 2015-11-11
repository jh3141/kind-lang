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
	            EXPR_TYPE_UNOP,
	            EXPR_TYPE_FNCALL,
	            EXPR_TYPE_MEMBERSELECT,
	            EXPR_TYPE_INTLITERAL,
	            EXPR_TYPE_STRINGLITERAL
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
	    
	    class FunctionCallExpression : public Expression
	    {
	    private:
	    	std::shared_ptr<Expression> function_;
	    	std::vector<std::shared_ptr<Expression>> args_;
	    public:
	    	FunctionCallExpression (std::shared_ptr<Expression> function) : function_(function)
	    	{
	    	}
	    	virtual Type type () const { return EXPR_TYPE_FNCALL; }
	    	void addArgument (std::shared_ptr<Expression> arg) { args_.push_back(arg); }
	    	std::shared_ptr<Expression> function () { return function_; }
	    	std::vector<std::shared_ptr<Expression>> & args () { return args_; }
	    };
	    
   	    class MemberSelectionExpression : public Expression
	    {
	    private:
	    	std::shared_ptr<Expression> left_;
	    	std::string right_;
	    public:
			MemberSelectionExpression(std::shared_ptr<Expression> left, std::string right) 
				: left_(std::move(left)), right_(std::move(right))
			{
			}
			virtual Type type () const { return EXPR_TYPE_MEMBERSELECT; }
			std::shared_ptr<Expression> left() { return left_; }
			std::string right() { return right_; }
	    };

		class IntegerLiteralExpression : public Expression
		{
		private:
			int value;			// FIXME should be stored in a format that can overflow bounds and catch errors
		public:
			IntegerLiteralExpression(std::string literal)
				: value(std::stoi(literal))
			{
			}
			
			virtual Type type () const { return EXPR_TYPE_INTLITERAL; }
			int intValue () { return value; }
		};
		
		class StringLiteralExpression : public Expression
		{
		private:
			std::string value;
		public:
			StringLiteralExpression (std::string value) : value(value)
			{
			}
			
			virtual Type type () const { return EXPR_TYPE_STRINGLITERAL; }
			std::string stringValue() { return value; }
		};
	}
}

#endif