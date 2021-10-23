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
int pNumberCurrentItem = 0, pNumberCurrentItemString = 0, pNumberCurrentItemStringForCheck, pNumberCurrentItemStringCommand=0;                               // индекс символов строки
char lCurrentItem;                                        // поточный елемент в строке
string  lString1, lString2, lString3, NameVariable;// раздичные переменные которые используем для проверки команды на правильную структуру
char lTolowerBuffer[255];                                      // выведенный буфер
string lTolowerBufferString;//строка в которую будем записивать буфер для проверки на последний елемент
string** database;
int NumberColumn=1;
int lQuantityOfDatabaseElements = 0;
bool NameColumn=1;
bool ColumnExistence = 0;
typedef std::map<string, string> ColumnStructure;//конструктор который имеет в себе имя самого столбца и тип данных который он сохраняет
typedef std::map<string, ColumnStructure> Database;//база данных всех бд что у нас существуют, где 1 колонка ето имя бд с которой взят стобец, вторая ето имя самого столбца и 3 тип данных
typedef std::map<int, string> NameOfDatabase;//конструктор всех существующих базданных

string** RequestMemory(int pNumberOfLines, int pNumberOfColumns)
{
    string** arr = (string**)malloc(pNumberOfLines * sizeof(string*));
    for (int i = 0; i < pNumberOfLines; i++)
        arr[i] = (string*)malloc(pNumberOfColumns * sizeof(string));
    return arr;
}
void AnalizArgumentsOfComand(string pComand)
{
    while (pComand[pNumberCurrentItemStringCommand])// пока не конец строки
    {
        if (pComand[pNumberCurrentItemStringCommand] != ' ' && NameColumn)
        {
            NameVariable = NameVariable + pComand[pNumberCurrentItemStringCommand];
            if (pComand[pNumberCurrentItemStringCommand+1] == ' ' )
            {
                cout << "Column number " << NumberColumn << " has this name " << NameVariable << endl;
                NumberColumn++;
                NameColumn = 0;
                ColumnExistence = 1;
            }
        }
        pNumberCurrentItemStringCommand++;
    }
}
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
    string lCommands[lNumberOfCommands] = { "create", "indexed", "insert",
    "select", "where", "left_join", "full_join","join","order_by" };

    for (int pNumberOfCommands = 0; pNumberOfCommands < lNumberOfCommands; pNumberOfCommands++) // Проверка на то являеться ли полученая строка одной из команд. если да то выполняем действия етой команды
    {
        if (pComandString == lCommands[0])
        {
            cout << "Create your table" << endl;
            while (lTolowerBuffer[pNumberCurrentItemString])                           // пока не конец буфера
            {
                std::string lTolowerBufferString(lTolowerBuffer);
                char endch = lTolowerBufferString.back();
                if (endch != ';')
                {
                    cout << "Вы не закончили команду с помощью символа ';'!" << endl;
                    goto breakEndCommandError;
                }
                if (lTolowerBuffer[pNumberCurrentItemString] != ' ')
                {
                    lString2 = lString2 + lTolowerBuffer[pNumberCurrentItemString];
                    if (lTolowerBuffer[pNumberCurrentItemString + 1] == ' ' || lTolowerBuffer[pNumberCurrentItemString + 1] == '\0' || lTolowerBuffer[pNumberCurrentItemString + 1] == '(' && !HellperChek(lTolowerBuffer[pNumberCurrentItemString + 1]))
                    {
                        cout << "The name of your table is " << lString2 << endl;

                        lQuantityOfDatabaseElements++;

                        if (lTolowerBuffer[pNumberCurrentItemString + 1] == '\0')
                        {
                            return 0;
                        }
                        if (lTolowerBuffer[pNumberCurrentItemString + 1] == '(')
                        {
                            pNumberCurrentItemStringForCheck = pNumberCurrentItemString + 1+1;
                            while (lTolowerBuffer[pNumberCurrentItemStringForCheck])                           // пока не конец буфера
                            {
                                if (lTolowerBuffer[pNumberCurrentItemStringForCheck] != ',')
                                {
                                    lString3 = lString3 + lTolowerBuffer[pNumberCurrentItemStringForCheck];
                                    if (lTolowerBuffer[pNumberCurrentItemStringForCheck + 1] == ',' || lTolowerBuffer[pNumberCurrentItemStringForCheck + 1] == ')' )
                                    {
                                        cout << lString3 <<endl;
                                        AnalizArgumentsOfComand(lString3);
                                        if (ColumnExistence == 0)
                                        {
                                            cout << "Вы не добавили никаких столбцов в таблицу!" << endl;
                                            goto breakColumnExistence;
                                        }
                                        if (lString2 == "")
                                        {
                                            cout << "Вы не указали имя таблицы!" << endl;
                                            goto breakNoTableName;
                                        }
                                        goto breakAll;
                                    }
                                }
                                pNumberCurrentItemStringForCheck++;
                            }
                        }
                    }
                }
                pNumberCurrentItemString++;
            }
        }
        else if (pComandString == lCommands[1])
        {

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
breakAll:
    {        
        puts("I'm finish analiz your comand!");
    }
breakEndCommandError:
    {
        puts("End command error!");
    }
breakColumnExistence:
    {
        puts("Column existence error!");
    }
breakNoTableName:
    {
        puts("No table name");
    }
}
void AnaliseComand(char buffer[255])//функцыя анализа нашей строки
{
    // Перебираем каждый символ, который ввел пользователь
    for (int index = 0; index < strlen(buffer); ++index)         // Делаем вс
    {
        while (buffer[pNumberCurrentItem])                           // пока не конец буфера
        {
            lCurrentItem = buffer[pNumberCurrentItem];
            lTolowerBuffer[pNumberCurrentItem] = tolower(lCurrentItem);//переводим всю строку в маленькие буквы для 100% коректного понимания програмы того что мы ввели 
            pNumberCurrentItem++;
            if (pNumberCurrentItem == strlen(buffer))
            {
                lCurrentItem = buffer[pNumberCurrentItem];
                lTolowerBuffer[pNumberCurrentItem] = tolower(lCurrentItem);
                lTolowerBuffer[pNumberCurrentItem + 1] = '\0';
                std::cout << lTolowerBuffer << endl;
            }
        }
    }
    for (int pIndex = 0; pIndex < strlen(lTolowerBuffer); ++pIndex)
    {
        while (lTolowerBuffer[pNumberCurrentItemString])                           // пока не конец буфера проверяем нашу строку на возможные команды
        {

            if (lTolowerBuffer[pNumberCurrentItemString] != ' ')//пока не встретим пробел записуем елемент в строку и потом проверяем является ли ето одной из возможных команд
            {
                lString1 = lString1 + lTolowerBuffer[pNumberCurrentItemString];
                if (lTolowerBuffer[pNumberCurrentItemString + 1] == ' ')
                {
                    pNumberCurrentItemString++;
                    check(lString1);
                }
            }
            pNumberCurrentItemString++;

        }
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
    std::cin.getline(buffer, 255);//записиваем строку в буфер
    AnaliseComand(buffer);//анализируем буфер
}


