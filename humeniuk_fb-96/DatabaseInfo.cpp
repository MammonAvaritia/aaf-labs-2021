#include "DatabaseInfo.h"

//������� ������� ���������� ��� ������ ����� ���������� ���������
string DatabaseInfo::GoodLine(int pSizeOfLine, string* pLine, string pElement)
{
    for (int i = 0; i < pSizeOfLine; i++)
    {
        *pLine = *pLine + pElement;
    }
    return *pLine;
}
//���������� 
Knot* DatabaseInfo::AddColumn(string pDatabaseName, string pDatabaseColumn, string pColumnTypeOfData) {
    Knot* NewNode = new (std::nothrow) Knot();
    if (NewNode != NULL) {
        NewNode->DatabaseName = pDatabaseName;          // ������������� ����� �� ���� ���������� ����� �������
        NewNode->DatabaseColumn = pDatabaseColumn;       // ������������� ����� �������
        NewNode->ColumnTypeOfData = pColumnTypeOfData;   // ������������� ���� ������ �������

        NewNode->next = NULL;

        if (head == NULL)
            head = tail = NewNode;
        else
            tail = tail->next = NewNode;
        ++cnt;
    }
    return NewNode;
}

//������� ����� pos
Knot* DatabaseInfo::Insert(Knot* pos, string pDatabaseName, string pDatabaseColumn, string pColumnTypeOfData) {
    if (pos == NULL)
        return pos;

    Knot* x = head, * y = head;
    while (x != pos) {
        y = x;
        x = x->next;
    }

    Knot* NewNode = new (std::nothrow) Knot();
    if (NewNode != NULL) {
        NewNode->DatabaseName = pDatabaseName;          // ������������� ����� �� ���� ���������� ����� �������
        NewNode->DatabaseColumn = pDatabaseColumn;       // ������������� ����� �������
        NewNode->ColumnTypeOfData = pColumnTypeOfData;   // ������������� ���� ������ �������

        if (pos == head) {
            NewNode->next = head;
            head = NewNode;
        }
        else {
            NewNode->next = pos;
            y->next = NewNode;
        }
        ++cnt;
    }
    return pos;
}

//�������� �� pos
Knot* DatabaseInfo::Erase(Knot* pos) {
    if (pos == NULL)
        return pos;
    else if (pos == head) {
        head = head->next;
        if (head == NULL)
            tail = NULL;
    }
    else {
        Knot* x = head, * y = head;
        while (x != pos) {
            y = x;
            x = x->next;
        }
        y->next = pos->next;

        if (pos == tail)
            tail = y;
    }

    Knot* p = pos->next;
    delete pos;
    --cnt;
    return p;
}

//�������� �� ������
void DatabaseInfo::DeleteFirstAddElement(void) { Erase(head); }

//�������� �� ������ �� O(n) "������" ��������
void DatabaseInfo::DeleteLastAddElement(void) { Erase(tail); }

//�������� ����
void DatabaseInfo::DeleteAllDatabases(void) {
    Knot* t;
    while (head != NULL) {
        t = head;
        head = head->next;
        delete t;
    }
    tail = NULL;
    cnt = 0;
}

//��������� �������� ���� ������� ��� ���������    
void DatabaseInfo::GetConsBuff(int& x, int& y)
{
    HANDLE hWndConsole;        //��� � �������� ���������� �������, � ����� ������������� ����������� hWndConsole, �� ��� ��������� ���������� � �������
    if (hWndConsole = GetStdHandle(-12))
    {
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;            //����������, ������� ����� ������� ��� ���������� � �������
        if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo))            //������ ��������� ���������� � ������� �� �����������
        {
            //���� ������� ���� �������
            //x - ��������, y - ���������(����� �������)
            x = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
            y = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
        }
        else
            printf("Error: %d\n", GetLastError());//����� ������ ���� ���-�� ������ �� ���
    }
    else
        printf("Error: %d\n", GetLastError());//����� ������ ���� ���-�� ������ �� ���
}

