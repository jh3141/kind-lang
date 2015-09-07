import kind::io::out;
import kind::String;

testfn (value1) { out.println(value1); },
       (value1 : String, value2) { out.println (value1 + ", " + value2); }
       
main ()
{
    testfn("hello, world");     // traditional C-style syntax
    "hello, world" -> testfn;   // argument from left
    greeter := testfn\"hello"   // defining a function with partial application
    greeter ("world");          // calling it traditionally
    "world" -> greeter;         // or with the argument on the left
    "world" -> testfn\"hello";  // inline definition
    testfn\"hello"\"world"();   // multiple partial applications then invocation
}