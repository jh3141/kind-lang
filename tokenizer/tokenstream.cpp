#include "kind/tokenizer/tokenstream.h"

namespace kind
{
	namespace tokenizer
	{
		Token * TokenStream::tokenPtrAt (int index)
		{
			// FIXME this doesn't work if a token is skipped without reading it!
			if (index >= tokens.size() && !finished) grow ();
			if (index < tokens.size()) return &tokens[index];
			return &eofToken;
		}
		void TokenStream::grow ()
		{			
			Token t = tokenizer.nextToken();
			if (t.tokenType() == Token::T_EOF)
			{
				finished = true;
				eofToken = t;
			}
			else
				tokens.push_back(t);
		}
		
		
		bool TokenStream::Iterator::operator ==(Iterator other) const
		{
			if (getCurrent()->tokenType() != Token::T_EOF)
				return position == other.position;
			else
				return other.position >= position;
		}
		
		bool TokenStream::Iterator::operator < (Iterator other) const
		{
			if (getCurrent()->tokenType() != Token::T_EOF)
				return position < other.position;
			else
				return false;
		}
		
		Token * TokenStream::Iterator::getCurrent() const
		{
			return stream.tokenPtrAt(position);
		}
		
		TokenStream::Iterator & TokenStream::Iterator::operator ++(int dummy)
		{
			position ++;
			return *this;
		}
		
		TokenStream::Iterator & TokenStream::Iterator::operator ++()
		{
			position ++;
			return *this;
		}
		
		TokenStream::Iterator & TokenStream::Iterator::operator --(int dummy)
		{
			position --;
			return *this;
		}
		
		TokenStream::Iterator & TokenStream::Iterator::operator --()
		{
			position --;
			return *this;
		}
	}

}
