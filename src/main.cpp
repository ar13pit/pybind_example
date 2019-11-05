#include <pybind11/pybind11.h>

namespace py = pybind11;

class Person {
public:
  int a, b;
  Person(int a_, int b_) : a(a_), b(b_) {}
};

class Gatto {
public:
  Person p1;
  Gatto(const Person& p1_) : p1(p1_) {}
};

PYBIND11_MODULE(python_example, m) {
  py::class_<Person>(m, "Person")
      .def(py::init<int, int>())
      .def_readwrite("a", &Person::a)
      .def_readwrite("b", &Person::b);


  py::class_<Gatto>(m, "Gatto")
      .def(py::init<Person>())
      .def_readwrite("p1", &Gatto::p1);


}
