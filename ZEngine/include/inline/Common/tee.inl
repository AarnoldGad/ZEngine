template<typename PrintFn>
Tee<PrintFn, if_is_invocable<PrintFn> >::Tee(PrintFn fn)
   : m_print(fn) {}

template<typename PrintFn>
template<typename Value>
decltype(auto) Tee<PrintFn, if_is_invocable<PrintFn> >::operator()(Value&& value)
{
   m_print(value);
   return std::forward<Value>(value);
}

Tee<std::filesystem::path>::Tee(std::filesystem::path const& filePath, std::ios_base::openmode mode)
   : m_file(filePath), m_mode(mode) {}

template<typename Value>
decltype(auto) Tee<std::filesystem::path>::operator()(Value&& value)
{
   std::ofstream file(m_file, m_mode);

   if (file)
      file << value << std::endl;
   else
      std::cerr << "unable to open file " << m_file << std::endl;

   return std::forward<Value>(value);
}

template<typename Stream>
Tee<Stream, if_is_stream<Stream> >::Tee(Stream& output)
   : m_output(output) {}

template<typename Stream>
template<typename Value>
decltype(auto) Tee<Stream, if_is_stream<Stream> >::operator()(Value&& value)
{
   m_output << value << std::endl;
   return std::forward<Value>(value);
}

template<typename PrintFunc, if_is_invocable<PrintFunc, int>>
Tee<PrintFunc> make_tee(PrintFunc func)
{
   return Tee<PrintFunc>(func);
}

template<typename Stream, if_is_stream<Stream, int>>
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

template<typename Value, typename CharType>
decltype(auto) stee(Value&& value, std::basic_ostream<CharType>& output)
{
   output << value << std::endl;
   return std::forward<Value>(value);
}

template<typename Value>
decltype(auto) ftee(Value&& value, std::filesystem::path const& outputFile, std::ios_base::openmode mode)
{
   std::ofstream file(outputFile, mode);

   if (file)
      file << value << std::endl;
   else
      std::cerr << "unable to open file " << outputFile << std::endl;

   return std::forward<Value>(value);
}
