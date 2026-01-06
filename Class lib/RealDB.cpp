#include "pch.h"
#include "RealDB.h"

RealDB::RealDB()
{
	int rc = sqlite3_open("CustomerDb.db", &db);
	if (rc)
	{
		std::cerr << "Nie mo¿na otworzyæ bazy danych: " << sqlite3_errmsg(db) << std::endl;
	}
	else
	{
		std::cout << "Uda³o siê po³¹czyæ z baz¹" << std::endl;
	}
}

void RealDB::executeQuerry(std::string&	 querry)
{
	std::cout << "Wykonuje zapytanie na prwawdziwej bazie danych: " << querry << std::endl;
	char* errMsg = 0;
	int rc = sqlite3_exec(db, querry.c_str(), 0, 0, &errMsg);
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