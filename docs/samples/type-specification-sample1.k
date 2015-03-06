import kind::Optional // Optional is a type that may or may not contain a value

[var T]	// declares a type variable T
class LinkedList
{
	private class Entry
	{
		// item is of type T, w
		var item : T;
		// the syntax Type1:Type2 identifies the type as Type1 with the
		// type of its first-declared type variable constrained to Type2.
		// ":" is left-associative and higher precedence than "::" so
		// Type1:Type2::Type3 is a reference to Type3 which is a subtype of
		// Type1 with Type2 as a constraint on a variable of Type1.
		// Square brackets are used to nest complex type expressions.
		var next : Optional:[LinkedList:T::Entry];
		
	}
	
	// Entry is a shortcut for LinkedList:T::Entry, because it is assumed
	// that the type of T is the same as for the current scope.
	var head : Optional:Entry;
	
	contains(value : T) : boolean
	{
		var e = head;
		while (e)
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
