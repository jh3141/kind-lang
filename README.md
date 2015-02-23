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

Kind is a work in progress.  These notes describe the current direction of the language, but are subject to change.
No working prototype is yet available.

