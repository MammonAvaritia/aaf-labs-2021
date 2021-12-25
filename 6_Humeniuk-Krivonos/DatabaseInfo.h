#pragma once

//���������� ����������
#include <iostream>
#include <windows.h>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <list>
#include <cstdlib>
#include <cassert>
#include <deque>
#include "DatabaseInsert.h"//���������� ���� ������ ���������� ��� ��������� �������� ������ ������ ���������� � ������� ������ ����� ��

using namespace std;
struct Knot
{
    Knot* next;
    string  TableName;       // ��� �������
    string  ColumnName;     // ��� ������
    string  ColumnIndexationCheck;   // ��� ������
};
class DatabaseInfo
{
private:// ������������ ������� private
    Knot* head, * tail;
    size_t cnt;
public:// ������������ ������� public
    DatabaseInfo(void) :head(NULL), tail(NULL), cnt(0) {}
    ~DatabaseInfo() { DeleteAllDatabases(); }

    Knot* AddColumn(string pDatabaseName, string pDatabaseColumn, string pColumnTypeOfData);        //���������� 
    Knot* Insert(Knot* pos, string pTableName, string pColumnName, string pColumnTypeOfData);//������� ����� pos

    Knot* Erase(Knot* pos);             //�������� �� pos
    void DeleteFirstAddElement(void);   //�������� �� ������
    void DeleteLastAddElement(void);    //�������� �� ������ �� O(n) "������" ��������
    void DeleteAllDatabases(void);      //�������� ����
    void GetConsBuff(int& x, int& y);   //��������� �������� ���� ������� ��� ���������    
    void CenterString(string& pTableName, string& pDatabaseColumns, const size_t& width, string* pLastLine);        //������� ���������� ������� �� ������ ���������� ����������
    void ShowDatabase(string pDatabaseColumns, string pDatabaseName, string* pLastLine);                               //������� ����������� ���� ��������� ����� ��
    void FindAllDatabaseColumns(const DatabaseInfo& pDatabaseInfo, string pDatabaseName);         //����� ���� �������� ��
    //void RetreatForDatabaseColumns(map<int, string>* pColumns, map<int, int>* lMaxLengthInfo, string* pAllDatabaseColumns);
    string GoodLine(int pSizeOfLine, string* pLine, string pElement);                               //������� ������� ���������� ��� ������ ����� ���������� ���������
    
    Knot* begin(void) const;
    Knot* end  (void) const;

    size_t size(void) const;
    bool  empty(void) const;
};