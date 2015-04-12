#include "kind/parser/parsetree.h"

namespace kind
{
	namespace parser
	{
		bool GuardPattern::matches (TupleType tuple)
		{
			return tuple.size() == tuple_.size();
		}
		
		void LambdaExpression::addCase (std::shared_ptr<GuardPattern> guard)
		{
			patterns_.push_back(guard);
		}
		
		void Declaration::makeLambda(std::shared_ptr<LambdaExpression> lambda)
		{
			type_ = DECL_TYPE_LAMBDA;
			lambda_ = lambda;
		}
		
		ParseTree::ParseTree()
		{
		}
	}

}

