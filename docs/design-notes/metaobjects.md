Meta-Objects
============

Kind features a very flexible meta-object system that can be used to control 
a wide variety of aspects of how Kind works.  Objects that are being either
operated on, or are simply in scope as a value object either in the local 
function, class or module get a chance to handle various operations, and
can therefore decide how those operations are implemented.

Operations that are supported include:

* Method dispatch (allows different techniques for overloading or for
  advanced effects such as aspect-oriented programming)
* Scope handling (allows metaprogramming of destructor calls)
* Memory allocation
* Exception handling
* Type errors (only for objects with statically-identifiable type)
* Parsing statements beginning with an identified keyword (only for objects
  with statically identifiable type) [macros]
* Altering the contents of classes or behaviour of methods via declarative code
* Post-processing changes to classes (e.g. notification when a subclass 
  adds a new method allowing the superclass to modify the subclass's code,
  add additional methods, change a parallel class heirarchy, etc.).

Because Kind is designed to be parsed by a single-pass parser, it is important
that the objects that are able to handle any parsing-related activities, i.e.
macros, are identifiable.  To this end, a strict parse order is required,
and objects whose declarations have not yet been parsed cannot influence the
parsing.  To enable this, each module has a top-level source file, and global
objects may only be defined there.  This allows us to easily find which objects
might be in scope.  The only complication comes when a module declares global
objects of types that it itself defines; in this case, it is necessary to parse
at least some of the source files of the module before the top-level file can
be processed.

The structure of a module is as follows:

* A module consists of a directory containing a number of source files.  Modules
  are heirarchical, so can contain other modules as subdirectories.
* The top level source file is called `module.k`.
* If a class is to be referred to within the module it must be either named 
  explicitly in an import statement (e.g. `import "file.k"`) or it must exist
  in a file whose name is the class's name followed by ".k".

Order of compilation is as follows:

* Compilation begins in `module.k`.
* Any import statements that refer to a file cause that file to be compiled
  immediately, after which compilation resumes from the next statement after the
  import statement.
* Any references to a type name that does not match one already declared (either
  explicitly in an import statement or via a class definition) will cause a file
  whose name matches the undeclared type to be compiled if one exists.
* An error occurs if a global variable is declared outside of `module.k`.

At each point, any global variables whose declaration has been completely parsed
may provide definition of a macro.  Standard macros (including many of the
standard control structures) are provided by the `_kernel` object.  This is an
object that is automatically defined by the environment.  The standard `_kernel`
is used unless and until a new definition by the same name is provided.  This
allows a module to override core functionality of the Kind programming language
(e.g. redefining core macros like `if` or `for`) if it wants.

Some capabilities that Kind's metaprogramming facilities are expected to provide
include:

* Ability to choose between static and dynamic dispatch on a case-by-case basis
* User-definable overload resolution rules, including multimethods
* Method dispatch interception (e.g. for purposes of implementing aspect-
  oriented programming)
* Declarative programming above and beyond the normal capabilities of most
  other OOP languages, including declarative error handling.
* Easy addition of new control structures
* Implementation of continuation passing style at a user-level rather than a
  language level
* Allow addition of facilities normally considered language features by
  library code (e.g. capabilities like C#'s LINQ or async/await could be added
  quite simply)
* Allow simple code generation based on declarations, thus making many 
  common design patterns easier to implement, and also eliminating problems
  maintaining (e.g.) complex parallel type heirarchies.
* Static resolution of missing methods and generation of code for them at
  compile time (e.g. zero-overhead implementation of dynamic proxies, ORM
  query methods a la ActiveRecord's find_by_xxx methods that are generated only
  if they're used, etc).
