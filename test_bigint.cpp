//#include "BigInt.h"
#include "BigInt.h"

using namespace std;

int main() {
    cout << "BIGINT TEST" << endl;

    cout << endl;

    cout << "Initialization:  ";  // should be:  1 2 3 4 5 6 7 8
    BigInt a(1);         cout << a << " ";
    BigInt b("2");       cout << b << " ";
    a = BigInt(3);       cout << a << " ";
    a = BigInt("4");     cout << a << " ";
    a = 5;               cout << a << " ";
    a = "6";             cout << a << " ";
    BigInt c(7);         cout << c << " ";
    BigInt d(8); c = d;  cout << c << " ";
    cout << endl;

    cout << "Addition:        ";  // should be:  1 2 3 4 5 6 7 8 9
    a = 1;               cout << a << " ";
    a += 1;              cout << a << " ";
    a += "1";            cout << a << " ";
    a += BigInt(1);      cout << a << " ";
    a++;                 cout << a << " ";
    ++a;                 cout << a << " ";
    a = a + 1;           cout << a << " ";
    a = a + "1";         cout << a << " ";
    a = a + BigInt(1);   cout << a << " ";
    cout << endl;

    cout << "Subtraction:     ";  // should be:  9 8 7 6 5 4 3 2 1
    a = 9;               cout << a << " ";
    a -= 1;              cout << a << " ";
    a -= "1";            cout << a << " ";
    a -= BigInt(1);      cout << a << " ";
    a--;                 cout << a << " ";
    --a;                 cout << a << " ";
    a = a - 1;           cout << a << " ";
    a = a - "1";         cout << a << " ";
    a = a - BigInt(1);   cout << a << " ";
    cout << endl;

    cout << "Multiplication:  ";  // should be:  2 4 8 16 32 64 128
    a = 2;               cout << a << " ";
    a *= 2;              cout << a << " ";
    a *= "2";            cout << a << " ";
    a *= BigInt(2);      cout << a << " ";
    a = a * 2;           cout << a << " ";
    a = a * "2";         cout << a << " ";
    a = a * BigInt(2);   cout << a << " ";
    cout << endl;

    cout << "Division:        ";  // should be:  128 64 32 16 8 4 2
    a = 128;             cout << a << " ";
    a /= 2;              cout << a << " ";
    a /= "2";            cout << a << " ";
    a /= BigInt(2);      cout << a << " ";
    a = a / 2;           cout << a << " ";
    a = a / "2";         cout << a << " ";
    a = a / BigInt(2);   cout << a << " ";
    cout << endl;

    cout << "Modulo:          ";  // should be:  1 2 3 4 5 6
    a = 10; a %= 9;              cout << a << " ";
    a = 10; a %= "8";            cout << a << " ";
    a = 10; a %= BigInt(7);      cout << a << " ";
    a = 10; a = a % 6;           cout << a << " ";
    a = 11; a = a % "6";         cout << a << " ";
    a = 19; a = a % BigInt(13);  cout << a << " ";
    cout << endl;

    cout << endl;

    cout << "is_prime():      ";  // should be:  1 1 1 1 1 0
    a = 11;              cout << a.is_prime() << " ";
    a = 113;             cout << a.is_prime() << " ";
    a = 1117;            cout << a.is_prime() << " ";
    a = 11119;           cout << a.is_prime() << " ";
    a = 111119;          cout << a.is_prime() << " ";
    a = "324543"; cout << a.is_prime() << " ";
    cout << endl;    

    cout << "pow():           ";  // should be:  1 2 4 8 16 32 64
    a = 2;
    cout << a.pow(0) << " ";
    cout << a.pow(1) << " ";
    cout << a.pow(2) << " ";
    cout << a.pow(3) << " ";
    cout << a.pow(4) << " ";
    cout << a.pow(5) << " ";
    cout << a.pow(6) << " ";
    cout << endl;    

    cout << "mod_pow():       ";  // should be:  9 9 9 9 9 9 9 9 9
    a = 123;
    cout << a.mod_pow(4, 13) << " ";
    cout << a.mod_pow("4", 13) << " ";
    cout << a.mod_pow(4, "13") << " ";
    cout << a.mod_pow("4", "13") << " ";
    cout << a.mod_pow(BigInt(4), BigInt(13)) << " ";
    cout << a.mod_pow(BigInt(4), 13) << " ";
    cout << a.mod_pow(4, BigInt(13)) << " ";
    cout << a.mod_pow(BigInt(4), "13") << " ";
    cout << a.mod_pow("4", BigInt(13)) << " ";
    cout << endl;  

    cout << "sqrt():          ";  // should be:  1 2 3 4 5 6 7 8 9
    cout << BigInt(1).sqrt() << " ";
    cout << BigInt(4).sqrt() << " ";
    cout << BigInt(9).sqrt() << " ";
    cout << BigInt(16).sqrt() << " ";
    cout << BigInt(25).sqrt() << " ";
    cout << BigInt(36).sqrt() << " ";
    cout << BigInt(49).sqrt() << " ";
    cout << BigInt(64).sqrt() << " ";
    cout << BigInt(81).sqrt() << " ";
    cout << endl;    

    cout << "modular_inverse():";  // should be:  1 2 3 4 5 6 7 8 9
    cout << BigInt(1).sqrt() << " ";
    cout << BigInt(4).sqrt() << " ";
    cout << BigInt(9).sqrt() << " ";
    cout << BigInt(16).sqrt() << " ";
    cout << BigInt(25).sqrt() << " ";
    cout << BigInt(36).sqrt() << " ";
    cout << BigInt(49).sqrt() << " ";
    cout << BigInt(64).sqrt() << " ";
    cout << BigInt(81).sqrt() << " ";
    cout << endl;    

    cout << endl;

    cout << "Comparisans:     ";  // should be:  1 1 0 0 1 1 1 1 1 0 0 0 0 0
    cout << (BigInt(1) == BigInt(1)) << " ";
    cout << !(BigInt(1) == BigInt(2)) << " ";

    cout << !(BigInt(2) != BigInt(1)) << " ";
    cout << (BigInt(2) != BigInt(2)) << " ";
    
    cout << (BigInt(2) > BigInt(1)) << " ";
    cout << !(BigInt(2) > BigInt(2)) << " ";
    cout << (BigInt(3) >= BigInt(2)) << " ";
    cout << (BigInt(2) >= BigInt(2)) << " ";
    cout << !(BigInt(1) >= BigInt(2)) << " ";
    
    cout << (BigInt(2) < BigInt(2)) << " ";
    cout << (BigInt(2) < BigInt(1)) << " ";
    cout << !(BigInt(2) <= BigInt(3)) << " ";
    cout << !(BigInt(2) <= BigInt(2)) << " ";
    cout << (BigInt(2) <= BigInt(1)) << " ";  
    cout << endl;

    cout << endl;

    cout << "Conversions:     ";  // should be:  5 5 5 5 5 5 5
    string s = BigInt(5).to_string();   cout << s << " ";
    int i1 = BigInt("555555555").to_int();         cout << i1 << " ";
    unsigned int i2 = BigInt("555555555").to_uint(); cout << i2 << " ";
    long int i3 = BigInt("555555555").to_long_int(); cout << i3 << " ";
    long unsigned int i4 = BigInt("555555555").to_long_uint(); cout << i4 << " ";
    long long int i5 = BigInt("555555555").to_long_long_int(); cout << i5 << " ";
    long long unsigned int i6 = BigInt("5555555555555555555").to_long_long_uint(); cout << i6 << " ";
    cout << endl;

    cout << BigInt("1234567890987654321234567890") + BigInt("12345") << endl;
    cout << endl;
}