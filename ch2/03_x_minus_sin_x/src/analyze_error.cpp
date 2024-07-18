#include <fstream>
#include <iomanip>
#include <iostream>
#include <functional>
#include <cmath>
#include <vector>

const double x_restrict=1.89549426703398;

void init_x(int, std::vector<double>*); 
void get_factorial(double, std::vector<double>*);
double f_x_series(double, std::vector<double>*);


int
main
(int argc, char* argv[])
{
  
  double tolerance, f_x;
  std::vector<double> factorial, x;
  std::function<double(double)> f_x_machine;

  std::ofstream data_file("error.dat");

  
  f_x_machine  = [&](double x){return (x-std::sin(x));};
  
  tolerance = 1e-15;
  get_factorial(tolerance, &factorial);
  init_x(-10,&x);

  for
    (double a : x)
    {
      std::cout << a << std::endl;
    }

  data_file.close();
    
  return 0;
}

void
init_x
(int bound, std::vector<double> *x)
{
  for
    (int i=0, i>=bound;i--)
    {
      x -> push_front(-1*pow(10,-i));
      x -> push_back(pow(10,-i));
    }
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



