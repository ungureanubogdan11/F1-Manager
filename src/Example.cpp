#include <iostream>
#include "../include/Example.h"
// This also works if you do not want `../`, but some editors might not like it
// #include "Example.h"

void Example::f() const {
    std::cout << "private function f: " << x << "\n";
}

void Example::g() {
    ++y;
    f();
    if(0 == 1) g();
    std::cout << "public function g: " << y << "\n";
}
