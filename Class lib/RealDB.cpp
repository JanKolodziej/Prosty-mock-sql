#include "pch.h"
#include "RealDB.h"

RealDB::RealDB()
{
	int rc = sqlite3_open("CustomerDb.db", &db);
	if (rc)
	{
		std::cerr << "Nie mozna otworzyc bazy danych: " << sqlite3_errmsg(db) << std::endl;
	}
	else
	{
		std::cout << "Udalo sie polaczyæ z baza" << std::endl;
	}
}
// Ta funkcja jest wo³ana przez SQLite automatycznie dla ka¿dego wiersza
// argc = liczba kolumn
// argv = tablica wartoœci (np. "Jan")
// azColName = tablica nazw kolumn (np. "Imie")
static int wypiszWiersz(void* NotUsed, int argc, char** argv, char** azColName) {

	std::cout << ">>> ZNALEZIONO REKORD:\n";

	for (int i = 0; i < argc; i++) {
		std::cout << "    " << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << "\n";
	}

	std::cout << "---------------------------------\n";

	return 0; 
}

void RealDB::executeQuerry(std::string&	 querry)
{
	std::cout << "Wykonuje zapytanie na prwawdziwej bazie danych: " << querry << std::endl;
	char* errMsg = 0;
	int rc = sqlite3_exec(db, querry.c_str(), wypiszWiersz, 0, &errMsg);
	if(rc != SQLITE_OK)
	{
		std::cerr << "SQL error: " << errMsg << std::endl;
		sqlite3_free(errMsg);
	}
	else
	{
		std::cout << "Zapytanie wykonane pomyœlnie" << std::endl;
	}
}
RealDB::~RealDB()
{
	sqlite3_close(db);
}