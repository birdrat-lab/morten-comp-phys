/**

   Date: 07-17-24

   I output the log relative error of s_up and s_down
   to a text file.

   I use gnuplot to create a log-log plot of the error
   against N to show the different regions of behavior.
   gnuplot let's us fit functions to the scatterplot
   to further analyze the error.

   The double precision error accumulates at a slope
   of roughly 0.5 across the whole range of N=1-10.
   This means the error scales with sqrt(N).

   The single precision error has a similar region
   through N=4, then sharply climbs between 4<=N<=8
   at a slope of 1.5, then levels off.

   I connect the leveling off at N>8 due to underflow
   errors in single precision.

   As for the region in single precision where error
   scales as N^(1.5), I'm not sure. 
   
**/

#include <functional>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

#define PRECISION double

void init_arr(double*, int, int);
void sum(double, double, PRECISION*, std::function<bool(double,double)>, std::function<void(double*)>);

int
main
(int argc, char *argv[])
{

  PRECISION sum_up, sum_down;

  std::string filename, column_space;
  std::ofstream data_file;
  double lower_bound, upper_bound, error;

  std::function<bool(double,double)> equals, condition;;
  std::function<void(double*)> iterate_up, iterate_down;
  
  filename = "../data/2_6_2_2_double.dat";
  column_space = "        ";
  int max_N=10;
  
  equals = [&](double x, double y){return (std::abs(x-y)<1e-4);};
  condition = [&](double limit, double index){return equals(limit,index);};
    
  iterate_up = [&](double *i){*i += 1.0;};
  iterate_down = [&](double *i){*i -= 1.0;};

  data_file.open(filename);
  
  data_file << "N" << column_space << "s_up" << column_space << "s_down" << column_space << "error" << std::endl;

  
  for
    (int i=0; i<max_N; i++)
    {

      sum_up=0;
      sum_down=0;

      upper_bound=pow(10,i+1)+1.0;
      lower_bound=0.0;
      
      sum(upper_bound, lower_bound+1.0, &sum_up, condition, iterate_up);
      sum(lower_bound, upper_bound-1.0, &sum_down, condition, iterate_down);

      error = std::log10(std::abs(sum_up-sum_down)/sum_down);

      data_file << i+1 << column_space << sum_up << column_space << sum_down << column_space << error << std::endl;

      std::cout << "Finished N=10^" << i+1 << std::endl;
      
    };

  data_file.close();
  
  return 0;
}

void
sum
(double limit, double index, PRECISION *curr_sum, std::function<bool(double,double)> condition, std::function<void(double*)> iterate)
{
  do
    {
      *curr_sum += ((PRECISION) 1.0)/( (PRECISION) index);
      iterate(&index);
    }
  while (!condition(limit,index));
}


