# matrix

```cpp

 template <typename Type> class matrix_t;
 
 typedef matrix_t <double> matrix;

 matrix_t <Type> ()

 matrix_t <Type> (size_t height, size_t width)
  
 matrix_t <Type> (size_t height, size_t width, Type const& scalar)
 
 matrix_t <Type> (matrix_t <Type> const& other)
 
 matrix_t <Type> (Type* buffer, size_t height, size_t width)

 size_t size() const

 Type const& get(size_t row, size_t column) const
 
 Type& get(size_t row, size_t column)   
  
 Type const& operator()(size_t row, size_t column) const
 
 Type& operator()(size_t row, size_t column)

 Type const& get(size_t column) const

 Type& get(size_t column)

 Type const& operator()(size_t column) const

 Type& operator()(size_t column)

 matrix_t <Type> & set(size_t row, size_t column, Type const& value)
 
 matrix_t <Type> & operator()(size_t row, size_t column, Type const& value)

 bool empty() const
 
 bool bounds(size_t row, size_t column) const+

 matrix_t <Type> & reshape(size_t height, size_t width)

 matrix_t <Type> & use(Type* buffer, size_t height, size_t width)
   
 matrix_t <Type> & use(Type* buffer)

 bool operator == (matrix_t <Type> const& other) const

 bool operator != (matrix_t <Type> const& other) const

 template  <typename Function> 
 matrix_t <Type> & each(Function process)

 template  <typename Function> 
 matrix_t <Type> & index(Function process)

 matrix_t <Type> & fill(Type const& value)

 matrix_t <Type> & operator = (Type const& scalar)

 matrix_t <Type> & operator += (Type const& value)

 matrix_t <Type> operator + (Type const& value) const
 
 matrix_t <Type> & operator -= (Type const& value)

 matrix_t <Type> operator - (Type const& value) const

 matrix_t <Type> & operator *= (Type const& value)

 matrix_t <Type> operator * (Type const& value) const

 matrix_t <Type> & operator /= (Type const& value)

 matrix_t <Type> operator / (Type const& value) const

 matrix_t <Type> & operator = (matrix_t <Type> const& other)
  
 matrix_t <Type> & operator += (matrix_t <Type> const& other)

 matrix_t <Type> operator + (matrix_t <Type> const& other) const
 
 matrix_t <Type> & operator -= (matrix_t <Type> const& other)

 matrix_t <Type> operator - (matrix_t <Type> const& other) const

 matrix_t <Type> & operator *= (matrix_t <Type> const& other)
 
 matrix_t <Type> operator * (matrix_t <Type> const& other) const

 matrix_t <Type> & transpose()

 matrix_t <Type> transposed() const

 Type trace() const

 Type determinant() const

 Type determinant(size_t excludeRow, size_t excludeColumn) const

 matrix_t <Type> & echelonate() 
 
 matrix_t <Type> echelon() const

 matrix_t <Type> & reduce()

 matrix_t <Type> reduced() const

 matrix_t <Type> inverse() const

 matrix_t <Type> & invert()

 matrix_t <Type> solve(matrix_t <Type> const& other) const

 matrix_t <Type> & swap(matrix_t <Type> & other)

 matrix_t <Type> & swap()

 std::string text(bool punctuate = false) const
 
 matrix_t& read(std::string const& input)
 
 matrix_t& read(std::istream& in)

 ~matrix_t <Type> ()

 template  <typename Type> 
 void swap(matrix_t <Type> & lhs, matrix_t <Type> & rhs)

 template  <typename Type> 
 std::ostream& operator  < < (std::ostream& out, matrix_t <Type> const& mat)

 template  <typename Type> 
 std::istream& operator > >  (std::istream& in, matrix_t <Type> & mat)

``` 
 

