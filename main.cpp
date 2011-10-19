#include <iostream>

#include "src/Mesero.h"
#include "src/HttpRequest.h"

void App(HttpRequest* request)
{
  request->write("HOLA MUNDO FROM APP.<br>");
  request->write("HOLA MUNDO FROM APP.<br>");
  request->end("HOLA MUNDO FROM APP.");
}

int main(int argc, char** argv)
{
  std::cout << "---Mesero---" <<std::endl;

  //Mesero m = Mesero();
  Mesero::createApp(App)->listen(8005);
  //m.listen();
}
