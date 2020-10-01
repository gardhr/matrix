# matrix

 typedef matrix_t&ltdouble&gt matrix;

 matrix_t&ltType&gt()

 matrix_t&ltType&gt(size_t height, size_t width)
  
 matrix_t&ltType&gt(size_t height, size_t width, Type const& scalar)
 
 matrix_t&ltType&gt(matrix_t&ltType&gt const& other)
 
 matrix_t&ltType&gt(Type* buffer, size_t height, size_t width)

 size_t size() const

 Type const& get(size_t row, size_t column) const
 
 Type& get(size_t row, size_t column)   
  
 Type const& operator()(size_t row, size_t column) const
 
 Type& operator()(size_t row, size_t column)

 Type const& get(size_t column) const

 Type& get(size_t column)

 Type const& operator()(size_t column) const

 Type& operator()(size_t column)

 matrix_t&ltType&gt& set(size_t row, size_t column, Type const& value)
 
 matrix_t&ltType&gt& operator()(size_t row, size_t column, Type const& value)

 bool empty() const
 
 bool bounds(size_t row, size_t column)

 matrix_t&ltType&gt& reshape(size_t height, size_t width)

 matrix_t&ltType&gt& use(Type* buffer, size_t height, size_t width)
   
 matrix_t&ltType&gt& use(Type* buffer)

 bool operator == (matrix_t&ltType&gt const& other) const

 bool operator != (matrix_t&ltType&gt const& other) const

 template &lttypename Function&gt
 matrix_t&ltType&gt& each(Function process)

 template &lttypename Function&gt
 matrix_t&ltType&gt& index(Function process)

 matrix_t&ltType&gt& fill(Type const& value)

 matrix_t&ltType&gt& operator = (Type const& scalar)

 matrix_t&ltType&gt& operator += (Type const& value)

 matrix_t&ltType&gt operator + (Type const& value) const
 
 matrix_t&ltType&gt& operator -= (Type const& value)

 matrix_t&ltType&gt operator - (Type const& value) const

 matrix_t&ltType&gt& operator *= (Type const& value)

 matrix_t&ltType&gt operator * (Type const& value) const

 matrix_t&ltType&gt& operator /= (Type const& value)

 matrix_t&ltType&gt operator / (Type const& value) const

 matrix_t&ltType&gt& operator = (matrix_t&ltType&gt const& other)
  
 matrix_t&ltType&gt& operator += (matrix_t&ltType&gt const& other)

 matrix_t&ltType&gt operator + (matrix_t&ltType&gt const& other) const
 
 matrix_t&ltType&gt& operator -= (matrix_t&ltType&gt const& other)

 matrix_t&ltType&gt operator - (matrix_t&ltType&gt const& other) const

 matrix_t&ltType&gt& operator *= (matrix_t&ltType&gt const& other)
 
 matrix_t&ltType&gt operator * (matrix_t&ltType&gt const& other) const

 matrix_t&ltType&gt& transpose()

 matrix_t&ltType&gt transposed() const

 Type trace() const

 Type determinant() const

 Type determinant(size_t excludeRow, size_t excludeColumn) const

 matrix_t&ltType&gt& echelonate() 
 
 matrix_t&ltType&gt echelon() const

 matrix_t&ltType&gt& reduce()

 matrix_t&ltType&gt reduced() const

 matrix_t&ltType&gt inverse() const

 matrix_t&ltType&gt& invert()

 matrix_t&ltType&gt solve(matrix_t&ltType&gt const& other) const

 matrix_t&ltType&gt& swap(matrix_t&ltType&gt& other)

 ~matrix_t&ltType&gt()

 template &lttypename Type&gt
 void swap(matrix_t&ltType&gt& lhs, matrix_t&ltType&gt& rhs)

 template &lttypename Type&gt
 std::ostream& operator &lt&lt (std::ostream& out, matrix_t&ltType&gt const& mat)

 template &lttypename Type&gt
 std::istream& operator &gt&gt (std::istream& in, matrix_t&ltType&gt& mat)

