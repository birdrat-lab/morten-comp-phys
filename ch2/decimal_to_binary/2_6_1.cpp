#include<functional> 
#include <iostream>
#include <cmath>

const int MAX_POWER=1000;
const int MIN_POWER=-1000;

int get_sign(double);
int leading_power(double);
// int scale(double, std::function<double(double)>, std::function<bool(double)>, bool*);

int
main
()
{

  double decimal;

  int sign, precision, first_order;

  std::cout << "Enter decimal to convert: " << std::endl;
  std::cin >> decimal;
  
  std::cout << "To what precision should the conversion be carried: " << std::endl;
  std::cin >> precision;

  sign = get_sign(decimal);
  if(!sign){std::cout<< "Binary representation: " <<  0 << std::endl; return 0;}

  decimal = std::abs(decimal);
  
  std::cout << "leading power: " << sign <<"*2^"<<leading_power(decimal)<<std::endl;
  
  int binary[precision];
  
  return 0;

}

int
get_sign
(double decimal)
{
  return ((decimal>0)-(decimal<0));
}

int
leading_power
(double decimal)
{
  int lower_bound, upper_bound;
  int guess;
  bool exact;
  
  std::function<bool(double,int,bool*)> decimal_is_higher=[&](double x,int exp, bool *is_exact)
  {
    double power = std::pow(2,exp);
    if(std::abs(power-decimal)<=1e-16){*is_exact=true;}
    return (x>power);
  };

  lower_bound=MIN_POWER;
  upper_bound=MAX_POWER;
  guess=0;
  exact=false;
    
  //  while
  //  (std::abs(lower_bound-upper_bound<=1))
  int i = 0;
  while
    (i<6);
    {
      if
	(decimal_is_higher(decimal, guess, &exact))
	{
	  lower_bound=guess;
	}
      else
	{
	  upper_bound=guess;
	}

      if(exact){return guess;};

      std::cout<<guess<<std::endl;
      
      guess=floor(upper_bound-lower_bound)*0.5;
      i++;
    }

  return guess;

}
