#ifndef __BIGINT_H__
#define __BIGINT_H__

#include <vector> // the BigInt number is stored as a vector
#include <string> // strings are used to convert other data types to BigInt

#include <algorithm> // for std::reverse, in several arithmetic operators
#include <iostream> // for >> and << operators


class BigInt {
public:
    std::vector<int> number;  // holds all the digits (ex: {1, 3, 5})
    void initialize(std::string);  // Generates this BigInt's number vector from an std::string input

    unsigned int size() const;  // returns the size (number of digits) of the BigInt
    bool negative = false;  // By default, the BigInt is not set to be negative

    BigInt();  // ex: BigInt a()
    BigInt(const BigInt&);
    BigInt(int);  // ex: BigInt a(135)
    BigInt(std::string);  // ex: BigInt a(string("135"))
    BigInt(const char*);  // ex: BigInt a("135")

    BigInt& operator=(const BigInt);  // ex: BigInt a = someBigInt
    BigInt& operator=(const char*);  // ex: BigInt a = "135"
    BigInt& operator=(const int&);  // ex: BigInt a = 135
    BigInt& operator=(std::string);  // ex: BigInt a = std::string("135")
    BigInt& operator=(std::vector<int>);  // ex: BigInt a = std::vector({1, 3, 5})

    BigInt& operator+=(const BigInt&);  // ex: a += 5
    BigInt& operator-=(const BigInt&);  // ex: a -= 5
    BigInt& operator*=(const BigInt&);  // ex: a *= 5
    BigInt& operator/=(const BigInt&);  // ex: a /= 5
    BigInt& operator%=(const BigInt&);  // ex: a %= 5

    BigInt& operator++(int);  // postfix increment
    BigInt& operator++();  // prefix increment

    BigInt& operator--(int);  // postfix decrement
    BigInt& operator--();  // prefix decrement

    friend std::ostream& operator<<(std::ostream&, const BigInt&);  // output the BigInt onto an stream (ex: someOutputStream << someBigInt)
    friend std::istream& operator>>(std::istream&, const BigInt&);  // read form a stream into a BigInt (ex: someInputStream >> someBigInt)

    BigInt sqrt();  // returns the square root of this BigInt
    BigInt pow(BigInt);  // returns this BigInt to the power of another BigInt
    BigInt mod_pow(BigInt, BigInt);  // returns the modular power as a BigInt
    BigInt mod_inverse(BigInt);  // returns the modular inverse of this BigInt
    bool is_prime();  // returns true if this BigInt is prime, false if not
    BigInt gcd(BigInt);  // returns the greatest common denominator of this and another number

    int to_int();  // returns this BigInt expressed as an int
    unsigned int to_uint();  // returns this BigInt expressed as an unsigned int
    long int to_long_int();  // returns this BigInt expressed as a long int
    long unsigned int to_long_uint();  // returns this BigInt expressed as a long unsigned int
    long long int to_long_long_int();  // returns this BigInt expressed as a long long int
    long long unsigned int to_long_long_uint();  // returns this BigInt expressed as a long long unsigned int

    std::string to_string();  // returns this BigInt as a string
};

// Comparisan Operator declarations
inline bool operator==(BigInt lhs, const BigInt& rhs);
inline bool operator!=(BigInt lhs, const BigInt& rhs);
inline bool operator<(BigInt lhs, BigInt rhs);
inline bool operator>(BigInt lhs, const BigInt& rhs);
inline bool operator>=(BigInt lhs, const BigInt& rhs);
inline bool operator<=(BigInt lhs, const BigInt& rhs);


// ////////// Arithmetic Operators ////////// //

