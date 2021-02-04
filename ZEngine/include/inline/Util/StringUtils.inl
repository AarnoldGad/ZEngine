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
