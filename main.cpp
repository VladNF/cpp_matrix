#include <iostream>
#include "matrix.hpp"

#define UNUSED(expr) (void)(expr)

int main(int argc, char const *argv[]) {
    UNUSED(argc);
    UNUSED(argv);

    Matrix<int, 0> m;

    for (int i = 0; i < 10; ++i) m[i][i] = i;
    for (int i = 0; i < 10; ++i) m[i][9 - i] = 9 - i;

    for (int i = 1; i < 9; ++i) {
        for (int j = 1; j < 9; ++j)
            std::cout << m[i][j] << " ";
        std::cout << std::endl;
    }

    std::cout << std::endl << "Matrix elements count: " << m.size() << std::endl << std::endl;

    for (auto e : m) {
        int v;
        Slice s;
        std::tie(s, v) = e;
        std::cout << s.to_string() << " --> " << v << std::endl;
    }
}