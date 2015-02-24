#include "kind/tokenizer/tokenstream.h"

namespace kind
{
	namespace tokenizer
	{
		Token * TokenStream::tokenPtrAt (int index)
		{
			if (index >= tokens.size() && !finished) grow ();
			if (index < tokens.size()) return &tokens[index];
			return nullptr;
				
		}
		void TokenStream::grow ()
		{			
			Token t = tokenizer.nextToken();
			if (t.tokenType() == Token::T_EOF)
				finished = true;
			else
				tokens.push_back(t);
		}
		
		
		bool TokenStream::Iterator::operator ==(Iterator other) const
		{
			if (getCurrent())
				return position == other.position;
			else
				return other.position >= position;
		}
		
		bool TokenStream::Iterator::operator < (Iterator other) const
		{
			if (getCurrent())
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
		
	}

}
