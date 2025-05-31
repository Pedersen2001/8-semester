#include <iostream>
#include <vector>
#include <typeinfo>
#include <cxxabi.h>

using namespace std;

template <typename T>
auto typename_of(){
    auto s = 0;
    auto name = abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, &s);
    auto res = (s) ? to_string(s) : string(name);
    free(name);
    return res;
}

//Declare a function print taking vector<int> argument,
//which prints the elements in a comma-separated-format inside curly braces, e.g.:
//print(std::vector{1,2,3}); // should print "{1,2,3}"
void print (vector<int> v) {
    cout << "{";
    for (int i = 0; i < v.size(); i++) {
        cout << v[i];
        if (i < v.size() - 1) {
            cout << ",";
        }
    }
    cout << "} \n";
}


//Change the print function signature into an output operator<< for the vector<int> type, test it:
//std::cout << std::vector{1,2,3}; // should print "{1,2,3}"
ostream& operator<<(ostream& os, const vector<int>& v) {
    os << "{";
    for (size_t i = 0; i < v.size(); i++) {
        os << v[i];
        if (i < v.size() - 1) {
            os << ",";
        }
    }
    os << "}";
    return os;
}


// Generalize: change the operator into template operator (template function),
// where the argument is a std::vector may hold arbitrary (printable) type, test:
template <typename T> ostream& operator<<(ostream& os, const vector<T>& v) {
    os << "{";
    for (size_t i = 0; i < v.size(); i++) {
        os << v[i];
        if (i < v.size() - 1) {
            os << ",";
        }
    }
    os << "}";
    os << " (Type: " << typename_of<T>() << ")";
    return os;
}

int main() {
    print(vector{1,2,3});

    cout << vector{1,2,3} << endl;

    cout << vector{2.7,3.14} << endl;
    cout << vector{vector{"hello", "template"}, vector{"world"}} << endl;
    return 0;
    }