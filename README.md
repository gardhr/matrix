# matrix

Single-header matrix library for C++.

Simply include "matrix.hpp" (or "matrix", if importing default namespace).

If matrix_t or matrix are already defined, library can be wrapped in a namespace:

```cpp
#define GARDHR_MATRIX_NAMESPACE xyz
#include "matrix.hpp"
xyz::matrix m(3, 5);

```

## API

```cpp

 template <typename Type> class matrix_t;

 typedef matrix_t<double> matrix;

// Create an empty matrix
 matrix_t()

// Ie: rows == height, columns == width
 matrix_t(size_t height, size_t width = 1)

// Diagonals set to scalar, otherwise "zero"
 matrix_t(size_t height, size_t width, Type const& scalar)

// Make a copy
 matrix_t(matrix_t const& other)

// Attach to a local memory buffer instead. Not freed!
 matrix_t(Type* buffer, size_t height, size_t width = 1)

// Ie: rows * columns
 size_t size() const

/*
  NOTE: No bounds checking with get() functions
*/

 Type const& get(size_t row, size_t column = 0) const

 Type& get(size_t row, size_t column = 0)

// Returns get(row, column)
 Type const& operator()(size_t row, size_t column = 0) const

 Type& operator()(size_t row, size_t column = 0)

/*
  NOTE: set() functions ARE bounds checked
*/

 matrix_t& set(size_t row, size_t column, Type const& value)

// Returns set(row, column, value)
 matrix_t& operator()(size_t row, size_t column, Type const& value)

// Ie: rows == columns == 0
 bool empty() const

// Check if `row` and `column` inside matrix boundaries
 bool bounds(size_t row, size_t column) const

// Destructive; Old data not saved!
 matrix_t& reshape(size_t height, size_t width = 1)

// Attach to a local memory buffer instead. Not freed!
 matrix_t& use(Type* buffer, size_t height, size_t width = 1)

// Same as above, but using current `rows` and `columns`
 matrix_t& use(Type* buffer)

 bool operator == (matrix_t const& other) const

 bool operator != (matrix_t const& other) const

// Apply `process` to each element; ie: process(data[row][column])
 template  <typename Function>
 matrix_t& each(Function process)

// Apply `process` to each element with indexes; ie: process(data[row][column], row, column)
 template  <typename Function>
 matrix_t& index(Function process)

// Set all elements to `value`
 matrix_t& fill(Type const& value)

// Diagonals set to scalar, otherwise "zero"
 matrix_t& operator = (Type const& scalar)

 matrix_t& operator += (Type const& value)

 matrix_t operator + (Type const& value) const

 matrix_t& operator -= (Type const& value)

 matrix_t operator - (Type const& value) const

 matrix_t& operator *= (Type const& value)

 matrix_t operator * (Type const& value) const

 matrix_t& operator /= (Type const& value)

 matrix_t operator / (Type const& value) const

 matrix_t& operator = (matrix_t const& other)

 matrix_t& operator += (matrix_t const& other)

 matrix_t operator + (matrix_t const& other) const

 matrix_t& operator -= (matrix_t const& other)

 matrix_t operator - (matrix_t const& other) const

 matrix_t& operator *= (matrix_t const& other)

 matrix_t operator * (matrix_t const& other) const

 matrix_t& operator /= (matrix_t const& other)

 matrix_t operator / (matrix_t const& other) const

// Flip
 matrix_t& transpose()

// Make a flipped copy
 matrix_t transposed() const

 Type trace() const

 Type determinant() const

 Type determinant(size_t excludeRow, size_t excludeColumn) const

// Put in row echelon form
 matrix_t& echelonate()

// Above, with copy
 matrix_t echelon() const

// Put in reduced row echelon form
 matrix_t& reduce()

// Above, with copy
 matrix_t reduced() const

// Invert the matrix, if possible (Must be square and have a non-zero determinant)
 matrix_t& invert()

// Above, with copy
 matrix_t inverse() const

// Solve systems of equations
 matrix_t solve(matrix_t const& other) const

// Trade places
 matrix_t& swap(matrix_t& other)

// Swap rows with columns
 matrix_t& swap()

 std::string text(bool punctuate = false) const

// Parse input and set matrix accordingly
 matrix_t& read(std::string const& input)

// Parse from stream instead
 matrix_t& read(std::istream& in)

/*
  Non-member functions
*/

// Ie: lhs.swap(rhs);
 void swap(matrix_t& lhs, matrix_t& rhs)

// Ie: out << mat.text();
 std::ostream& operator << (std::ostream& out, matrix_t const& mat)

// Ie: mat.read(in);
 std::istream& operator >> (std::istream& in, matrix_t& mat)

```
