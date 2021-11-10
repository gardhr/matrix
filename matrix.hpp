#ifndef GARDHR_MATRIX_INCLUDED
#define GARDHR_MATRIX_INCLUDED

#ifndef GARDHR_MATRIX_NAMESPACE
#define GARDHR_MATRIX_NAMESPACE
#endif

#include <cstddef>
#include <exception>
#include <istream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

namespace GARDHR_MATRIX_NAMESPACE {

template <typename Type>
struct matrix_t {
  typedef std::size_t size_t;
  typedef std::string string;
  typedef std::istream istream;
  typedef std::stringstream stringstream;

  struct exception : std::exception {
    exception(char const* text) : message(text) {}

    virtual char const* what() const throw() { return message; }

    inline operator char const*() const throw() { return message; }

    char const* message;
  };

#define MATRIX_REJECT(condition, function) \
  if (condition)                           \
  throw exception(#function " [" #condition "]")

  Type* data;
  size_t columns;
  size_t rows;
  bool managed;

  inline matrix_t() : data(0), rows(0), columns(0), managed(false) {}

  inline matrix_t(size_t height, size_t width = 1)
      : data(0), rows(0), columns(0), managed(false) {
    reshape(height, width);
  }

  inline matrix_t(size_t height, size_t width, Type const& scalar)
      : data(0), rows(0), columns(0), managed(false) {
    reshape(height, width);
    *this = scalar;
  }

  inline matrix_t(matrix_t const& other)
      : data(0), rows(0), columns(0), managed(false) {
    *this = other;
  }

  inline matrix_t(Type* buffer, size_t height, size_t width = 1)
      : data(0), rows(0), columns(0), managed(false) {
    use(buffer, height, width);
  }

  inline size_t size() const { return rows * columns; }

  inline size_t span(size_t row, size_t column) const {
    return row * columns + column;
  }

  inline Type const& get(size_t row, size_t column = 0) const {
    return data[span(row, column)];
  }

  inline Type& get(size_t row, size_t column = 0) {
    return data[span(row, column)];
  }

  inline Type const& operator()(size_t row, size_t column = 0) const {
    return get(row, column);
  }

  inline Type& operator()(size_t row, size_t column = 0) {
    return get(row, column);
  }

  inline matrix_t& set(size_t row, size_t column, Type const& value) {
    MATRIX_REJECT(row >= rows || column >= columns,
                  matrix_t::set(size_t row, size_t column, Type const& value));
    get(row, column) = value;
    return *this;
  }

  inline matrix_t& operator()(size_t row, size_t column, Type const& value) {
    return set(row, column, value);
  }

  inline bool empty() const { return rows == 0 && columns == 0; }

  inline matrix_t& reshape(size_t height, size_t width = 1) {
    if (managed)
      delete[] data;
    data = 0;
    rows = height;
    columns = width;
    if (!empty()) {
      size_t dimensions = size();
      MATRIX_REJECT(dimensions == 0,
                    matrix_t::reshape(size_t height, size_t width));
      data = new Type[dimensions];
      for (size_t ddx = 0; ddx < dimensions; ++ddx)
        data[ddx] = Type();
      managed = true;
    }
    return *this;
  }

  inline matrix_t& use(Type* buffer, size_t height, size_t width = 1) {
    if (managed)
      delete[] data;
    data = buffer;
    managed = false;
    rows = height;
    columns = width;
    if (!empty())
      MATRIX_REJECT(size() == 0,
                    matrix_t::use(Type * buffer, size_t height, size_t width));
    return *this;
  }

  inline matrix_t& use(Type* buffer) { return use(buffer, rows, columns); }

  inline bool operator==(matrix_t const& other) const {
    if (rows != other.rows || columns != other.columns)
      return false;
    Type const* rhs = other.data;
    for (size_t ddx = 0, dmx = size(); ddx < dmx; ++ddx)
      if (data[ddx] != rhs[ddx])
        return false;
    return true;
  }

  inline bool operator!=(matrix_t const& other) const {
    return !(*this == other);
  }

  inline bool bounds(size_t row, size_t column) const {
    return row < rows && column < columns;
  }

  inline bool square() const { return rows == columns; }

  template <typename Function>
  inline matrix_t& each(Function process) {
    for (size_t ddx = 0, dmx = size(); ddx < dmx; ++ddx)
      process(data[ddx]);
    return *this;
  }

  template <typename Function>
  inline matrix_t& index(Function process) {
    for (size_t rdx = 0; rdx < rows; ++rdx)
      for (size_t cdx = 0; cdx < columns; ++cdx)
        process(get(rdx, cdx), rdx, cdx);
    return *this;
  }

  inline matrix_t& fill(Type const& value) {
    for (size_t ddx = 0, dmx = size(); ddx < dmx; ++ddx)
      data[ddx] = value;
    return *this;
  }

  inline matrix_t& operator=(Type const& scalar) {
    for (size_t rdx = 0; rdx < rows; ++rdx)
      for (size_t cdx = 0; cdx < columns; ++cdx)
        get(rdx, cdx) = (rdx == cdx) ? scalar : 0;
    return *this;
  }

  inline matrix_t& operator+=(Type const& value) {
    for (size_t ddx = 0, dmx = size(); ddx < dmx; ++ddx)
      data[ddx] += value;
    return *this;
  }

  inline matrix_t operator+(Type const& value) const {
    return matrix_t(*this) += value;
  }

  inline matrix_t& operator-=(Type const& value) {
    for (size_t ddx = 0, dmx = size(); ddx < dmx; ++ddx)
      data[ddx] -= value;
    return *this;
  }

  inline matrix_t operator-(Type const& value) const {
    return matrix_t(*this) -= value;
  }

  inline matrix_t& operator*=(Type const& value) {
    for (size_t ddx = 0, dmx = size(); ddx < dmx; ++ddx)
      data[ddx] *= value;
    return *this;
  }

  inline matrix_t operator*(Type const& value) const {
    return matrix_t(*this) *= value;
  }

  inline matrix_t& operator/=(Type const& value) {
    for (size_t ddx = 0, dmx = size(); ddx < dmx; ++ddx)
      data[ddx] /= value;
    return *this;
  }

  inline matrix_t operator/(Type const& value) const {
    return matrix_t(*this) /= value;
  }

  inline matrix_t& operator=(matrix_t const& other) {
    reshape(other.rows, other.columns);
    Type const* rhs = other.data;
    for (size_t ddx = 0, dmx = size(); ddx < dmx; ++ddx)
      data[ddx] = rhs[ddx];
    return *this;
  }

  inline matrix_t& operator+=(matrix_t const& other) {
    MATRIX_REJECT(rows != other.rows || columns != other.columns,
                  matrix_t::operator+=(matrix_t const& other));
    Type const* rhs = other.data;
    for (size_t ddx = 0, dmx = size(); ddx < dmx; ++ddx)
      data[ddx] += rhs[ddx];
    return *this;
  }

  inline matrix_t operator+(matrix_t const& other) const {
    return matrix_t(*this) += other;
  }

  inline matrix_t& operator-=(matrix_t const& other) {
    MATRIX_REJECT(rows != other.rows || columns != other.columns,
                  matrix_t::operator-=(matrix_t const& other));
    Type const* rhs = other.data;
    for (size_t ddx = 0, dmx = size(); ddx < dmx; ++ddx)
      data[ddx] -= rhs[ddx];
    return *this;
  }

  inline matrix_t operator-(matrix_t const& other) const {
    return matrix_t(*this) -= other;
  }

  inline matrix_t& operator*=(matrix_t const& other) {
    return *this = *this * other;
  }

  inline bool right(matrix_t const& other) const {
    return columns == other.rows;
  }

  inline matrix_t operator*(matrix_t const& other) const {
    MATRIX_REJECT(columns != other.rows,
                  matrix_t::operator*(matrix_t const& other));
    size_t height = rows;
    size_t width = other.columns;
    matrix_t result = matrix_t(height, width);
    show((void*)result.data);
    for (size_t wdx = 0; wdx < width; ++wdx) {
      for (size_t hdx = 0; hdx < height; ++hdx) {
        Type& cell = result(hdx, wdx);
        for (size_t cdx = 0; cdx < columns; ++cdx)
          cell += get(hdx, cdx) * other(cdx, wdx);
      }
    }
    return result;
  }

  inline matrix_t& transpose() {
    matrix_t copy = transposed();
    return swap(copy);
  }

  inline matrix_t transposed() const {
    matrix_t result(columns, rows);
    for (size_t rdx = 0; rdx < rows; ++rdx)
      for (size_t cdx = 0; cdx < columns; ++cdx)
        result(cdx, rdx) = get(rdx, cdx);
    return result;
  }

  Type trace() const {
    MATRIX_REJECT(rows != columns, matrix_t::trace());
    Type sum = 0;
    for (size_t ddx = 0; ddx < rows; ++ddx)
      sum += get(ddx, ddx);
    return sum;
  }

  Type determinant() const {
    MATRIX_REJECT(rows != columns, matrix_t::determinant());
    MATRIX_REJECT((rows * columns) == 0, matrix_t::determinant());
    if (size() == 1)
      return get(0, 0);
    return echelon()(rows - 1, columns - 1);
  }

  Type determinant(size_t excludeRow, size_t excludeColumn) const {
    MATRIX_REJECT(rows != columns, matrix_t::determinant(size_t excludeRow,
                                                         size_t excludeColumn));
    MATRIX_REJECT(
        (rows * columns) == 0,
        matrix_t::determinant(size_t excludeRow, size_t excludeColumn));
    matrix_t buffer = matrix_t(rows - 1, columns - 1);
    MATRIX_REJECT(
        (buffer.rows * buffer.columns) == 0,
        matrix_t::determinant(size_t excludeRow, size_t excludeColumn));
    for (size_t idx = 0, rdx = 0; rdx < rows; ++rdx) {
      if (excludeRow == rdx)
        continue;
      for (size_t jdx = 0, cdx = 0; cdx < columns; ++cdx) {
        if (excludeColumn == cdx)
          continue;
        buffer(idx, jdx++) = get(rdx, cdx);
      }
      ++idx;
    }
    return buffer.determinant();
  }

  inline matrix_t& echelonate() {
    MATRIX_REJECT((rows * columns) == 0, matrix_t::echelonate());
    size_t dim = rows;
    size_t win = dim - 1;
    for (size_t ddx = 0; ddx < win; ddx++) {
      size_t nxt = ddx + 1;
      size_t prv = ddx - 1;
      Type cen = get(ddx, ddx);
      Type div = (ddx == 0 ? 1 : get(prv, prv));
      for (size_t idx = nxt; idx < dim; idx++) {
        Type cur = get(idx, ddx);
        for (size_t jdx = ddx; jdx < columns; jdx++) {
          Type& data = get(idx, jdx);
          Type left = data * cen;
          Type right = cur * get(ddx, jdx);
          data = (left - right) / div;
        }
      }
    }
    return *this;
  }

  inline matrix_t echelon() const { return matrix_t(*this).echelonate(); }

  inline matrix_t& reduce() {
    echelonate();
    size_t dim = columns;
    for (size_t rdx = 0; rdx < rows; ++rdx) {
      Type div = get(rdx, rdx);
      for (size_t cdx = rdx; cdx < columns; ++cdx)
        get(rdx, cdx) /= div;
    }
    return *this;
  }

  inline matrix_t reduced() const { return matrix_t(*this).reduce(); }

  inline matrix_t inverse() const {
    MATRIX_REJECT(rows != columns, matrix_t::inverse());
    Type determinant_ = determinant();
    MATRIX_REJECT(determinant_ == 0, matrix_t::inverse());
    matrix_t result = matrix_t(rows, columns);
    for (size_t rdx = 0; rdx < rows; ++rdx) {
      for (size_t cdx = 0; cdx < columns; ++cdx) {
        Type sign = (((rdx + cdx) & 1) ? -1 : 1);
        result(rdx, cdx) = sign * determinant(rdx, cdx);
      }
    }
    result.transpose();
    return result /= determinant_;
  }

  inline matrix_t& invert() {
    matrix_t copy = inverse();
    return swap(copy);
  }

  inline matrix_t solve(matrix_t const& other) const {
    return inverse() * other;
  }

  template <typename Data>
  static inline void swap_(Data& lhs, Data& rhs) {
    Data tmp = lhs;
    lhs = rhs;
    rhs = tmp;
  }

  inline matrix_t& swap(matrix_t& other) {
    swap_(rows, other.rows);
    swap_(columns, other.columns);
    swap_(data, other.data);
    swap_(managed, other.managed);
    return *this;
  }

  inline matrix_t& swap() {
    swap_(rows, columns);
    return *this;
  }

  string text(bool punctuate = false) const {
    size_t rmx = rows;
    size_t cmx = columns;
    string crlf = "\n";
    string open;
    string close;
    string comma;
    if (punctuate) {
      open = "[";
      close = "]";
      comma = ",";
      crlf = "";
    }
    if (size() == 0)
      return "[[]]";
    std::string result = open;
    size_t lst = rmx - 1;
    size_t non = cmx - 1;
    for (uint rdx = 0; rdx < rmx; ++rdx) {
      result += open;
      if (rdx != 0)
        result += crlf;
      for (uint cdx = 0; cdx < cmx; ++cdx) {
        if (cdx != 0)
          result += comma;
        stringstream ss;
        ss << get(rdx, cdx);
        result += ss.str();
        if (cdx != non)
          result += " ";
      }
      result += close;
      if (rdx != lst)
        result += comma;
    }
    result += close;
    return result;
  }

  static string& replace_(string& haystack,
                          string const& needle,
                          string const& patch) {
    size_t idx = 0;
    size_t nmx = needle.length();
    size_t pmx = patch.length();
    for (;;) {
      idx = haystack.find(needle, idx);
      if (idx == string::npos)
        break;
      haystack.replace(idx, nmx, patch);
      idx += pmx;
    }
    return haystack;
  }

  matrix_t& read(string const& input) {
    string crlf = "\n";
    string open = "[";
    string close = "]";
    string comma = ",";
    string space = " ";
    string lines = input;
    replace_(lines, open, space);
    replace_(lines, close, crlf);
    replace_(lines, comma, space);
    stringstream ss(lines);
    string line;
    std::vector<Type> values;
    size_t rows = 0;
    size_t columns = 0;
    while (getline(ss, line)) {
      stringstream ls(line);
      size_t rectangular = 0;
      Type value;
      while (ls >> value) {
        values.push_back(value);
        ++rectangular;
      }
      if (rectangular == 0)
        break;
      if (columns != 0)
        MATRIX_REJECT(columns != rectangular,
                      matrix_t::read(string const& input));
      columns = rectangular;
      ++rows;
    }
    return *this = matrix_t(&values[0], rows, columns);
  }

  matrix_t& read(istream& in) {
    string line;
    string lines;
    while (getline(in, line)) {
      size_t len = line.length();
      if (len == 0)
        break;
      lines += line + "\n";
    }
    return read(lines);
  }

  ~matrix_t() {
    if (managed)
      delete[] data;
  }
};

template <typename Type>
inline void swap(matrix_t<Type>& lhs, matrix_t<Type>& rhs) {
  lhs.swap(rhs);
}

template <typename Type>
inline std::ostream& operator<<(std::ostream& out, matrix_t<Type> const& mat) {
  return out << mat.text();
}

template <typename Type>
inline std::istream& operator>>(std::istream& in, matrix_t<Type>& mat) {
  mat.read(in);
  return in;
}

typedef matrix_t<double> matrix;

}  // namespace GARDHR_MATRIX_NAMESPACE

#endif  // GARDHR_MATRIX_INCLUDED

