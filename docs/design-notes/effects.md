## Towards a non-obtrusive Effect system

An effect type is a modification to a function type.  Syntactically, it is
written:

```Argument -> Result ^ Effect```

The effect is optional, and binds to the innermost function in a chain, i.e.
type `T1 -> T2 -> T3 ^ E` is equivalent to `T1 -> (T2 -> T3 ^ E)` not
`T1 -> (T2 -> T3) ^ E`.

Individual effects are governed by an effect type.  Effect types are compile-time
metatypes that may contain functions to modify the way actions that are controlled
by the effect type are performed; a new type declared in a function that is
invoked with a specified effect type may subclass that type and use the subclass
in place of the original effect in invocations to other functions.  The compiler
is able to generate composite effect types that are subclasses of many separate
effects such that a single effect type may always exist that is able to provide
all the required effects for any context.

Various operations may only be performed in a function whose type includes a
specific effect category.  Any operation may declare an effect type that is
required before it can be executed.  Functions implicitly require effect types
for any action they will perform.  Global variables require either the
`ReadGlobal` or `WriteGlobal` effect.  For each object introduced into a scope
effect types are generated/unified such that read or write access can be
specifically controlled for that object; when an object is created the object's
metaclass can identify the metaclass of the effect types created for it.
Effect types can be declared arbitrarily in libraries, and any method or
function may require such an effect type before it may be called.

Unless otherwise specified, if any function or method requires an effect type
to be called, and the caller function has that effect type, the effect is
transferred along with the call.

Unless otherwise declared, if a function requires a certain effect, e.g. to
call a function or method that it invokes, that effect is required to invoke
the function.  Functions whose types are polymorphic (either parametrically
or through accepting subtypes in arguments) are implicitly polymorphic in
effect, thus if `A.f()` requires effect `E`:

* A function `g(a : A!) { a.f(); }` (which requires `a` have exactly the type
  `A`) requires effect `E` to invoke (i.e. it has type `A -> void ^E`), but
* a function `g(a : A) { a.f(); }` (which allows subtypes of `A` to be passed)
  implicitly has polymorphic type:

```
[forall A1, E1 .
    A1.subtype_of(A) &&
    E1.satisfies(E) &&
    E1.satisfies(required_effects(A1.f))]
A1 -> void ^E1
```

* and a parametrically polymorphic function `g(a) { a.f(); }` has the type:

```
[forall T, E, exists U .
    T.has_member(f : () -> U ^E)]
T -> void ^E
```

A function may be declared with an explicit set of effects, which adds to its
default required effects:

```
g(a) ^ SpecialEffect
{
   a.f();
}
```

A function may also be declared to exclude a given effect, which will cause an
error if the function (or any used typing of it) requires the effect:

g(a) ^! FireMissiles
{
    a.f();  // error will be reported here if a.f() requires FireMissiles effect
}
n
