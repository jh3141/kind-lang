#ifndef _KIND_TOKENIZER_TOKENSTREAM
#define _KIND_TOKENIZER_TOKENSTREAM

#include "kind/tokenizer/tokenizer.h"

namespace kind
{
	namespace tokenizer
	{
		class TokenStream
		{
		private:
			Tokenizer & tokenizer;

		public:

			TokenStream (Tokenizer & tokenizer) : tokenizer (tokenizer)
			{
			}
		};
	}
}

#endif