// addition using the elementary algorithm
BigInt& BigInt::operator+=(const BigInt& rhs) {
    // uses the addition algorithm you learned in elementary school:
    //    12321  (top bar)
    //   +33333  (bottom bar)
    //   ------
    //    45654  (sum bar)

    BigInt top = rhs; // top bar

    // finds the length of the smaller number
    int min = this->size();
    if (top.size() < min) { min = top.size(); }

    int max = this->size();
    if (top.size() > max) { max = top.size(); }

    // reverses the numbers, so we can iterate left to right
    std::reverse(this->number.begin(), this->number.end());
    std::reverse(top.number.begin(), top.number.end());

    // fills the smaller number with zeros so the lengths match
    if (top.size() < max) {
        while (top.size() < max) {
            top.number.push_back(0);
        }
    }
    else if (this->size() < max) {
        while (this->size() < max) {
            this->number.push_back(0);
        }
    }

    // creates the sum bar, initializes to zeros
    BigInt sum;
    sum.number = std::vector<int>(max+1, 0);

    // adds the tops and bottom bars into the sum bar
    for (int i = 0; i < max; i++) {
        sum.number.at(i) = top.number.at(i) + this->number.at(i);
    }

    // adds the excess digits into the sum bar
    for (int i = 0; i < max; i++) {
        if (sum.number.at(i) > 9) {
            sum.number.at(i) -= 10;
            sum.number.at(i+1) += 1;
        }
    }

    // removes any excess zeros
    for (int i = max; i >= 0; i--) {
        if (sum.number.at(i) != 0) {
            break;
        }
        else {
            sum.number.pop_back();
        }
    }

    // reverses the sum bar back to normal
    std::reverse(sum.number.begin(), sum.number.end());
    this->number = sum.number; // sets the sum number as this number
    return *this;
}

inline BigInt operator+(BigInt lhs, const BigInt& rhs) {
    lhs += rhs;
    return lhs;
}


// subtraction using the elementary "carry" algorithm
BigInt& BigInt::operator-=(const BigInt& rhs) {
    // uses the subtraction algorithm you learned in elementary school:
    //    87654  (upper bar)
    //   -33333  (lower bar)
    //   ------
    //    54321  (sum bar)

    BigInt result;

    // sets the upper bar to the larger number
    BigInt upper = *this;
    BigInt lower = rhs;

    if (lower > upper) {
        result.negative = true;
        upper = rhs;
        lower = *this;
    }

    // reverse the upper and lower bars, so we can iterate left to right
    std::reverse( upper.number.begin(), upper.number.end() );
    std::reverse( lower.number.begin(), lower.number.end() );

    // goes through each digit, subtraction (may get negative digits here, like {4, 3, -2, -5, 4})
    for (int i = 0; i < lower.size(); i++) {
        result.number.push_back(upper.number.at(i) - lower.number.at(i));
    }

    // adds any extra digits
    for (int i = lower.size(); i < upper.size(); i++) {
        result.number.push_back(upper.number.at(i));
    }

    // deals with negatives by subtracting from the digit over
    for (int i = 0; i < result.size(); i++) {
        if (result.number.at(i) < 0) {
            result.number.at(i+1) -= 1;
            result.number.at(i) += 10;
        }
    }

    // removes any extra zeros
    while (result.size() != 0 && result.number.at(result.size()-1) == 0) {
        result.number.pop_back();
    }

    // if the result is zero, ensure the number is empty
    if (result.size() == 0) {
        result.number = {};
    }

    // reverse back to normal
    std::reverse( result.number.begin(), result.number.end() );

    this->number = result.number;  // set this number to the result number
    return *this;
}

inline BigInt operator-(BigInt lhs, const BigInt& rhs) {
    lhs -= rhs;
    return lhs;
}


// multiplication using the elementary algorithm
BigInt& BigInt::operator*=(const BigInt& rhs) {
    // uses the multiplication algorithm you learned in elementary school:
    //      7654  (upper bar)
    //   x    23  (lower bar)
    //   -------
    //     22962  (mult results)
    //   +153080
    //   -------
    //    176042  (result)


    BigInt lhs = *this;
    std::vector<BigInt> mult_results; // list of the additions results
    int rhs_carry_size = rhs.number.size() + lhs.number.size(); // determines the max carry size
    std::vector<int> rhs_carry(rhs_carry_size, 0); // initializes the carry to zeros

    for (int i = lhs.size()-1; i >= 0; i--) { // for each on lower bar (going in reverse)

        for (unsigned int i = 0; i < rhs_carry.size(); i++) { // set carry to 0
            rhs_carry.at(i) = 0;
        }

        BigInt sub_result;
        for (int k = 0; k < lhs.size()-1 - i; k++) { // push back initial zeroes
            sub_result.number.push_back(0);
        }

        for (int j = rhs.number.size()-1; j >= 0; j--) { // for each on upper bar
            sub_result.number.push_back(lhs.number.at(i) * rhs.number.at(j) + rhs_carry.at(j)); // push back lower * upper + carry
            
            if (sub_result.number.at(sub_result.number.size()-1) > 9) { // if last number > 9
                int new_digit = sub_result.number.at(sub_result.number.size()-1) % 10; // digit is the remainder / 10
                if (j > 0) { // if upper bar not the last one
                    rhs_carry.at(j-1) += sub_result.number.at(sub_result.number.size()-1) / 10; // increase carry 
                    sub_result.number.at(sub_result.number.size()-1) = new_digit; // set digit
                }
                else { // if upper bar last one
                    sub_result.number.push_back(sub_result.number.at(sub_result.number.size()-1) / 10); // push back carry
                    sub_result.number.at(sub_result.number.size()-2) = new_digit; // set digit
                }
            }
        }
        std::reverse(sub_result.number.begin(), sub_result.number.end()); // reverse back to normal
        mult_results.push_back(sub_result); // appends this sub result to the mult results for later addition
    }

    // adds up all the mult results to get the final result
    BigInt result(0);
    for (BigInt i : mult_results) {
        result = i + result;
    }

    this->number = result.number;  // sets the result number into this number
    return *this;
}

