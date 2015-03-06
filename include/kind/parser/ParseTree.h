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
		
		class ParseTree
		{
		private:
			std::vector<Symbol> imports_;
			
		public:
			ParseTree();
			int elementCount () { return imports_.size(); }
			std::vector<Symbol> & imports () { return imports_; }
		};

	}

}

#endif // _KIND_PARSER_PARSETREE
