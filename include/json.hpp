#​pragma​ once 

//所引用的hpp头文件
​#​include​ ​<​initializer_list​> 
​#​include​ ​<​memory​ream​> 
#include​ ​<​optional​> 
#​include​ ​<​ostream​> 
#​include​ ​<​string​>
//还可以用<QString>读取Minecraft的json文件
​#​include​ ​<​unordered_map​> 
​#​include​ ​<​vector​> 
​#​include​ ​<​tuple​> 
​#​include​ ​<​variant​> 
#​include​ ​<​string_view​> 

//inline常量设置
#define MMCJSON_INLINE inline

namespace json 
{
	class array;
	class object;

	//value declare
	class value;
	{
		using array_ptr = std::unique_ptr<array>;
		using onject_ptr = std::unique_ptr<object>;

	public:
		enum class value_type : char
		{
			Invalid,
			Null,
			Boolean,
			String,
			Number,
			Array,
			Object,
		};

		using var_t = std::variant<std::string, array_ptr, object_ptr>;

	public:
		//value declare
		value();
		value(const value& rhs);
		value(value&& rhs) noexcept;
		value(bool b);
		
		//C.h变量
		value(int num);
		value(unsigned num);
		value(long num);
		value(unsigned long num);
		value(long long num);
		value(unsigned long long num);
		
		value(float num);
		value(double num);
		value(long double num);

		value(const char* str);
		value(std::string str);


		value(array arr);
		//for array
		value(std::initializer_list<value> init_list);


		value(object obj);


		//从原始数据构建~
		template<typename... Args> value(value_type type, Args &&...args);
		
		//禁止将其他类型转换为值
		template <typename T>value(T) = delete;

		~value();

	
		//bool
		bool valid() const noexcept { return _type != value_type::Invalid; }
		bool empty() const noexcept { return is_null(); }
		bool is_null() const noexcept { return _type == value_type::Null; }
		bool is_number() const noexcept { return _type == value_type::Number; }
		bool is_boolean() const noexcept { return _type == value_type::Boolean; }
		bool is_string() const noexcept { return _type == value_type::String; }
		bool is_array() const noexcept { return _type == value_type::Array; }
		bool is_object() const noexcept { return _type == value_type::Object; }
		bool contains(const std::string& key) const;
		bool contains(size_t pos) const;

		value_type type() const noexcept { return _type; }

		const value& t(size_t pos) const;
		const value& at(const std : string & key) const;


	//usage:get(key, key_child, ..., default_value);
		template<typename... KeysThenDefaultValue>
		decltype(auto) get(KeyThenDefaultValue &&... Keys_then_default_value) const;

		bool as_boolean() const;
		int as_integer() const;
		//unsigned as_unsigned() const;
		long as_long() const;
		unsigned long as_unsigned_long() const;
		long long as_long_long() const;
		unsigned long long as_unsigned_long_long() const;
		float as_float() const;
		double as_double() const;
		long double as_long_double() const;
		const std::string as_string() const;
		const array& as_array() const;
		const object& as_object() const;


		array& as_array();
		object& as_object();


		template<typename... Args> decltype(auto) array_emplace(Args &&...args);
		template<typename... Args> decltype(auto) object_emplace(Args &&...args);
		void clear() noexcept;

		// return raw string
		const std::string to_string() const;
		const std::string format(std::string shift_str = "    ",
		size_t basic_shift_count = 0) const;

		value& operator=(const value& rhs);
		value& operator=(value&&) noexcept;

		const value& operator[](size_t pos) const;
		value& operator[](size_t pos);
		value& operator[](const std::string& key);
		value& operator[](std::string&& key);

		value operator|(const object& rhs)&;
		value operator|(object&& rhs)&;
		value operator|(const object& rhs)&&;
		value operator|(object&& rhs)&&;

		value& operator|=(const object& rhs);
		value& operator|=(object&& rhs);

