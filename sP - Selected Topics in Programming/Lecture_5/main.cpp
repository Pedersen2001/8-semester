#include <chrono>
#include <iostream>
#include <memory>
#include <vector>
using std::vector;


// The purpose is to measure the overhead of virtual function calls.
//
// Create a minimal class Base with:
// a single integer field
// a pure virtual increment() method
// a non-virtual decrement() method which decrements the integer field..
class Base {
public:
    int counter{};

    virtual void increment() = 0; // Abstract class since no implementation is specified
    // If there is at least one method with virtual = 0, the class is abstract

    void decrement() {
        counter -= 1;
    }

};


// Create a derived class Derived, that overrides just the increment() method
// which increments the integer field.
class Derived : public Base {
public:
    Derived() {}

    void increment() override {
        counter += 1;
    }


};



int main() {


    // Create a vector of 10 million (smart) pointers to Base
    // and fill it with pointers to Derived objects.
    // vector<std::unique_ptr<Base*>> bases;

    // std::shared_ptr<Base> ptr1 = std::make_shared<Derived>(); // Creates a shared_ptr
    std::unique_ptr<Base> ptr = std::make_unique<Derived>(); // Allocate memory
    vector<std::unique_ptr<Base>> vec;



    // Hello and welcome to my tutorial
    std::cout << ptr->counter << std::endl;
    for (int i = 0; i < 1000000; i++) {
        vec.emplace_back(std::make_unique<Derived>()); // No need for std::move
    }

    // Measure the time of:
    //
    // 1. Calling increment() on all the elements of the vector;
    // 2. Calling decrement() on all elements of the vector.
    auto timer = std::chrono::high_resolution_clock::now();
    for (const auto & i : vec) {
        i->increment();
    }
    auto timerend = std::chrono::high_resolution_clock::now();
    std::cout << "Time for increment ((smart) pointers to Base): " << std::chrono::duration_cast<std::chrono::milliseconds>(timerend - timer).count() << " milliseconds" << std::endl;

    timer = std::chrono::high_resolution_clock::now();
    for (const auto & i : vec) {
        i->decrement();
    }
    timerend = std::chrono::high_resolution_clock::now();
    std::cout << "Time for decrement ((smart) pointers to Base): " << std::chrono::duration_cast<std::chrono::milliseconds>(timerend - timer).count() << " milliseconds" << std::endl;

    //     Finally, create another vector of 10 million Derived objects (not pointers to them) and measure the time of:
    //
    //     Calling increment() on all the elements of the vector;
    //     Calling decrement() on all elements of the vector.
    vector<std::unique_ptr<Derived>> vec2;
    for (int i = 0; i < 1000000; i++) {
        vec2.emplace_back(std::make_unique<Derived>()); // No need for std::move
    }

    timer = std::chrono::high_resolution_clock::now();
    for (const auto & i : vec2) {
        i->increment();
    }
    timerend = std::chrono::high_resolution_clock::now();
    std::cout << "Time for increment (Derived objects (not pointers to them)): " << std::chrono::duration_cast<std::chrono::milliseconds>(timerend - timer).count() << " milliseconds" << std::endl;

    timer = std::chrono::high_resolution_clock::now();
    for (const auto & i : vec2) {
        i->decrement();
    }
    timerend = std::chrono::high_resolution_clock::now();
    std::cout << "Time for decrement (Derived objects (not pointers to them)): " << std::chrono::duration_cast<std::chrono::milliseconds>(timerend - timer).count() << " milliseconds" << std::endl;
    // Remember to measure optimized (Release) builds (without the Debug instrumentation) and measure at least twice per run and alternating (the first batch can be slow due to cold start).
    // What can we conclude?
    //  - They are equally epic



    return 0;
}