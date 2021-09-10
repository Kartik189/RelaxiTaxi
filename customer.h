#pragma once
#include<iostream>
#include"position.h"
#include"connect.h"
#include"idGenerator.h"
#include"customerCRUD.h"

using namespace std;

bool runInsertQuery(int id, string Name, string phone_Number, string pass);
void customerLogin();
void customerRegister();
void customer();

//Helper Function
bool runInsertQuery(int id,string Name,string phone_Number,string pass) {
    vector<string> data;
    string cid = to_string(id);
    data.push_back(cid);
    data.push_back(Name);
    data.push_back(phone_Number);
    data.push_back(pass);
    return insert(data, "customer");
}

void customerLogin() {

    system("cls");
    MYSQL_RES* res;
    MYSQL_ROW row;
    int qstate;
    string phoneNumber,pass;

    cout << "Enter Phone Number: ";
    cin >> phoneNumber;

    res = read(phoneNumber, "customer", "Phone_Number");
    row = mysql_fetch_row(res);

    if (row != NULL)
    {
        bool ctr = 1;
        while (ctr)
        {
            cout << "Enter Password \n";
            cin >> pass;
            if (pass == row[3])
            {
                cout << "Login Successfull \n";
                Sleep(1000);
                string id = row[0];
                customerHome(id);
                ctr = 0;
            }
            else cout << "Incorrect Password \n";
        }
    }
    else {
        cout << "You do not have a registered account. Please Register!! ";
        Sleep(2000);
        customerRegister();
    }
}

void customerRegister() {

    system("cls");

    string phoneNumber, pass1="", pass2="", name;
    int id,qstate;
    MYSQL_RES* res;
    MYSQL_ROW row;

    cout << "Enter Phone Number: ";
    cin >> phoneNumber;

    res = read(phoneNumber, "customer", "Phone_Number");
    row = mysql_fetch_row(res);

    if (row == NULL)
    {
        cout << "Name: ";
        cin >> name;
        upper(name);
        do {
            if (pass1 != "" && pass1 != pass2)
                cout << "Passwords Do Not Match \n";
            cout << "Password: ";
            cin >> pass1;
            cout << "Confirm Password: ";
            cin >> pass2;
        } while (pass1 != pass2);

        id = generate_id("customer");
        bool ctr=runInsertQuery(id, name, phoneNumber, pass1);

        if (ctr)
        {
            cout << "Registration Successfull \n";
            Sleep(1000);
            customerHome(to_string(id));
        }
        else cout << "Something Went Wrong! \n";
    }
    else {
        cout << " You Already have a registered account with this Number.Kindly Login!! \n";
        Sleep(2000);
        customerLogin();
    }
}

void customer() {

    if (!conn)
    {
        if (!connect())
        {
            cout << "Could not Connect To Database \n";
            return;
        }
        cout << "Connection Established \n";
    }
    Sleep(2000);
    system("cls");
    int ctr;
    cout << "1. Login \n";
    cout << "2. Register \n";
    cout << "Choice? ";
    cin >> ctr;

    if (ctr == 1)
        customerLogin();
    else if(ctr==2) 
        customerRegister();
}