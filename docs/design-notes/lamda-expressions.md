Lamda Expressions
=================

The syntax for lamda expressions is a little unusual.  This is for two reasons:

 * To enable parsing of expressions without needing look-ahead
 * To provide the ability for a lambda function to match multiple argument patterns

The currently anticipated syntax is as follows:

  "\" ["[" type "]"]? argument-pattern implementation ["," argument-pattern implementation]*
  
where argument-pattern is the same as for standard function declaration only
without the enclosing parenthesis (these may be optionally allowed (??)), and
implementation is either "=" followed by an expression, or a statement block in
braces.  Examples:

    // identity function
    \ x = x
    
    // no-argument function
    \ = 42           
    
    // two arguments
    \ a, b = a + b   
    
    // with type-specification
    \ a : int, b : string = b.replace("%d", a.toString())
    
    // multiple argument patterns
    \ x = x,
      x, y = x + y
      
    // longer body
    \ a : int, b : string {
      StringBuffer result;
      foreach (x : intseq(1,a)) result += b;
      return result.toString();
    }
  
    // explicit result type
    \[int] x y = x / y
    