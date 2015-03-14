#include "kind/parser/parser.h"

namespace kind
{
	namespace parser
	{
		using namespace kind::tokenizer;
		
		Parser::Parser(std::string filename, TokenStream & tokens, ErrorHandler & errorHandler) :
			ParserUtil(filename, errorHandler),
			filename(filename), tokens(tokens), errorHandler(errorHandler), result(new ParseTree)
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
				else
				{
					unexpectedTokenError (current, "start of top level declaration");
					skipToSyncPoint (current, end);
				}
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
				if (!advanceAndTestEOF(current, end)) return;
				
				switch (current->tokenType())
				{
				case Token::Type::T_STAR:
					if (symbol.path().size() == 0)
					{
						errorSync(current, end, Error::E_INVALIDWILDCARDIMPORT);
						return;
					}
					symbol.wildcard = true;
					break;
				case Token::Type::T_ID:
					if (symbol.wildcard)
					{
						errorSync(current, end, Error::E_WILDCARDSCOPECHILD);
						return;
					}
					symbol.path().push_back(current->text());
					break;
				default:
					unexpectedTokenError (current,
						symbol.path().size() > 0 ? "identifier or '*'" : "identifier");
				}
				
				if (!advanceAndTestEOF(current, end)) return;
			}
			while (current->tokenType() == Token::Type::T_SCOPE);
		
			if (current->tokenType() != Token::T_SEMI)
				unexpectedTokenError (current,  "semicolon or '::'");
			else
				current ++;

			result->imports().push_back(symbol);
		}
		
	}
}
