/**
 * Logger.hpp
 * 1 Dec 2020
 * Gaétan "The Aarnold" Jalin
 *
 * Copyright (C) 2020 Gaétan Jalin
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *    1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 *    2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 *    3. This notice may not be removed or altered from any source distribution.
 **/
#ifndef ZE_LOGGER
#define ZE_LOGGER

#include <zebuild.hpp>

namespace ze
{
	template<typename CharType>
	class ZLogger
	{
	public:
		using LoggerType = typename ze::ZLogger<CharType>;
		using StreamType = typename std::basic_ostream<CharType>;
		using BufType = typename std::basic_streambuf<CharType>;
		using StringType = typename std::basic_string<CharType>;

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

	// Member functions
		template<typename Message>
		void log(Level logLevel, Message const& message);

		template<typename... Messages>
		void logLine(Level logLevel, Messages&&... messages);

		template<typename... Args>
		void logFormatedLine(Level logLevel, StringType const& unformattedLine, Args&&... args);

		void setOutput(StreamType& output);
		void setOutput(BufType* output);
		StreamType& getOutput() const noexcept;

		void setLogMask(unsigned int mask) noexcept;
		unsigned int getLogMask() const noexcept;

		bool canLog() const;
		bool isConsole() const;

	// Operators
		template<typename Message>
		LoggerType& operator<<(Message const& message);
		LoggerType& operator<<(StreamType& (*manip)(StreamType&));
		LoggerType& operator<<(LoggerType& (*manip)(LoggerType&));

	// Manipulators
		LoggerType& info();
		static LoggerType& info(LoggerType& logger);

		LoggerType& debug();
		static LoggerType& debug(LoggerType& logger);

		LoggerType& warn();
		static LoggerType& warn(LoggerType& logger);

		LoggerType& error();
		static LoggerType& error(LoggerType& logger);

		LoggerType& critical();
		static LoggerType& critical(LoggerType& logger);

		LoggerType& newLine();
		static LoggerType& newLine(LoggerType& logger);

		//LoggerType& stacktrace();
		//static LoggerType& stacktrace(LoggerType& logger);

		// Constructors/Destructor
		explicit ZLogger(BufType* = nullptr, unsigned int logMask = 0b11111);
		explicit ZLogger(StreamType& output, unsigned int logMask = 0b11111);

	private:
		void printLineDetails();

		template<unsigned int N = 1, typename Head, typename... Tail>
		StringType formatLine(StringType const& unformattedLine, Head const& head, Tail&&... tail);
		template<unsigned int N = 1, typename Arg>
		StringType formatLine(StringType const& unformattedLine, Arg const& arg);

		void setConsoleColor() const;
		void resetConsoleColor() const;
		TextColor getCorrespondingTextColor() const noexcept;

		void setLogLevel(Level logLevel) noexcept;
		LoggerType& startNewLineAs(Level logLevel);

		template<typename Head, typename... Tail>
		void write(Head const& head, Tail&&... tail);

		template<typename Message>
		void write(Message const& message);

		static StringType levelToString(Level logLevel) noexcept;

		StreamType m_output;
		unsigned int m_logMask;
		bool m_lineStart;
		Level m_logLevel;
	};

	template<typename CharType>
	constexpr CharType const* StringLiteral(char const* str, wchar_t const* wstr, char16_t const* ustr, char32_t const* Ustr);
	#define STRING_LITERAL(type, str) ze::StringLiteral<type>(str, L##str, u##str, U##str)

	using Logger = ZLogger<char>;
	using WLogger = ZLogger<wchar_t>;
	#if defined(_MSC_VER) && __cplusplus > 201704L
		using Logger8 = ZLogger<char8_t>;
	#elif defined(__GCC__) && __cpluspluc > 201709L
		using Logger8 = ZLogger<char8_t>;
	#endif
	using Logger16 = ZLogger<char16_t>;
	using Logger32 = ZLogger<char32_t>;
}

#include <inline/Common/Logger.inl>

#endif // ZE_LOGGER
