/**

   Date: 07-14-24

 We implement two different algorithms to compute the harmonic
 sum for finite N.

 The first, s_up, computes starting from 1 to N, the second, s_down,
 begins with N and adds through n=1.

 The program inputs N from the screen and allows one to toggle from
 single to double precision.

 The output of s_up and s_down is put to the screen. We expect s_up and
 s_down to agree in double precision through N<1e16, and for single precision
 (mostly) through 1e8.
 
   
**/


#include <functional>
#include <iostream>
#include <cmath>

#define PRECISION double

void sum(double, double, PRECISION*, std::function<bool(double,double)>, std::function<void(double*)>);

int
main
(int argc, char *argv[])
{

  double N;
  PRECISION sum_up, sum_down;

  std::function<bool(double,double)> sum_up_condition, sum_down_condition, equals;
  std::function<void(double*)> iterate_up, iterate_down;

  std::cout << "Please enter an integer N: " << std::endl;
  std::cin >> N;

  sum_up=0;
  sum_down=0;

  
  equals = [&](double x, double y){return (std::abs(x-y)<1e-15);};
  
  sum_up_condition = [&](double N, double index){return equals(N+1.0,index);};
  sum_down_condition = [&](double N, double index){return equals(index,0);};
    
  iterate_up = [&](double *i){*i += 1.0;};
  iterate_down = [&](double *i){*i -= 1.0;};

  sum(N, 1.0, &sum_up, sum_up_condition, iterate_up);
  sum(N,N, &sum_down, sum_down_condition, iterate_down);

  std::cout << "s_up=" << sum_up << std::endl;
  std::cout << "s_down=" << sum_down << std::endl;
  
  return 0;
}


void
sum
(double N, double index, PRECISION *curr_sum, std::function<bool(double,double)> condition, std::function<void(double*)> iterate)
{
  while
    (!condition(N,index))
    {
      *curr_sum += (PRECISION) 1.0/( (PRECISION) index);
      iterate(&index);
    }
}


