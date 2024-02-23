#include <pybind11/pybind11.h>
#include "matrix.hpp"

namespace py = pybind11;

PYBIND11_MODULE(mll, m) {
    py::class_<Matrix<float>>(m, "Matrix")
        .def(py::init<>())
        .def(py::init<int, int>())
        .def(py::init<int, int, const float *>())
        .def(py::init<const Matrix<float>&>())
        .def("resize", &Matrix<float>::resize)
        .def("getElement", &Matrix<float>::getElement)
        .def("setElement", &Matrix<float>::setElement)
        .def("getNumRows", &Matrix<float>::getNumRows)
        .def("getNumCols", &Matrix<float>::getNumCols)
        .def("__eq__", &Matrix<float>::operator==)
        .def("__add__", [](const Matrix<float>& a, const Matrix<float>& b) { return a + b; })
        .def("__add__", [](const Matrix<float>& a, const float& b) { return a + b; })
        .def("__add__", [](const float& a, const Matrix<float>& b) { return a + b; })
        .def("__sub__", [](const Matrix<float>& a, const Matrix<float>& b) { return a - b; })
        .def("__sub__", [](const Matrix<float>& a, const float& b) { return a - b; })
        .def("__sub__", [](const float& a, const Matrix<float>& b) { return a - b; })
        .def("__mul__", [](const Matrix<float>& a, const Matrix<float>& b) { return a * b; })
        .def("__mul__", [](const Matrix<float>& a, const float& b) { return a * b; })
        .def("__mul__", [](const float& a, const Matrix<float>& b) { return a * b; });
}