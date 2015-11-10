#include <string>
#include "kind/tokenizer/token.h"

std::string kind::tokenizer::Token::typeName ()
{
    switch (type)
    {
		case T_EOF:	return "EOF";
		case T_ID:	return "identifier";
		case T_INTLITERAL:	return "integer literal";
		case T_STRINGLITERAL:	return "string literal";
		case T_COMMA:	return "','";
		case T_EXCL:	return "'!'";
		case T_MOD:	return "'%'";
		case T_XOR:	return "'^'";
		case T_AND:	return "'&'";
		case T_OR:	return "'|'";
		case T_STAR:	return "'*'";
		case T_LPAREN:	return "'('";
		case T_RPAREN:	return "')'";
		case T_LBRACKET:	return "'['";
		case T_RBRACKET:	return "']'";
		case T_LBRACE:	return "'{'";
		case T_RBRACE:	return "'}'";
		case T_APOS:	return "'''";
		case T_TILDE:	return "'~'";
		case T_SEMI:	return "';'";
		case T_SLASH:	return "'/'";
		case T_QUERY:	return "'?'";
		case T_COLON:	return "':'";
		case T_LT:	return "'<'";
		case T_GT:	return "'>'";
		case T_DOT:	return "'.'";
		case T_MINUS:	return "'-'";
		case T_PLUS:	return "'+'";
		case T_EQ:	return "'='";
		case T_LXOR:	return "'^^'";
		case T_LAND:	return "'&&'";
		case T_LOR:	return "'||'";
		case T_SCOPE:	return "'::'";
		case T_PLUS_EQ:	return "'+='";
		case T_MINUS_EQ:	return "'-='";
		case T_STAR_EQ:	return "'*='";
		case T_SLASH_EQ:	return "'/='";
		case T_MOD_EQ:	return "'%='";
		case T_XOR_EQ:	return "'^='";
		case T_AND_EQ:	return "'&='";
		case T_OR_EQ:	return "'|='";
		case T_DOUBLEMINUS:	return "'--'";
		case T_DOUBLEPLUS:	return "'++'";
		case T_ARROW:	return "'->'";
		case T_LTE:	return "'<='";
		case T_GTE:	return "'>='";
		case T_LSH:	return "'>>'";
		case T_RSH:	return "'<<'";
		case T_NEQ:	return "'!='";
		case T_DOUBLEEQ: return "'=='";
		case T_IMPORT:	return "'import'";
		case T_VAR:	return "'var'";
		case T_CLASS:	return "'class'";
		case T_PRIVATE:	return "'private'";
		case T_RETURN:	return "'return'";
		case T_NEW:	return "'new'";
		case T_WHILE:	return "'while'";
		case T_IF:	return "'if'";
		case T_UNTERMINATEDSTRING: return "unterminated string literal";
        default: return "unknown token";
    }
}