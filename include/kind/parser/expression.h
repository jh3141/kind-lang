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
	    
	    class VariableReferenceExpression : public Expression
	    {
	    public:  
	        virtual Type type () const { return EXPR_TYPE_VARREF; }
	        
	    };
	}
}

#endif