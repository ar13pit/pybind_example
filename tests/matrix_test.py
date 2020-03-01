#! /usr/bin/env python3

import numpy as np
import python_example as m

#  inp = np.array([[0, 1, 2, 3, 4], [5, 6, 7, 8, 9.]], dtype=np.float32)
inp = np.array(np.random.rand(2, 5), dtype=np.float32)
print("Input matrix:")
print(inp)
print()

mat = m.Matrix(2, 5)
mat.set(inp)
mat.print()
