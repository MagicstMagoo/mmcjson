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

        enum class LexState
        {
            default_ = 0,
            comment,
            multiLineComment,
            multiLineCommentAsterisk,
            singleLineComment,
            value,
            identifierNameStartEscape,
            identifierName,
            identifierNameEscape,
            sign,
            zero,
            decimalInteger,
            decimalPointLeading,
            decimalPoint,
            decimalFraction,
            decimalExponent,
            decimalExponentSign,
            decimalExponentInteger,
            hexadecimal,
            hexadecimalInteger,
            string,
            start,
            beforePropertyName,
            afterPropertyName,
            beforePropertyValue,
            afterPropertyValue,
            beforeArrayValue,
            afterArrayValue,
            end
        };

        enum class ParseState
        {
            start = 21,
            beforePropertyName,
            afterPropertyName,
            beforePropertyValue,
            afterPropertyValue,
            beforeArrayValue,
            afterArrayValue,
            end
        };

        enum class TokenType
        {
            punctuator = 0,
            identifier,
            null,
            boolean,
            numeric,
            string,
            eof,
        };

        struct Token
        {
            TokenType type;
            value _value;
            size_t col = 0;
            size_t line = 0;
        }:



    //constrators and callers

    public:
        ~parser5() noexcept = default;
        static std::optional<value> parse(const std::string& content, std::string* error = nullptr);

    private:
        parser5(const std::string::const_iterator& cbegin,
            const std::string::const_iterator& cend) noexcept
            : _cur(cbegin), _end(cend), _line_begin_cur(cbegin)
        {}
        std::optional<value> parse();

    private:

        //utf-8 reader

        static u8char peek(std::string::const_iterator& begin,
            const std::string::const_iterator& end,
            size_t* len = nullptr);
        static u8char peek(const std::string& str);
        parser5::u8char read();
        static std::string StringFromCharCode(u8char code);
        // escape and format
        void literal(const std::string& s);
        std::optional<u8char> escape();
        u8char hexEscape();
        u8char unicodeEscape();
        // lex, parse, token
        Token lex();
        Token newToken(TokenType type, value value);


        // opional token
        std::optional<Token> lex_default();
        std::optional<Token> lex_comment();
        std::optional<Token> lex_multiLineComment();
        std::optional<Token> lex_multiLineCommentAsterisk();
        std::optional<Token> lex_singleLineComment();
        std::optional<Token> lex_value();
        std::optional<Token> lex_identifierNameStartEscape();
        std::optional<Token> lex_identifierName();
        std::optional<Token> lex_identifierNameEscape();
        std::optional<Token> lex_sign();
        std::optional<Token> lex_zero();
        std::optional<Token> lex_decimalInteger();
        std::optional<Token> lex_decimalPointLeading();
        std::optional<Token> lex_decimalPoint();
        std::optional<Token> lex_decimalFraction();
        std::optional<Token> lex_decimalExponent();
        std::optional<Token> lex_decimalExponentSign();
        std::optional<Token> lex_decimalExponentInteger();
        std::optional<Token> lex_hexadecimal();
        std::optional<Token> lex_hexdecimalInteger();
        std::optional<Token> lex_string();
        std::optional<Token> lex_start();
        std::optional<Token> lex_beforePropertyName();
        std::optional<Token> lex_afterPropertyName();
        std::optional<Token> lex_beforePropertyValue();
        std::optional<Token> lex_afterPropertyValue();
        std::optional<Token> lex_beforeArrayValue();
        std::optional<Token> lex_afterArrayValue();
        std::optional<Token> lex_end();

        std::optional<Token> lexStates(LexState state);

        // void
        void parse_start();
        void parse_beforePropertyName();
        void parse_afterPropertyName();
        void parse_beforePropertyValue();
        void parse_beforeArrayValue();
        void parse_afterPropertyValue();
        void parse_afterArrayValue();
        void parse_end();

        void parseStates(ParseState state);

        // stack operation
        void push();
        void pop();

    private:
        std::string::const_iterator _cur, _end;
        std::string::const_iterator _line_begin_cur;
        size_t _line = 1, _col = 0, _print_len = 0;
        ParseState _parse_state = ParseState::start;
        std::stack<value*> _stack;
        std::optional<Token> _token;
        std::string _key;
        std::optional<value> _root;

        LexState _lex_state = LexState::default_;
        std::string _buffer;
        bool _double_quote = false;
        size_t _sign = 1;
        u8char _current_char = 0;
    };

