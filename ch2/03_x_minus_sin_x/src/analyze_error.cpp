/**

   07-18-24

   I investigate how the error accumulates between the
   direct evaluation of f(x) and the series expansion
   as x approaches 0.

   I consider the values of x where;

        x = 10^N

   with N an integer on [-10,1].

   The values of the series, the direct evaluation, and
   the error between them are logged in a data file by this
   script. The error plot is made in the plot directory
   by gnuplot.

   There are two regions in the error graph:

       N on [-10,-8]
       N on [-8,0]

   In the former region, the log(error) flattens off at 0, indicating
   total error. This is due to the direct evaluation rounding
   to zero at these values.

   In the latter region, error declines linearly on the log plot
   as x increases. I made a linear fit on this region and found
   the slope to be -2. Thus, the error accumulates proportionally to
   1/x^2 until x=1e-8, where the error maxes out catastrophicaly to
   100%.


**/

#include <fstream>
#include <iomanip>
#include <iostream>
#include <functional>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>

double f_x_series(double, double);
double set_x_restrict();
void init_x(int, std::vector<double>*);	    

int
main
(int argc, char* argv[])
{
  double tolerance, x_restrict;
  std::vector<double> x;
  std::function<double(double)> f_x_machine;   
  std::ofstream data_file;
  std::stringstream tol_string;
  std::string filename;
  int min_N, column_width;

  min_N=-10;
  init_x(min_N, &x);
  tolerance = 1e-32;
  x_restrict = set_x_restrict();
  
  f_x_machine  = [&](double x){return (x-std::sin(x));};

  filename = "";
  tol_string << tolerance;
  
  filename.append("../data/2_6_3_error_tol_");
  filename.append(tol_string.str());
  filename.append(".dat");
  
  data_file.open(filename);
  
  column_width=12;
  data_file << std::setw(column_width) << "log10(x)"
	    << std::setw(column_width) << "series"
	    << std::setw(column_width) << "direct"
	    << std::setw(column_width) << "error" << std::endl;
  
  for
    (int i=0; i<x.size(); i++)
    {
      double f_series, f_direct, x_curr, error;
      
      x_curr = x.at(i);
      f_series = f_x_series(x_curr, tolerance);
      f_direct = f_x_machine(x_curr);
      error = std::log10(std::abs(f_series-f_direct)/f_series);

      data_file << std::setw(column_width) << std::log10(x_curr)
	    << std::setw(column_width) << f_series
	    << std::setw(column_width) << f_direct
	    << std::setw(column_width) << error << std::endl;
     
      
    }

  data_file.close();  
    
  return 0;
}

void
init_x
(int bound,std::vector<double> *x)
{
  for
    (int i=bound; i<=0; i++)
    {
      x -> push_back((pow(10,i)));
    }
}

double
set_x_restrict
()
{
  double r;
  
  std::ifstream restrict_dat;
  restrict_dat.open("../data/restriction.dat");
  restrict_dat >> r;
  restrict_dat.close();

  return r;
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



