#ifndef TEEDEBUG_HPP
#define TEEDEBUG_HPP

#include <iostream>
#include <fstream>
#include <functional>
#include <filesystem>
#include <type_traits>

/*
 * tee.hpp
 * 31 Aug 2020
 * Gaétan "The Aarnold" Jalin
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

//
// Templated Functors Specialisation
//

// Primary specialisable template
template<typename T, typename Enable = void>
class Tee {};

// Generic Customisable tee
template<typename PrintFunc>
class Tee<PrintFunc, std::enable_if_t<std::is_invocable_v<PrintFunc> > >
{
public:

   explicit Tee(PrintFunc func)
   : print(func) {}

   template<typename T>
   decltype(auto) operator()(T&& value)
   {
      print(value);
      return std::forward<T>(value);
   }

private:

   PrintFunc print;
};

// File output specialisation
// TODO Open a file at each call is performance heavy
template<>
class Tee<std::filesystem::path>
{
public:

   explicit Tee(std::filesystem::path const& filePath, std::ios_base::openmode mode = std::ios_base::out | std::ios_base::app)
   : m_file(filePath), m_mode(mode) {}

   template<typename T>
   decltype(auto) operator()(T&& value)
   {
      std::ofstream file(m_file, m_mode);

      if (file)
         file << value << std::endl;
      else
         std::cerr << "unable to open file " << m_file << std::endl;

      return std::forward<T>(value);
   }

private:

   std::filesystem::path m_file;
   std::ios_base::openmode m_mode;
};

// Stream output specialisation
template<typename Stream>
class Tee<Stream, std::enable_if_t<std::is_base_of_v<std::ios_base, Stream> > >
{
public:

   explicit Tee(Stream& output)
   : m_output(output) {}

   template<typename T>
   decltype(auto) operator()(T&& value)
   {
      m_output << value << std::endl;
      return std::forward<T>(value);
   }

private:

   std::ostream& m_output;
};

// Deductions guides
Tee(char const*) -> Tee<std::filesystem::path>;
Tee(std::string const&) -> Tee<std::filesystem::path>;

template<typename PrintFunc, std::enable_if_t<std::is_invocable_v<PrintFunc>, int> = 0>
Tee<PrintFunc> make_tee(PrintFunc func)
{
   return Tee<PrintFunc>(func);
}

template<typename Stream, std::enable_if_t<std::is_base_of_v<std::ios_base, Stream>, int> = 0>
Tee<Stream> make_tee(Stream& stream)
{
   return Tee<Stream>(stream);
}

template<typename Value, typename TeeType>
decltype(auto) operator|(Value&& value, Tee<TeeType> tee)
{
   tee(value);
   return std::forward<Value>(value);
}

// Default tee
Tee<std::ostream> tee = make_tee(std::cout);

//
// Low Level Functions
//

// Simplest form
template<typename Value>
decltype(auto) stee(Value&& value, std::ostream& output)
{
   output << value << std::endl;
   return std::forward<Value>(value);
}

// TODO Open a file at each call is performance heavy
template<typename Value>
decltype(auto) ftee(Value&& value, std::filesystem::path const& outputFile, std::ios_base::openmode mode = std::ios_base::out)
{
   std::ofstream file(outputFile, mode);

   if (file)
      file << value << std::endl;
   else
      std::cerr << "unable to open file " << outputFile << std::endl;

   return std::forward<Value>(value);
}

#endif // TEEDEBUG_HPP
