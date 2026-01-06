#pragma once
#include <string>
#include <vector>
class IDataBase
{
public:
	virtual ~IDataBase() = default;
	virtual void executeQuerry(std::string& querry) = 0;
};

