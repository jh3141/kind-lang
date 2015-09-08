#include "kind/parser/type.h"

namespace kind
{
    namespace parser
    {
        std::shared_ptr<NumericType> NumericType::INT = std::make_shared<NumericType> ();
    }
}