		//value operator&(const object& rhs)&;
		//value operator&(object&& rhs)&;
		//value operator&(const object& rhs)&&;
		//value operator&(object&& rhs)&&;

		//value& operator&=(const object& rhs);
		//value& operator&=(object&& rhs);

		value operator+(const array& rhs)&;
		value operator+(array&& rhs)&;
		value operator+(const array& rhs)&&;
		value operator+(array&& rhs)&&;

		value& operator+=(const array& rhs);
		value& operator+=(array&& rhs);

		explicit operator bool() const { return as_boolean(); }
		explicit operator int() const { return as_integer(); }
		explicit operator long() const { return as_long(); }
		explicit operator unsigned long() const { return as_unsigned_long(); }
		explicit operator long long() const { return as_long_long(); }
		explicit operator unsigned long long() const { return as_unsigned_long_long(); }
		explicit operator float() const { return as_float(); }
		explicit operator double() const { return as_double(); }
		explicit operator long double() const { return as_long_double(); }
		explicit operator std::string() const { return as_string(); }

		private:
			static var_t deep_copy(const var_t& src);

			template <typename... KeysThenDefaultValue, size_t... KeysIndexes>
			decltype(auto) get(
				std::tuple<KeysThenDefaultValue...> keys_then_default_value,
				std::index_sequence<KeysIndexes...>) const;

			template <typename T, typename FirstKey, typename... RestKeys>
			decltype(auto) get_aux(T&& default_value, FirstKey&& first, RestKeys &&... rest) const;
			template <typename T, typename UniqueKey>
			decltype(auto) get_aux(T&& default_value, UniqueKey&& first) const;

			const std::string& as_basic_type_str() const;
			std::string& as_basic_type_str();

			value_type _type = value_type::Null;
			var_t _raw_data;
	};


	const value json::invalid_value()
	{
		return value();
		const value invalid_value();
		std::ostream& operator<<(std::ostream & out, const value & val);
	}



    class array
    {
    public:
        using raw_array = std::vector<value>;
        using value_type = raw_array::value_type;
        using iterator = raw_array::iterator;
        using const_iterator = raw_array::const_iterator;
        using reverse_iterator = raw_array::reverse_iterator;
        using const_reverse_iterator = raw_array::const_reverse_iterator;

    public:
        array() = default;
        array(const array& rhs) = default;
        array(array&& rhs) noexcept = default;
        array(const raw_array& arr);
        array(raw_array&& arr) noexcept;
        array(std::initializer_list<raw_array::value_type> init_list);

        template<typename ArrayType> array(ArrayType arr);

        ~array() noexcept = default;

        bool empty() const noexcept { return _array_data.empty(); }
        size_t size() const noexcept { return _array_data.size(); }
        bool contains(size_t pos) const { return pos < _array_data.size(); }
        const value& at(size_t pos) const;
        const std::string to_string() const;
        const std::string format(std::string shift_str = "    ",
            size_t basic_shift_count = 0) const;

        bool get(size_t pos, bool default_value) const;
        int get(size_t pos, int default_value) const;
        long get(size_t pos, long default_value) const;
        unsigned long get(size_t pos, unsigned default_value) const;
        long long get(size_t pos, long long default_value) const;
        unsigned long long get(size_t pos,
            unsigned long long default_value) const;
        float get(size_t pos, float default_value) const;
        double get(size_t pos, double default_value) const;
        long double get(size_t pos, long double default_value) const;
        const std::string get(size_t pos, std::string default_value) const;
        const std::string get(size_t pos, const char* default_value) const;
        const value& get(size_t pos) const;

        template <typename... Args> decltype(auto) emplace_back(Args &&...args);

        void clear() noexcept;
        // void erase(size_t pos);

        iterator begin() noexcept;
        iterator end() noexcept;
        const_iterator begin() const noexcept;
        const_iterator end() const noexcept;
        const_iterator cbegin() const noexcept;
        const_iterator cend() const noexcept;

