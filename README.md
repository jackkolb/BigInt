# BigInt

Just an easy-to-use BigInt library that is, well, actually easy to use and has a bunch of useful functions

### Installation:

Just place the "BigInt.h" file in your source directory (or sub directory) and include it in your script

```
#include <"BigInt.h">
or
#include <"sub/directory/BigInt.h">
```

### Usage:

BigInt works just like any other integer, and can be initialized as a std::string, char array, and an integer.

Examples follow:

```
// Initializations
BigInt a, b;
BigInt a(5); BigInt a("5");
BigInt a = 5;
BigInt a = "5";
BigInt a = b;

// Operators
a = 5;   // 5

a += 3;  // addition
b = a + 5
++a;
a++;

a -= 3;  // subtraction
b = a - 5;
--a;
a--;

a *= 3;  // multiplication
b = a * 5;

a /= 3;  // division
b = a / 5;

a %= 3;  // modulo
b = a % 3;

// Comparisans
a > b, a >= b
a < b, a <= b
a == b, a != b

// Streams
cout << a;
somestream >> a;

// Functions
a.sqrt();               // typical square root function
a.pow(b);               // returns this BigInt to the power of another BigInt (does not change original value)
a.mod_pow(b, c);        // returns the modular power (does not change original value)
a.mod_inverse(b);       // returns the modular inverse (does not change original value)
a.is_prime();           // returns true if this BigInt is prime, false if not (deterministic)
a.gcd(b);               // returns the greatest common denominator (does not change original value)

a.to_string();          // returns the number as a string
a.to_int();             // returns the number as an int
a.to_uint();            // returns the number as an unsigned int
a.to_long_int();        // returns the number as a long int
a.to_long_uint();       // returns the number as a long unsigned int
a.to_long_long_int();   // returns the number as a long long int
a.to_long_long_uint();  // returns the number as a long long unsigned int

```
