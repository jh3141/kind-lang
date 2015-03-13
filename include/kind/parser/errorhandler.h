#ifndef _KIND_PARSER_ERRORHANDLER
#define _KIND_PARSER_ERRORHANDLER

#include <string>
#include <vector>
#include "kind/tokenizer/fileposition.h"
#include <iostream>
#include <initializer_list>

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
                E_INVALIDWILDCARDIMPORT,        // invalid wildcard import ('*' must have parent scope)
                E_WILDCARDSCOPECHILD,           // wildcard may only appear at end of imported scope specification
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
        
        class DefaultErrorPrinter : public ErrorHandler
        {
        public:
            virtual void error (Error error) { 
                std::cout.flush ();
                std::cerr << error.filename << ":" << error.position.lineNumber() << "," << error.position.columnNumber() << ": " << error.code << " " << error.firstParameter << " " << error.secondParameter << std::endl;
                std::cerr.flush ();
            }
        };
        
        class ErrorHandlerMultiplexer : public ErrorHandler
        {
        private:
            std::vector<ErrorHandler *> handlers;
        public:
            ErrorHandlerMultiplexer(std::initializer_list<ErrorHandler *> initializer)
                : handlers(initializer)
            {
            }
            virtual void error (Error error) 
            {
                for (ErrorHandler * handler : handlers)
                    handler->error(error);
            }
        };
    }
}
#endif