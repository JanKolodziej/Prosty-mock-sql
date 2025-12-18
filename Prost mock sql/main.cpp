#include <iostream>
#include <string>
#include <vector>
#include "../Class lib/MockDB.h"
using namespace std;

int main()
{
	cout << "----------------" << endl;
	cout << "| Sql mock 1.0 |" << endl;
	cout << "----------------" << endl;

	cout << "Podaj instrukcje: ";
	/*string wejscie;
	getline(cin, wejscie);
	cout << wejscie;*/

	//Wszytkie zapytania musz¹ byæ podane w jednej linii
	// W "idealym" formacie SQL
	// Przyk³ad: SELECT * FROM Customers
	//Program nie zadzia³a z np: Select *  FROM Customers
	MockDB db;
	string querry = "SELECT * FROM Customers";
	auto result = db.executeQuerry(querry);

	for (const auto& row : result) {
		for (const auto& col : row) {
			cout << col << " ";
		}
		cout << endl;
	}

	//INSERT INTO Customers (CustomerID, CompanyName, Address, City) VALUES (6, 'New Company', 'New Address', 'New City');


}