#pragma once
//���������� ����������
#include <windows.h>
#include <map>
#include <vector>
#include "DatabaseInfo.h"//��������� ���� ���������� ��� ������������� ������� ��������� �����

using namespace std;
#pragma once
typedef vector< pair<string, string> > DatabaseString; // ������ ��������� �������� ��� ������, � ������ ������� ����� ������
//������ ������� -  ��� �������������� �������, ������ �� ����� � ������� �������� �������������� �������� � ��������� �� ������
typedef  vector < pair<string, map<string, map<int, DatabaseString*>>>> IndexedTable;
struct Node
{
    Node* next;
    string  TableName;          // ��� �������
    map<int, DatabaseString> DatabaseStringMap;//��� ������ ��������� �������� �������� ������� ����� ������
    IndexedTable lIndexedTable;
};
class DatabaseInsert
{
private:// ������������ ������� private
    Node* head, * tail;
    size_t cnt;
public:// ������������ ������� public
    DatabaseInsert(void) :head(NULL), tail(NULL), cnt(0) {}
    ~DatabaseInsert() { DeleteAllDatabases(); }
    Node* AddColumn(string pTableName, map<int, DatabaseString> pDatabaseStringMap);                                        //���������� 
    Node* Insert(Node* pos, map<int, DatabaseString> pDatabaseStringMap, string  pTableName);                                //������� ����� pos
    void AddAllElementsDatabase(DatabaseInsert& lDatabaseInsert, string pTableName, map<int, DatabaseString> pDatabaseStringMap);//���������� ���� ������� ����� ���� ������
    Node* Erase(Node* pos);             //�������� �� pos
    void DeleteFirstAddElement(void);   //�������� �� ������
    void DeleteLastAddElement(void);    //�������� �� ������ �� O(n) "������" ��������
    void DeleteAllDatabases(void);      //�������� ����

    void CenterString(string& pDatabaseColumnsInfo, const size_t& width);//������� ���������� ������� �� ������ ���������� ����������

    Node* begin(void);

    size_t size(void) const;
    bool  empty(void) const;
};



