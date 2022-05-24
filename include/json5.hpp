#pragma once

#include <cctype>
#include <clocale>
#include <cmath>
#include <iomanip>
#include <regex>
#include <sstream>
#include <stack>

#include "json.hpp"

namespace json
{

    //declare

    class parser5
    {
    private:
        using u8char = uint64_t;

    //exceptions

    public:
        class exception : public json::exception
        {
        public:
            exception() = default;
            exception(const std::string& type, const std::string& msg,
                const std::string& detail)
            {
                std::stringstream ss;
                ss << "JSON5: [" << type << "] " << msg << '\n';
                ss << detail << std::endl;
                _what = ss.str();
            }
            exception(const exception&) = default;
            exception& operator=(const exception&) = default;
            exception(exception&&) = default;
            exception& operator=(exception&&) = default;

            virtual ~exception() noexcept = default;
        };

        class InvalidChar : public exception
        {
        public:
            InvalidChar(u8char ch = 0, const std::string& detail = "")
                : exception("Invalid Char",
                    "Unexpected token \'" + StringFromCharCode(ch) + "\'",
                    detail)
            {}
        };

        class InvalidIdentifier : public exception
        {
        public:
            InvalidIdentifier(const std::string& msg = "",
                const std::string& detail = "")
                : exception("Invalid Identifier", msg, detail)
            {}
        };

        class InvalidEOF : public exception
        {
        public:
            InvalidEOF(const std::string& msg = "", const std::string& detail = "")
                : exception("Invalid EOF", msg, detail)
            {}
        };

    public:
        std::string exceptionDetailInfo()
        {
            size_t start_point = _col;
            auto len = _print_len;
            auto current_line = _line_begin_cur;
            std::stringstream ss;
            ss << "at line " << _line << ", column " << _col + 1 << '\n';

            while (read() != '\n' && _cur != _end && (_col - start_point) < 5)
                ;
            ss << std::string(current_line, _cur) << '\n';
            ss << std::setw(len) << '^' << '\n';
            return ss.str();
        }

        //helper class and type
    private:
        class unicode
        {
        public:
            static const std::wregex space_separator;
            static const std::wregex id_start;
            static const std::wregex id_continue;

            static bool isSpaceSeparator(u8char ch);
            static bool isIdStartChar(u8char ch);
            static bool isIdContinueChar(u8char ch);
            static bool isDigit(u8char ch);
            static bool isHexDigit(u8char ch);
        };

