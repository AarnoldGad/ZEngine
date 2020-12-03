template<typename Message>
void ze::Logger::log(Level logLevel, Message const& message)
{
   if (canLogToDefault())
      s_defaultLog.log(logLevel, message);

   setLogLevel(logLevel);
   write(message);
}

template<typename... Messages>
void ze::Logger::logLine(Level logLevel, Messages&&... messages)
{
   if (canLogToDefault())
      s_defaultLog.logLine(logLevel, std::forward<Messages>(messages)...);

   startNewLineAs(logLevel);
   write(std::forward<Messages>(messages)...);
}

//template<typename... Args>
//void ze::Logger::logFormattedLine(Level logLevel, std::string const& unformattedString, Args&&... args)
//{
//
//}

template<typename Message>
ze::Logger& ze::Logger::operator<<(Message const& message)
{
   if (canLogToDefault())
      s_defaultLog.write(message);

   write(message);
   return *this;
}

template<typename Head, typename... Tail>
void ze::Logger::write(Head const& head, Tail&&... tail)
{
   write(head);
   write(std::forward<Tail>(tail)...);
}

template<typename Message>
void ze::Logger::write(Message const& message)
{
   if (canLog())
   {
      if (isConsole())
         setConsoleColor();

      printLineDetails();
      m_output << message;

      if (isConsole())
         resetConsoleColor();
   }
}
