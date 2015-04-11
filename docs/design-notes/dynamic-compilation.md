Dynamic Compilation
===================

A few features planned for Kind provide a dynamic language environment at
compile time.  The Kind compiler includes a Kind run-time environment, so that
code is able to affect the compilation directly.  In any block, Kind provides
any in-scope immutable variables with the opportunity to perform various
changes to the compilation process.  Note that only variables' statically
defined types are relevant -- attempting to change the type of the variable
using type substitution will not affect it, at least for macros (need to check
the most logical order for annotation/linkage handling, but I suspect this will
also apply here).

Means of manipulating compilation include:

Macros
------

An object may introduce a macro by definining a macro parsing function called
`macro_<id>`.  This is then invoked if the first token of a statement is
`<id>` and that is not a defined identifier in the current environment.  The 
macro is passed the sequence of tokens from its identifier up to the first
semicolon (excluding any that are inside bracketed structures, which must 
balance), along with an object containing utility functions to parse
expressions, skip expected punctuation, etc.  The macro function is expected
to return a parse tree; a suitable builder interface for producing the parse
tree is returned.

Code annotations / always-active transformations
------------------------------------------------
If a method or class is annotated with an annotation `annotation_id`, objects
that define a method `preprocess[Method|Class]_<annotation_id>` are given an
opportunity to manipulate the method or class: they are passed the parse tree
for the class or method, and may choose to modify the tree or build and return
a new one.  Methods called `preprocess[Method|Class]Always` are always 
invoked, regardless of presence of any annotations.

Linkage/type error handling
---------------------------
If a method contains a linkage or type error, then objects are given an
opportunity to attempt to resolve this by manipulating its definition.  One
application of this is the implementation of continuation passing style: if a
method calls another method whose type signature ends with a parameter of type
`Continuation`, but no such parameter is supplied, a continuation passing style
transformation is applied to the method, adding a new `Continuation` parameter
and moving the part of the original method that is to be executed after the call
(along with an added invocation of the new continuation) into a closure which
is then passed as the continuation to the called method.  Additionally, mutable
data with automatic lifetime may be moved to a dynamically managed object whose
lifetime is shared between the stack frame and the continuation, ensuring the
data survives as required.  This facility may also be useful for other automatic
transformation and type conversion facilities, such as provision of implicit
conversion to/from strings, etc, as a library function.
