#include "src/Utils.h"

#include <iostream>

int main(int argv, char** argc)
{
  std::cout << "Local: " << Utils::getLocalTime() << std::endl;
  std::cout << "UTC: " << Utils::getUTCTime() << std::endl;
}
