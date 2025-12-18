#include "pch.h"
#include "MockDB.h"
MockDB::MockDB()
{
	Customers.push_back({ 1,"Alfreds Futterkiste","Obere Str. 57","Berlin" });
	Customers.push_back({ 2,"Ana Trujillo Emparedados y helados","Avda. de la Constitución 2222","Mexico D.F." });
	Customers.push_back({ 3,"Antonio Moreno Taquería","Mataderos 2312","Mexico D.F." });
	Customers.push_back({ 4,"Around the Horn","120 Hanover Sq.","London" });
	Customers.push_back({ 5,"Berglunds snabbkop","Berguvsvagen 8","Lulea" });
}
std::vector< std::vector<std::string>> MockDB::executeQuerry(std::string& querry)
{
	std::vector<std::string> ListofWords = BreakDownQuerry(querry);
	std::string Where;
	if (ListofWords[0] == "SELECT")
	{
		std::vector<std::string> WhatToSelect;
		for (int i=1;i<ListofWords.size();i++)
		{
			if (ListofWords[i] == "FROM")
			{
				Where = ListofWords[i + 1];
				break;
			}
			else if (ListofWords[i] == ",") { continue; }
			else
			{
				WhatToSelect.push_back(ListofWords[i]);
			}
		}
		 return SelectFrom(Where, WhatToSelect);
	}
	else if (ListofWords[0] == "INSERT" && ListofWords[1] == "INTO")
	{
		Where = ListofWords[2];
		/*InsertInto(Where)*/
		
	}

	
}



std::vector<std::string> MockDB::BreakDownQuerry(std::string& querry)
{
	if (querry.empty()) return std::vector<std::string>();
	//Musimy podzieliæ zapytanie na pojedyncze s³owa
	std::string word;
	std::vector<std::string> ListofWords;
	querry += ' ';
	for (auto& c : querry)
	{
		if (c == '\n')
		{
			break;
		}
		if (c == ' ')
		{
			ListofWords.push_back(word);
			word = "";
		}
		else
		{
			word += c;
		}
	}
	return ListofWords;
}

std::vector< std::vector<std::string>> MockDB::SelectFrom(std::string From, std::vector<std::string> What)
{
	if (From == "Customers")
	{
		bool hasID = false;
		bool hasCompanyName = false;
		bool hasAddress = false;
		bool hasCity = false;

		for (auto& element : What)
		{
			if (element == "*")
			{
				hasID = true;
				hasCompanyName = true;
				hasAddress = true;
				hasCity = true;
				break;
			}
			else if (element == "CustomerID")
			{
				hasID = true;
			}
			else if (element == "CompanyName")
			{
				hasCompanyName = true;
			}
			else if (element == "Address")
			{
				hasAddress = true;
			}
			else if (element == "City")
			{
				hasCity = true;
			}
		}
		std::vector< std::vector<std::string>> Result;

		for (auto& element : Customers)
		{
			std::vector<std::string> Row;
			if (hasID) Row.push_back(std::to_string(element.CustomerID));
			if (hasCompanyName) Row.push_back(element.CompanyName);
			if(hasAddress) Row.push_back(element.Address);
			if (hasCity) Row.push_back(element.City);
			Result.push_back(Row);

		}


		return Result;
	}
	

}

void MockDB::InsertInto(std::string Into, std::vector<std::string> Values)
{
	if (Into == "Customers")
	{
		if (Values.size() != 4) return; //Niepoprawna liczba wartoœci
		Customers.push_back({ std::stoi(Values[0]), Values[1], Values[2], Values[3] });
	}
}

		
			
		

	
	


