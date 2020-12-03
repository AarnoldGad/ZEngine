#include "zepch.hpp"
#include <zengine/Common/Logger.hpp>
#include <iomanip>

ze::Logger ze::Logger::s_defaultLog(std::cout);

ze::Logger::Logger(std::streambuf* output, unsigned int logMask)
   : m_output(output), m_logMask(logMask), m_lineStart(true), m_logLevel(Level::Info) {}

ze::Logger::Logger(std::ostream& output, unsigned int logMask)
   : m_output(output.rdbuf()), m_logMask(logMask), m_lineStart(true), m_logLevel(Level::Info) {}

void ze::Logger::setOutput(std::ostream& output)
{
   m_output.rdbuf(output.rdbuf());
}

void ze::Logger::setOutput(std::streambuf* output)
{
   m_output.rdbuf(output);
}

void ze::Logger::setLogMask(unsigned int mask)
{
   m_logMask = mask;
}

ze::Logger& ze::Logger::operator<<(std::ostream& (*manip)(std::ostream&))
{
   if (canLogToDefault())
      s_defaultLog.write(manip);

   write(manip);
   return *this;
}

ze::Logger& ze::Logger::operator<<(Logger& (*manip)(Logger&))
{
   if (canLogToDefault())
      manip(s_defaultLog);

   return manip(*this);
}

ze::Logger& ze::Logger::info()
{
   return startNewLineAs(Info);
}

ze::Logger& ze::Logger::info(Logger& logger)
{
   return logger.info();
}

ze::Logger& ze::Logger::debug()
{
   return startNewLineAs(Debug);
}

ze::Logger& ze::Logger::debug(Logger& logger)
{
   return logger.debug();
}

ze::Logger& ze::Logger::warn()
{
   return startNewLineAs(Warn);
}

ze::Logger& ze::Logger::warn(Logger& logger)
{
   return logger.warn();
}

ze::Logger& ze::Logger::error()
{
   return startNewLineAs(Error);
}

ze::Logger& ze::Logger::error(Logger& logger)
{
   return logger.error();
}

ze::Logger& ze::Logger::critical()
{
   return startNewLineAs(Critical);
}

ze::Logger& ze::Logger::critical(Logger& logger)
{
   return logger.critical();
}

ze::Logger& ze::Logger::newLine()
{
   if (!m_lineStart)
   {
      write('\n');
      m_lineStart = true;
   }

   return *this;
}

ze::Logger& ze::Logger::newLine(Logger& logger)
{
   return logger.newLine();
}

void ze::Logger::SetDefaultLogOutput(std::ostream& output)
{
   ze::Logger::s_defaultLog.setOutput(output);
}

void ze::Logger::SetDefaultLogOutput(std::streambuf* output)
{
   ze::Logger::s_defaultLog.setOutput(output);
}

void ze::Logger::printLineDetails()
{
   if (m_lineStart)
   {
      std::time_t t = std::time(nullptr);
      std::tm tm;
      localtime_s(&tm, &t);
      #if defined(_DEBUG)
         m_output << "[" << std::put_time(&tm, "%H:%M:%S") << "] [" << (this == &s_defaultLog ? "DEFAULT | " + levelToString(m_logLevel) : levelToString(m_logLevel)) << "] ";
      #elif
         m_output << "[" << std::put_time(&tm, "%H:%M:%S") << "] [" << levelToString(m_logLevel) << "] ";
      #endif

      m_lineStart = false;
   }
}

void ze::Logger::setConsoleColor() const
{
#if defined(_WIN32)
   HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(console, static_cast<unsigned short>(getCorrespondingTextColor()));
#elif defined(__unix__)
   // TODO ANSI code insertion
#endif
}

void ze::Logger::resetConsoleColor() const
{
#if defined(_WIN32)
   HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(console, static_cast<unsigned short>(TextColor::White));
#elif defined(__unix__)
#endif
}

ze::Logger::TextColor ze::Logger::getCorrespondingTextColor() const
{
   switch (m_logLevel)
   {
   case Info:
      return TextColor::White;
   case Debug:
      return TextColor::LightGreen;
   case Warn:
      return TextColor::LightYellow;
   case Error:
      return TextColor::Red;
   case Critical:
      return TextColor::Red;
   default:
      return TextColor::White;
   }
}

void ze::Logger::setLogLevel(Level logLevel)
{
   m_logLevel = logLevel;
}

ze::Logger& ze::Logger::startNewLineAs(Level logLevel)
{
   setLogLevel(logLevel);
   newLine();
   return *this;
}

std::string ze::Logger::levelToString(Level logLevel)
{
   switch (logLevel)
   {
      case Level::Info:
         return "Info";
      case Level::Debug:
         return "Debug";
      case Level::Warn:
         return "Warn";
      case Level::Error:
         return "Error";
      case Level::Critical:
         return "Critical";
      default:
         return "None";
   }
}
