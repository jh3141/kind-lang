#ifndef _KIND_PARSER_PARSETREE
#define _KIND_PARSER_PARSETREE

#include "kind/parser/type.h"

#include <memory>
#include <vector>
#include <string>

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
		
		class GuardPattern
		{
		public:
			virtual ~GuardPattern() {}
			virtual bool matches(std::shared_ptr<Type> argumentDescription) = 0;
		};
		
		class TupleGuardPattern : public GuardPattern
		{
		private:
			int size_;
		public:
			TupleGuardPattern(int size) : size_(size) {}
			virtual bool matches(std::shared_ptr<Type> argumentDescription);
		};
		
		class LambdaExpression
		{
		private:
			std::vector<std::shared_ptr<GuardPattern>> patterns_;
		public:
			void addCase (std::shared_ptr<GuardPattern> guard);
			std::vector<std::shared_ptr<GuardPattern>> & patterns() { return patterns_; }
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
