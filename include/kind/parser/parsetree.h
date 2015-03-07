#ifndef _KIND_PARSER_PARSETREE
#define _KIND_PARSER_PARSETREE

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
			friend class Parser;	// Parser is allowed to change wildcard status
		private:
			bool wildcard;
		public:
			bool isWildcard () { return wildcard; }
		};
		
		class ParseTree
		{
		private:
			std::vector<Import> imports_;
			
		public:
			ParseTree();
			int elementCount () { return imports_.size(); }
			std::vector<Import> & imports () { return imports_; }
		};

	}

}

#endif // _KIND_PARSER_PARSETREE
