<div align="center">
mmcjson

Json/Json5 解析/生成器

**中文** | [English](./README_EN.md)

[![License](https://img.shields.io/github/license/MagicstMagoo/mmcjson?style=flat-square)](https://mit-license.org/)
[![C++](https://img.shields.io/badge/C++-17-%2300599C?logo=cplusplus&style=flat-square)](https://en.wikipedia.org/wiki/C++17)
[![platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-blueviolet?style=flat-square)](https://github.com/MagicstMagoo/mmcjson)

</div>


## 使用说明书

- 在项目中包含头文件即可使用
- [demo](https://io.magicst.cn/download/benchmark.cpp)

 ```cpp
 #include "json.hpp"
 ```
  
- 如果需要解析 Json5 ,则请包含 `json5.hpp` 头文件

```cpp
#include "json5.hpp"
```

- mmcjson仅依赖 STL ,需要[C++17](https://en.wikipedia.org/wiki/C++17)标准

## 示例

### 解析

```cpp
#include <iostream>

// using json.hpp
#include "json.hpp"

void parsing()
{
    std::string content = R"(
{
    "repo": "mmcjson",
    "author": {
        "MagicstMagoo": "https://github.com/MagicstMagoo"
    },
    "list": [
        1,
        2,
        3
    ],
    "str": "abc",
    "num": 3.1416,
    "A_obj": {
        "B_arr": [
            {
                "C_str": "you found me!"
            }
        ]
    }
}
    )";

    auto ret = json::parse(content);

    if (!ret) {
        std::cerr << "Parsing failed" << std::endl;
        return;
    }
    auto& value = ret.value(); // you can use rvalues if needed, like
                               // `auto value = std::move(ret).value();`
    // Output: mmcjson
    std::cout << value["repo"].as_string() << std::endl;

    /* Output:
        MagicstMagoo's homepage: https://github.com/MagicstMagoo
    */
    for (auto&& [name, homepage] : value["author"].as_object()) {
        std::cout << name << "'s homepage: " << homepage.as_string() << std::endl;
    }

    // Output: abc
    std::string str = (std::string)value["str"];    // it is equivalent to `value["str"].as_string()`
    std::cout << str << std::endl;

    // Output: 3.141600
    double num = value["num"].as_double();          // similarly, you can use `(double)value["num"]`
    std::cout << num << std::endl;

    // Output: default_value
    std::string get = value.get("maybe_exists", "default_value");
    std::cout << get << std::endl;

    // Output: you found me!
    std::string nested_get = value.get("A_obj", "B_arr", 0, "C_str", "default_value");
    std::cout << nested_get << std::endl;

    /*  Output:
        1
        2
        3
    */
    // It's const!
    for (const auto& ele : value.at("list").as_array()) {
        int x = (int)ele;
        std::cout << x << std::endl;
    }
}
```

### 解析 Json5

```cpp
#include <iostream>

//using json5.hpp
#include "json5.hpp"

void parsing()
{
    std::string content = R"(
// 这是一段json5格式的信息
{
  name: "Magicst",                 // key的引号可省略
  emoji: '🥵',                     // emoji为key
  thanks: 'thanksforyourstar',     // 单引号也可以表示字符串
  \u006Bey: ['value',],            // 普通字符和转义可以混用
  inf: +Infinity, nan: NaN,        // 数字可以以"+"开头
  fractional: .3, integer: 42.,    // 小数点作为起始/结尾
  byte_max: 0xff,                  // 十六进制数
  light_speed: +3e8,               // 科学计数法
}
)";
    auto ret = json::parse5(content);
    if (!ret) {
        std::cerr << "Parsing failed" << std::endl;
        return;
    }
    auto& value = ret.value(); // you can use rvalues if needed, like
                               // `auto value = std::move(ret).value();`

    // Output: Magicst
    std::cout << value["name"].as_string() << std::endl;
    // Output: value
    std::string str = (std::string)value["key"][0];
    std::cout << str << std::endl;

    // for more json::value usage, please refer to sample.cpp
}
```

### 生成

```cpp
#include <iostream>

// using json.hpp
#include "json.hpp"

void serializing()
{
    json::value root;
    root["hello"] = "mmcjson";
    root["Pi"] = 3.1416;

    root["arr"] = json::array{
        "a", "b", "c"
    };
    root["obj"] = json::object{
        {"obj_key1", "aaa"},
        {"obj_key2", 123},
        {"obj_key3", true}
    };
    root["obj"].object_emplace("key4", json::object{ { "key4 child", "lol" } });
    root["obj_another"]["child"]["grand"] = "i am grand";

    std::vector<int> vec = { 1, 2, 3, 4, 5 };
    root["arr from vec"] = json::array(vec);
    root["arr from vec"].array_emplace(6);

    root["arr from vec"] += json::array{ 7, 8, 9, 10 };

    std::set<std::string> set = { "a", "bbb", "cc" };
    root["arr from set"] = json::array(set);

    std::map<std::string, int> map;
    map.emplace("key1", 1);
    map.emplace("key2", 2);
    root["obj from map"] = json::object(map);

    auto other = json::object{
        { "other_key", "lol" },
        { "obj", "Existing key will not be overwritten"}
    };
    // take union
    root |= other;

    std::cout << root.format() << std::endl;
}
```


<img alt="FUN" src="./img/icon.png" width=256 height=258/>
