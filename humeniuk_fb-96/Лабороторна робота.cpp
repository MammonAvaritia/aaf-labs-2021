#include <string>
#include <fstream>
#include <streambuf>
#include <iostream>
#include <vector>
#include <locale>
#include <string>
#include <algorithm>
#include<conio.h>
#include <stdio.h>
#include<windows.h>
#include <string.h>
#include<stdlib.h>
#include <memory>
#include <map>
#include <unordered_map>
#include <iterator>
#include <regex>
#include <sstream>
#include <cctype> 
#include <string_view>
using namespace std;
typedef std::vector<char>     T_araay;
std::map<string, string> ColumInformation;
typedef std::map<string, map<string, string>> Database;
int pNumberCurrentItem = 0, pNumberCurrentItemString = 0, pNumberCurrentItemStringForCheck, pNumberCurrentItemStringCommand = 0;                               // индекс символов строки
char lCurrentItem;                                        // поточный елемент в строке
string  lTolowerComand, lNameTable, lComand;// раздичные переменные которые используем для проверки команды на правильную структуру
string  NameVariable; //то куда мы записываем имя таблицы
string  TypeOfData; //то куда мы записываем тип данных таблицы
string lTolowerBufferString;//строка в которую будем записивать буфер для проверки на последний елемент
char buffer[255];
std::string pBufferWithoutSpace;
string** database;
int NumberColumn = 1;
int lQuantityOfDatabaseElements = 0;
bool NameColumn = 1;
bool ColumnExistence = 0;
bool pBoolForInsert = 1;
string lTolowerCommand;// Строка в которую записиваем значения переведенной команды
char lTolowerCommandElementChar;// перменная в которую мы записиваем елемент команды
Database AllDatabases;//база данных всех бд что у нас существуют, где 1 колонка ето имя бд с которой взят стобец, вторая ето имя самого столбца и 3 тип данных * так было задумано, но чет пошло не так, поетому прийдеться создавать 2 мапа
string lFullCommand = "";
string pFullCommand = "";

