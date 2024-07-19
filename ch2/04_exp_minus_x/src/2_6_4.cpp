/**

   07-18-24

   I implement an algorithm to calculate

       exp(-x)

   Define:

       x=n*ln(2)-eps

   where n is an integer and eps is small.
       
   Thus:

       exp(-x)=2^(-n)*exp(eps)

   The crux of the problem is choosing n. I
   checked a reference to find that [-700,700] 
   for x is good, as exp(-x) runs very near the
   maximum/minimum value of a double on x= +/- 700.

   The method of bisection can be employed for x
   comfortably then as x and n are comfortably small.
   
   
**/

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <functional>
#include <vector>

double exp_minus_x(double, double);

int
main
(int argc, char *argv[])
{
  double x, tolerance, e_series, e_machine, error;

  x=atof(argv[1]);
  tolerance=1e-16;  

  e_series=exp_minus_x(x,tolerance);
  e_machine=std::exp(-1.0*x);
  error = std::log10(std::abs(e_series-e_machine)/e_machine);
  
  std::cout << "e_series: " << e_series << std::endl;
  std::cout << "e_machine: " << e_machine << std::endl;
  std::cout << "error: " << error << std::endl;

  
  
  return 0;
}

double
exp_minus_x
(double x, double tol)
{
  std::function<double(int)> sign;
  std::function<double(int, double, double)> calc_term;
  int n;
  double x_scale, factorial, sum, curr_term;

  sign=[&](int index){return pow(-1,index);};
  calc_term=[&](int index, double a, double f){return sign(index)*(a/f);};

  n=1;
  
  x_scale = x;
  factorial = 1.0;
  sum = 1.0;
  curr_term=calc_term(n, x_scale, factorial);
    
  while
    ((std::abs(curr_term/x))>tol)
    {
      sum += curr_term;

      factorial *= ((double) (n+1));
      x_scale *= x;
      n += 1;
      curr_term=calc_term(n, x_scale, factorial);
    }

  return sum;
}



