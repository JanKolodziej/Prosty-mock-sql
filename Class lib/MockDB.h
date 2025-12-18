#pragma once
#include <vector>
#include "IDataBase.h"
#include "Customers.h"

class MockDB : public IDataBase
{
private:
    /// <summary>
    /// Funkcja rozbijaj¹ca zapytanie na pojedyncze s³owa
    /// </summary>
    /// <param name="querry"></param>
    /// <returns></returns>
    std::vector<std::string> BreakDownQuerry(std::string& querry);
    

    std::vector< std::vector<std::string>> SelectFrom(std::string From, std::vector<std::string> What);
	void InsertInto(std::string Into, std::vector<std::string> Values);
    std::vector<Customers> Customers;

public:
    /// <summary>
    /// Wykonuje zapytanie podane w SQL
    /// </summary>
    /// <param name="querry"></param>
    std::vector< std::vector<std::string>> executeQuerry(std::string&  querry) override;
	MockDB();
};