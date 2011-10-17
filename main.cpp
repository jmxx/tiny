#include <iostream>

#include "src/Mesero.h"

int main(int argc, char** argv)
{
  std::cout << "---Mesero---" <<std::endl;

  //Mesero m = Mesero();
  Mesero::createApp()->listen();
  //m.listen();
}
