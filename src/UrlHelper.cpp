#include "UrlHelper.h"
//#include "stdHelpers.h"

#include <sstream>
#include <iostream>

bool UrlHelper::RemoveProtocolFromUrl(std::string const& url, std::string& protocol, std::string& rest) {
  std::string::size_type pos_colon = url.find(":");

  if (pos_colon == std::string::npos) {
    rest = url;  
    return false;
  }

  if (url.size() < pos_colon + 2) {
    rest = url;
    return false;
  }

  if (url[pos_colon+1] != '/' ||
      url[pos_colon+2] != '/')  {
    rest = url;
    return false;
  }

  protocol = url.substr(0,pos_colon);
  rest     = url.substr(3+pos_colon);  // Skipping three characters ( '://' )

  return true;
}

void UrlHelper::parseGetRequest(std::string request, std::string& path, std::map<std::string, std::string>& params) {

  // Remueve los caracteres de salto de line [\n] y retorno de carro [\r]
  if (request[request.size()-1] == '\x0d' || request[request.size()-1] == '\x0a') {
    request = request.substr(0, request.size()-1);
  }
  if (request[request.size()-1] == '\x0d' || request[request.size()-1] == '\x0a') {
    request = request.substr(0, request.size()-1);
  }

  // Remueve de la petición la cadena 'HTTP/1.x'
  if (request.size() > 7) {
    if (request.substr(request.size()-8, 7) == "HTTP/1.") {
      request = request.substr(0, request.size() - 9);
    }
  }

  std::string::size_type query_symbol = request.find("?");
  
  /*
   * ¿Qué es std::string::npos? 
   * Es el máximo valor posible de un string::size_type y se utiliza para indicar
   * (en este caso) que la función find falló (no encontró el '?').
   */
  if (query_symbol != std::string::npos) {
    std::string url_params = request.substr(query_symbol + 1);

    path = request.substr(0, query_symbol);

    // Appending a '&' so that there are as many '&' as name-value pairs.
    // It makes it easier to split the url for name value pairs, he he he
    url_params += "&";

    std::string::size_type next_amp = url_params.find("&");

    while (next_amp != std::string::npos) {
      std::string pair_name_value = url_params.substr(0, next_amp);
      url_params                  = url_params.substr(next_amp + 1);
      next_amp                    = url_params.find("&");

      std::string::size_type equal_symbol_pos = pair_name_value.find("=");

      std::string nam = pair_name_value.substr(0, equal_symbol_pos);
      std::string val = pair_name_value.substr(equal_symbol_pos + 1);

      /*
       * Reemplazando los signos '+' por espacios.
       */
      std::string::size_type pos_plus;
      while ( (pos_plus = val.find("+")) != std::string::npos ) {
        val.replace(pos_plus, 1, " ");
      }

      // Reemplazando notación (%xy) hexadecimal a ascii
      std::string::size_type pos_hex = 0;
      while ((pos_hex = val.find("%", pos_hex)) != std::string::npos) {
        std::stringstream h;
        h << val.substr(pos_hex + 1, 2);
        h << std::hex;

        int i;
        h >> i;

        std::stringstream f;
        f << static_cast<char>(i);
        std::string s;
        f >> s;

        val.replace(pos_hex, 3, s);
        pos_hex ++;
      }

      params.insert(std::map<std::string,std::string>::value_type(nam, val));
    }
  }
  else {
    path = request;
  }
}
/*
void UrlHelper::SplitUrl(std::string const& url, std::string& protocol, std::string& server, std::string& path) {
  RemoveProtocolFromUrl(url, protocol, server);

  if (protocol == "http") {
    std::string::size_type pos_slash = server.find("/");
  
    if (pos_slash != std::string::npos) {
      //Trace("slash found");
      path   = server.substr(pos_slash);
      server = server.substr(0, pos_slash);
    }
    else {
      //Trace("slash not found");
      path = "/";
    }
  }
  else if (protocol == "file") {
    path = ReplaceInStr(server, "\\", "/");
    server = "";
  }
  else {
    std::cerr << "unknown protocol in SplitUrl: '" << protocol << "'" << std::endl;
  }
}*/
