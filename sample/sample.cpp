#include <iostream>
#include <vector>
#include <set>
#include <map>
#include "json.hpp"

void parsing();
void serializing();

int main()
{
	std::cout << "\nParsing\n" << std::endl;

	parsing();

	std::cout << "\nSerializing\n" << std::endl;

	serializing();

	return 0;
}

void parsing()
{
	std::string content = "R"()
	{
		"repo":"mmcjson",
		"author" : {
		"Magicst_Magoo":"https://github.com/MagicstMagoo"},
		"list" : [
				1,
				2,
				3
				],
		"str":"abc",
		"num":3.1416,
		"A_obj" : {
		"B_obj": [
					{
						"C_obj":"hey you found me"
					}
				]
			}
		}
	)";

}
