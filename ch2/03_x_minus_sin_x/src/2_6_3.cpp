/**

   7-18-24

**/


#include <iomanip>
#include <iostream>
#include <functional>
#include <cmath>
#include <vector>

const double x_restrict=1.89549426703398;

void get_factorial(double, std::vector<double>*);
double f_x_series(double, std::vector<double>*);

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

  double tolerance, x, f_x;
  std::function<double(double)> f_x_machine;
  std::function<bool(double)> f_x_is_small;

  x = atof(argv[1]);
  tolerance = 1e-15;

  f_x_machine  = [&](double x){return (x-std::sin(x));};
  f_x_is_small  = [&](double x){return (std::abs(x)<=x_restrict);};

  if
    (f_x_is_small(x))
    {
      std::vector<double> factorial;
      get_factorial(tolerance, &factorial);
      
      f_x = f_x_series(x, &factorial);
    }
  else
    {
      f_x = f_x_machine(x);
    }

  std::cout << std::setprecision((int) (-1*log10(tolerance)+1.0)) << "f(x)=" << f_x << std::endl;
  
  return 0;
}



void
get_factorial
(double tol, std::vector<double> *fact)
{
  double power, factorial;

  int n=3;

  power=pow(x_restrict, n);
  factorial=6.0;
 
  fact->push_back(factorial);
  
  while
    ((power/factorial)>tol)
    {
      power *= pow(x_restrict,2);
      factorial *= (double) ((n+1)*(n+2));

      n+=2;
      fact->push_back(factorial);	
    }
}

double
f_x_series
(double x,  std::vector<double> *fact)
{
  int N, n;
  double f_x, x_power;

  N = (int) fact -> size();
  n = 3;
  f_x = 0.0;
  x_power = pow(x,3);
  
  for
    (int i=0; i<N; i++)
    {

      f_x += pow(-1,i)*(x_power/(fact -> at(i)));

      n += 2;
      x_power *= pow(x, 2);
    };

  return f_x;
}



