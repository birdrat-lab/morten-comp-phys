/**

   7-18-24

   I write a program to calculate

      f(x) = x - sin(x)

   For a wide range of x. The text warns us to be careful
   in the region where x - sin(x) is close to 0, as the
   subtraction of nearly equivalent floats loses precision.

   It can be shown from the loss of precision theorem that we
   can directly evaluate f(x) so long as

      1 - (sin(x)/x) >= 1/2  

   and we need to carefully consider the taylor expansion if
   this condition fails.

   First, I wrote a script (find_tolerance.cpp) to find the range
   of x where we must expand the series. The method of bisection
   is employed to find x_restrict to a specified tolerance, and the
   value is outputted to a text file (restriction.dat).

   This script uses reads in that value as x_restrict.

   The value of x to calculate is passed as an argument at runtime.
   
   If abs(x) >= x_restrct, f(x) is calculated directly. Otherwise,
   I expand the series.

   A recurrence relation calculates x^(2n+3) and (2n+3)!. We sum these
   values (appropriately signed) until the terms fall below a specified
   tolerance in the script.

   I tested values of x as small as 1e-10, and by setting the
   tolerance to 1e-32, the series was able to accurately calculate f(x)
   when checked with a reference.

   This condludes the assigned problem, though I was curious about
   the behavior of the error and investigated it in another script
   (analyze_error.cpp).
   
**/

#include <fstream>
#include <iomanip>
#include <iostream>
#include <functional>
#include <cmath>
#include <vector>

double f_x_series(double, double);

int
main
(int argc, char* argv[])
{

  std::cout << std::scientific;
  
  if
   (argc != 2)
    {
      std::cout << "Provide where you want the function evaluated as an execution arguement." << std::endl;
      return 1;
    } 

  double tolerance, x, x_restrict, f_x;
  std::function<double(double)> f_x_machine;
  std::function<bool(double)> f_x_is_small;
  std::ifstream restrict_dat;
   
  x = atof(argv[1]);
  tolerance = 1e-32;

  restrict_dat.open("../data/restriction.dat");
  restrict_dat >> x_restrict;
  restrict_dat.close();
  
  f_x_machine  = [&](double x){return (x-std::sin(x));};
  f_x_is_small  = [&](double x){return (std::abs(x)<x_restrict);};

  if
    (f_x_is_small(x))
    {
      f_x = f_x_series(x, tolerance);
    }
  else
    {
      f_x = f_x_machine(x);
    }

  std::cout << std::setprecision(10) << "f(x)=" << f_x << std::endl;
   
  return 0;
}


double
f_x_series
(double x, double tol)
{
  int n;
  double f_x, x_power, factorial;
  std::function<int(int)> sign;

  sign=[&](int a){return pow(-1,((a-3)/2));};
  
  // first term of the series
  n = 3;
  f_x = 0.0;
  factorial = 6.0;
  x_power = pow(x,3);

  
  while
    ((x_power/factorial) >= tol)
    {
      f_x += sign(n)*(x_power/factorial);
      
      x_power *= pow(x, 2);
      factorial *= ((n+1)*(n+2));
      n += 2;
    };

  return f_x;
}



