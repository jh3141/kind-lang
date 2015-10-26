Type Substitution
=================

Where the name of a specific type is required, the following syntax may alternatively be used:

    TypeName~[type1 => type2]
    
or for multiple substitutions:

    TypeName~[type1 => type2, type3 => type4]
    
etc.

This is a definition that creates a new class that is a subclass of `TypeName`, but which has all occurrences of the type `type1` 
changed to be occurrences of `type2` instead.  For this to be valid, `type2` must be a subtype of `type1`.  Similarly for `type3`
and `type4`, and so on.

A similar syntax may be applied to function invocation:

    function (arg1, arg2, ...) ~[type1 => type2, ...]
    
This applies a substitution to all static references to `type1` etc, including creation of new instances.  If the called function
is a member of an object, references to `type1` in the remainder of the object remain unchanged.

Substitution may be prevented in an object or method by using a type restriction that requires an exact type for a specific variable
or field, e.g.:

    class Test {
       var t : [exactly(type1)];
    }
    
In this case, the type description `Test~[type1 => type2]` produces a compile-time type error.

For fields that do not have a declared type, a type variable is implicitly created.  This variable
can be referred to using the syntax `typeof(fieldName)`.  For example:

    class Test {
       var x;
    }
    
    inst := new Test~[typeof(x) => int];

Overrides and new functions may also be added to classes using the syntax `Type~[methodName => lambda-expression]`, e.g.:

    ints := new ArrayList [int] ~[total => (){ fold (0, (a,b){a+b}) }];
    ints.add (4);
    ints.add (5);
    out.println (ints.total()); // prints 9

or for static references:

    testfn () {
        out.println("The time is " + DateTime.now());
    }
    main () {
        testfn () ~[ 
            DateTime => DateTime ~[
                now => () { DateTime.fromISOString("2015-10-16T00:30:00+0000") }
            ]
        ];
    }
