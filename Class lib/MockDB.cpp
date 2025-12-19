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
	std::string WhereTable;
	if (ListofWords[0] == "SELECT")
	{
		std::vector<std::string> WhatToSelect;

		std::vector<int> IndicesToSelectFrom;
		for(int i=0; i < Customers.size(); i++)
		{
			IndicesToSelectFrom.push_back(i);
		}
		
		for (int i = 1; i < ListofWords.size();i++)
		{
			if (ListofWords[i] == "FROM")
			{
				WhereTable = ListofWords[i + 1];
			}
			else if (ListofWords[i] == "WHERE")
			{
				std::vector<std::string> Condition;
				for (int j = i + 1; j < ListofWords.size(); j++)
				{
					Condition.push_back(ListofWords[j]);
				}
				IndicesToSelectFrom = std::vector<int>();
				IndicesToSelectFrom = WhereClause(WhereTable, Condition);
				
				break;
			}
			else
			{
				WhatToSelect.push_back(ListofWords[i]);
			}
		}
		 return SelectFrom(WhereTable, WhatToSelect, IndicesToSelectFrom);
	}
	else if (ListofWords[0] == "INSERT" && ListofWords[1] == "INTO" && ListofWords[3] == "VALUES")
	{
		WhereTable = ListofWords[2];
		std::vector<std::string> Values;
		for (int i = 4;i < ListofWords.size();i++) 
		{
			Values.push_back(ListofWords[i]);
		}
		InsertInto(WhereTable, Values);
		return std::vector< std::vector<std::string>>(); //INSERT nie zwraca nic
		
	}
	/*UPDATE table_name
		SET column1 = value1, column2 = value2, ...
		WHERE condition;*/
	else if (ListofWords[0] == "UPDATE" && ListofWords[2] == "SET")
	{
		WhereTable = ListofWords[1];
		for(int i =2; i<ListofWords.size();i++)
		{
			if (ListofWords[i] == "WHERE")
			{
				std::vector<std::string> Condition;
				for (int j = i + 1; j < ListofWords.size(); j++)
				{
					Condition.push_back(ListofWords[j]);
				}
				std::vector<int> IndicesToUpdate = WhereClause(WhereTable, Condition);
				for (int& index : IndicesToUpdate)
				{
					for (int k = 3; k < i-1; k += 2) // Od 3 do WHERE co 2 (bo mamy pary pole-wartoœæ)
					{
						std::string Field = ListofWords[k];
						std::string Value = ListofWords[k + 1];
						if (Field == "CustomerID")
						{
							Customers[index].CustomerID = std::stoi(Value);
						}
						else if (Field == "CompanyName")
						{
							Customers[index].CompanyName = Value;
						}
						else if (Field == "Address")
						{
							Customers[index].Address = Value;
						}
						else if (Field == "City")
						{
							Customers[index].City = Value;
						}
					}
				}
				break;
			}
		}
		return std::vector< std::vector<std::string>>(); //UPDATE nie zwraca nic

	}
		

	
}



std::vector<std::string> MockDB::BreakDownQuerry(std::string& querry)
{
	if (querry.empty()) return std::vector<std::string>();
	std::string word;
	std::vector<std::string> ListofWords;
	querry += ' ';
	bool inQuotes = false; //Mówi czy jesteœmy w cudzys³owie
	for (auto& c : querry)
	{
		if (c == '\'') {
			inQuotes = !inQuotes; // Prze³¹czamy stan 
			continue; 
		}
		// Jeœli jesteœmy w cudzys³owie -> dodajemy WSZYSTKO (spacje, przecinki)
		if (inQuotes) {
			word += c;
		}
		else 
		{
			if (c == ' ' || c == ',' || c == '(' || c == ')' || c == '=') {
				// To s¹ separatory. Jeœli mamy jakieœ s³owo w buforze, zapisujemy je.
				if (!word.empty()) {
					ListofWords.push_back(word);
					word.clear();
				}
			}
			else {
				// To zwyk³a litera/cyfra, doklejamy do s³owa
				word += c;
			}
		}
	}
	return ListofWords;
}

std::vector< std::vector<std::string>> MockDB::SelectFrom(std::string From, std::vector<std::string> What,std::vector<int> IndicesToSelectFrom)
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

		for (auto& element : IndicesToSelectFrom)
		{
			std::vector<std::string> Row;
			if (hasID) Row.push_back(std::to_string(Customers[element].CustomerID));
			if (hasCompanyName) Row.push_back(Customers[element].CompanyName);
			if(hasAddress) Row.push_back(Customers[element].Address);
			if (hasCity) Row.push_back(Customers[element].City);
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

std::vector<int> MockDB::WhereClause(std::string Where, std::vector<std::string> Condition)
{ 
	std::vector<int> ResultIndices;
	if (Where == "Customers")
	{
		if (Condition.size() == 2) // poniewa¿ usuneliœmy znak '=' podczas rozbijania zapytania
		{
			std::string Field = Condition[0];
			std::string Value = Condition[1];
			for (int i = 0; i < Customers.size(); i++)
			{
				if (Field == "CustomerID" && std::to_string(Customers[i].CustomerID) == Value)
				{
					ResultIndices.push_back(i);
				}
				else if (Field == "CompanyName" && Customers[i].CompanyName == Value)
				{
					ResultIndices.push_back(i);
				}
				else if (Field == "Address" && Customers[i].Address == Value)
				{
					ResultIndices.push_back(i);
				}
				else if (Field == "City" && Customers[i].City == Value)
				{
					ResultIndices.push_back(i);
				}
			}
		}	
		else if (Condition.size() == 3) // mamy np: CustomerID > 5
		{
			std::string Field = Condition[0];
			std::string Operator = Condition[1];
			std::string Value = Condition[2];
			for (int i = 0; i < Customers.size(); i++)
			{
				if (Field == "CustomerID") //Sprawdzenie tylko dla CustomerID, bo inne pola s¹ stringami
				{
					int CustomerIDValue = std::stoi(Value);
					if (Operator == ">" && Customers[i].CustomerID > CustomerIDValue)
					{
						ResultIndices.push_back(i);
					}
					else if (Operator == "<" && Customers[i].CustomerID < CustomerIDValue)
					{
						ResultIndices.push_back(i);
					}
					else if (Operator == ">=" && Customers[i].CustomerID >= CustomerIDValue)
					{
						ResultIndices.push_back(i);
					}
					else if (Operator == "<=" && Customers[i].CustomerID <= CustomerIDValue)
					{
						ResultIndices.push_back(i);
					}
				}
			}
		}
			
		
	}
	return ResultIndices;
}


		
			
		

	
	


