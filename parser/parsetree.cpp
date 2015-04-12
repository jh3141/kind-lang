#include "kind/parser/parsetree.h"

namespace kind
{
	namespace parser
	{
		bool GuardPattern::matches (Tuple tuple)
		{
			return true;
		}
		
		void LambdaExpression::addCase (GuardPattern guard)
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

