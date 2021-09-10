#pragma once
#include<iostream>
#include<string>
#include<windows.h>
#include<conio.h>
#include<iomanip>
#include"dbCRUD.h"
#include"idGenerator.h"

using namespace std;

//Functions
void display(MYSQL_ROW row);
bool addDriver(MYSQL_ROW row);
void verifyDriver();
void removeDriver();
void showDriver();
void modifyDriver();

//Helper Function to customize data to be inserted
bool addDriver(MYSQL_ROW row) {
    bool qstate;
    int myid = generate_id("driver");
    vector<string> data;
    data.push_back(to_string(myid));
    for (int i = 1; i <= 14; i++)
    {
        string str = row[i];
        data.push_back(str);
    }
    qstate = insert(data, "driver");
    return qstate;
}

//Choice 1
void verifyDriver() {
    system("cls");
    MYSQL_ROW row;
    MYSQL_RES* res;

    res = readAll("pdriver");
    while (row = mysql_fetch_row(res))
    {
        system("cls");
        int choice;
        display(row);
        cout << "1. Successfully Verified \n";
        cout << "2. Verification Pending \n";
        cout << "3. Denied \n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            //add driver
            if (addDriver(row))
                cout << "Successfully Inserted Into Driver List \n";
            else {
                cout << "Failed to Insert into Driver List\n";
                Sleep(2000);
                continue;
            }
            Sleep(2000);
        }
        if (choice == 1 || choice == 3)
        {
            //remove driver
            bool qstate;
            string id = row[0];
            qstate = remove(id, "pdriver","id");

            if (qstate)
                cout << "Successfully Deleted from Pending List \n";
            else cout << "Failed to delete from Pending List\n";
            Sleep(2000);
        }
    }
    cout << "No Drivers Left To Be Verified \n";
    Sleep(2000);
}
//choice2
void removeDriver() {
    system("cls");
    int d_id, qstate;
    cout << "Driver ID to be removed? ";
    cin >> d_id;
    string id = to_string(d_id);

    if (remove(id,"driver","id"))
        cout << "Successfully Deleted.... \n";
    else cout << "Query failed: \n";
    Sleep(2000);
}
//choice3
void showDriver() {

    string id;
    MYSQL_ROW row;
    MYSQL_RES* res;
    system("cls");

    cout << "Enter Driver ID of the driver: ";
    cin >> id;
    system("cls");

    res = read(id,"driver","id");

    if (mysql_num_rows(res) == 0)
    {
        cout << "No Driver with Driver ID: " << id << "\n";
        Sleep(2000);
        return;
    }

    while (row = mysql_fetch_row(res))
        display(row);
    _getch();
}
//choice 4
void modifyDriver() {
    string id,column;
    int k, qstate;
    string nval;

    system("cls");

    cout << "Enter The Driver Id You want to modify: ";
    cin >> id;

    system("cls");

    //Display Column Name to choose
    cout << "What is to be modified? ";
    for (auto it : dtable)
        cout << it.first << ": " << it.second << "\n";
    cin >> k;
    auto it = dtable.find(k);
    column = (*it).second;

    cout << "New Value: ";
    cin >> nval;
    upper(nval);
    
    if (modify(id, "driver", column, nval,"id"))
        cout << "Successfully modified \n";
    else cout << "Unsuccessfull modification \n";
    Sleep(2000);
}