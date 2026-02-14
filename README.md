# Prosty Mock SQL w C++

## 📝 O projekcie
Ten projekt to aplikacja edukacyjna napisana w języku C++, demonstrująca zasady **programowania obiektowego**, **wstrzykiwania zależności (Dependency Injection)** oraz tworzenia **mocków** na potrzeby testowania oprogramowania.

System pozwala na wykonywanie operacji na bazie danych (takich jak `INSERT`, `SELECT`, `UPDATE`) przy użyciu wspólnego interfejsu, z możliwością dynamicznego przełączania się między:
1.  **MockDB** – Lekką, symulowaną bazą danych działającą w pamięci RAM (własny parser SQL).
2.  **RealDB** – Prawdziwą bazą danych opartą na silniku **SQLite**.

## 🚀 Funkcjonalności

### 1. Architektura "Plug & Play"
Dzięki zastosowaniu interfejsu `IDataBase`, aplikacja kliencka nie musi wiedzieć, z jakiej bazy korzysta. Zmiana z Mocka na SQLite wymaga zmiany tylko jednej linijki kodu lub wyboru w menu.

### 2. Mock Database (Symulator)
* Przechowuje dane w kontenerach STL (`std::vector`, `std::map`).
* Posiada **autorski parser SQL**, który:
    * Rozpoznaje komendy `INSERT`, `SELECT`, `UPDATE`.
    * Obsługuje spacje w wartościach tekstowych (np. `'Jan Kowalski'`).

### 3. Real Database (SQLite)
* Integracja z biblioteką **SQLite 3** .
* Trwały zapis danych do pliku `.db`.
* Wykorzystanie mechanizmu `callback` do odbierania wyników zapytań `SELECT`.

## 🛠 Technologie i Narzędzia

* **Język:** C++ (Standard C++14/17)
* **IDE:** Visual Studio 2019
* **Biblioteki zewnętrzne:** SQLite3 (dołączona do projektu)
* **Typ projektu:**
    * `Class Lib` (Biblioteka statyczna z logiką bazy)
    * `Console App` (Aplikacja kliencka)

## 🏗 Struktura Projektu

```text
├── Class lib/                 # Biblioteka statyczna (Silnik)
│   ├── Pliki nagłówkowe
│   │   ├── IDataBase.h        # Interfejs (Kontrakt)
│   │   ├── MockDB.h           # Nagłówek Mocka
│   │   ├── RealDB.h           # Nagłówek SQLite Writera
│   │   ├── Customers.h        # Struktury danych
│   │   └── sqlite3.h          # Nagłówek biblioteki SQLite
│   └── Pliki źródłowe
│       ├── MockDB.cpp         # Implementacja Mocka (RAM)
│       ├── RealDB.cpp         # Implementacja SQLite (Dysk)
│       ├── IDataBase.cpp      # Logika wspólna
│       └── sqlite3.c          # Kod źródłowy SQLite
├── Prosty mock sql/           # Aplikacja konsolowa (Klient)
│   ├── main.cpp               # Punkt wejścia, wybór bazy
│   └── ...
└── README.md
```
## 💻 Jak uruchomić (Visual Studio)

1.  Otwórz plik `Prosty mock sql.sln` w Visual Studio.
2.  Upewnij się, że projekt **Prosty mock sql** jest ustawiony jako projekt startowy (Prawy przycisk myszy -> *Set as Startup Project*).
3.  **Ważne dla SQLite:** Jeśli kompilacja `sqlite3.c` zgłasza błędy, upewnij się, że wyłączono dla tego pliku prekompilowane nagłówki:
    * Prawy przycisk na `sqlite3.c` -> *Properties* -> *C/C++* -> *Precompiled Headers* -> **Not Using Precompiled Headers**.
4.  Skompiluj i uruchom rozwiązanie (`Ctrl + F5`).

## 📖 Przykłady użycia

### Wybór bazy w kodzie (`main.cpp`):

```cpp
// Polimorfizm w akcji
IDataBase* db;

int wybor;
std::cout << "1. Mock, 2. SQLite: ";
std::cin >> wybor;

if (wybor == 1) {
    db = new MockDB(); // Baza w RAM
} else {
    db = new RealDB(); // Baza na dysku
}

// Aplikacja nie wie, że to Mock!
db->executeQuery("INSERT INTO Customers VALUES 'Jan Kowalski'");
db->executeQuery("SELECT * FROM Customers");
```

### Przykładowe zapytania obsługiwane przez Mocka:
```sql
DELETE FROM Customers WHERE CompanyName = 'Alfred Schmidt'
INSERT INTO Customers VALUES 6, 'New Company', 'New Address', 'New City'
SELECT * FROM Customers
SELECT CustomerID,City FROM Customers
```


## 👤 Author

**Jan Kołodziej** 💼   
📧 [jankolodziej@outlook.com](mailto:jankolodziej@outlook.com)  
🔗 [LinkedIn Profile](https://www.linkedin.com/in/jan-kolodziej-krk/)