inline BigInt operator*(BigInt lhs, BigInt rhs) {
    lhs *= rhs;
    return lhs;
}


// division using the long division algorithm
BigInt& BigInt::operator/=(const BigInt& rhs) {
    // uses the long division algorithm to computer the division:
    //    _102_
    // 13|1326

    BigInt lhs = *this;

    // edge case: the outside is greater than the inside, result is zero (empty number)
    if (rhs.size() > lhs.size()) { 
        this->number = {};
        return *this;
    }

    BigInt inside = lhs;
    BigInt outside = rhs;
    BigInt result;

    BigInt remainder;

    BigInt test;  // the temporary, recycled variable that travels along the inside digits

    for (int i = 0; i < inside.size(); i++) {
        test.number.push_back(inside.number.at(i)); // adds the next digit to the test variable
        
        // edge case: test is nothing
        if (test.size() == 0) {
            result.number.push_back(0);
            test.number = {};
            continue;
        }
        // when test is less than the outside number (ex: the first operation of the example above, 1 < 13)
        if (test < outside) {
            result.number.push_back(0);
            continue;
        }
        else {
            int counter = 0;
            BigInt temp = test; // temp will decrease until it is less than the outside, so we know the result digit
            while (outside <= temp) {
                counter++;
                temp = temp - outside;
                if (temp == 0 && outside == 0) { break; } // redundancy edge case: it won't go lower than zero, so break there
            }
            result.number.push_back(counter);  // add the counter (aka the reult of this mini-division) to the result
            
            // whatever temp is now is the remainder, add this to test number
            remainder = temp;  
            test.number = {};
            if (remainder != 0) {
                for (int n : remainder.number) {  // iterates through the digits and appends to the number vector
                    test.number.push_back(n);
                }
            }
        }
    }


    BigInt filtered_result;  // filtered result will get rid of the excess zeros

    // zeroes_flag is initially true until it encounters a non-zero digit, then it grabs all the remaining digits
    // ex: 00012345 becomes 12345
    bool zeroes_flag = true;
    for (int i = 0; i < result.size(); i++) {
        if (zeroes_flag == true) {
            if (result.number.at(i) != 0) {
                zeroes_flag = false;
            }
        }
        
        if (zeroes_flag == false) {
            filtered_result.number.push_back(result.number.at(i));
        }
    }

    result = filtered_result;  // sets this filtered result to the overall result

    this->number = result.number; // sets this number to the result number
    return *this;
}

inline BigInt operator/(BigInt lhs, BigInt rhs) {
    lhs /= BigInt(rhs);
    return lhs;
}


// modulo using division and remainder
BigInt& BigInt::operator%=(const BigInt& rhs) {
    // *this % rhs --> divides this by rhs, and subtracts the result*rhs from this to get the modulo
    BigInt division = *this / rhs;
    BigInt mult = rhs * division;
    BigInt result = *this - mult;

    this->number = result.number;
    return *this;
}

inline BigInt operator%(BigInt lhs, const BigInt& rhs) {
    lhs %= rhs;
    return lhs;
}


// ////////// Initializations ////////// //

// base initialization to empty number ("0")
BigInt::BigInt() {
    number = {};
}

// initialization to another BigInt
BigInt::BigInt(const BigInt& rhs) {
    number = rhs.number;
}

// initialization to a string 
BigInt::BigInt(std::string rhs) {
    initialize(rhs);
}

// initialization to an int
BigInt::BigInt(int rhs) {
    initialize(std::to_string(rhs));
}

