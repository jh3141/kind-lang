The Kind Programming Language
=============================

Kind is:

* Multi-paradigm (with support for object-oriented, generic and functional features).
* Gradually typed, with a choice of structural or nominal typing.  Type inference is used heavily to identify as many
  types as possible at compile time.
* Compiled to native code, with heavy use of type specialization to produce code with as little dynamic dispatch as
  possible.
* Reflective (although some reflection options may require the use of just-in-time compilation, which is optional).
* Designed to support modern programming practices:
	* Immutability
	* Practices for safe lock-free sharing of data between multiple threads
	* Scoped resource lifetimes ("RAII")
	* Multiple strategies for memory leak avoidance including object ownership tracking and garbage collection

There is a [brief description of Kind's philosophy](docs/design-notes/philosophy.md).

Notes on other features can be seen in these documents:

* [Subtyping by type substitution](docs/design-notes/type-substitution.md)
* [Dynamic compilation](docs/design-notes/dynamic-compilation.md)

You can get more idea of the general flavour of the language by looking at samples written using my currently-planned
syntax.  The sample directory is viewable [here](docs/samples/).

Kind is a work in progress.  These notes describe the current direction of the language, but are subject to change.
No working prototype is yet available.

