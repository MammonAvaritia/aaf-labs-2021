#include "InsertTable.h"
#include "Checker.h"
#include "Hellper.h"
typedef  map<int, string> IS_map;
typedef IS_map::iterator IS_Iterator;
typedef  map<string, int> SI_map;
typedef SI_map::iterator SI_Iterator;
// vector< pair<string, string> > - DatabaseString 
vector < pair<int, string>> AllIndexedColumns(DatabaseInfo* pDatabaseInfo, string pTableName)
{
    vector< pair<int, string> > lIndexedColumns;
    int lColumn = 1;
    for (Knot* lKnot = pDatabaseInfo->begin(); lKnot != NULL; lKnot = lKnot->next)
    {
        if (lKnot->TableName == pTableName)
        {
            if (lKnot->ColumnIndexationCheck == "INDEXED")
            {
                lIndexedColumns.push_back(pair<int, string>(lColumn, lKnot->ColumnName));
                lColumn++;
            }
        }
    }
    return lIndexedColumns;
}
//IndexedTable vector < pair<string, map<string, map<int, DatabaseString*>>>>
void IndexedNeededTable(DatabaseInfo* pDatabaseInfo, DatabaseInsert* pDatabaseInsert, DatabaseString pDatabaseString, string pTableName)
{
    IndexedTable lIndexedTable_1;
    vector< pair<int, string> > lIndexedColumns = AllIndexedColumns( pDatabaseInfo, pTableName);
    for (vector< pair<int, string> > ::iterator lICiterator = lIndexedColumns.begin(); lICiterator != lIndexedColumns.end(); lICiterator = next(lICiterator))//����� ������� � ��������
    {
        for (Node* lNode = pDatabaseInsert->begin(); lNode != NULL; lNode = lNode->next)//���� ���� �������
        {
            if (lNode->TableName == pTableName)//������� ���� ��������
            {
                //������� ���� ������, ��� ��� �� �� ���������, �� ����� ��� ��� ���������� ���������!
                map<int, DatabaseString>::iterator  lIterator = prev(lNode->DatabaseStringMap.end());
                for (DatabaseString::iterator lDatabaseString = lIterator->second.begin(); lDatabaseString != lIterator->second.end(); lDatabaseString = next(lDatabaseString))
                {
                    if (lDatabaseString->first == lICiterator->second)
                    {
                        if (lNode->lIndexedTable.begin() == lNode->lIndexedTable.end())
                        {
                            map<int, DatabaseString* > lDatabaseStringIndex;
                            lDatabaseStringIndex.insert(make_pair(1, &lIterator->second));
                            map<string, map<int, DatabaseString*>> lNeeded;
                            lNeeded.insert(make_pair(lDatabaseString->second, lDatabaseStringIndex));
                            lNode->lIndexedTable.push_back(pair<string, map<string, map<int, DatabaseString*>>>(lDatabaseString->first, lNeeded));
                            if (next(lICiterator) == lIndexedColumns.end()) { return; }
                        }
                        else {
                            bool lExit = 0;
                            for (IndexedTable::iterator lIndexedTable_1 = lNode->lIndexedTable.begin(); lIndexedTable_1 != lNode->lIndexedTable.end(); lIndexedTable_1 = next(lIndexedTable_1))
                            {
                                if (lIndexedTable_1->first == lDatabaseString->first)
                                {
                                    map<string, map<int, DatabaseString*>>::iterator lIndexedTable_1_1;
                                    for (lIndexedTable_1_1 = (lIndexedTable_1->second).begin(); lIndexedTable_1_1 != (lIndexedTable_1->second).end(); lIndexedTable_1_1 = next(lIndexedTable_1_1))
                                    {
                                        if (lIndexedTable_1_1->first == lDatabaseString->second)
                                        {
                                            lIndexedTable_1_1->second.insert(make_pair(prev(lIndexedTable_1_1->second.end())->first + 1, &lIterator->second));
                                            lExit = 1;
                                            if (next(lICiterator) == lIndexedColumns.end()) { return; }
                                            break;
                                        }
                                        else if (next(lIndexedTable_1_1) == (lIndexedTable_1->second).end())
                                        {
                                            map<int, DatabaseString* > lDatabaseStringIndex;
                                            lDatabaseStringIndex.insert(make_pair(1, &lIterator->second));
                                            lIndexedTable_1->second.insert(make_pair(lDatabaseString->second, lDatabaseStringIndex));
                                            lExit = 1;
                                            if (next(lICiterator) == lIndexedColumns.end()) { return; }
                                            break;
                                        }
                                    }
                                }
                                if (lExit == 1) { break; }
                                else if (next(lIndexedTable_1) == lNode->lIndexedTable.end())
                                {
                                    map<int, DatabaseString* > lDatabaseStringIndex;
                                    lDatabaseStringIndex.insert(make_pair(1, &lIterator->second));
                                    map<string, map<int, DatabaseString*>> lNeeded;
                                    lNeeded.insert(make_pair(lDatabaseString->second, lDatabaseStringIndex));
                                    lNode->lIndexedTable.push_back(pair<string, map<string, map<int, DatabaseString*>>>(lDatabaseString->first, lNeeded));
                                    if (next(lICiterator) == lIndexedColumns.end()) { return; }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
void AnalizArgumentsOfComandInsert(string pComand, string pTableName, DatabaseInfo *pDatabaseInfo, DatabaseInsert *pDatabaseInsert, SI_map *TablesLinesInfo)
{
    int lNumberCurrentItemStringCommand = 0, NumberColumn = 1;
    string  NameVariable = ""; //�� ���� �� ���������� ��� �������
    bool NameColumn = 1;
    IS_map DatabaseInsert, lDatabaseColumnsName, lColumns;
    SI_Iterator lIterator = TablesLinesInfo->find(pTableName);
    DatabaseInfo DatabaseColumns;
    DatabaseString lDatabaseString;
    FindAllDatabaseColumns_1(pDatabaseInfo, pTableName, &lColumns, &DatabaseColumns, lDatabaseColumnsName);//������� ��� ��������� ������� � ����� ������ ��
    map<int, string> ::iterator lColumnslIterator = lColumns.begin();
    if (lIterator == TablesLinesInfo->end()) { TablesLinesInfo->insert(make_pair(pTableName, 1)); lIterator = TablesLinesInfo->find(pTableName); }
    else { lIterator->second++; }
    while (pComand[lNumberCurrentItemStringCommand + 1])// ���� �� ����� ������
    {
        if (pComand[lNumberCurrentItemStringCommand] != ' ' && NameColumn && pComand[lNumberCurrentItemStringCommand] != ',')
        {
            if (pComand[lNumberCurrentItemStringCommand] != '"')
            {
                NameVariable = NameVariable + pComand[lNumberCurrentItemStringCommand];
                if (pComand[lNumberCurrentItemStringCommand + 1] == ' ' || pComand[lNumberCurrentItemStringCommand + 1] == ',' || pComand[lNumberCurrentItemStringCommand + 1] == ')' || pComand[lNumberCurrentItemStringCommand + 1] == '\"')
                {
                    if ((pComand[lNumberCurrentItemStringCommand + 1] == '\"') || (pComand[lNumberCurrentItemStringCommand + 1] == '\"' && (pComand[lNumberCurrentItemStringCommand + 2] == ',' || pComand[lNumberCurrentItemStringCommand + 2] == ')' || pComand[lNumberCurrentItemStringCommand + 3] == ',' || pComand[lNumberCurrentItemStringCommand + 3] == ')')))
                    {
                        std::cout << "You insert in table " << pTableName << "; column number " << NumberColumn << " has this value " << NameVariable << endl;
                        lDatabaseString.push_back(pair<string, string>(lColumnslIterator->second, NameVariable));
                        NumberColumn++;
                        NameVariable.clear();
                        lColumnslIterator = next(lColumnslIterator);
                    }
                }
            }
        }
        lNumberCurrentItemStringCommand++;
    }
    int lSizeTable = 0;
    for (Knot* lKnot = pDatabaseInfo->begin(); lKnot != NULL; lKnot = lKnot->next)
    {
        if (lKnot->TableName == pTableName) { lSizeTable++; }
    }
    if (lSizeTable != lDatabaseString.size())
    {
        if (lSizeTable > lDatabaseString.size()) { cout << "�� ��������� �������� �� ��� ���� �������� ������� " << pTableName << "!\n"; }
        else cout << "�� ����� �������� ������, ��� ���������� ������� ������� ���������� � ������� " << pTableName << "!\n";
        cout << " �� ����� �������� ��� " << lDatabaseString.size() << " �������, � � ��� � �� ���������� " << lSizeTable << " �������!" << endl;
        return;
    }
    if (pDatabaseInsert->begin() == NULL)
    {
        map<int, DatabaseString> lDatabaseStringMap;
        lDatabaseStringMap.insert(make_pair(1, lDatabaseString));
        pDatabaseInsert->AddColumn(pTableName, lDatabaseStringMap);
        IndexedNeededTable(pDatabaseInfo, pDatabaseInsert, lDatabaseString, pTableName);
        return;
    }
    for (Node* lNode = pDatabaseInsert->begin(); lNode != NULL; lNode = lNode->next)//���� ���� �������
    {
        if      (lNode->TableName == pTableName)
        {
            lNode->DatabaseStringMap.insert(make_pair(prev(lNode->DatabaseStringMap.end())->first + 1, lDatabaseString));
            IndexedNeededTable(pDatabaseInfo, pDatabaseInsert, lDatabaseString, pTableName);
        }
        else if (lNode == NULL || lNode->next == NULL)
        {
            map<int, DatabaseString> lDatabaseStringMap;
            lDatabaseStringMap.insert(make_pair(1, lDatabaseString));
            pDatabaseInsert->AddColumn(pTableName, lDatabaseStringMap);
            IndexedNeededTable(pDatabaseInfo, pDatabaseInsert, lDatabaseString, pTableName);
            return;
        }
    }
}
int InsertTableHellper(string pFullCommand, int pNumberCurrentItemStringForCheck, string pNameTable, DatabaseInfo* pDatabaseInfo, DatabaseInsert* pDatabaseInsert, SI_map *TablesLinesInfo)
{
    string lComand = "";
    while (pFullCommand[pNumberCurrentItemStringForCheck])                           // ���� �� ����� ����� �������
    {
        if (pFullCommand[pNumberCurrentItemStringForCheck] != ';')
        {
            lComand = lComand + pFullCommand[pNumberCurrentItemStringForCheck];
            if (pFullCommand[pNumberCurrentItemStringForCheck] == ')')
            {
                std::cout << lComand << endl;
                AnalizArgumentsOfComandInsert(lComand, pNameTable, pDatabaseInfo, pDatabaseInsert, TablesLinesInfo);
                if (pNameTable == "")
                {
                    std::cout << "�� �� ������� ��� ������� ���� ����� ����������� ������!" << endl;
                }
                return 0;
            }
        }
        pNumberCurrentItemStringForCheck++;
    }
}
int InsertTable(string pFullCommand, int pNumberCurrentItemString, DatabaseInfo* pDatabaseInfo, DatabaseInsert *pDatabaseInsert, SI_map *TablesLinesInfo)
{
    string  lNameTable = "", lComand;// ��������� ���������� ������� ���������� ��� �������� ������� �� ���������� ���������
    int lNumberCurrentItemStringForCheck = 0;// ������ �������� ������

    while (pFullCommand[pNumberCurrentItemString])                           // ���� �� ����� ������
    {
        bool lCheckLastSymphol = CheckForTheLastCharacter(pFullCommand);
        if (lCheckLastSymphol == 0) { return 0; }
        if (pFullCommand[pNumberCurrentItemString] != ' ')
        {
            lNameTable = lNameTable + pFullCommand[pNumberCurrentItemString];
            if (pFullCommand[pNumberCurrentItemString + 1] == ' ' || pFullCommand[pNumberCurrentItemString + 1] == '\0' || pFullCommand[pNumberCurrentItemString + 1] == '(' && !HellperChek(pFullCommand[pNumberCurrentItemString + 1]))
            {
                std::cout << "The name table in which you insert data is " << lNameTable << "!" << endl;
                bool lCheck = CheckForAvailability(lNameTable, *pDatabaseInfo);
                DatabaseCheckExist(lCheck, lNameTable);
                if (lCheck == 0) { break; }
                if (pFullCommand[pNumberCurrentItemString + 1] == '\0') { break; return 0; }
                if (pFullCommand[pNumberCurrentItemString + 1] == '(' || pFullCommand[pNumberCurrentItemString + 2] == '(')
                {
                    if (pFullCommand[pNumberCurrentItemString + 1] == '(')
                    {
                        lNumberCurrentItemStringForCheck = pNumberCurrentItemString + 2;
                        InsertTableHellper(pFullCommand, lNumberCurrentItemStringForCheck, lNameTable, pDatabaseInfo, pDatabaseInsert, TablesLinesInfo);
                        return 0;
                    }
                    else if (pFullCommand[pNumberCurrentItemString + 2] == '(')
                    {
                        lNumberCurrentItemStringForCheck = pNumberCurrentItemString + 3;
                        InsertTableHellper(pFullCommand, lNumberCurrentItemStringForCheck, lNameTable, pDatabaseInfo, pDatabaseInsert, TablesLinesInfo);
                        return 0;
                    }
                }
            }
        }
        pNumberCurrentItemString++;
    }
}