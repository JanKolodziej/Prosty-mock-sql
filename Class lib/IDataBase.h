#pragma once
#include <string>
#include <vector>
class IDataBase
{
public:
	virtual ~IDataBase() = default;
	virtual std::vector< std::vector<std::string>> executeQuerry(std::string& querry) = 0;
};

