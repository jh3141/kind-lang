#ifndef _KIND_PARSER_PARSETREE
#define _KIND_PARSER_PARSETREE

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
		
		class Declaration
		{
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
