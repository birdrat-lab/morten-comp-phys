

/**

date: 07-12-24

Exercise 2.6.1:

The goal is to convert an arbitrary floating decimal to binary.

nI implemented the following algorithm:


1. Check if the decimal is zero or negative.

  If the decimal is zero, its representation is identical in
  binary and decimal, the algorithm is finished.

  If the decimal is negative, we work with its absolute value.

  We rely on the log of the decimal later, which is undefined
  on negative values.
  

2. Find the leading power of two

   To find the leading bit, we need to find the largest power
   of two (i.e. 2^n where n is an integer) which is still less
   than Our Decimal.

   Consider:
   
      >> log_2(x) = b

   where 'x' is our decimal. then, 2^b=x, and by necessity

      >> floor(b)

   gives the leading bit. our binary representatino of 'x' thus far is:

      >> 1eb


      
3. build an approximation from this leading bit to set precision

   suppose:

     >> (2^b + 2^(b-1)) < x
 
   we may then extend our representation of 'x':

     >> 1.1eb

   and in the case where the sum exceeds x, the following bit becomes 0:

     >> 1.0eb

   we can extend our approximation to a specified number of bits, and thus
   set a limit to the error of our representation as not exceeding

     >> 2^(b-p)

   where 'p' is the chosen precision (number of bits).


 **/



#include <iostream>
#include <cmath>


int
main
(int argc, char *argv[])
{

  double decimal, approx;
  int sign, precision, first_order;
   
  if
    (argc==2)
    {
      std::cout << "no precision specified, assuming default precision of 16 bits." << std::endl;
      decimal = std::atof(argv[1]);
      precision=16;
    }
  else if
    (argc==3)
    {

      decimal = std::atof(argv[1]);
      precision = std::atoi(argv[2]);
    }
  else
    {
      std::cout << "please input two arguments: a decimal in scientific notation," <<
         "followed by the number of bits of percision desired in the conversion to binary." << std::endl;
      return 1;
    
    }
 
  if (decimal==0){ std::cout << "0" << std::endl; return 0;}
  else if (decimal<0){ std::cout << "-1."; decimal = std::abs(decimal);}
  else { std::cout << "1.";};
  
  first_order = (int) std::floor(std::log2(decimal));

  approx = std::pow(2,first_order);
  
  
  for
    (int j = first_order-1; j>=first_order-precision; j--)
    {

      double increase = std::pow(2,j);       
      
      if
	((increase+approx)<=decimal)
	{
	  approx += increase;
	  std::cout << "1";
	}
      else
	{
	  std::cout << "0";
	};
     
    };

  std::cout << "e"<<first_order << std::endl;

  return 0;
  
}
