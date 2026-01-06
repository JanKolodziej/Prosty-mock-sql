#include <iostream>
#include <string>
#include <vector>
#include "../Class lib/IDataBase.h"
#include "../Class lib/MockDB.h"
#include "../Class lib/RealDB.h"
using namespace std;

int main()
{
	cout << "----------------" << endl;
	cout << "| Sql mock 1.0 |" << endl;
	cout << "----------------" << endl;
	cout << "Chcesz pracowac na:" << endl;
	cout << "1. Prawdziwej bazie danych (wymaga pliku CustomerDb.db)" << endl;
	cout << "2. Mock bazie danych (dane przechowywane w pamiêci)" << endl;
	IDataBase* db; //wskaŸnik na baze danych
	string wejscie;
	cin >> wejscie;
	cout << "----------------" << endl;
	if (wejscie == "1")
	{
		cout << "Praca na prawdziwej bazie danych" << endl;
		db = new RealDB();
	}
	else
	{
		cout << "Praca na mock bazie danych" << endl;
		db = new MockDB();	
	}
	cout << "----------------" << endl;
	cout << "Chcesz zobaczyæ przykladowe zapytania \"1\", Czy napisac wlasne? \" 0\": ";
	cin >> wejscie;
	cout << "----------------" << endl;
	if (wejscie == "1")
	{
		string querry;
		//cout testowy/ pokazauj¹ce co potrafi program
		cout << "Poczatkowa Baza danych:" << endl;
		cout << "----------------" << endl;
		querry = "SELECT * FROM Customers";
		db->executeQuerry(querry);


		//Pokazanie tylko ID firmy i miasta
		cout << "Pokazuje tylko CompanyID i City:" << endl;
		cout << "----------------" << endl;
		querry = "SELECT CustomerID,City FROM Customers";
		db->executeQuerry(querry);



		//INSERT INTO Customers (CustomerID, CompanyName, Address, City) 
		cout << "Dodajemy nowy rekord:" << endl;
		cout << "----------------" << endl;
		querry = "INSERT INTO Customers VALUES 6, 'New Company', 'New Address', 'New City'";
		db->executeQuerry(querry);


		// Przyk³ad: SELECT * FROM Customers WHERE CustomerID > 3
		cout << "Rekordy z  CustomerID > 3:" << endl;
		cout << "----------------" << endl;
		querry = "SELECT * FROM Customers WHERE CustomerID > 3";
		db->executeQuerry(querry);

		//UPDATE Customers SET CompanyName = 'Alfred Schmidt', City = 'Frankfurt' WHERE CustomerID = 1;
		cout << "Zmiana rekordu z CustomerID = 1:" << endl;
		cout << "----------------" << endl;
		querry = "UPDATE Customers SET CompanyName = 'Alfred Schmidt', City = 'Frankfurt' WHERE CustomerID = 1";
		db->executeQuerry(querry);


		//DELETE Customers WHERE CompanyName = 'Alfred Schmidt'
		cout << "Usuwanie rekordu z CompanyName = 'Alfred Schmidt':" << endl;
		cout << "----------------" << endl;
		querry = "DELETE FROM Customers WHERE CompanyName = 'Alfred Schmidt'";
		db->executeQuerry(querry);

		cout << "Baza danych po wszystkich zmianach:" << endl;
		cout << "----------------" << endl;
		querry = "SELECT * FROM Customers";
		db->executeQuerry(querry);
	}
	else
	{
		cout << "---------------------------------------------------------------------------------" << endl;
		cout << "Kilka zasad do przestrzegania:" << endl;
		cout << "1. Wszystkie zapytania musza byc podane w jednej linii" << endl;
		cout << "2. Zapytania musz¹ byæ w idealnym formacie SQL" << endl;
		cout << "3. Dostêpne tabele: Customers" << endl;
		cout << "4. Dostêpne kolumny w tabeli Customers: CustomerID, CompanyName, Address, City" << endl;
		cout << "5. Na ten moment program obs³uguje komendy INSERT, SELECT, DELETE,UPDATE,WHERE" << endl;
		cout << "----------------------------------------------------------------------------------" << endl;
		cout << "Podaj zapytanie: ";
		string querry;
		cin.ignore();
		getline(cin,querry);
		db->executeQuerry(querry);

	}


	

}