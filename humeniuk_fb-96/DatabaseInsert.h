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
#include <map>
#include <iterator>
#include "DatabaseInfo.h"//��������� ���� ���������� ��� ������������� ������� ��������� �����

using namespace std;
#pragma once
struct Node
{
    Node* next;
    string  DatabaseName;       // ��� ����������
    string  ColumnData;         // �������� �������
    int CounterOfLine;          // ������� ������
};
class DatabaseInsert
{
private:// ������������ ������� private
    Node* head, * tail;
    size_t cnt;
public:// ������������ ������� public
    DatabaseInsert(void) :head(NULL), tail(NULL), cnt(0) {}
    ~DatabaseInsert() { DeleteAllDatabases(); }
    Node* AddColumn(string pDatabaseName, string pColumnData, int pCounterOfLine);                                        //���������� 
    Node* Insert(Node* pos, string pDatabaseName, string pColumnData, int pCounterOfLine);                                //������� ����� pos
    void AddAllElementsDatabase(DatabaseInsert& lDatabaseInsert, int* pCounter, string pDatabaseName, string pColumnData);//���������� ���� ������� ����� ���� ������
    Node* Erase(Node* pos);             //�������� �� pos
    void DeleteFirstAddElement(void);   //�������� �� ������
    void DeleteLastAddElement(void);    //�������� �� ������ �� O(n) "������" ��������
    void DeleteAllDatabases(void);      //�������� ����

    void CenterString(string& pDatabaseColumnsInfo, const size_t& width);//������� ���������� ������� �� ������ ���������� ����������

    Node* begin(void);
    Node* begin(void) const;

    size_t size(void) const;
    bool  empty(void) const;
};



