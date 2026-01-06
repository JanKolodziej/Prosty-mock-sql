#pragma once
#include "IDataBase.h"
#include "sqlite3.h" 
#include <iostream>
#include <vector>
class RealDB : public IDataBase
{
private:
	sqlite3* db;
	public:
	void executeQuerry(std::string& querry) override;
	RealDB();
	~RealDB();
};

