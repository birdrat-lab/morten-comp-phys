
#include <iostream>
#include <fstream>
#include <iomanip>
#include <functional>
#include <cmath>
int
main
(int argc, char *argv[])
{

  double term, n, sum;

  n=0.0;
  sum=0.0;
  
  do   
    {
      term=(2.0/(2.0*n+1.0))*pow((1.0/3.0),2.0*n+1.0);
      sum += term;
      n+=1.0;
    } while (term > 1e-16);

  std::ofstream data_file;
  data_file.open("../data/ln_2.dat");
  data_file << std::setprecision(16) << sum;
  data_file.close();

  std::cout << "error: " << std::log10(std::abs(sum-std::log(2.0))) << std::endl;
  
  return 0;
}
