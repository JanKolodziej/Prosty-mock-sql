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

	/*cout << "Podaj instrukcje: ";*/
	/*string wejscie;
	getline(cin, wejscie);
	cout << wejscie;*/

	//Wszytkie zapytania musz¹ byæ podane w jednej linii
	// W "idealym" formacie SQL
	// Przyk³ad: SELECT * FROM Customers
	//Program nie zadzia³a z np: Select *  FROM Customers
	MockDB db;
	string querry_show_all = "SELECT * FROM Customers";
	auto result = db.executeQuerry(querry_show_all);

	for (const auto& row : result) {
		for (const auto& col : row) {
			cout << col << " ";
		}
		cout << endl;
	}
	cout << "----------------" << endl;

	//Pokazanie tylko ID firmy i miasta
	string querry_show_City_ID = "SELECT CustomerID,City FROM Customers";
	 result = db.executeQuerry(querry_show_City_ID);

	for (const auto& row : result) {
		for (const auto& col : row) {
			cout << col << " ";
		}
		cout << endl;
	}
	cout << "----------------" << endl;


	//INSERT INTO Customers (CustomerID, CompanyName, Address, City) 
	string querry_insert = "INSERT INTO Customers VALUES 6, 'New Company', 'New Address', 'New City'";
	db.executeQuerry(querry_insert);
	auto result_after_insert = db.executeQuerry(querry_show_all);
	for (const auto& row : result_after_insert) {
		for (const auto& col : row) {
			cout << col << " ";
		}
		cout << endl;
	}
	cout << "----------------" << endl;

	// Przyk³ad: SELECT * FROM Customers WhERE CustomerID = 3


	//UPDATE Customers SET CompanyName = 'Alfred Schmidt', City = 'Frankfurt' WHERE CustomerID = 1;
	string querry_update = "UPDATE Customers SET CompanyName = 'Alfred Schmidt', City = 'Frankfurt' WHERE CustomerID = 1";
	db.executeQuerry(querry_update);
	auto result_after_update = db.executeQuerry(querry_show_all);
	for (const auto& row : result_after_update) {
		for (const auto& col : row) {
			cout << col << " ";
		}
		cout << endl;
	}
	cout << "----------------" << endl;


}