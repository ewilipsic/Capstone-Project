#include <pybind11/pybind11.h>
#include <string>

std::string greet(std::string name) {
    return "Hello, " + name + "!";
}

namespace py = pybind11;

PYBIND11_MODULE(example, m) {
    m.doc() = "pybind11 test module";
    m.def("greet", &greet, "Say hello to someone");
}
