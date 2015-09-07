#ifndef _KIND_PARSER_PARSETREE
#define _KIND_PARSER_PARSETREE

#include "kind/parser/type.h"
#include "kind/parser/expression.h"

#include <memory>
#include <vector>
#include <string>
#include <unordered_map>

namespace kind
{
	namespace parser
	{
		class Symbol
		{
		private: 
			std::vector<std::string> idPath;
		public:
			std::vector<std::string> & path () { return idPath; }
		};
		
		class Import : public Symbol
		{
			friend class ImportParser;	// ImportParser is allowed to change wildcard status
		private:
			bool wildcard;
		public:
			Import() : wildcard(false) { }
			bool isWildcard () { return wildcard; }
		};
		
		class Variable
		{
		private:
		public:
		};
		
		class Scope
		{
		private:
			std::unordered_map<std::string, std::shared_ptr<Variable>> variables;
		public:
			void add (std::string name, std::shared_ptr<Variable> variable) { variables[name] = variable; }
			std::shared_ptr<Variable> get(std::string name) { 
				auto i = variables.find(name);
				if (i == variables.end())
					return std::shared_ptr<Variable>(); 
				else
					return std::get<1>(*i);
			}
		};
		
		
		class GuardPattern
		{
		private:
			std::vector<std::string> identifiers;
		public:
			GuardPattern(std::vector<std::string> identifiers) : identifiers(identifiers) {}
			virtual bool matches(std::shared_ptr<Type> argumentDescription);
			virtual std::shared_ptr<Scope> generateScope();
			size_t size() { return identifiers.size(); }
			std::string fieldIdentifier(int fieldIndex) { return identifiers[fieldIndex]; }
		};
		
		class Block
		{
		private:
			std::vector<std::shared_ptr<Expression>> expressions_;
		public:
			void append (std::shared_ptr<Expression> expression) { expressions_.push_back(expression); }
			std::vector<std::shared_ptr<Expression>> & expressions() { return expressions_; }
		};
		
		class LambdaExpression	// FIXME should be subclass of Expression
		{
		private:
			struct Case
			{
				std::shared_ptr<GuardPattern> guard;
				std::shared_ptr<Block> block;
				std::shared_ptr<Scope> scope;
				
				Case(std::shared_ptr<GuardPattern> guard, std::shared_ptr<Block> block, std::shared_ptr<Scope> scope) : 
					guard(guard), block(block), scope(scope) 
				{ 
				}
			};
			std::vector<Case> cases;
		public:
			void addCase (std::shared_ptr<GuardPattern> guard, std::shared_ptr<Block> block);
			int caseCount () { return cases.size(); }
			std::shared_ptr<GuardPattern> pattern(int i) { return cases[i].guard; }
			std::shared_ptr<Block> block(int i) { return cases[i].block; }
			std::shared_ptr<Scope> scope(int i) { return cases[i].scope; }
		};
		
		class Declaration
		{
		public:
			enum Type { DECL_TYPE_NULL, DECL_TYPE_LAMBDA };
		private:
			std::string id_;
			Type type_;
			std::shared_ptr<LambdaExpression> lambda_;
		public:
			Declaration (std::string id) : id_(id), type_(DECL_TYPE_NULL) {}
			std::string id() { return id_; }
			void makeLambda (std::shared_ptr<LambdaExpression> lambda);
			std::shared_ptr<LambdaExpression> lambda() { return lambda_; }
			Type type() { return type_; }
		};
		
		class ParseTree
		{
		private:
			std::vector<Import> imports_;
			std::vector<std::shared_ptr<Declaration>> declarations_;
		public:
			ParseTree();
			int elementCount () { return imports_.size(); }
			std::vector<Import> & imports () { return imports_; }
			std::vector<std::shared_ptr<Declaration>> & declarations () { return declarations_; }
		};

	}

}

#endif // _KIND_PARSER_PARSETREE
