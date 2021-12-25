#include "Checker.h"

//����� ��������������� ������� ������� ������������ �� ����� ������� ���� ������
//�������� �� ��������� ������ ;
bool CheckForTheLastCharacter(string pFullCommand)
{
    char endch = pFullCommand[pFullCommand.size() - 2];
    if (endch != ';') { std::cout << "�� �� ��������� ������� � ������� ������� ';'!" << endl; return 0; }
    else { return 1; }
}
//��������� �� ������������� �������
void DatabaseCheckExist(bool lCheck, string pNameTable)
{
    if (lCheck == 1)
    {
        cout << "������� � ������ " << pNameTable << " ��� ����������!" << endl;
    }
    if (lCheck == 0)
    {
        cout << "������� � ������ " << pNameTable << " �� ����������!" << endl;
    }
}
//�������� �� �� ���������� �� ��� �������!
bool CheckForAvailability(string  pNameTable, const DatabaseInfo& pDatabaseInfo)
{
    if (pDatabaseInfo.size() == 0) { return 0; }
    for (const Knot* p = pDatabaseInfo.begin(); p != NULL; p = p->next)
    {
        if (p->TableName == pNameTable) { return 1; }
        if (next(p) == next(pDatabaseInfo.end())) { return 0; }
    }
}
//�������� �� ������, �������� �� �� � ��������� ����������� ��������
bool HellperChek(char c)
{
    return isdigit(c) || ('a' <= c && c <= 'z');
}