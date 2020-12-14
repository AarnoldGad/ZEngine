template<typename CharType>
ze::ZLogger<CharType>::ZLogger(BufType* output, unsigned int logMask)
	: m_output(output), m_logMask(logMask), m_lineStart(true), m_logLevel(Level::Info) {}

template<typename CharType>
ze::ZLogger<CharType>::ZLogger(StreamType& output, unsigned int logMask)
	: m_output(output.rdbuf()), m_logMask(logMask), m_lineStart(true), m_logLevel(Level::Info) {}

template<typename CharType>
template<typename Message>
void ze::ZLogger<CharType>::log(Level logLevel, Message const& message)
{
	setLogLevel(logLevel);
	write(message);
}

template<typename CharType>
template<typename... Messages>
void ze::ZLogger<CharType>::logLine(Level logLevel, Messages&&... messages)
{
	startNewLineAs(logLevel);
	write(std::forward<Messages>(messages)...);
}

template<typename CharType>
template<typename... Args>
void ze::ZLogger<CharType>::logFormatedLine(Level logLevel, StringType const& unformattedLine, Args&&... args)
{
	logLine(logLevel, formatLine(unformattedLine, std::forward<Args>(args)...));
}

template<typename CharType>
void ze::ZLogger<CharType>::setOutput(StreamType& output)
{
	m_output.rdbuf(output.rdbuf());
}

template<typename CharType>
void ze::ZLogger<CharType>::setOutput(BufType* output)
{
	m_output.rdbuf(output);
}

template<typename CharType>
inline std::basic_ostream<CharType>& ze::ZLogger<CharType>::getOutput() const noexcept
{
	return m_output;
}

template<typename CharType>
void ze::ZLogger<CharType>::setLogMask(unsigned int mask) noexcept
{
	m_logMask = mask;
}

template<typename CharType>
inline unsigned int ze::ZLogger<CharType>::getLogMask() const noexcept
{
	return m_logMask;
}

template<typename CharType>
inline bool ze::ZLogger<CharType>::canLog() const
{
	return m_logLevel & m_logMask && m_output.rdbuf();
}

template<typename CharType>
inline bool ze::ZLogger<CharType>::isConsole() const
{
	return false;
}

template<>
inline bool ze::ZLogger<char>::isConsole() const
{
	return m_output.rdbuf() == std::cout.rdbuf() || m_output.rdbuf() == std::cerr.rdbuf() || m_output.rdbuf() == std::clog.rdbuf();
}

template<typename CharType>
template<typename Message>
ze::ZLogger<CharType>& ze::ZLogger<CharType>::operator<<(Message const& message)
{
	write(message);
	return *this;
}

template<typename CharType>
ze::ZLogger<CharType>& ze::ZLogger<CharType>::operator<<(StreamType& (*manip)(StreamType&))
{
	write(manip);
	return *this;
}

template<typename CharType>
ze::ZLogger<CharType>& ze::ZLogger<CharType>::operator<<(LoggerType& (*manip)(LoggerType&))
{
	return manip(*this);
}

template<typename CharType>
ze::ZLogger<CharType>& ze::ZLogger<CharType>::info()
{
	return startNewLineAs(Info);
}

template<typename CharType>
ze::ZLogger<CharType>& ze::ZLogger<CharType>::info(LoggerType& logger)
{
	return logger.info();
}

template<typename CharType>
ze::ZLogger<CharType>& ze::ZLogger<CharType>::debug()
{
	return startNewLineAs(Debug);
}

template<typename CharType>
ze::ZLogger<CharType>& ze::ZLogger<CharType>::debug(LoggerType& logger)
{
	return logger.debug();
}

template<typename CharType>
ze::ZLogger<CharType>& ze::ZLogger<CharType>::warn()
{
	return startNewLineAs(Warn);
}

template<typename CharType>
ze::ZLogger<CharType>& ze::ZLogger<CharType>::warn(LoggerType& logger)
{
	return logger.warn();
}

template<typename CharType>
ze::ZLogger<CharType>& ze::ZLogger<CharType>::error()
{
	return startNewLineAs(Error);
}

template<typename CharType>
ze::ZLogger<CharType>& ze::ZLogger<CharType>::error(LoggerType& logger)
{
	return logger.error();
}

template<typename CharType>
ze::ZLogger<CharType>& ze::ZLogger<CharType>::critical()
{
	return startNewLineAs(Critical);
}

template<typename CharType>
ze::ZLogger<CharType>& ze::ZLogger<CharType>::critical(LoggerType& logger)
{
	return logger.critical();
}