        reverse_iterator rbegin() noexcept;
        reverse_iterator rend() noexcept;
        const_reverse_iterator rbegin() const noexcept;
        const_reverse_iterator rend() const noexcept;
        const_reverse_iterator crbegin() const noexcept;
        const_reverse_iterator crend() const noexcept;

        const value& operator[](size_t pos) const;
        value& operator[](size_t pos);

        array operator+(const array& rhs)&;
        array operator+(array&& rhs)&;
        array operator+(const array& rhs)&&;
        array operator+(array&& rhs)&&;

        array& operator+=(const array& rhs);
        array& operator+=(array&& rhs);

        array& operator=(const array&) = default;
        array& operator=(array&&) noexcept = default;

        // const raw_array &raw_data() const;

    private:
        raw_array _array_data;
    };

    std::ostream& operator<<(std::ostream& out, const array& arr);

    // *************************
    // *     object declare    *
    // *************************
    class object
    {
    public:
        using raw_object = std::unordered_map<std::string, value>;
        using value_type = raw_object::value_type;
        using iterator = raw_object::iterator;
        using const_iterator = raw_object::const_iterator;

    public:
        object() = default;
        object(const object& rhs) = default;
        object(object&& rhs) noexcept = default;
        object(const raw_object& raw_obj);
        object(raw_object&& raw_obj);
        object(std::initializer_list<raw_object::value_type> init_list);
        template <typename MapType> object(MapType map);

        ~object() = default;

        bool empty() const noexcept { return _object_data.empty(); }
        size_t size() const noexcept { return _object_data.size(); }
        bool contains(const std::string& key) const { return _object_data.find(key) != _object_data.cend(); }
        const value& at(const std::string& key) const;
        const std::string to_string() const;
        const std::string format(std::string shift_str = "    ",
            size_t basic_shift_count = 0) const;

        bool get(const std::string& key, bool default_value) const;
        int get(const std::string& key, int default_value) const;
        long get(const std::string& key, long default_value) const;
        unsigned long get(const std::string& key, unsigned default_value) const;
        long long get(const std::string& key, long long default_value) const;
        unsigned long long get(const std::string& key,
            unsigned long long default_value) const;
        float get(const std::string& key, float default_value) const;
        double get(const std::string& key, double default_value) const;
        long double get(const std::string& key,
            long double default_value) const;
        const std::string get(const std::string& key,
            std::string default_value) const;
        const std::string get(const std::string& key,
            const char* default_value) const;
        const value& get(const std::string& key) const;

        template <typename... Args> decltype(auto) emplace(Args &&...args);
        template <typename... Args> decltype(auto) insert(Args &&...args);

        void clear() noexcept;
        bool erase(const std::string& key);

        iterator begin() noexcept;
        iterator end() noexcept;
        const_iterator begin() const noexcept;
        const_iterator end() const noexcept;
        const_iterator cbegin() const noexcept;
        const_iterator cend() const noexcept;

        value& operator[](const std::string& key);
        value& operator[](std::string&& key);

        object operator|(const object& rhs)&;
        object operator|(object&& rhs)&;
        object operator|(const object& rhs)&&;
        object operator|(object&& rhs)&&;

        object& operator|=(const object& rhs);
        object& operator|=(object&& rhs);

        //object operator&(const object& rhs)&;
        //object operator&(object&& rhs)&;
        //object operator&(const object& rhs)&&;
        //object operator&(object&& rhs)&&;

        //object& operator&=(const object& rhs);
        //object& operator&=(object&& rhs);

        object& operator=(const object&) = default;
        object& operator=(object&&) = default;

        // const raw_object &raw_data() const;

    private:
        raw_object _object_data;
    };

    std::ostream& operator<<(std::ostream& out, const object& obj);




    //exception declare

    class exception : public std::exception
    {
    public:
        exception() = default;
        exception(const std::string& msg) : _what(msg) {}

