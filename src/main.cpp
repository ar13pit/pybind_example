#include <iostream>
#include <stdexcept>
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

class Beta {
public:
    Person* p1;
    Beta(Person* p1_) : p1(p1_) {}
};

class Matrix {
public:
    Matrix(size_t rows, size_t cols) : m_rows(rows), m_cols(cols) {
        m_data = new float[rows*cols];
    }
    float *data() { return m_data; }
    size_t rows() const { return m_rows; }
    size_t cols() const { return m_cols; }

    void set(size_t num_frames, float* frames) {
      if (num_frames != m_rows*m_cols)
      {
        throw std::runtime_error("Not equal to allotted memory");
      }
      m_data = frames;
    }

    void print() {
      size_t i;
      std::cout << "Matrix(";
      for (i = 0; i < m_rows*m_cols - 1; i++)
      {
        std::cout << m_data[i] << ", ";
      }
      std::cout << m_data[i] << ")" << std::endl;
    }

private:
    size_t m_rows, m_cols;
    float *m_data;
};


// pybind11 code
PYBIND11_MODULE(python_example, m) {
  py::class_<Person>(m, "Person")
      .def(py::init<int, int>())
      .def_readwrite("a", &Person::a)
      .def_readwrite("b", &Person::b);


  py::class_<Gatto>(m, "Gatto")
      .def(py::init<Person>())
      .def_readonly("p1", &Gatto::p1);

  py::class_<Beta>(m, "Beta")
      .def(py::init<Person *>())
      .def_readwrite("p1", &Beta::p1);

  py::class_<Matrix>(m, "Matrix")
      .def(py::init<size_t, size_t>())
      .def("set", [](Matrix &m, py::buffer b) {
        py::buffer_info info = b.request();

        if (info.ndim != 2)
            throw std::runtime_error("Incompatible buffer dimensions");

        std::cout << "Input buffer dimensions: " << info.ndim << std::endl;
        std::cout << "Input buffer shape: (" << info.shape[0] << ", " << info.shape[1] << ")" << std::endl;

        m.set(info.shape[0]*info.shape[1], static_cast<float *>(info.ptr));
              })
      .def("print", &Matrix::print);

}
