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

