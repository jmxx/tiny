#include "Utils.h"

std::string Utils::getUTCTime()
{
  time_t ltime;
  struct tm* timeinfo;
  time(&ltime);
  timeinfo = gmtime(&ltime);
  char* asctime_remove_nl = asctime(timeinfo);
  asctime_remove_nl[24] = 0;
  return std::string(asctime_remove_nl) + " GMT";
}

/*
std::string Utils::getLocalTime()
{
  time_t ltime;
  time(&ltime);
  char* ctime_remove_nl = ctime(&ltime);
  ctime_remove_nl[24] = 0;
  return std::string(ctime_remove_nl) + " GMT";
}*/
