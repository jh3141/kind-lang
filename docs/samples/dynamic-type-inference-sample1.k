class SimpleClass
{
	var f;	// f has no type specified, so it will be inferred based on usage
			// note that f is private, as all fields are private
	
	SimpleClass: 	// constructor; defaults to public access
	{
		f = 5;
	}
	
	// public mutator for f:
	setF (value)		// value has no type declared, so the type of f is detected
	{				// based on usage:
		f = value;
	}
	
	getF: 
	{
		return f;
	}
}

main (args)			// main has known predefined type, so args is inferred as string[]
{
	SimpleClass sc1 = new SimpleClass;
	sc1.setF(10);	// this is the last usage of sc1, so the compiler can determine
					// at this point that f never takes a non-integer value, so 
					// the type of sc1 is determined statically as 
					// SimpleClass~[typeof(f) => int] and the appropriate constructor
					// called.  Note that this a subtype of SimpleClass that would
					// cause an exception if setF were called with a non-integer
					// parameter (but we have determined statically that this cannot
					// happen, so it is not an LSP violation).

	SimpleClass sc2 = new SimpleClass;
	sc2.setF("new value");	// as different types are used for f, this instance cannot
					// be constrained as sc1 was, so this uses a variant field for f.
}
