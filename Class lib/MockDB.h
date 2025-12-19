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
	/// <summary>
	/// Dodaje nowy rekord do bazy
	/// </summary>
	/// <param name="Into"></param>
	/// <param name="Values"></param>
	void InsertInto(std::string Into, std::vector<std::string> Values);

	/// <summary>
	/// Zwraca indeksy rekordów spe³niaj¹cych warunek
	/// </summary>
	/// <param name="Where nazwa tabeli"></param>
	/// <param name="Condition wektor z warunkiem w string"></param>
	/// <returns>Vector indeksów które spe³niaj¹ warunek</returns>
	std::vector<int> WhereClause(std::string Where, std::vector<std::string> Condition);
    std::vector<Customers> Customers;

public:
    /// <summary>
    /// Wykonuje zapytanie podane w SQL
    /// </summary>
    /// <param name="querry"></param>
    std::vector< std::vector<std::string>> executeQuerry(std::string&  querry) override;
	MockDB();
};