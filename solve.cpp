#include <fstream>
#include <iostream>
#include <string>
#include "matrix"

using namespace std;

matrix solve_conglomerate(matrix const& block) {
  size_t rows = block.rows;
  size_t columns = block.columns;
  if (rows == columns)
    return block.inverse();
  if (rows > columns)
    return solve_conglomerate(block.transposed()).transpose();
  matrix system = matrix(rows, rows);
  for (size_t idx = 0; idx < rows; ++idx)
    for (size_t jdx = 0; jdx < rows; ++jdx)
      system(idx, jdx) = block(idx, jdx);
  size_t width = columns - rows;
  matrix evaluation = matrix(rows, width);
  for (size_t idx = 0; idx < rows; ++idx)
    for (size_t jdx = 0; jdx < width; ++jdx)
      evaluation(idx, jdx) = block(idx, rows + jdx);
  return system.solve(evaluation);
}

int main(int argc, char** argv) {
  try {
    if (argc < 2 || argc > 3) {
      cout << "Conglomerate Matrix Solver" << endl;
      cout << "Usage: " << argv[0] << " INFILE OUTFILE" << endl;
      cout << " Note:" << endl;
      cout << "Read from standard input if INFILE is set to `stdin` (or "
              "unspecified)"
           << endl;
      cout << "Written to standard output if OUTFILE is set to `stdout` (or "
              "unspecified)"
           << endl;
      cout << " Example: solve 2x + 5y = 41, 7x + 11y = 98" << endl << endl;
      cout << argv[0] << endl;
      cout << "2 5 41 [ENTER]" << endl;
      cout << "7 11 98 [ENTER]" << endl;
      cout << "[ENTER]" << endl;
      cout << "3 <- x" << endl;
      cout << "7 <- y" << endl << endl;
    }

    string infile = (argc > 1) ? argv[1] : "stdin";
    ifstream in;
    istream* pin = &in;
    if (infile == "stdin")
      pin = &cin;
    else
      in.open(infile);

    string outfile = (argc > 2) ? argv[2] : "stdout";
    ofstream out;
    ostream* pout = &out;
    if (outfile == "stdout")
      pout = &cout;
    else
      out.open(outfile);

    matrix input;
    *pin >> input;
    *pout << solve_conglomerate(input) << endl;
  } catch (exception const& error) {
    cerr << "Error: " << error.what() << endl;
    return 1;
  }
  return 0;
}
