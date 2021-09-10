#pragma once
#include<iostream>
#include<windows.h>
#include"connect.h"
#include"driverCRUD.h"
#include"position.h"

using namespace std;

void driverRegister();

int cal_sal(string car_type)
{
    if (car_type == "MINI")
        return 10000;
    else if (car_type == "SEDAN")
        return 15000;
    else if (car_type == "SUV")
        return 20000;
    else if (car_type == "LUXURY")
        return 30000;
    return 10000;
} 

bool runCreateAndInsertQuery() {
    system("cls");
    vector<string> data(15);
    int i=0;
    string id,pass1="",pass2="";
    data[0] = to_string(generate_id("driver"));

    for (auto it : pdtable)
    {
        if (it.first <= 0)
            continue;
        else if (it.first >= 10)
            break;

        string str;
        cout << "Enter " << it.second << ": ";
        cin >> str;
        upper(str);
        data[it.first] = str;
    }
    data[10] = cal_sal(data[4]);
    data[11] = "5";
    data[12] = "0";
    data[13] = "N";   
    do {
        if (pass1 != "" && pass1 != pass2)
            cout << "Passwords Do Not Match \n";
        cout << "Password: ";
        cin >> pass1;
        cout << "Confirm Password: ";
        cin >> pass2;
    } while (pass1 != pass2);
    data[14] = pass1;

    if (insert(data,"pdriver"))
        return 1;
    else return 0;
}

void driverLogin() {
    system("cls");
    MYSQL_RES* res;
    MYSQL_ROW row;
    int qstate;
    string phoneNumber, pass;

    cout << "Enter Phone Number: ";
    cin >> phoneNumber;

    res = read(phoneNumber, "driver", "Phone_Number");
    row = mysql_fetch_row(res);

    if (row != NULL)
    {
        bool ctr = 1;
        while (ctr)
        {
            system("cls");

            cout << "Enter Password: ";
            cin >> pass;
            if (pass == row[14])
            {
                cout << "Login Successfull ";
                Sleep(1000);
                driverHome(row);
                ctr = 0;
            }
            else cout << "Incorrect Password ";
            Sleep(1000);
        }
    }
    else {
        res = read(phoneNumber, "pdriver", "Phone_Number");
        row = mysql_fetch_row(res);
        if (row != NULL)
            cout << "Verification in Pending!! \n";
        else {
            cout << "You are not Registered as a driver with us. Please Register!!! ";
            Sleep(2000);
            driverRegister();
        }
    }
}

void driverRegister() {
    system("cls");
    MYSQL_RES* res;
    MYSQL_ROW row;
    int qstate;
    string phoneNumber, pass;

    cout << "Enter Phone Number: ";
    cin >> phoneNumber;

    res = read(phoneNumber,"driver","Phone_Number");
    row = mysql_fetch_row(res);

    if (row != NULL)
    {
        cout << "You are already Registered with us. Please Login!! \n";
        Sleep(2000);
        driverLogin();
    }
    else {
        res= read(phoneNumber, "pdriver", "Phone_Number");
        row = mysql_fetch_row(res);
        if (row != NULL)
            cout << "Your Verification in Pending!! \n";
        else {
            if (runCreateAndInsertQuery())
                cout << "Successfully Registered. Kindly wait for verification process!! \n";
            else cout << "Something Went Wrong!! \n";
        }
    } 
}

void driver() {
    system("cls");
    if (!conn)
    {
        if (!connect())
        {
            cout << "Could not Connect To Database.... \n";
            return;
        }
        cout << "Connection Established.... \n";
    }
    Sleep(2000);
    system("cls");
    gotoxy(35, 0);
    cout << " #-WELCOME TO RelaxiTaxi Driver WORKSPACE-# " << endl;
    int ctr;
    cout << "1. Login \n";
    cout << "2. Register \n";
    cout << "Choice? ";
    cin >> ctr;

    if (ctr == 1)
        driverLogin();
    else if (ctr == 2)
        driverRegister();

}