        exception(const exception&) = default;
        exception& operator=(const exception&) = default;
        exception(exception&&) = default;
        exception& operator=(exception&&) = default;

        virtual ~exception() noexcept override = default;

        virtual const char* what() const noexcept override
        {
            return _what.empty() ? "Unknown exception" : _what.c_str();
        }

    protected:
        std::string _what;
    };





    //aux declare

    std::string unescape_string(std::string str);
    std::string escape_string(std::string str);






    //value impl

    MMCJSON_INLINE value::value() = default;

    MMCJSON_INLINE value::value(const value & rhs)
        : _type(rhs._type), _raw_data(deep_copy(rhs._raw_data))
    {
        ;
    }

    MMCJSON_INLINE value::value(value && rhs) noexcept = default;

    MMCJSON_INLINE value::value(bool b)
        : _type(value_type::Boolean), _raw_data(std::string(b ? "true" : "false"))
    {
        ;
    }

    MMCJSON_INLINE value::value(int num)
        : _type(value_type::Number), _raw_data(std::to_string(num))
    {
        ;
    }

    MMCJSON_INLINE value::value(unsigned num)
        : _type(value_type::Number), _raw_data(std::to_string(num))
    {
        ;
    }

    MMCJSON_INLINE value::value(long num)
        : _type(value_type::Number), _raw_data(std::to_string(num))
    {
        ;
    }

    MMCJSON_INLINE value::value(unsigned long num)
        : _type(value_type::Number), _raw_data(std::to_string(num))
    {
        ;
    }

    MMCJSON_INLINE value::value(long long num)
        : _type(value_type::Number), _raw_data(std::to_string(num))
    {
        ;
    }

    MMCJSON_INLINE value::value(unsigned long long num)
        : _type(value_type::Number), _raw_data(std::to_string(num))
    {
        ;
    }

    MMCJSON_INLINE value::value(float num)
        : _type(value_type::Number), _raw_data(std::to_string(num))
    {
        ;
    }

    MMCJSON_INLINE value::value(double num)
        : _type(value_type::Number), _raw_data(std::to_string(num))
    {
        ;
    }

    MMCJSON_INLINE value::value(long double num)
        : _type(value_type::Number), _raw_data(std::to_string(num))
    {
        ;
    }

    MMCJSON_INLINE value::value(const char* str)
        : _type(value_type::String), _raw_data(unescape_string(str))
    {
        ;
    }

    MMCJSON_INLINE value::value(std::string str)
        : _type(value_type::String),
        _raw_data(unescape_string(std::move(str)))
    {
        ;
    }

    MMCJSON_INLINE value::value(array arr)
        : _type(value_type::Array),
        _raw_data(std::make_unique<array>(std::move(arr)))
    {
        ;
    }

    MMCJSON_INLINE value::value(object obj)
        : _type(value_type::Object),
        _raw_data(std::make_unique<object>(std::move(obj)))
    {
        ;
    }



    // for Pimpl
    MMCJSON_INLINE value::~value() = default;

    MMCJSON_INLINE bool value::contains(const std::string & key) const
    {
        return is_object() && as_object().contains(key);
    }

    MMCJSON_INLINE bool value::contains(size_t pos) const
    {
        return is_array() && as_array().contains(pos);
    }

    MMCJSON_INLINE const value& value::at(size_t pos) const
    {
        return as_array().at(pos);
    }

    MMCJSON_INLINE const value& value::at(const std::string & key) const
    {
        return as_object().at(key);
    }

    template <typename... KeysThenDefaultValue>
    MMCJSON_INLINE decltype(auto) value::get(
        KeysThenDefaultValue &&... keys_then_default_value) const
    {
        return get(
            std::forward_as_tuple(keys_then_default_value...),
            std::make_index_sequence<sizeof...(keys_then_default_value) - 1>{});
    }

