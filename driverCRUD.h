#pragma once

#include<iostream>
#include<string>
#include<windows.h>
#include<conio.h>
#include<iomanip>
#include "idGenerator.h"
#include"position.h"
#include"dbCRUD.h"
#include"connect.h"

using namespace std;

void displayDriverTrip(MYSQL_ROW row)
{
    cout << "Source: " << row[3] << "\n";
    cout << "Destination: " << row[4] << "\n";
    string cid = row[2];
    cout << "Customer Details \n";
    MYSQL_RES* res = read(cid, "customer", "ID");
    row = mysql_fetch_row(res);
    displayCustomer(row);
}

void driverHome(MYSQL_ROW row)
{
    system("cls");
start:
    int choice;
    char wish;
    system("cls");
    gotoxy(40, 0);
    cout << " #-WELCOME TO CAB_BUDDY$ WORKSPACE-# " << endl;
    gotoxy(50, 1);
    cout << " #-OPERATIONS-# \n" << endl;
    cout << " 1. Look for rides near your Location! " << endl;
    cout << " 2. End Current Trip successfully. " << endl;
    cout << " 3. Check Past Trips " << endl;
    cout << " You'd Like To Continue With ? ";
    cin >> choice;

    string booked = row[14];
    string id = row[0];
    string location = row[8];

    if (choice == 1)
    {
        if (booked == "Y" || booked == "y")
        {
            cout << "You already have a trip Pending!! \n";
            Sleep(2000);
            goto start;
        }

        MYSQL_RES* res = read(location,"ntrips","Source");
        MYSQL_ROW r;

        while (r = mysql_fetch_row(res))
        {
            system("cls");
            string src = r[3];
            string d = r[4];
            cout << "Source: " << src << "\n";
            cout << "Destination: " << d << "\n";
            cout << "Would you like to accept this trip? \n";
            char choice;
            cin >> choice;

            if (choice == 'Y' || choice == 'y')
            {
                bool ctr = modify(id,"driver","Booked","Y","ID");
                if (ctr)
                    cout << "Successfully Booked \n";
                else cout << "Some Error Occured \n";
                Sleep(2000);

                //Insert in btrips
                vector<string> data;
                for (int i = 0; i < 5; i++)
                {
                    if (i == 1)
                        data.push_back(id);
                    else {
                        string str = r[i];
                        data.push_back(str);
                    }
                }
                if (insert(data, "btrips"))
                    cout << "Successfully Moved Record To btrips \n";
                else cout << "Could'nt move record to btrips \n";

                //Delete from ntrips
                string tid = r[0];
                if (remove(tid, "ntrips", "TID"))
                    cout << "Successfully Removed from ntrips \n";
                else cout << "Could'nt remove from ntrips \n";

                Sleep(2000);
                break;
            }
        }
    }
    else if (choice == 2)
    {
        MYSQL_RES* res;
        MYSQL_ROW r;

        res = read(id, "btrips", "DID");
        if (mysql_num_rows(res) == 0)
        {
            cout << "No trip To END !! \n";
            Sleep(2000);
            goto start;
        }
        else {
            r = mysql_fetch_row(res);
            string nott= row[12];
            int numoftrips = stoi(nott);
            string destination = r[4];

            modify(id, "driver", "Number_Of_Trips", to_string(numoftrips + 1), "ID");
            modify(id, "driver", "Booked", "N", "ID");
            modify(id, "driver", "Location", destination, "ID");            

            //Insert in ptrips
            vector<string> data;
            for (int i = 0; i < 5; i++)
            {
                if (i == 1)
                    data.push_back(id);
                else {
                    string str = r[i];
                    data.push_back(str);
                }
            }
            if (insert(data, "ptrips"))
                cout << "Successfully Moved Record To ptrips \n";
            else cout << "Could'nt move record to ptrips \n";

            //Delete from btrips
            string tid = r[0];
            if (remove(tid, "btrips", "TID"))
                cout << "Successfully Removed from btrips \n";
            else cout << "Could'nt remove from btrips \n";

            Sleep(2000);
        }
    }
    else if (choice == 3)
    {
        MYSQL_RES* res;
        MYSQL_ROW r;

        res = read(id, "ptrips", "DID");
        while (r = mysql_fetch_row(res))
            displayDriverTrip(r);
        _getch();
    }
    else cout << " Sorry Wrong Choice !! ";

    system("cls");
    gotoxy(25, 0);
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