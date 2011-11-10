#include "Logger.h"

const char
  *Logger::RESET = "\x1b[0m",
  *Logger::FgBLACK = "\x1b[30m",
  *Logger::FgRED = "\x1b[31m",
  *Logger::FgGREEN = "\x1b[32m",
  *Logger::FgYELLOW = "\x1b[33m",
  *Logger::FgBLUE = "\x1b[34m",
  *Logger::FgMAGENTA = "\x1b[35m",
  *Logger::FgCYAN = "\x1b[36m",
  *Logger::FgWHITE = "\x1b[37m";

Logger* Logger::_instance = NULL;
bool Logger::instanceFlag = false;

/**
 * Singleton pattern
 */
Logger* Logger::getLog(std::string _fnName)
{
  if (!instanceFlag) {
    _instance = new Logger(_fnName);
    instanceFlag = true;
    return _instance;
  } else {
    //_instance->changeFnName(fnName);
    _instance->fnName = _fnName;
    return _instance;
  }
}

Logger::~Logger()
{
    std::cout << std::endl;
}

template <class T>
Logger& Logger::operator <<(const T &v)
{
  std::cout << v;
  return  *this;
}

void Logger::log(const std::ostream &_str)
{  
  debug(_str);
}

void Logger::debug(const std::ostream &str){
  log(ostreamToString(str), DEBUG_LOG_LEVEL);
}

void Logger::error(const std::ostream &str){
  log(ostreamToString(str), ERROR_LOG_LEVEL);
}

void Logger::fatal(const std::ostream &str){
  log(ostreamToString(str), FATAL_LOG_LEVEL);
}

void Logger::info(const std::ostream &str){
  log(ostreamToString(str), INFO_LOG_LEVEL);
}

void Logger::notice(const std::ostream &str){
  log(ostreamToString(str), NOTICE_LOG_LEVEL);
}

void Logger::warning(const std::ostream &str){
  log(ostreamToString(str), WARN_LOG_LEVEL);
}

void Logger::log(const std::string &_str, LogLevelEnum level)
{
  LevelColor lColor = logLevelColor(level);
  std::cout <<"in: "  << fnName << " " <<  lColor.color << lColor.level << ":" << RESET << " " << _str << std::endl;
}

std::string Logger::ostreamToString(const std::ostream &ostr)
{
  return ((std::ostringstream&)ostr).str();
}

LevelColor Logger::logLevelColor(LogLevelEnum level)
{
  LevelColor lColor;
  switch(level)
  {
    case ERROR_LOG_LEVEL:
      lColor.level = "ERROR";
      lColor.color = "\x1b[31m\x1b[1m";
      break;
    case FATAL_LOG_LEVEL:
      lColor.level = "FATAL";
      lColor.color = "\x1b[41m";
      break;
    case INFO_LOG_LEVEL:
      lColor.level = "INFO";
      lColor.color = "\x1b[42m";
      break;
    case NOTICE_LOG_LEVEL:
      lColor.level = "NOTICE";
      lColor.color = "\x1b[46m";
      break;
    case WARN_LOG_LEVEL:
      lColor.level = "WARNING";
      lColor.color = "\x1b[33m\x1b[1m";
      break;
    case DEBUG_LOG_LEVEL:
    default:
      lColor.level = "DEBUG";
      lColor.color = "\x1b[1m";
  }
  return lColor;
}