// initialization to a character/array
BigInt::BigInt(const char* rhs) {
    initialize(std::string(rhs));
}

// catchall initialization function: takes a string, assigns each character to the number vector
void BigInt::initialize(std::string source) {
    number.resize(source.size());
    for (unsigned int i = 0; i < source.size(); i++) {
        number.at(i) = source.at(i) - '0';
    }
    return;
}


// ////////// Conversion Functions ////////// //

// converts the number to string form: 12345 to "12345"
std::string BigInt::to_string() {
    std::string result;
    for (int i : this->number) {
        result += std::to_string(i);
    }
    return result;
}

// converts the number to an integer
int BigInt::to_int() {
    return std::stoi(this->to_string());
}

// converts the number to an unsigned integer
unsigned int BigInt::to_uint() {
    return std::stoul(this->to_string());  // using stoul() as there is no stoui()
}

// converts the number to a long integer
long int BigInt::to_long_int() {
    return std::stol(this->to_string());
}

// converts the number to a long unsigned integer
long unsigned int BigInt::to_long_uint() {
    return std::stoul(this->to_string());
}

// converts the number to a long long integer
long long int BigInt::to_long_long_int() {
    return std::stoll(this->to_string());
}

// converts the number to a long long unsigned integer
long long unsigned int BigInt::to_long_long_uint() {
    return std::stoull(this->to_string());
}


// ////////// Assignment Operators ////////// //

// asignment to another BigInt
BigInt& BigInt::operator=(const BigInt rhs) {
    number = rhs.number;
    return *this;
}

// assignment to a char array (BigInt a = "123")
BigInt& BigInt::operator=(const char* rhs) {
  initialize(std::string(rhs));
  return *this;
}

// assignment to an integer (BigInt a = 123)
BigInt& BigInt::operator=(const int& rhs) {
  initialize(std::to_string(rhs));
  return *this;
}

// asignment to a string
BigInt& BigInt::operator=(std::string rhs) {
  initialize(rhs);
  return *this;
}

// assignment to a vector
BigInt& BigInt::operator=(std::vector<int> rhs) {
  number = rhs;
  return *this;
}


// ////////// Stream Operators ////////// //

// outstream (ex: cout << BigInt)
std::ostream& operator<<(std::ostream& os, const BigInt& rhs) {
    for (int i : rhs.number) {
        os << i;
    }
    return os;  
}  

// instream (ex: somestream >> BigInt)
std::istream& operator>>(std::istream& is, BigInt& rhs) {
    std::string input;
    is >> input;
    rhs = input;
    return is;  
}


// ////////// Comparisan Operators ////////// //

bool operator==(BigInt lhs, const BigInt& rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }
  for (int i = 0; i < lhs.size(); i++) {
    if (rhs.number.at(i) != lhs.number.at(i)) {
        return false;
    }
  }
  return true;
}

bool operator!=(BigInt lhs, const BigInt& rhs) {
    return !(lhs == rhs);
}

bool operator<(BigInt lhs, BigInt rhs) {
    if (lhs.size() == 0 && rhs.size() != 0) {
        return true;
    }

    if (lhs.size() != 0 && rhs.size() == 0) {
        return false;
    }

    if (lhs == BigInt(0) && rhs == BigInt(0)) {
        return false;
    }

    if (lhs.negative == true && rhs.negative == false) {
        return true;
    }

    if (lhs.negative == false && rhs.negative == true) {
        return false;
    }

    if (lhs.negative == true && rhs.negative == true) {
        if (lhs.size() < rhs.size()) {
            return true;
        }
        else {
            return false;
        }
    }

    if (lhs.negative == false && lhs.size() > rhs.size()) {
        return false;
    }
    
    if (lhs.negative == false && lhs.size() < rhs.size()) {
        return true;
    }

    for (int i = 0; i < lhs.size(); i++) {
      if (lhs.number.at(i) > rhs.number.at(i)) {
        return false;
      }
      if (lhs.number.at(i) < rhs.number.at(i)) {
        return true;
      }
    }

    return false;
}

bool operator>(BigInt lhs, const BigInt& rhs) {
    return !(lhs < rhs) && !(lhs == rhs);
}

bool operator>=(BigInt lhs, const BigInt& rhs) {
    return !(lhs < rhs);
}

bool operator<=(BigInt lhs, const BigInt& rhs) {
    return !(lhs > rhs);
}


// ////////// Prefix/Postfix Operators ////////// //

