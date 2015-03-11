#ifndef _KIND_PARSER_ERRORHANDLER
#define _KIND_PARSER_ERRORHANDLER

#include <string>
#include <vector>
#include "kind/tokenizer/fileposition.h"

namespace kind
{
    namespace parser
    {
        using namespace kind::tokenizer;
        
        class Error
        {
        public:
            enum ErrorCode
            {
                E_UNEXPECTEDTOKEN,              // unexpected %1 (expecting %2)
                E_UNEXPECTEDEOF,                // unexpected EOF
                E_MAX
            };
            
            const std::string filename;
            const FilePosition position;
            const ErrorCode code;
            const std::string firstParameter;
            const std::string secondParameter;
            
            Error (std::string filename, FilePosition position, ErrorCode code, std::string firstParameter = "", std::string secondParameter = "")
                : filename(filename), position(position), code(code), firstParameter(firstParameter), secondParameter(secondParameter)
            {
            }
            
            std::string formatMessage();
        };
        
        class ErrorHandler
        {
        public:
            virtual ~ErrorHandler() {}
            virtual void error (Error error) = 0;
        };
        
        class ErrorStorageHandler : public ErrorHandler
        {
        private:
            std::vector<Error> errors;
        public:
            virtual void error (Error error) { errors.push_back(error); }
            std::vector<Error> getErrors() { return errors; }
        };
    }
}
#endif