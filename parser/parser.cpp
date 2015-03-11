#include "kind/parser/parser.h"

namespace kind
{
	namespace parser
	{
		using namespace kind::tokenizer;
		
		Parser::Parser(std::string filename, TokenStream & tokens, ErrorHandler & errorHandler) : 
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
					// FIXME this isn't allowed at the beginning
					symbol.wildcard = true;
					current ++;
					goto finished;
				case Token::Type::T_ID:
					break;
				default:
					errorHandler.error(Error(
						filename, current->startPos(), Error::ErrorCode::E_UNEXPECTEDTOKEN,
						current->typeName(), 
						"identifier"	// FIXME "identifier or *" for second & subsequent parts
						));
				}
				symbol.path().push_back(current->text());
				
				if (!advanceAndTestEOF(current, end)) return;
			}
			while (current->tokenType() == Token::Type::T_SCOPE);
		finished:
			// FIXME what if we are not on a semicolon here?
			current ++;
			
			result->imports().push_back(symbol);
		}
		
		bool Parser::advanceAndTestEOF(TokenStream::Iterator & i, TokenStream::Iterator end)
		{
			i++;
			if (i == end) 
			{
				errorHandler.error(Error(
					filename, i->startPos(), Error::ErrorCode::E_UNEXPECTEDEOF));
				return false;
			}			
			return true;
		}
	}
}
