#ifndef _KIND_PARSER_TYPE
#define _KIND_PARSER_TYPE

#include <memory>
#include <vector>
#include <string>

namespace kind
{
	namespace parser
	{
        class Type
        {
        public:
            virtual ~Type() {}
        };
        
        class TupleType : public Type
        {
        private:
            int size_;
        public:
            TupleType(int size) : size_(size){}
            int size() { return size_; }
        };
        
    }
}
#endif
