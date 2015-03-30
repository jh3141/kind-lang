Design Philosophy
=================

Background 
----------

One of the most important questions to answer when choosing a language for a
project is whether you want the language to have a static or dynamic type 
system.  This choice has several consequences.  A static language may offer
the following advantages:

* Static languages offer safety, catching type errors at compile time and
  therefore preventing certain classes of bugs entering production.
* They also generally offer improved performance over dynamic languages
  (because the job of optimizing code when you know the types of values it will 
  be working with ahead of time is easier than doing so when those types cannot
  easily be predicted).
* Furthermore, they often have better tool support for refactoring, code
  generation, static analysis (e.g. "findbugs" and similar programs) and so on,
  because the availability of type information makes these easier to write.

A dynamic language, however, could offer a different set of advantages:

* Code brevity may allow for faster development and can also make code
  easier to read.
* Functions may operate on any data type that supports the necessary operations,
  rather than just on a single type.  While some static languages support
  such polymorphic functions, they usually require a special form of declaration
  indicating that a function is polymorphic, whereas in a dynamic language a
  function may simply be polymorphic because there is no reason for it not to 
  be.
* Judicious use of "monkey patching" can add useful capabilities to the
  language's standard library that are missing from it in its original form,
  without the inconvenience of needing to use an external helper method.
* Another use of monkey patching is to provide isolation for units under test
  by stubbing out classes that they depend on.  In many dynamic languages,
  alternative versions of standard methods can be added and removed as and when
  they are required.  This technique allows for testing objects with hardcoded
  dependencies without introducing additional code to isolate them from those
  dependencies (some advocates of dynamic languages refer to such code as
  "test-induced design damage").
* Dynamic languages may offer more flexibility in terms of redefining the basic
  operations of the language, allowing the programmer to design objects that
  behave in a more dynamic way than can easily be achieved with a static
  language.

Choosing between a static and dynamic language can therefore be difficult.

Things don't have to be this way
--------------------------------

Kind is designed to bring all of these advantages into a single language, so
that you no longer need to decide.  Kind's design is guided by the following
principles:

* An advanced, highly expressive type system can both prevent errors and
  improve performance, so should be used at any opportunity to do so.
* Redundant type specifications should not be required.  In most circumstances
  it should be possible to assign a type to a variable or to parameters to a 
  function based on usage, and the return type of a function can usually be
  determined by analysing the types of values the function creates that could
  be returned.
* In cases where a single type cannot be placed on a variable or parameter,
  duplication of the compiled code for the possible types can be used to
  eliminate ambiguity without loss of performance.
* By implementing as much as possible of the basic behaviour of the language in 
  the form of objects in the language's standard library rather than as compiler 
  features it should be possible to allow the programmer to override those
  default behaviours, thus producing a language of unusual flexibility among
  static languages.
* Novel language features can be provided that substitute for the abilities
  added to dynamic languages by monkey patching, but do so in a static and
  safe way.
* By designing the language carefully, it should be possible to have a parser
  that is fast enough for near instantaneous execution after a source file is
  changed.  The use of a JIT compiler can allow execution to begin immediately
  after parsing is complete.
* For optimum performance, an AOT compiler should be available.
