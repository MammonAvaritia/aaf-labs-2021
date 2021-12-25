#include "Parser.h"

string GetName(string pFullCommand, int lLength)
{
    string lTableNme = "";
    for (int i = 0; pFullCommand[lLength + i + 2] != ';'; i++)
    {
        lTableNme = lTableNme + pFullCommand[lLength + i + 2];
    }
    return lTableNme;
}
void check(string pComandString, string pFullCommand, int pNumberCurrentItemString , DatabaseInfo *pDatabaseInfo, DatabaseInsert *pDatabaseInsert, map <string, int> *TablesLinesInfo)
{
    // ������ ����� ���� string
    // 1. ������������� ������� ����� ��������� ������� �������
    const int lNumberOfCommands = 6;
    string lCommands[lNumberOfCommands] = { "create", "insert", "select","delete","print","exit" };

    for (int pNumberOfCommands = 0; pNumberOfCommands < lNumberOfCommands; pNumberOfCommands++) // �������� �� �� ��������� �� ��������� ������ ����� �� ������. ���� �� �� ��������� �������� ���� �������
    {
        if (pComandString == lCommands[0])//������� Create
        {
            cout << "Create your table" << endl;
            CreateTable(pFullCommand, pNumberCurrentItemString, pDatabaseInfo);
            break;
            return;
        }
        else if (pComandString == lCommands[1])//������� Insert
        {
            cout << "Insert into your table!" << endl;
            InsertTable(pFullCommand, pNumberCurrentItemString, pDatabaseInfo, pDatabaseInsert, TablesLinesInfo);
            break;
            return;
        }
        else if (pComandString == lCommands[2])
        {
            cout << "Select your values!" << endl;
            SelectTable(pFullCommand, pNumberCurrentItemString, pDatabaseInfo, pDatabaseInsert);
            break;
            return;
        }
        else if (pComandString == lCommands[3])
        {
            string lTableNme = GetName(pFullCommand, pComandString.length());
            DeleteTable(lTableNme, pDatabaseInfo, pDatabaseInsert);
            break;
            return;
        }
        else if (pComandString == lCommands[4])
        {
            PrintOutDatabaseInfo(pFullCommand, pNumberCurrentItemString, pDatabaseInfo, pDatabaseInsert);
            break;
            return;
        }
        else if (pComandString == lCommands[5])
        {
            system("pause");
        }
    }
}
//����������� ������� 
void AnaliseComand(char buffer[255], DatabaseInfo* pDatabaseInfo, DatabaseInsert* pDatabaseInsert, map <string, int>* TablesLinesInfo)//������� ������� ����� ������
{
    string lFullCommand = "", pFullCommand = "", lTolowerComand;
    int lNumberCurrentItemString = 0, pNumberCurrentItem = 0, pIndex = 0;
    char lCurrentItem;              // �������� ������� � ������
    char lTolowerCommandElementChar;// ��������� � ������� �� ���������� ������� �������
    string lTolowerCommand;         // ������ � ������� ���������� �������� ������������ �������

    while (buffer[lNumberCurrentItemString] && true)                           // ���� �� ����� ������ ��������� ���� ������ �� ��������� �������
    {
        if (buffer[lNumberCurrentItemString] != ' ')//���� �� �������� ������ �������� ������� � ������ � ����� ��������� �������� �� ��� ����� �� ��������� ������
        {
            lTolowerComand = lTolowerComand + buffer[lNumberCurrentItemString];
            if (buffer[lNumberCurrentItemString + 1] == ' ' || buffer[lNumberCurrentItemString + 1] == ';')
            {
                for (int index = 0; index < lTolowerComand.length(); ++index)         // ������ ������� ������ ��� �������
                {
                    //� ������ ������� ��� ������ ����
                    while (lTolowerComand[pNumberCurrentItem])                        // ���� �� ����� ������ � ������� �������� �������
                    {
                        lCurrentItem = lTolowerComand[pNumberCurrentItem];
                        lTolowerCommandElementChar = tolower(lCurrentItem);
                        lTolowerCommand = lTolowerCommand + lTolowerCommandElementChar;//��������� ��� ������ � ��������� ����� ��� 100% ���������� ��������� �������� ���� ��� �� �����
                        pNumberCurrentItem++;
                        if (pNumberCurrentItem == lTolowerComand.length())
                        {
                            lCurrentItem = lTolowerComand[pNumberCurrentItem];
                            lTolowerCommandElementChar = tolower(lCurrentItem);
                            lFullCommand = lTolowerCommand;                             // ��������� ������� � ��������� ����� ��� 100 % ���������� ��������� �������� ���� ��� �� �����
                            std::cout << lTolowerCommand << endl;
                            pIndex = lNumberCurrentItemString + 1;
                            break;
                        }
                    }
                    if (pNumberCurrentItem == lTolowerComand.length()) break;
                }
                for (pIndex; pIndex <= strlen(buffer); pIndex++)
                {
                    pFullCommand = pFullCommand + buffer[pIndex];
                }
                lNumberCurrentItemString++;
                std::regex twoormorespaces(" [ ]+");
                lFullCommand = lFullCommand + " " + pFullCommand;
                cout << "���� ������� ����� ���������: " << endl << std::regex_replace(lFullCommand, twoormorespaces, " ") << endl;
                lNumberCurrentItemString = size(lTolowerCommand);
                check(lTolowerCommand, lFullCommand, lNumberCurrentItemString, pDatabaseInfo, pDatabaseInsert, TablesLinesInfo);//�������� � ������� ������ �������� ��� ���� ����� � ������, ��� �� ��� ����� ���� ���������� ��
                break;
            }
        }
        lNumberCurrentItemString++;
    }
}