#include <iostream>
#include "node.hpp"

int main(void) {
    auto x = variable<double>("x");
    auto y = square(x);
    auto z = add(x, y);

    x->val = 3.0;

    y->forward();
    z->forward();

    std::cout << x->val << std::endl;
    std::cout << y->val << std::endl;
    std::cout << z->val << std::endl;
}
