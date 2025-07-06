#include <pybind11/embed.h>  // pybind11::scoped_interpreter
#include <iostream>

namespace py = pybind11;

int main() {
    std::cout << "[C++] Starting embedded Python test...\n";
    py::scoped_interpreter guard{};  // Start interpreter

    try {
        py::exec(R"(
print("[Python] Hello from embedded Python!")
x = 42
print("[Python] x =", x)
)");
    } catch (const std::exception& e) {
        std::cerr << "[C++] Python execution error: " << e.what() << "\n";
    }

    std::cout << "[C++] Finished Python block.\n";
    return 0;
}
