#pragma once

#include <string>
#include <iostream>
#include "DatabaseInfo.h"
using namespace std;

//����� ��������������� ������� ������� ������������ �� ����� ������� ���� ������
//�������� �� ��������� ������ ;
bool CheckForTheLastCharacter(string pFullCommand);
//��������� �� ������������� ��
void DatabaseCheckExist(bool lCheck, string pNameTable);
//�������� �� �� ���������� �� ��� �������!
bool CheckForAvailability(string  pNameTable, const DatabaseInfo& pDatabaseInfo);
//�������� �� ������, �������� �� �� � ��������� ����������� ��������
bool HellperChek(char c);