// somebigint++
BigInt& BigInt::operator++(int blank) {   
    *this = *this + 1;
    return *this;
}   

// ++somebigint
BigInt& BigInt::operator++() {   
    *this = *this + 1;
    return *this;
}

// somebigint--
BigInt& BigInt::operator--(int blank) {   
    *this = *this - 1;
    return *this;
}   

// --somebigint
BigInt& BigInt::operator--() {   
    *this = *this - 1;
    return *this;
}   


// ////////// Useful Functions ////////// //

// returns the length of the number (digits)
unsigned int BigInt::size() const {
    return number.size();
}

// finds the square root using a binary search approach
BigInt BigInt::sqrt() {
    // edge case: square root of 1
    if (*this == BigInt(1)) {
        return BigInt(1);
    }

    BigInt root = *this;
    BigInt midpoint = root / 2;

    BigInt original = root;
    BigInt low = 0;
    BigInt high = original;
    BigInt square;
    BigInt old_midpoint;
    std::string trash;

    while (true) {
        old_midpoint = midpoint;
        
        square = midpoint * midpoint;
        if (square > original) {
            high = midpoint;
            midpoint = (midpoint + low) / 2;
        }
        else if (square < original) {
            low = midpoint;
            midpoint = (midpoint + high) / 2;
        }
        
        if (midpoint == old_midpoint) {
            break;
        }
    }
    return midpoint;
}

// calculates a power by exponentiation by squaring
BigInt BigInt::pow(BigInt power) {
    BigInt base = *this;
    BigInt result = 1;

    while (power > 0) {
        if (power.number.at(power.size()-1) % 2 == 0) {
            power = power / 2;
            base = base * base;
        }

        else {
            power = power - 1;
            result = result * base;
            power = power / 2;
            base = base * base;
        }
    }

    return result;
}

// finds the modular power recursively
BigInt BigInt::mod_pow(BigInt exponent, BigInt mod) {
    BigInt base = *this;

    if (exponent == 1) {
        return base % mod;
    }

    else {
        if (exponent % 2 == 1) {
            BigInt temp = base.mod_pow((exponent - 1) / 2, mod);
            return ((base * temp * temp) % mod);
        }

        else {
            BigInt temp = base.mod_pow(exponent / 2, mod);
            return (temp * temp) % mod; 
        }
    }
}

// calculates the greatest common denominator using the Extended Euclidean algorithm
BigInt BigInt::gcd(BigInt b) {
    BigInt a = *this;

    // edge case: a is 0 (returns b)
    if (a == 0) {
        return b;
    }

    // edge case: b is 0 (returns a)
    if (b == 0) {
        return a;
    }

    // ensures a is greater than b, swaps if otherwise
    if (a < b) {
        a += b;
        b = a - b;
        a -= b;
    }

    // the euclidean algorithm
    while (a % b != 0) {
        a += b;
        b = a - b;
        a -= b;
        b %= a;
    }

    return b;
}

// adapted from 'www.geeksforgeeks.org'
// returns the modular inverse using the Extended Euclidean Algorithm
BigInt BigInt::mod_inverse(BigInt b) {
    BigInt a = *this;  // reassignment as we change a
    BigInt b_initial = b;  // reserved in case x becomes negative
    BigInt x = 1;  // x = 1 because a and b are relatively prime
    BigInt y = 0;

    // edge case
    if (b == 1) {
      return 0;
    }
    

    // keeps cycling through the calculation, adjusting a/b/x/y as per the equation, until a <= 1
    while (a > 1) {
        // q is quotient
        BigInt q = a / b;
        BigInt t = b;

        b = a % b;
        a = t;
        t = y;

        y = x - q * y;
        x = t;
    }
 
    // Make sure x is positive
    if (x < 0) {
       x += b_initial;
    }
 
    return x;  // x is the modular inverse result
}

// determines primality using the "naive test" -- testing every number up to the square root
bool BigInt::is_prime() {
   // initial conditions: even, 5, 0
    int last_digit = number.at(size()-1);
    if (last_digit % 2 == 0 && size() >= 2) { return false; }
    if (last_digit == 5 && size() >= 2) { return false; }
    if (last_digit == 0) { return false; }

    BigInt i;
    BigInt j = (*this).sqrt();

    for (i = 2; i <= j; i = i + 1)
    {
        if (*this % i == 0) {
            return false;
        }
    }
    return true;
}


#endif
