#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include <iostream>

bool kind_test_verbose = false;

void set_kind_test_verbose (Catch::ConfigData & ignored)
{
    std::cout << "Being verbose!" << std::endl;
    kind_test_verbose = true;
}

int main (int argc, char ** argv)
{
    Catch::Session session; // There must be exactly once instance
    
    auto & cli = session.cli();
    
    cli["-v"]["--verbose"]
        .describe ("be verbose in running tests")
        .bind ( set_kind_test_verbose );
        
    int returnCode = session.applyCommandLine( argc, argv );
    if( returnCode != 0 ) // Indicates a command line error
        return returnCode;
    
    // Writing to session.configData() or session.Config() here 
    // overrides command line args.
    // Only do this if you know you need to.
    
    return session.run();    
}