//////////////////////////////////////////////////////////////////////////////////////////
void CreateTable()
{

}
void AnalizArgumentsOfComandCreate(string pComand)
{
    while (pComand[pNumberCurrentItemStringCommand+1])// пока не конец строки
    {
        if (pComand[pNumberCurrentItemStringCommand ] != ' ' && NameColumn && pComand[pNumberCurrentItemStringCommand] != ',')
        {
            if (pComand[pNumberCurrentItemStringCommand] == ')')
            {
                cout << "we end read comand!" << endl;
                break;
            }
            NameVariable = NameVariable + pComand[pNumberCurrentItemStringCommand];
            if (pComand[pNumberCurrentItemStringCommand + 1] == ' ' || pComand[pNumberCurrentItemStringCommand + 1] == ',' || pComand[pNumberCurrentItemStringCommand + 1] == ')')
            {
                if      (pComand[pNumberCurrentItemStringCommand + 1] == ' ')
                {
                    cout << "Column number " << NumberColumn << " has this name " << NameVariable;
                    NumberColumn++;
                    NameColumn = 0;
                    NameVariable.clear();
                    ColumnExistence = 1;
                }
                else if (pComand[pNumberCurrentItemStringCommand + 1] == ','|| pComand[pNumberCurrentItemStringCommand + 1] == ')')
                {
                    cout << "Column number " << NumberColumn << " has this name " << NameVariable << endl;
                    NumberColumn++;
                    NameVariable.clear();
                    ColumnExistence = 1;
                }
            }
        }
        else if (!NameColumn)
        {
            if      (pComand[pNumberCurrentItemStringCommand + 1] != ',' && pComand[pNumberCurrentItemStringCommand] != ' ')
            {
                TypeOfData = TypeOfData + pComand[pNumberCurrentItemStringCommand];
            }
            else if (pComand[pNumberCurrentItemStringCommand + 1] == ',' && pComand[pNumberCurrentItemStringCommand] == ' ')
            {
                cout << " ,type of data is " << TypeOfData << endl;
                NameColumn = 1;
                ColumnExistence = 1;
            }
        }
        pNumberCurrentItemStringCommand++;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
void AnalizArgumentsOfComandInsert(string pComand, string pNameTable)
{
    while (pComand[pNumberCurrentItemStringCommand + 1])// пока не конец строки
    {
        if (pComand[pNumberCurrentItemStringCommand] != ' ' && NameColumn && pComand[pNumberCurrentItemStringCommand] != ',')
        {
            if (pComand[pNumberCurrentItemStringCommand] == ')')
            {
                cout << "We end read comand!" << endl;
                break;
            }
            if (pComand[pNumberCurrentItemStringCommand] != '"')
            {
                NameVariable = NameVariable + pComand[pNumberCurrentItemStringCommand];
                if (pComand[pNumberCurrentItemStringCommand + 1] == ' ' || pComand[pNumberCurrentItemStringCommand + 1] == ',' || pComand[pNumberCurrentItemStringCommand + 1] == ')' || pComand[pNumberCurrentItemStringCommand + 1] == '\"')
                {
                    if (pComand[pNumberCurrentItemStringCommand + 1] == '\"')
                    {
                        cout << "You insert in table " << pNameTable << "; column number " << NumberColumn << " has this value " << NameVariable << endl;
                        NumberColumn++;
                        NameVariable.clear();
                        ColumnExistence = 1;
                    }
                    else if (pComand[pNumberCurrentItemStringCommand + 1] == '\"' && (pComand[pNumberCurrentItemStringCommand + 2] == ',' || pComand[pNumberCurrentItemStringCommand + 2] == ')' || pComand[pNumberCurrentItemStringCommand + 3] == ',' || pComand[pNumberCurrentItemStringCommand + 3] == ')'))
                    {
                        cout << "You insert in table " << pNameTable << "; column number " << NumberColumn << " has this value " << NameVariable << endl;
                        NumberColumn++;
                        NameVariable.clear();
                        ColumnExistence = 1;
                    }
                }
            }
        }
        pNumberCurrentItemStringCommand++;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
bool HellperChek(char c)
{
    switch (c)
    {
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
    case 'h':
    case 'i':
    case 'j':
    case 'k':
    case 'l':
    case 'm':
    case 'n':
    case 'o':
    case 'p':
    case 'q':
    case 'r':
    case 's':
    case 't':
    case 'u':
    case 'v':
    case 'w':
    case 'x':
    case 'y':
    case 'z':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        return true;
    default:
        return false;
    }
}

int check(string pComandString)
{
    // Массив строк типа string
    // 1. Инициализация массива строк указанием размера массива
    const int lNumberOfCommands = 9;
    string lCommands[lNumberOfCommands] = { "create", "insert", "indexed",
    "select", "where", "left_join", "full_join","join","order_by" };

    for (int pNumberOfCommands = 0; pNumberOfCommands < lNumberOfCommands; pNumberOfCommands++) // Проверка на то являеться ли полученая строка одной из команд. если да то выполняем действия етой команды
    {
        if      (pComandString == lCommands[0])//команда Create
        {
            cout << "Create your table" << endl;
            while (lFullCommand[pNumberCurrentItemString])                           // пока не конец буфера
            {
                char endch = lFullCommand[lFullCommand.size() - 2];
                if (endch != ';')
                {
                    cout << "Вы не закончили команду с помощью символа ';'!" << endl;
                }
                if (lFullCommand[pNumberCurrentItemString] != ' ')
                {
                    lNameTable = lNameTable + lFullCommand[pNumberCurrentItemString];
                    if (lFullCommand[pNumberCurrentItemString + 1] == ' ' || lFullCommand[pNumberCurrentItemString + 1] == '\0' || lFullCommand[pNumberCurrentItemString + 1] == '(' && !HellperChek(lFullCommand[pNumberCurrentItemString + 1]))
                    {
                        cout << "The name of your table is " << lNameTable << endl;

                        lQuantityOfDatabaseElements++;

                        if (lFullCommand[pNumberCurrentItemString + 1] == '\0')
                        {
                            return 0;
                        }
                        if (lFullCommand[pNumberCurrentItemString + 1] == '(' || lFullCommand[pNumberCurrentItemString + 2] == '(')
                        {
                            if      (lFullCommand[pNumberCurrentItemString + 1] == '(')
                            {
                                pNumberCurrentItemStringForCheck = pNumberCurrentItemString + 2;
                                while (lFullCommand[pNumberCurrentItemStringForCheck])                           // пока не конец нашей команды
                                {
                                    if (lFullCommand[pNumberCurrentItemStringForCheck] != ';')
                                    {
                                        lComand = lComand + lFullCommand[pNumberCurrentItemStringForCheck];
                                        if (lFullCommand[pNumberCurrentItemStringForCheck] == ')')
                                        {
                                            cout << lComand << endl;
                                            AnalizArgumentsOfComandCreate(lComand);
                                            if (ColumnExistence == 0)
                                            {
                                                cout << "Вы не добавили никаких столбцов в таблицу!" << endl;
                                            }
                                            if (lNameTable == "")
                                            {
                                                cout << "Вы не указали имя таблицы!" << endl;
                                            }
                                        }
                                    }
                                    pNumberCurrentItemStringForCheck++;
                                }
                            }
                            else if (lFullCommand[pNumberCurrentItemString + 2] == '(')
                            {
                                pNumberCurrentItemStringForCheck = pNumberCurrentItemString + 3;
                                while (lFullCommand[pNumberCurrentItemStringForCheck])                           // пока не конец нашей команды
                                {
                                    if (lFullCommand[pNumberCurrentItemStringForCheck] != ';')
                                    {
                                        lComand = lComand + lFullCommand[pNumberCurrentItemStringForCheck];
                                        if (lFullCommand[pNumberCurrentItemStringForCheck] == ')')
                                        {
                                            cout << lComand << endl;
                                            AnalizArgumentsOfComandCreate(lComand);
                                            if (ColumnExistence == 0)
                                            {
                                                cout << "Вы не добавили никаких столбцов в таблицу!" << endl;
                                            }
                                            if (lNameTable == "")
                                            {
                                                cout << "Вы не указали имя таблицы!" << endl;
                                            }
                                        }
                                    }
                                    pNumberCurrentItemStringForCheck++;
                                }
                            }
                        }
                    }
                }
                pNumberCurrentItemString++;
            }
        }
        else if (pComandString == lCommands[1])//команда Insert
        {
            cout << "Insert into your table!" << endl;
            while (lFullCommand[pNumberCurrentItemString])                           // пока не конец буфера
            {
                char endch = lFullCommand[lFullCommand.size() - 2];
                if (endch != ';')
                {
                    cout << "Вы не закончили команду с помощью символа ';'!" << endl;
                }
                if (lFullCommand[pNumberCurrentItemString] != ' ')
                {
                    lNameTable = lNameTable + lFullCommand[pNumberCurrentItemString];
                    if (lFullCommand[pNumberCurrentItemString + 1] == ' ' || lFullCommand[pNumberCurrentItemString + 1] == '\0' || lFullCommand[pNumberCurrentItemString + 1] == '(' && !HellperChek(lFullCommand[pNumberCurrentItemString + 1]))
                    {
                        cout << "The name table in which you insert data is " << lNameTable << endl;

                        lQuantityOfDatabaseElements++;

                        if (lFullCommand[pNumberCurrentItemString + 1] == '\0')
                        {
                            return 0;
                        }
                        if (lFullCommand[pNumberCurrentItemString + 1] == '(' || lFullCommand[pNumberCurrentItemString + 2] == '(')
                        {
                            if (lFullCommand[pNumberCurrentItemString + 1] == '(')
                            {
                                pNumberCurrentItemStringForCheck = pNumberCurrentItemString + 2;
                                while (lFullCommand[pNumberCurrentItemStringForCheck])                           // пока не конец нашей команды
                                {
                                    if (lFullCommand[pNumberCurrentItemStringForCheck] != ';')
                                    {
                                        lComand = lComand + lFullCommand[pNumberCurrentItemStringForCheck];
                                        if (lFullCommand[pNumberCurrentItemStringForCheck] == ')')
                                        {
                                            cout << lComand << endl;
                                            AnalizArgumentsOfComandInsert(lComand, lNameTable);
                                            if (lNameTable == "")
                                            {
                                                cout << "Вы не указали имя таблицы куда будут записыватся данные!" << endl;
                                            }
                                            return 0;
                                        }
                                    }
                                    pNumberCurrentItemStringForCheck++;
                                }
                            }
                            else if (lFullCommand[pNumberCurrentItemString + 2] == '(')
                            {
                                pNumberCurrentItemStringForCheck = pNumberCurrentItemString + 3;
                                while (lFullCommand[pNumberCurrentItemStringForCheck])                           // пока не конец нашей команды
                                {
                                    if (lFullCommand[pNumberCurrentItemStringForCheck] != ';')
                                    {
                                        lComand = lComand + lFullCommand[pNumberCurrentItemStringForCheck];
                                        if (lFullCommand[pNumberCurrentItemStringForCheck] == ')')
                                        {
                                            cout << lComand << endl;
                                            AnalizArgumentsOfComandInsert(lComand, lNameTable);
                                            if (lNameTable == "")
                                            {
                                                cout << "Вы не указали имя таблицы куда будут записыватся данные!" << endl;
                                            }
                                            return 0;
                                        }
                                    }
                                    pNumberCurrentItemStringForCheck++;
                                }
                            }
                        }
                    }
                }
                pNumberCurrentItemString++;
            }
        }
        else if (pComandString == lCommands[2])
        {

        }
        else if (pComandString == lCommands[3])
        {

        }
        else if (pComandString == lCommands[4])
        {

        }
        else if (pComandString == lCommands[5])
        {

        }
        else if (pComandString == lCommands[6])
        {

        }
        else if (pComandString == lCommands[7])
        {

        }
    }
}
int pIndex;
void AnaliseComand(char buffer[255])//функцыя анализа нашей строки
{
        while (buffer[pNumberCurrentItemString] && true)                           // пока не конец буфера проверяем нашу строку на возможные команды
        {
            if (buffer[pNumberCurrentItemString] != ' ')//пока не встретим пробел записуем елемент в строку и потом проверяем является ли ето одной из возможных команд
            {
                lTolowerComand = lTolowerComand + buffer[pNumberCurrentItemString];
                if (buffer[pNumberCurrentItemString + 1] == ' ')
                {
                    for (int index = 0; index < lTolowerComand.length(); ++index)         // меняем регистр именно для команды
                    {
                        while (lTolowerComand[pNumberCurrentItem])                           // пока не конец строки в которую записали команду
                        {
                            lCurrentItem = lTolowerComand[pNumberCurrentItem];
                            lTolowerCommandElementChar = tolower(lCurrentItem);
                            lTolowerCommand = lTolowerCommand + lTolowerCommandElementChar;//переводим всю строку в маленькие буквы для 100% коректного понимания програмы того что мы ввели
                            pNumberCurrentItem++;
                            if (pNumberCurrentItem == lTolowerComand.length())
                            {
                                lCurrentItem = lTolowerComand[pNumberCurrentItem];
                                lTolowerCommandElementChar = tolower(lCurrentItem);
                                lFullCommand = lTolowerCommand; // переводим команду в маленькие буквы для 100 % коректного понимания програмы того что мы ввели
                                std::cout << lTolowerCommand << endl;
                                pIndex = pNumberCurrentItemString + 1;
                                break;
                            }
                        }
                        if (pNumberCurrentItem == lTolowerComand.length()) break;
                    }
                    for (pIndex; pIndex <= strlen(buffer); pIndex++)
                    {
                        pFullCommand = pFullCommand + buffer[pIndex];
                    }
                    pNumberCurrentItemString++;
                    std::regex twoormorespaces(" [ ]+");
                    lFullCommand = lFullCommand + " " + pFullCommand;
                    cout << "Наша команда после обработки: " << endl << std::regex_replace(lFullCommand, twoormorespaces, " ") << endl;
                    pNumberCurrentItemString = size(lTolowerCommand);
                    check(lTolowerCommand);//добавить к толовер команд значения что идут после в буфере, что бы оно могло норм обработать их
                    break;
                }
            }
            pNumberCurrentItemString++;
        }
}
int main()
{
    setlocale(LC_ALL, "ru");
    SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
    SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывод

    // Просим пользователя ввести строку
    char buffer[255];
    std::cout << "Enter a string: ";
    std::cin.getline(buffer, 255);//записиваем то что мы вводили в командную строку в буфер
    AnaliseComand(buffer);//анализируем наш буфер
}


