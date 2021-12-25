#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <map>
#include <algorithm>
#include <iterator>
#include "DatabaseInfo.h"
#include "DatabaseInsert.h"
using namespace std;
//����� ���� ��� ������ ��
void CoutDatabaseInsert(DatabaseInsert* pDatabaseInsert);
//������� ���������� ���������� ����� � ��
int LastLineInfo(DatabaseInsert* pDatabaseInsert);
//����� ������ ���� ��� �� ������� � ��
void FindAllDatabaseInsert(DatabaseInsert* pDatabaseInsert, map<int, string> pTableName, DatabaseInsert* pDatabaseColumnsInsert, map<string, string> lCondition, string ConditionSign, string pChecker);
//������� ������� ���� ������� � ���� ������
vector< pair<string, int> > CountinSize(map<int, string>* pColumns);
//������� ��������� ������� ��������� �������� � ��
vector< pair<string, int> > FindLength(DatabaseInsert* pDatabaseInsert, map<int, string>* pColumns);
//������� ��������� ������� ��������� �������� � �� � ���������� �������� ������� ��
vector< pair<string, int> > CheckLength(vector< pair<string, int> >* pLengthColumn, vector < pair<string, int>>* pLengthInfo);
//��������� ����� � ��������
void RetreatForDatabaseColumns(map<int, string>* pColumns, vector< pair<string, int> >* lMaxLengthInfo, string* pAllDatabaseColumns);
//��������� ����� � �������� ��� ������ ��
void RetreatForDatabaseInfo(DatabaseInsert* pDatabaseInsert, vector< pair<string, int> >* lMaxLengthInfo, map<int, string>* pAllDatabaseColumnsInsert);
//�������� ����� �������� ����� ��
void  OutDatabaseInsert(map<int, string>* lColumnsInfo, map<int, int>* pMaxLengthInfo, DatabaseInsert* pDatabaseInsert);
//�������� �� ������ ���������� ��������� ������
void CgeckingVeluesOfInsert(DatabaseInsert* pDatabaseInsert, int pQuontityColumns, bool* pValue);
//������ �� � ��������� � �������� (�������� ���������)
void PrintOurDatabase(DatabaseInfo* pDatabaseColumns, DatabaseInsert* pDatabaseInsert, map<int, string>* pColumns);
//������� ������� ����� � ���� ��� ������� ���� � ������� ���� �������
void PrintOurDatabaseHellper(DatabaseInfo* pDatabaseInfo, DatabaseInsert* pDatabaseInsert, vector< pair<string, string> > lTableVector, map<int, string> pDatabaseColumnsName);
//������� ������ �� �� �����
void PrintOutDatabaseInfoHellper(vector< pair<string, string> > lTableVector, bool lCheck, map<int, string> pDatabaseColumnsName, DatabaseInfo *gDatabaseInfo, DatabaseInsert *gDatabaseInsert);
//������� ��������� ������� �����
void PrintOutDatabaseInfo(string pFullCommand, int pNumberCurrentItemString, DatabaseInfo* pDatabaseInfo, DatabaseInsert* pDatabaseInsert);
