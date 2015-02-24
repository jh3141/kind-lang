#ifndef _KIND_TOKENIZER_TOKENSTREAM
#define _KIND_TOKENIZER_TOKENSTREAM

#include "kind/tokenizer/tokenizer.h"
#include <deque>
#include <limits>

namespace kind
{
	namespace tokenizer
	{
		class TokenStream
		{
		private:
			Tokenizer & tokenizer;
			std::deque<Token> tokens;
			bool finished;
			
		public:
			class Iterator
			{
			private:
				TokenStream & stream;
				int position;
			public:
				Iterator (TokenStream & stream) : Iterator(stream, 0)
				{
				}
				Iterator (TokenStream & stream, int position) : 
					stream(stream), position(position)
				{ 
				}
				Token * getCurrent () const;
				Token operator * () const { return *(getCurrent()); }
				Token * operator -> () const { return getCurrent(); }
				Iterator & operator ++ ();
				Iterator & operator -- ();
				Iterator & operator ++ (int dummy);
				Iterator & operator -- (int dummy);
				bool operator == (Iterator other) const;
				bool operator < (Iterator other) const;
			};
						
			TokenStream (Tokenizer & tokenizer) : 
				tokenizer (tokenizer),
				finished(false)
			{
			}
			
			Iterator begin () { return Iterator(*this); }
			Iterator end () { return Iterator(*this, std::numeric_limits<int>::max()); }
			
			// intended for internal use: return pointer to token stored in 
			// deque, or nullptr if out of range.
			Token * tokenPtrAt (int index);
			void grow ();
		};
	}
}

#endif
