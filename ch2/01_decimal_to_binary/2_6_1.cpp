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
      std::cout << "No precision specified, assuming default precision of 16 bits." << std::endl;
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
      std::cout << "Please input two arguments: a decimal in scientific notation," <<
         "followed by the number of bits of percision desired in the conversion to binary." << std::endl;
      return 1;
    
    }
  
  first_order = (int) std::floor(std::log2(decimal));

  approx = std::pow(2,first_order);
  

  std::cout << "1.";
  
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
