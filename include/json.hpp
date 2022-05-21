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

		value operator&(const object& rhs)&;
		value operator&(object&& rhs)&;
		value operator&(const object& rhs)&&;
		value operator&(object&& rhs)&&;

		value& operator&=(const object& rhs);
		value& operator&=(object&& rhs);

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





	}
}