    template <typename... KeysThenDefaultValue, size_t... KeysIndexes>
    MMCJSON_INLINE decltype(auto) value::get(
        std::tuple<KeysThenDefaultValue...> keys_then_default_value,
        std::index_sequence<KeysIndexes...>) const
    {
        constexpr unsigned long DefaultValueIndex = sizeof...(KeysThenDefaultValue) - 1;
        return get_aux(
            std::get<DefaultValueIndex>(keys_then_default_value),
            std::get<KeysIndexes>(keys_then_default_value)...);
    }

    template <typename T, typename FirstKey, typename... RestKeys>
    MMCJSON_INLINE decltype(auto) value::get_aux(T && default_value, FirstKey && first, RestKeys &&... rest) const
    {
        if constexpr (std::is_constructible<std::string, FirstKey>::value) {
            return is_object() ?
                as_object().get(
                    std::forward<FirstKey>(first)).get_aux(
                        std::forward<T>(default_value), std::forward<RestKeys>(rest)...)
                : default_value;
        }
        else if constexpr (std::is_integral<typename std::remove_reference<FirstKey>::type>::value) {
            return is_array()
                ? as_array().get(
                    std::forward<FirstKey>(first)).get_aux(
                        std::forward<T>(default_value), std::forward<RestKeys>(rest)...)
                : default_value;
        }
        else {
            static_assert(!sizeof(FirstKey), "Parameter must be integral or std::string constructible");
        }
    }

    template <typename T, typename UniqueKey>
    MMCJSON_INLINE decltype(auto) value::get_aux(T && default_value, UniqueKey && first) const
    {
        if constexpr (std::is_constructible<std::string, UniqueKey>::value) {
            return is_object() ?
                as_object().get(std::forward<UniqueKey>(first), std::forward<T>(default_value))
                : default_value;
        }
        else if constexpr (std::is_integral<typename std::remove_reference<UniqueKey>::type>::value) {
            return is_array() ?
                as_array().get(std::forward<UniqueKey>(first), std::forward<T>(default_value))
                : default_value;
        }
        else {
            static_assert(!sizeof(UniqueKey), "Parameter must be integral or std::string constructible");
        }
    }

    MMCJSON_INLINE bool value::as_boolean() const
    {
        if (is_boolean()) {
            if (const std::string& b_str = as_basic_type_str();
                b_str == "true") {
                return true;
            }
            else if (b_str == "false") {
                return false;
            }
            else {
                throw exception("Unknown Parse Error");
            }
        }
        else {
            throw exception("Wrong Type");
        }
    }

    MMCJSON_INLINE int value::as_integer() const
    {
        if (is_number()) {
            return std::stoi(as_basic_type_str());
        }
        else {
            throw exception("Wrong Type");
        }
    }

    // const unsigned value::as_unsigned() const
    // {
    //     if (is_number())
    //     {
    //         return std::stou(_raw_data); // not contains
    //     }
    //     else
    //     {
    //         throw exception("Wrong Type");
    //     }
    // }

    MMCJSON_INLINE long value::as_long() const
    {
        if (is_number()) {
            return std::stol(as_basic_type_str());
        }
        else {
            throw exception("Wrong Type");
        }
    }

    MMCJSON_INLINE unsigned long value::as_unsigned_long() const
    {
        if (is_number()) {
            return std::stoul(as_basic_type_str());
        }
        else {
            throw exception("Wrong Type");
        }
    }

    MMCJSON_INLINE long long value::as_long_long() const
    {
        if (is_number()) {
            return std::stoll(as_basic_type_str());
        }
        else {
            throw exception("Wrong Type");
        }
    }

    MMCJSON_INLINE unsigned long long value::as_unsigned_long_long() const
    {
        if (is_number()) {
            return std::stoull(as_basic_type_str());
        }
        else {
            throw exception("Wrong Type");
        }
    }

    MMCJSON_INLINE float value::as_float() const
    {
        if (is_number()) {
            return std::stof(as_basic_type_str());
        }
        else {
            throw exception("Wrong Type");
        }
    }

