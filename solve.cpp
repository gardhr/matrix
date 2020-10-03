#include "matrix"
#include <fstream>
#include <iostream>

using namespace std;

matrix solve_conglomerate(matrix const& block)
{
 size_t rows = block.rows;
 size_t columns = block.columns; 
 if(rows == columns)
  return block.inverse();
 if(rows > columns)
  return solve_conglomerate(block.transposed()).transpose();
 matrix known = matrix(rows, rows);
 for(size_t idx = 0; idx < rows; ++idx)
  for(size_t j = 0; j < rows; ++j)
   known(idx, j) = block(idx, j);
 size_t width = columns - rows;
 matrix unknown = matrix(rows, width);
 for(size_t idx = 0; idx < rows; ++idx)
  for(size_t j = 0; j < width; ++j)
   unknown(idx, j) = block(idx, rows + j);
 return known.solve(unknown);
}

int main(int argc, char** argv)
{
 try
 {
  if(argc < 2 || argc > 3)
  {
   cout << "Conglomerated matrix Solver" << endl;
   cout << "Usage: " << argv[0] << " INFILE OUTFILE" << endl;
   cout << " Note:" << endl;   
   cout << "Read from standard input if INFILE is set to `stdin` (or unspecified)" << endl;   
   cout << "Written to standard output if OUTFILE is set to `stdout` (or unspecified)" << endl;
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
  if(infile == "stdin")
   pin = &cin;
  else
   in.open(infile);

  string outfile = (argc > 2) ? argv[2] : "stdout";
  ofstream out;
  ostream* pout = &out; 
  if(outfile == "stdout")
   pout = &cout;
  else
   out.open(outfile);
 
  string input;
  vector<double> data;
  size_t columns = 0;
  size_t rows = 0;
  
  while(getline(*pin, input))
  {
   size_t count = 0;
   stringstream ss(input);
   double value;
   vector<double> next;
   
   while(ss >> value)
   {
    data.push_back(value);
    ++count;
   }
   if(count == 0)
    break; 
   if(columns != count)
   {
    if(columns != 0)
     throw matrix::exception("Invalid input"); 
    columns = count;
   }
   ++rows; 
  }
  *pout << solve_conglomerate(matrix(&data[0], rows, columns)) << endl; 
 } 
 catch(exception const& error)
 {
  cerr << "Error: " << error.what() << endl;
  return 1;
 }
 return 0;
}
