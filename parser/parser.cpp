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
				else
				{
					errorHandler.error(Error(
						filename, current->startPos(), Error::E_UNEXPECTEDTOKEN,
						current->typeName(), 
						"start of top level declaration"));
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
					current ++;
					if (symbol.path().size() == 0)
					{
						errorHandler.error(Error(filename, current->startPos(), Error::E_INVALIDWILDCARDIMPORT));
						skipToSyncPoint (current, end);
						return;
					}
					symbol.wildcard = true;
					goto finished;
				case Token::Type::T_ID:
					break;
				default:
					errorHandler.error(Error(
						filename, current->startPos(), Error::ErrorCode::E_UNEXPECTEDTOKEN,
						current->typeName(), 
						symbol.path().size() > 0 ? "identifier or '*'" : "identifier"	
						));
				}
				symbol.path().push_back(current->text());
				
				if (!advanceAndTestEOF(current, end)) return;
			}
			while (current->tokenType() == Token::Type::T_SCOPE);
		finished:
			if (current->tokenType() != Token::T_SEMI)
			{
				errorHandler.error(Error(
					filename, current->startPos(), Error::ErrorCode::E_UNEXPECTEDTOKEN,
					current->typeName(), 
					"semicolon or '::'"
					));
			}
			else
			{
				current ++;
			}
			
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
		
		void Parser::skipToSyncPoint (TokenStream::Iterator & i, TokenStream::Iterator end)
		{
			while (i < end && i->tokenType() != Token::T_SEMI) i++;
			i ++;	// skip over sync point
		}
	}
}
