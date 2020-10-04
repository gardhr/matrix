# matrix

```cpp

 template <typename Type> class matrix_t;
 
 typedef matrix_t<double> matrix;

 matrix_t()

 matrix_t(size_t height, size_t width)
  
 matrix_t(size_t height, size_t width, Type const& scalar)
 
 matrix_t(matrix_t const& other)
 
 matrix_t(Type* buffer, size_t height, size_t width)

 size_t size() const

 Type const& get(size_t row, size_t column) const
 
 Type& get(size_t row, size_t column)   
  
 Type const& operator()(size_t row, size_t column) const
 
 Type& operator()(size_t row, size_t column)

 Type const& get(size_t column) const

 Type& get(size_t column)

 Type const& operator()(size_t column) const

 Type& operator()(size_t column)

 matrix_t& set(size_t row, size_t column, Type const& value)
 
 matrix_t& operator()(size_t row, size_t column, Type const& value)

 bool empty() const
 
 bool bounds(size_t row, size_t column) const+

 matrix_t& reshape(size_t height, size_t width)

 matrix_t& use(Type* buffer, size_t height, size_t width)
   
 matrix_t& use(Type* buffer)

 bool operator == (matrix_t const& other) const

 bool operator != (matrix_t const& other) const

 template  <typename Function> 
 matrix_t& each(Function process)

 template  <typename Function> 
 matrix_t& index(Function process)

 matrix_t& fill(Type const& value)

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

 matrix_t& transpose()

 matrix_t transposed() const

 Type trace() const

 Type determinant() const

 Type determinant(size_t excludeRow, size_t excludeColumn) const

 matrix_t& echelonate() 
 
 matrix_t echelon() const

 matrix_t& reduce()

 matrix_t reduced() const

 matrix_t inverse() const

 matrix_t& invert()

 matrix_t solve(matrix_t const& other) const

 matrix_t& swap(matrix_t& other)

 matrix_t& swap()

 std::string text(bool punctuate = false) const
 
 matrix_t& read(std::string const& input)
 
 matrix_t& read(std::istream& in)

 ~matrix_t()

 void swap(matrix_t& lhs, matrix_t& rhs)

 std::ostream& operator << (std::ostream& out, matrix_t const& mat)

 std::istream& operator >> (std::istream& in, matrix_t& mat)

``` 
 

