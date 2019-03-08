#include <stdlib.h>
#include <iostream>

int main()
{
  int i, num, j;
  std::cout << "Enter the number: ";
  std::cin >> num;

  for (i=1; i<num; i++)
    j=j*i;    

  std::cout << "The factorial of " << num << " is " << j << "\n";
  return 0;
}