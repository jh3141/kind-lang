// flexible literals allow a class to implement a literal syntax at compile
// time. usage of this feature looks like this:

import kind::Version;
import kind::io::out;
import kind::text::Regex;

main ()
{
    // where the required type can be statically determined, the
    // syntax looks like this:
    if (Version::kindVersion >= /1.1.0.5/) {
        out.println ("Kind version >= 1.1.0.5.");
    }

    // where type cannot be statically determined, it must have
    // a type annotation:
    myVersion := /2.0.0.1325/::Version

    // some types may implement a second field outside of the
    // slashes; this may only contain letters (?)
    myRegex : Regex = /([a-z]+)([1-9])/i;
}