#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Spy {
private:
    int data {}; // {} default initializes the data to 0 - usally done for correctness
public:
    Spy() {
        cout << "Spy constructor" << endl;
    }
    ~Spy () {
        cout << "Spy destructor" << endl;
    }
    Spy(const Spy& other) {
        cout << "Spy copy constructor" << endl;
    }
    Spy (Spy&& other) noexcept{
        cout << "Spy move constructor" << endl;
    }
    Spy& operator=(const Spy& other) noexcept{
        cout << "Spy copy assign" << endl;
        return *this;
    }
    Spy& operator=(Spy&& other) noexcept {
        cout << "Spy move assign" << endl;
        return *this;
    }
    friend std::ostream& operator << (std::ostream& os, const Spy& spy) {
        return os << "Spy{" << spy.data << "}";
    }
};

auto spy = Spy();

Spy make_spy() {
    auto result = Spy{};
    return result;
}

int main() {
    auto Spies = std::vector<Spy>(); //Vector of spies
    Spies.reserve(5); //Reserve 5 spots in the vector
    for (int i = 0; i < 5; i++) { //Loop to add 5 spies to the vector
        cout << "!!! adding a spy !!!" << endl;
        Spies.emplace_back(); //Pushes 5 spies into the vector
    }

    for (auto&& spy      : Spies) {
        cout << spy << endl;
    }

    // for_each(Spies.begin(), Spies.end(), [](Spy& spy) //Lambda function to print each spy in the vector
    //    {std::cout << spy << std::endl;}); //Prints each spy in the vector

    std::cout << "Hello World!" << std::endl;

    // auto const spy2 = Spy(); //Local initialization of the spy
    // auto const spy2 = spy; //Spy 2 initialized using global spy - expect same data
    // auto const spy3 = spy; //Spy 3 initialized using global spy - expect same data
    // auto const spy4 = spy; //Spy 4 initialized using global spy - expect same data
    // auto const spy5 = spy; //Spy 5 initialized using global spy - expect same data

    // std::cout << "Spy2: " << spy2 << std::endl; //Local is initialized after the "Hello World!" message
    // std::cout << "Spy3: " << spy3 << std::endl;
    // std::cout << "Spy4: " << spy4 << std::endl;
    // std::cout << "Spy5: " << spy5 << std::endl;
    std::cout << "Spy: " << spy << std::endl; //Global is initialized first, but written last due to placement in main

    std::cout << "Spy{}: " << Spy{} << std::endl;
    std::cout << "make_spy(): " << make_spy() << std::endl;
    auto spy2 = make_spy();
    std::cout << "spy2: " << spy2 << std::endl;

}