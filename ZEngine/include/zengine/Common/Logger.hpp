#ifndef ZE_LOGGER
#define ZE_LOGGER

// TODO
// Sortie formattée
// Stacktrace
// Support wchar_t, char16_t, char32_t

#include <zebuild.hpp>
#include <iostream>

namespace ze
{
   class ZE_API Logger
   {
   public:
      #if defined(_WIN32)
         enum class TextColor : unsigned short
         {
            Black = 0, Blue,        Green,       Aqua,
            Red,       Purple,      Yellow,      White,
            Gray,      LightBlue,   LightGreen,  LightAqua,
            LightRed,  LightPurple, LightYellow, BrightWhite
         };
      #elif defined(__unix__)
         // TODO ANSI Code enum
      #endif

      enum Level : unsigned int
      {
         Info     = FLAG(0),
         Debug    = FLAG(1),
         Warn     = FLAG(2),
         Error    = FLAG(3),
         Critical = FLAG(4)
      };

   // Constructors/Destructor
      explicit Logger(std::streambuf* = nullptr, unsigned int logMask = 0b11111);
      explicit Logger(std::ostream& output, unsigned int logMask = 0b11111);
      ~Logger() = default;

   // Member functions
      template<typename Message>
      void log(Level logLevel, Message const& message);

      template<typename... Messages>
      void logLine(Level logLevel, Messages&&... messages);

      //template<typename... Args>
      //void logFormatLine(Level logLevel, std::string const& unformattedString, Args&&... args);

      void setOutput(std::ostream& output);
      void setOutput(std::streambuf* output);
      inline std::ostream const& getOutput() const { return m_output; }

      void setLogMask(unsigned int mask);
      inline unsigned int getLogMask() const { return m_logMask; }

   // Operators
      template<typename Message>
      Logger& operator<<(Message const& message);
      Logger& operator<<(std::ostream& (*manip)(std::ostream&));
      Logger& operator<<(Logger& (*manip)(Logger&));

   // Manipulators
      Logger& info();
      static Logger& info(Logger& logger);

      Logger& debug();
      static Logger& debug(Logger& logger);

      Logger& warn();
      static Logger& warn(Logger& logger);

      Logger& error();
      static Logger& error(Logger& logger);

      Logger& critical();
      static Logger& critical(Logger& logger);

      Logger& newLine();
      static Logger& newLine(Logger& logger);

      //Logger& stacktrace();
      //static Logger& stacktrace(Logger& logger);

   // Statics
      static void SetDefaultLogOutput(std::ostream& output);
      static void SetDefaultLogOutput(std::streambuf* output);

   private:
      void printLineDetails();

      void setConsoleColor() const;
      void resetConsoleColor() const;
      TextColor getCorrespondingTextColor() const;

      void setLogLevel(Level logLevel);
      inline bool canLog() const { return m_logLevel & m_logMask && m_output.rdbuf(); };
      inline bool canLogToDefault() const { return this != &s_defaultLog && m_output.rdbuf() != s_defaultLog.getOutput().rdbuf(); }
      inline bool isConsole() const { return m_output.rdbuf() == std::cout.rdbuf() || m_output.rdbuf() == std::cerr.rdbuf(); }

      Logger& startNewLineAs(Level logLevel);

      template<typename Head, typename... Tail>
      void write(Head const& head, Tail&&... tail);

      template<typename Message>
      void write(Message const& message);

      static std::string levelToString(Level logLevel); // TODO Find better way to convert log level to string

      std::ostream m_output;
      unsigned int m_logMask;
      bool m_lineStart;
      Level m_logLevel;
      //TextColor m_color;

      static Logger s_defaultLog;
   };
}

#include <zengine/Common/Logger.inl>

#endif // ZE_LOGGER