template<typename CharType>
ze::ZLogger<CharType>& ze::ZLogger<CharType>::newLine()
{
	if (!m_lineStart)
	{
		write("\n");
		m_lineStart = true;
	}

	return *this;
}

template<typename CharType>
ze::ZLogger<CharType>& ze::ZLogger<CharType>::newLine(LoggerType& logger)
{
	return logger.newLine();
}

template<typename CharType>
void ze::ZLogger<CharType>::printLineDetails()
{
	if (m_lineStart)
	{
		std::time_t t = std::time(nullptr);
		std::tm tm;
		localtime_s(&tm, &t);
		m_output << "[" << std::put_time(&tm, STRING_LITERAL(CharType, "%H:%M:%S")) << "] [" << levelToString(m_logLevel) << "] ";

		m_lineStart = false;
	}
}

template<typename CharType>
template<unsigned int N, typename Head, typename... Tail>
std::basic_string<CharType> ze::ZLogger<CharType>::formatLine(StringType const& unformattedLine, Head const& head, Tail&&... tail)
{
	return formatLine<N + 1>(formatLine<N>(unformattedLine, head), std::forward<Tail>(tail)...);
}

template<typename CharType>
template<unsigned int N, typename Arg>
std::basic_string<CharType> ze::ZLogger<CharType>::formatLine(StringType const& unformattedLine, Arg const& arg)
{
	std::stringstream ss;

	size_t start = 0;
	size_t charPos = unformattedLine.find("{" + std::to_string(N) + "}");
	while (charPos != std::string::npos)
	{
		ss << unformattedLine.substr(start, charPos - start) << arg;

		start = charPos + 3;
		charPos = unformattedLine.find("{" + std::to_string(N) + "}", start);
	}

	ss << unformattedLine.substr(start);
	return ss.str();
}

template<typename CharType>
void ze::ZLogger<CharType>::setConsoleColor() const
{
#if defined(_WIN32)
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, static_cast<unsigned short>(getCorrespondingTextColor()));
#elif defined(__unix__)
	// TODO ANSI code insertion
#endif
}

template<typename CharType>
void ze::ZLogger<CharType>::resetConsoleColor() const
{
#if defined(_WIN32)
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, static_cast<unsigned short>(TextColor::White));
#elif defined(__unix__)
	// TODO ANSI code insertion
#endif
}

template<typename CharType>
typename ze::ZLogger<CharType>::TextColor ze::ZLogger<CharType>::getCorrespondingTextColor() const noexcept
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

template<typename CharType>
void ze::ZLogger<CharType>::setLogLevel(Level logLevel) noexcept
{
	m_logLevel = logLevel;
}

template<typename CharType>
ze::ZLogger<CharType>& ze::ZLogger<CharType>::startNewLineAs(Level logLevel)
{
	setLogLevel(logLevel);
	newLine();
	return *this;
}

template<typename CharType>
template<typename Head, typename... Tail>
void ze::ZLogger<CharType>::write(Head const& head, Tail&&... tail)
{
	write(head);
	write(std::forward<Tail>(tail)...);
}

template<typename CharType>
template<typename Message>
void ze::ZLogger<CharType>::write(Message const& message)
{
	if (canLog())
	{
		if (isConsole())
			setConsoleColor();

		printLineDetails();
		m_output << message ;

		if (isConsole())
			resetConsoleColor();
	}
}

template<>
constexpr char const* ze::StringLiteral(char const* str, wchar_t const* wstr, char16_t const* ustr, char32_t const* Ustr)
{
	return str;
}

template<>
constexpr wchar_t const* ze::StringLiteral(char const* str, wchar_t const* wstr, char16_t const* ustr, char32_t const* Ustr)
{
	return wstr;
}

template<>
constexpr char16_t const* ze::StringLiteral(char const* str, wchar_t const* wstr, char16_t const* ustr, char32_t const* Ustr)
{
	return ustr;
}

template<>
constexpr char32_t const* ze::StringLiteral(char const* str, wchar_t const* wstr, char16_t const* ustr, char32_t const* Ustr)
{
	return Ustr;
}

template<typename CharType>
std::basic_string<CharType> ze::ZLogger<CharType>::levelToString(Level logLevel) noexcept
{
	switch (logLevel)
	{
	case Level::Info:
		return STRING_LITERAL(CharType, "Info");
	case Level::Debug:
		return STRING_LITERAL(CharType, "Debug");
	case Level::Warn:
		return STRING_LITERAL(CharType, "Warn");
	case Level::Error:
		return STRING_LITERAL(CharType, "Error");
	case Level::Critical:
		return STRING_LITERAL(CharType, "Critical");
	default:
		return STRING_LITERAL(CharType, "None");
	}
}
