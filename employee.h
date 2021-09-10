#pragma once

#include<iostream>
#include<windows.h>
#include"connect.h"
#include"employeeCRUD.h"
#include"position.h"

using namespace std;

//functions
void employee();

void employee()
{
    system("cls");
    if (!conn)
    {
        if (!connect())
        {
            cout << "Could not Connect To Database.... \n";
            Sleep(2000);
            return;
        }
    }
    cout << "Connection Established.... \n";
    Sleep(2000);

start:
    int choice;
    char wish;
    system("cls");
    gotoxy(35, 0);
    cout << " #-WELCOME TO RelaxiTaxi Employee WORKSPACE-# " << endl;
    gotoxy(50, 1);
    cout << " #-OPERATIONS-# \n" << endl;
    cout << " 1. Verify New Driver and Add/Remove them " << endl;
    cout << " 2. Remove Existing Driver" << endl;
    cout << " 3. Modify Existing Driver Information " << endl;
    cout << " 4. Show Existing Drivers " << endl;
    cout << " You'd Like To Continue With ? ";
    cin >> choice;
    if (choice == 1)
        verifyDriver();
    else if (choice == 2)
        removeDriver();
    else if (choice == 3)
        modifyDriver();
    else if (choice == 4)
        showDriver();
    else cout << " Sorry Wrong Choice !! ";

    system("cls");
    gotoxy(35, 0);
    cout << " WISH TO PERFORM MORE OPERATIONS(Y/N) :: ";
    cin >> wish;
    if ((wish == 'y') || (wish == 'Y'))
        goto start;
    else
    {
        system("cls");
        gotoxy(35, 0);
        cout << " #! GOODBYE !# ";
        gotoxy(35, 1);
        cout << " SEE YOU SOON ";
    }
}