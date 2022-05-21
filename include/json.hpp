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
		//value
	}
}