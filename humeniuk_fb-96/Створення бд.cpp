#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <Windows.h>

using namespace std;
typedef std::map<string, string> ColumnStructure;
typedef std::map<string, ColumnStructure> Database;
typedef std::map<int, string> NameOfDatabase;

int main()
{
    setlocale(LC_ALL, "ru");
    SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
    SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывод

    int i = 1;
    // Create a map of three strings (that map to integers)
    ColumnStructure ColumnStructureOfAllDatabases{ {"5", "CPU"}, {"3", "2"}, {"CPU", "3"} };

    Database AllDatabase;
    NameOfDatabase NameOfAllDatabase;
    NameOfDatabase ::iterator itNameOfAllDatabase = NameOfAllDatabase.begin();
    Database::iterator itDatabase = AllDatabase.begin();
    ColumnStructure::iterator itColumnStructure = ColumnStructureOfAllDatabases.begin();
    cout << "А вот и наша базаданных: " << endl;
    for (int i = 0; itNameOfAllDatabase != NameOfAllDatabase.end(); itNameOfAllDatabase++, itColumnStructure++) // выводим их
    {  
        cout << itNameOfAllDatabase->second << "\t" <<itColumnStructure->first << "\t" << itColumnStructure->second << "\t" << endl;
        std::string NameOfDatabase = itNameOfAllDatabase->second;
        AllDatabase.insert(std::make_pair(NameOfDatabase, itColumnStructure->first, itColumnStructure->second));
    }
}