    MMCJSON_INLINE double value::as_double() const
    {
        if (is_number()) {
            return std::stod(as_basic_type_str());
        }
        else {
            throw exception("Wrong Type");
        }
    }

    MMCJSON_INLINE long double value::as_long_double() const
    {
        if (is_number()) {
            return std::stold(as_basic_type_str());
        }
        else {
            throw exception("Wrong Type");
        }
    }

    MMCJSON_INLINE const std::string value::as_string() const
    {
        if (is_string()) {
            return escape_string(as_basic_type_str());
        }
        else {
            throw exception("Wrong Type");
        }
    }

    MMCJSON_INLINE const array& value::as_array() const
    {
        if (is_array()) {
            return *std::get<array_ptr>(_raw_data);
        }

        throw exception("Wrong Type");
    }

    MMCJSON_INLINE const object& value::as_object() const
    {
        if (is_object()) {
            return *std::get<object_ptr>(_raw_data);
        }

        throw exception("Wrong Type or data empty");
    }

    MMCJSON_INLINE array& value::as_array()
    {
        if (empty()) {
            *this = array();
        }

        if (is_array()) {
            return *std::get<array_ptr>(_raw_data);
        }

        throw exception("Wrong Type");
    }

    MMCJSON_INLINE object& value::as_object()
    {
        if (empty()) {
            *this = object();
        }

        if (is_object()) {
            return *std::get<object_ptr>(_raw_data);
        }

        throw exception("Wrong Type or data empty");
    }

    MMCJSON_INLINE const std::string& value::as_basic_type_str() const
    {
        return std::get<std::string>(_raw_data);
    }
    MMCJSON_INLINE std::string& value::as_basic_type_str()
    {
        return std::get<std::string>(_raw_data);
    }

    template<typename... Args>
    MMCJSON_INLINE decltype(auto) value::array_emplace(Args &&...args)
    {
        return as_array().emplace_back(std::forward<Args>(args)...);
    }

    template<typename... Args>
    MMCJSON_INLINE decltype(auto) value::object_emplace(Args &&...args)
    {
        return as_object().emplace(std::forward<Args>(args)...);
    }

    MMCJSON_INLINE void value::clear() noexcept
    {
        *this = json::value();
    }

    MMCJSON_INLINE const std::string value::to_string() const
    {
        switch (_type) {
        case value_type::Null:
            return "null";
        case value_type::Boolean:
        case value_type::Number:
            return as_basic_type_str();
        case value_type::String:
            return '"' + as_basic_type_str() + '"';
        case value_type::Array:
            return as_array().to_string();
        case value_type::Object:
            return as_object().to_string();
        default:
            throw exception("Unknown Value Type");
        }
    }

    MMCJSON_INLINE const std::string value::format(std::string shift_str,
        size_t basic_shift_count) const
    {
        switch (_type) {
        case value_type::Null:
            return "null";
        case value_type::Boolean:
        case value_type::Number:
            return as_basic_type_str();
        case value_type::String:
            return '"' + as_basic_type_str() + '"';
        case value_type::Array:
            return as_array().format(shift_str, basic_shift_count);
        case value_type::Object:
            return as_object().format(shift_str, basic_shift_count);
        default:
            throw exception("Unknown Value Type");
        }
    }

    MMCJSON_INLINE value& value::operator=(const value & rhs)
    {
        _type = rhs._type;
        _raw_data = deep_copy(rhs._raw_data);

        return *this;
    }

    MMCJSON_INLINE value& value::operator=(value && rhs) noexcept = default;

    MMCJSON_INLINE const value& value::operator[](size_t pos) const
    {
        // Array not support to create by operator[]

        return as_array()[pos];
    }

    MMCJSON_INLINE value& value::operator[](size_t pos)
    {
        // Array not support to create by operator[]

        return as_array()[pos];
    }