//������� ���������� ������� �� ������ ���������� ����������
void DatabaseInfo::CenterString(string& pDatabaseName, string& pDatabaseColumns, const size_t& width, string* pLastLine)//Width ����� ������ ������ ���� ��� ����� ��������� �� �����, � ������ ������ ������ ������ ��� ���� �������� 5 - ����� ��������� �� 5 �������� � ����� ������
{
    int buffer_x_size, buffer_y_size;                                               //�������� ������� ���� �������
    string IndentForDatabaseName = "";
    string RightIndentForDatabaseName = "";
    string lLastLine = "";
    string lLeftBordForColumns = "";
    GetConsBuff(buffer_x_size, buffer_y_size);
    size_t LeftBordForColumns = (buffer_x_size - width) / 2.;                                           //������������� ����� ������
    size_t LeftBordForDatabaseName = (width - pDatabaseName.length()) / 2.;                             //������������� ����� ������ ��� ����� ��
    size_t RightBordForDatabaseName = width - LeftBordForDatabaseName - pDatabaseName.length();         //������������� ������ ������ ��� ����� ��

    GoodLine(LeftBordForDatabaseName, &IndentForDatabaseName, "-");
    GoodLine(RightBordForDatabaseName, &RightIndentForDatabaseName, "-");
    GoodLine(width, &lLastLine, "-");

    for (;;)        //������ ����������� ����
    {
        cout << setw(LeftBordForColumns) << "";                                         //����� ������ � ����
        cout << setw(LeftBordForDatabaseName) << IndentForDatabaseName;                 //����� ������ ����� ������ � ����
        cout << pDatabaseName.substr(0u, width);                                        //��������� ��������� � ����� � �� �������
        cout << setw(LeftBordForDatabaseName) << RightIndentForDatabaseName << endl;    //������ ������ ����� ����� � ����
        pDatabaseName.erase(pDatabaseName.begin(), pDatabaseName.begin() + (pDatabaseName.size() < width ? pDatabaseName.size() : width));
        //���� ������ ��� ��������� - ����������� ����������� ���� break;
        if (pDatabaseName.empty())
        {
            break;
        }
    }
    for (int lCounter = 0; lCounter < LeftBordForColumns; lCounter++)//�������� ������
    {
        lLeftBordForColumns = lLeftBordForColumns + " ";
    }
    *pLastLine = lLeftBordForColumns + lLastLine + "\n";//�������� ��������� ������
    for (;;)        //������ ����������� ����
    {
        //����� ������ � ����
        //cout.fill(' '); �� ���������
        cout << setw(LeftBordForColumns) << "";
        //��������� ��������� � ����� � �� �������
        cout << pDatabaseColumns.substr(0u, width) << endl;
        cout << setw(LeftBordForColumns) << "" << lLastLine << endl;
        //�������� �� ������ ��� �����, ��� ������ �� �������
        //(s.size() < width ? s.size() : width) ����� �� ����� �� ������� ���������� - ��������
        pDatabaseColumns.erase(pDatabaseColumns.begin(), pDatabaseColumns.begin() + (pDatabaseColumns.size() < width ? pDatabaseColumns.size() : width));
        //���� ������ ��� ��������� - ����������� ����������� ���� break;
        if (pDatabaseColumns.empty())
        {
            break;
        }
    }
}

//������� ����������� ���� ��������� ����� ��
void DatabaseInfo::ShowDatabase(string pDatabaseColumns, string pDatabaseName, string* pLastLine)
{
    setlocale(LC_ALL, "rus"); // ��������� ������
    cout << "���� ������ �������� ���: " << endl;
    CenterString(pDatabaseName, pDatabaseColumns, pDatabaseColumns.length(), pLastLine);
}

//����� ���� �������� ��
void DatabaseInfo::FindAllDatabaseColumns(const DatabaseInfo& pDatabaseInfo, string pDatabaseName)
{
    string DatabaseColumns = "";
    for (const Knot* p = pDatabaseInfo.begin(); p != NULL; p = p->next)
    {
        if (p->DatabaseName == pDatabaseName)
        {
            DatabaseColumns = DatabaseColumns + "|" + p->DatabaseColumn;
        }
    }
    DatabaseColumns = DatabaseColumns + "|";
    string lLastLine = "";
    ShowDatabase(DatabaseColumns, pDatabaseName,&lLastLine);
}

Knot* DatabaseInfo::begin(void) { return head; }
Knot* DatabaseInfo::begin(void) const { return head; }

size_t DatabaseInfo::size(void) const { return cnt; }
bool  DatabaseInfo::empty(void) const { return (head == NULL); }
