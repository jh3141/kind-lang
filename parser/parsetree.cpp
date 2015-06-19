#include <memory>
#include "kind/parser/parsetree.h"

namespace kind
{
	namespace parser
	{
		bool TupleGuardPattern::matches (std::shared_ptr<Type> type)
		{
			TupleType * tupleType = dynamic_cast<TupleType *>(type.get());
			if (tupleType)
				return tupleType->size() == identifiers.size();
			else
				return false;
		}
		
		void LambdaExpression::addCase (std::shared_ptr<GuardPattern> guard, std::shared_ptr<Block> block)
		{
			cases.push_back(Case(guard, block, std::make_shared<Scope>()));
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