    MMCJSON_INLINE value& value::operator[](const std::string& key)
    {
        if (empty()) {
            *this = object();
        }

        return as_object()[key];
    }

    MMCJSON_INLINE value& value::operator[](std::string&& key)
    {
        if (empty()) {
            *this = object();
        }

        return as_object()[std::move(key)];
    }

    MMCJSON_INLINE value value::operator|(const object & rhs)&
    {
        return as_object() | rhs;
    }

    MMCJSON_INLINE value value::operator|(object && rhs)&
    {
        return as_object() | std::move(rhs);
    }

    MMCJSON_INLINE value value::operator|(const object & rhs)&&
    {
        return std::move(as_object()) | rhs;
    }

    MMCJSON_INLINE value value::operator|(object && rhs)&&
    {
        return std::move(as_object()) | std::move(rhs);
    }

    MMCJSON_INLINE value& value::operator|=(const object & rhs)
    {
        as_object() |= rhs;
        return *this;
    }

    MMCJSON_INLINE value& value::operator|=(object && rhs)
    {
        as_object() |= std::move(rhs);
        return *this;
    }

    MMCJSON_INLINE value value::operator&(const object& rhs)&
    {
        return as_object() & rhs;
    }

    MMCJSON_INLINE value value::operator&(object&& rhs)&
    {
        return as_object() & std::move(rhs);
    }

    MMCJSON_INLINE value value::operator&(const object& rhs)&&
    {
        return std::move(as_object()) & rhs;
    }

    MMCJSON_INLINE value value::operator&(object&& rhs)&&
    {
        return std::move(as_object()) & std::move(rhs);
    }

    MMCJSON_INLINE value& value::operator&=(const object& rhs)
    {
        as_object() &= rhs;
        return *this;
    }

    MMCJSON_INLINE value& value::operator&=(object&& rhs)
    {
        as_object() &= std::move(rhs);
        return *this;
    }

    MMCJSON_INLINE value value::operator+(const array & rhs)&
    {
        return as_array() + rhs;
    }

    MMCJSON_INLINE value value::operator+(array && rhs)&
    {
        return as_array() + std::move(rhs);
    }

    MMCJSON_INLINE value value::operator+(const array & rhs)&&
    {
        return std::move(as_array()) + rhs;
    }

    MMCJSON_INLINE value value::operator+(array && rhs)&&
    {
        return std::move(as_array()) + std::move(rhs);
    }

    MMCJSON_INLINE value& value::operator+=(const array & rhs)
    {
        as_array() += rhs;
        return *this;
    }

    MMCJSON_INLINE value& value::operator+=(array && rhs)
    {
        as_array() += std::move(rhs);
        return *this;
    }

    template <typename... Args>
    value::value(value_type type, Args &&...args)
        : _type(type), _raw_data(std::forward<Args>(args)...)
    {
        static_assert(std::is_constructible<var_t, Args...>::value,
            "Parameter can't be used to construct a var_t");
    }

    MMCJSON_INLINE value::var_t value::deep_copy(const var_t & src)
    {
        var_t dst;
        if (const auto string_ptr = std::get_if<std::string>(&src)) {
            dst = *string_ptr;
        }
        else if (const auto arr_ptr = std::get_if<array_ptr>(&src)) {
            dst = std::make_unique<array>(**arr_ptr);
        }
        else if (const auto obj_ptr = std::get_if<object_ptr>(&src)) {
            dst = std::make_unique<object>(**obj_ptr);
        }
        else {
            // maybe invalid_value
        }

        return dst;
    }

    MMCJSON_INLINE const value invalid_value()
    {
        return value(value::value_type::Invalid, value::var_t());
    }

    MMCJSON_INLINE std::ostream& operator<<(std::ostream & out, const value & val)
    {
        //TODO: format output
        out << val.to_string();
        return out;
    }

    // std::istream &operator>>(std::istream &in, value &val)
    // {
    //     return in;
    // }

	}
}