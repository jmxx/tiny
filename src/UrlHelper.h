
#ifndef URL_HELPER_H
#define URL_HELPER_H

#include <string>
#include <map>

class UrlHelper
{
public:
  UrlHelper(std::string url);

  static void SplitUrl             (std::string const& url, std::string& protocol, std::string& server, std::string& path);
  static bool RemoveProtocolFromUrl(std::string const& url, std::string& protocol, std::string& rest);

  /*
   * Parse una petición GET y devuelve la ruta solicitada y los parametros.
   */
  static void parseGetRequest(std::string et_req,     std::string& path,     std::map<std::string, std::string>& params);
};

#endif /* URL_HELPER_H */
