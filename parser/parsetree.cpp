#include <memory>
#include "kind/parser/parsetree.h"

namespace kind
{
	namespace parser
	{
		GuardPattern::MatchClass GuardPattern::matches (std::shared_ptr<Type> type)
		{
			TupleType * tupleType = dynamic_cast<TupleType *>(type.get());
			if (tupleType)
				return tupleType->size() == identifiers.size() ? MatchClass::ALWAYS : MatchClass::NEVER;
			else
				return MatchClass::NEVER;
		}
		
		std::shared_ptr<Scope> GuardPattern::generateScope ()
		{
			std::shared_ptr<Scope> result = std::make_shared<Scope> ();
			for (auto identifier : identifiers)
				result->add(identifier, std::make_shared<Variable> ());
			return result;
		}
		
		void LambdaExpression::addCase (std::shared_ptr<GuardPattern> guard, std::shared_ptr<Block> block)
		{
			cases.push_back(Case(guard, block, guard->generateScope()));
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

