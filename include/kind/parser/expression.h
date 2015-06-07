#ifndef _KIND_PARSER_EXPRESSION
#define _KIND_PARSER_EXPRESSION

#include "kind/parser/type.h"

#include <memory>
#include <vector>
#include <string>

namespace kind
{
	namespace parser
	{   
	    class Expression
	    {
	    public:
	        enum Type {
	            EXPR_NULL,
	            EXPR_TYPE_VARREF
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
	}
}

#endif