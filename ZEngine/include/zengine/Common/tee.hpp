/*
 * tee.hpp
 * 31 Aug 2020
 * Gaétan "The Aarnold" Jalin
 *
 * Copyright (C) 2020 Gaétan Jalin
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * C++ 17
 * Experimental (i.e unfinished and unoptimised) header-only tee debugging tool.
 *
 * Based on the "tee" unix command, this debugging tool is used
 * to display object values at run-time in a simple and readable way, based on expressiveness.
 *
 *           []================[]
 * Value In -->    ------>    ---> Value Out
 *           []=====| | |======[]
 *                  | v |
 *                  |   |   ___   ___
 *                  |   |  |     |
 *                  |   |  |==   |==
 *                  |   |  |___  |___
 *                 || | ||
 *                    |
 *                    v
 *                Debugging
 *
 * TODO Improve template deduction
 * TODO Improve template deduction
 */
#ifndef ZE_TEEDEBUG
#define ZE_TEEDEBUG

template<typename Fn, typename Type = void>
using if_is_invocable = std::enable_if_t<std::is_invocable_v<Fn>, Type>;

template<typename Stream, typename Type = void>
using if_is_stream = std::enable_if_t<std::is_base_of_v<std::ios_base, Stream>, Type>;

// Primary specialisable template
template<typename T, typename Enable = void>
class Tee {};

// Generic Customisable tee
template<typename PrintFn>
class Tee<PrintFn, if_is_invocable<PrintFn> >
{
public:
	template<typename Value>
	decltype(auto) operator()(Value&& value);

	explicit Tee(PrintFn func);

private:
	PrintFn m_print;
};

// File output specialisation
// TODO Open a file at each call is performance heavy
template<>
class Tee<std::filesystem::path>
{
public:
	template<typename Value>
	decltype(auto) operator()(Value&& value);

	explicit Tee(std::filesystem::path const& filePath, std::ios_base::openmode mode = std::ios_base::out | std::ios_base::app);

private:
	std::filesystem::path m_file;
	std::ios_base::openmode m_mode;
};

// Stream output specialisation
template<typename Stream>
class Tee<Stream, if_is_stream<Stream> >
{
public:
	template<typename Value>
	decltype(auto) operator()(Value&& value);

	explicit Tee(Stream& output);

private:
	std::ostream& m_output;
};

// Deductions guides
Tee(char const*) -> Tee<std::filesystem::path>;
Tee(std::string const&) -> Tee<std::filesystem::path>;

template<typename PrintFunc, if_is_invocable<PrintFunc, int> = 0>
Tee<PrintFunc> make_tee(PrintFunc func);

template<typename Stream, if_is_stream<Stream, int> = 0>
Tee<Stream> make_tee(Stream& stream);

template<typename Value, typename TeeType>
decltype(auto) operator|(Value&& value, Tee<TeeType> tee);

// Default tee
Tee<std::ostream> tee = make_tee(std::cout);

//
// Low Level Functions
//

// Simplest form
template<typename Value, typename CharType>
decltype(auto) stee(Value&& value, std::basic_ostream<CharType>& output);

// TODO Open a file at each call is performance heavy
template<typename Value>
decltype(auto) ftee(Value&& value, std::filesystem::path const& outputFile, std::ios_base::openmode mode = std::ios_base::out);

#include <inline/Common/tee.inl>

#endif // ZE_TEEDEBUG
