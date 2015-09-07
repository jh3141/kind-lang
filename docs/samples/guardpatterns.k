import kind::io::out;
import kind::patterns::Matcher;
import kind::String;
import kind::Optional;

class MyMatchDescription : Matcher:String
{
    unpack(value : string) : Optional:(String,String,String) { 
        exploded := value.explode(" ");
        return 
            exploded.length >= 3 ?  // "?" is an operator that takes a bool on its lhs and returns either 
                                    // Optional.value(rhs) if true or Optional.none if false, using short-circuit
                                    // evaluation.
                (exploded[0], exploded[1], exploded[2:].join(" "));  // TODO: not especially sure of slice syntax
    }
}
class GuardPatternDemo
{
    example
       ("hello") { out.println("hello to you too"); },
       (value : String) { out.println(value); },
       (MyMatchDescription(name1, "and", others)) { out.println ("hello " + name1 + ", and " + others + " too"); },
       (Optional.value(value1)) { out.println (value1); },
       (Optional.none) { out.println ("say what?"); },
       (value1, value2) { out.println (value1 + "\n" + value2); }
       (value1, remainder...) { out.println (value1); example(remainder); }
}