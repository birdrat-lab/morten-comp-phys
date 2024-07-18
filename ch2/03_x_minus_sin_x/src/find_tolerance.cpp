#include <fstream>
#include <iostream>
#include <cmath>
#include <iomanip> 

int
main
(int argc, char *argv[])
{
  double min, max, res, tolerance;

  tolerance=1e-15;
  min=0.5;
  max=16;

  res=(max+min)/2.0;

  std::ofstream data_file("../data/restriction.dat");

  int i=0;
  
  while
    ((max-min)>tolerance)
    {
      if
	(0.5*res >= std::sin(res))	
	{
	  max=res;
	}
      else
	{
	  min=res;
	}

      res = (max+min)/2.0;
      i++;
    }

  data_file << std::setprecision((int) std::abs(std::log10(tolerance))+1) << res;
  data_file.close();
  
  return 0;
}
