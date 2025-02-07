#include <iostream>
#include <limits>
#include <bitset>

using namespace std;

union computer {
     float f;
     unsigned int ui;
     char c[4];
};

void printCharArray(computer comp) {
     for (int i = 0; i < 4; ++i) {
          cout << "c[" << i << "]: " << static_cast<int>(comp.c[i]) << endl;
     }
}

void printBitset(computer comp) {
     cout << "Bitset: " << bitset<32>(comp.ui) << endl;
}

double max(double a, double b) {
     return a < b ? b : a;
}

int main() {
    cout << "bool: " << sizeof(bool) << " bytes, "
         << "min: " << numeric_limits<bool>::min() << ", "
         << "max: " << numeric_limits<bool>::max() << endl;

    cout << "char: " << sizeof(char) << " bytes, "
         << "min: " << +numeric_limits<char>::min() << ", "
         << "max: " << +numeric_limits<char>::max() << endl;

    cout << "signed char: " << sizeof(signed char) << " bytes, "
         << "min: " << +numeric_limits<signed char>::min() << ", "
         << "max: " << +numeric_limits<signed char>::max() << endl;

    cout << "unsigned char: " << sizeof(unsigned char) << " bytes, "
         << "min: " << +numeric_limits<unsigned char>::min() << ", "
         << "max: " << +numeric_limits<unsigned char>::max() << endl;

    cout << "short: " << sizeof(short) << " bytes, "
         << "min: " << numeric_limits<short>::min() << ", "
         << "max: " << numeric_limits<short>::max() << endl;

    cout << "unsigned short: " << sizeof(unsigned short) << " bytes, "
         << "min: " << numeric_limits<unsigned short>::min() << ", "
         << "max: " << numeric_limits<unsigned short>::max() << endl;

    cout << "int: " << sizeof(int) << " bytes, "
         << "min: " << numeric_limits<int>::min() << ", "
         << "max: " << numeric_limits<int>::max() << endl;

    cout << "unsigned int: " << sizeof(unsigned int) << " bytes, "
         << "min: " << numeric_limits<unsigned int>::min() << ", "
         << "max: " << numeric_limits<unsigned int>::max() << endl;

    cout << "long: " << sizeof(long) << " bytes, "
         << "min: " << numeric_limits<long>::min() << ", "
         << "max: " << numeric_limits<long>::max() << endl;

    cout << "unsigned long: " << sizeof(unsigned long) << " bytes, "
         << "min: " << numeric_limits<unsigned long>::min() << ", "
         << "max: " << numeric_limits<unsigned long>::max() << endl;

    cout << "long long: " << sizeof(long long) << " bytes, "
         << "min: " << numeric_limits<long long>::min() << ", "
         << "max: " << numeric_limits<long long>::max() << endl;

    cout << "unsigned long long: " << sizeof(unsigned long long) << " bytes, "
         << "min: " << numeric_limits<unsigned long long>::min() << ", "
         << "max: " << numeric_limits<unsigned long long>::max() << endl;

    cout << "float: " << sizeof(float) << " bytes, "
         << "min: " << numeric_limits<float>::min() << ", "
         << "max: " << numeric_limits<float>::max() << endl;

    cout << "double: " << sizeof(double) << " bytes, "
         << "min: " << numeric_limits<double>::min() << ", "
         << "max: " << numeric_limits<double>::max() << endl;

    cout << "long double: " << sizeof(long double) << " bytes, "
         << "min: " << numeric_limits<long double>::min() << ", "
         << "max: " << numeric_limits<long double>::max() << endl;

     computer comp;

     // Set the integer value and print the character array
     comp.ui = 1;
     cout << "Integer value: " << comp.ui << endl;
     printCharArray(comp);

     // Check endianness
     if (comp.c[0] == 1) {
          cout << "Little-endian" << endl;
     } else {
          cout << "Big-endian" << endl;
     }

     // Reinterpret floating point numbers as unsigned integers
     float values[] = {1.0f, 2.0f, 4.0f, 8.0f};
     for (float value : values) {
          comp.f = value;
          cout << "Float value: " << comp.f << endl;
          cout << "Unsigned int value: " << comp.ui << endl;
          printBitset(comp);
     }

    return 0;


}