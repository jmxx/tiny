#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <sstream>
#include <ostream>

/**
 * http://stackoverflow.com/questions/674060/customize-cout
 */

#define LOG(stream)     (*Logger::getLog(__FUNCTION__)).log(std::stringstream().flush() << stream)
#define DEBUG(stream)   (*Logger::getLog(__FUNCTION__)).debug(std::stringstream().flush() << stream)
#define ERROR(stream)   (*Logger::getLog(__FUNCTION__)).error(std::stringstream().flush() << stream)
#define FATAL(stream)   (*Logger::getLog(__FUNCTION__)).fatal(std::stringstream().flush() << stream)
#define INFO(stream)    (*Logger::getLog(__FUNCTION__)).info(std::stringstream().flush() << stream)
#define NOTICE(stream)  (*Logger::getLog(__FUNCTION__)).notice(std::stringstream().flush() << stream)
#define WARNING(stream) (*Logger::getLog(__FUNCTION__)).warning(std::stringstream().flush() << stream)
//#define LOG(stream) do{ std::ostringstream s; s << stream; (*Logger::getLog(__FUNCTION__)).log(s.str()); } while(0)

struct LevelColor {
  const char *level;
  const char *color; 
};

enum LogLevelEnum {
  DEBUG_LOG_LEVEL,
  INFO_LOG_LEVEL,
  WARN_LOG_LEVEL,
  ERROR_LOG_LEVEL,
  NOTICE_LOG_LEVEL,
  FATAL_LOG_LEVEL
};

class Logger
{
public:
  /**
   * Método estático que retorna la instancia actual del Logger.
   */
  static Logger* getLog(std::string fnName);
  
  ~Logger();
  
  /**
   * Sobrecarga del operador <<
   */
  template <class T>
  Logger& operator <<(const T &v);
  
  void debug(const std::ostream &str);
  void error(const std::ostream &str);
  void fatal(const std::ostream &str);
  void info(const std::ostream &str);
  void log(const std::ostream &str);
  void notice(const std::ostream &str);
  void warning(const std::ostream &str);
  void log(const std::string &str);
  void log(const std::string &str, LogLevelEnum level);
  
protected:
  void message(std::string msg, const char* color);

  static const char *RESET, *FgBLACK, *FgRED, *FgGREEN, *FgYELLOW, *FgBLUE, *FgMAGENTA, *FgCYAN, *FgWHITE;

private:
  /**
   * Constructor de Logger
   */
  Logger(std::string _fnName) : fnName(_fnName) {
    if (instanceFlag) {
      std::cout << fnName << ": ";
    }
  }
  
  static Logger* _instance;
  static bool instanceFlag;
  
  std::string ostreamToString(const std::ostream &ostr);
  LevelColor logLevelColor(LogLevelEnum level);

  //std::ostringstream stream;
  std::string fnName;
};

#endif /* LOG_H */
