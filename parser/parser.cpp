#include "kind/parser/parser.h"

namespace kind
{
	namespace parser
	{
		using namespace kind::tokenizer;
		
		Parser::Parser(TokenStream & tokens) : 
			tokens(tokens), result(new ParseTree)
		{
			
		}
		
		std::unique_ptr<ParseTree> kind::parser::Parser::parse()
		{
			auto current = tokens.begin ();
			auto end = tokens.end ();
			while (current < end)
			{
				if (current->tokenType() == Token::Type::T_IMPORT)
					parseImport (current, end);
					
			}
			return std::move(result);
		}
		
		/*
		 * Parse import declaration:
		 *
		 * import-decl            ::= "import" scoped-id opt-wildcard-indicator ";"
		 * scoped-id              ::= id opt-scope-spec
		 * opt-scope-spec         ::= 
		 *                          | "::" id opt-scope-spec
		 * opt-wildcard-indicator ::= 
		 *                          | "::" "*"
		 */
		void Parser::parseImport(TokenStream::Iterator & current, TokenStream::Iterator end)
		{
			Import symbol;
			do
			{
				current ++;
				// FIXME what if we reach EOF here?
				// FIXME what if token type is wrong? current->tokenType() != Token::Type::T_ID/Token::Type::T_STAR
				if (current->tokenType() == Token::Type::T_STAR) {
					symbol.wildcard = true;
					current ++;
					break;
				}
				symbol.path().push_back(current->text());
				current++;
				// FIXME what if we reach EOF here?
			}
			while (current->tokenType() == Token::Type::T_SCOPE);
			// FIXME what if we are not on a semicolon here?
			current ++;
			
			result->imports().push_back(symbol);
		}
		
	}
}
