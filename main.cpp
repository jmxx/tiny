#include <iostream>

#include "src/Tiny.h"

void App(HttpRequest req, HttpResponse res)
{
  req.write("HOLA MUNDO FROM APP.<br>");
  req.write("HOLA MUNDO FROM APP.<br>");
  req.end("HOLA MUNDO FROM APP.");
}

int main(int argc, char** argv)
{
  Tiny::createApp(App).listen(/*8005*/);
}
