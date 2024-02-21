#include <iostream>

int main()
{
  std::cout << "Enter two numbers:" << std::endl;
  int v1 = 0, v2 = 0;
  std::cin >> v1 >> v2;
  std::cout << "The product of " << v1; << " and " << v2;
  << " is " << v1 * v2 << std::endl;

  // 针对练习1.5/1.6的修改
  // std::cout << "The product of " << v1; 
  // std::cout << " and " << v2;
  // std::cout << " is " << v1 * v2 << std::endl;
}
