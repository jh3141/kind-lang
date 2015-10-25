import kind::Optional; // Optional is a type that may or may not contain a value

[var T]	// declares a type variable T
class LinkedList
{
	private class Entry
	{
		// item is of type T, w
		var item : T;
		// the syntax Type1[Type2] identifies the type as Type1 with the
		// type of its first-declared type variable constrained to Type2.
		var next : Optional[LinkedList[T]::Entry];  
		// nb this replaces an older syntax that used colons and which required
		// a fairly in-depth analysis of precedence to understand how it worked
		// clearly this approach is better, even if it requires one more character
		// in complex cases.  note that '[]' may be used to group any type
		// expression in the same way that '()' can value expressions.
	}
	
	// Entry is a shortcut for LinkedList[T]::Entry, because it is assumed
	// that the type of T is the same as for the current scope.
	// Where the type constraint is simple, the square brackets may be omitted:
	var head : Optional Entry; // equivalent to Optional[Entry]
	
	contains(value : T) : boolean
	{
		e := head;	// 'id : [optional-type] = expr' declares and initialises
		while (e)   // Optional has an implicit conversion to boolean
		{
			if (e.value.item == value) return true;
			e = e.next;
		}
		return false;
	}
	// overload of contains for values of type E, where E can be any type
	// that is not a subtype of T:
	contains(value : [E | !subtype(E,T)]) : boolean
	{
		return false;
	}
}
