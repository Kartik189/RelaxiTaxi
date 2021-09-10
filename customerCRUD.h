#pragma once

#include<iostream>
#include<string>
#include"position.h"
#include"connect.h"

using namespace std;

int countRecords(string table)
{
    int qstate;
    string query = "SELECT * from " + table;
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    MYSQL_RES* res = mysql_store_result(conn);
    if (!qstate)
        return mysql_num_rows(res);
    else return 0;
}

int totalTrips() {
    int count = countRecords("ntrips") + countRecords("btrips") + countRecords("ptrips");
    return count;
}

string generateTripID() {
    int id = totalTrips() + 1;
    return to_string(id);
}

void displayCustomerTrip(MYSQL_ROW row)
{
    string source = row[3],destination=row[4];
    cout << "Source: " << source << "\n";
    cout << "Destination: " << destination << "\n";
    string did = row[1];
    cout << "Driver Details \n";
    MYSQL_RES* res = read(did, "driver", "ID");
    row = mysql_fetch_row(res);
    display(row);
}

void customerHome(string id) {
start:
    char wish;
    int choice;
    system("cls");
    gotoxy(28, 0);
    cout << " #-WELCOME TO CAB_BUDDY$ TOURS-# " << endl;
    gotoxy(37, 1);
    cout << " #PREFRENCES# " << endl;
    cout << " 1. Start A New Trip " << endl;
    cout << " 2. Booked Trip Information. " << endl;
    cout << " 3. Past Trips Information. " << endl;
    cout << " 4. Cancel Trip " << endl;
    cout << " YOU WANNA ? ";
    cin >> choice;

    if (choice == 1)
    {
        //can also ask car-type choice
        vector<string> data(5);
        data[2] = id;
        data[1] = "";

        cout << "Travelling from: ";
        cin >> data[3];
        upper(data[3]);
        cout << "Travelling To: ";
        cin >> data[4];
        upper(data[4]);
        data[0] = generateTripID();

        if (insert(data,"ntrips"))
        {
            bool ctr = 1;
            cout << "Finding You a Driver..... \n";
            while (ctr)
            {
                MYSQL_RES* res = read(data[0],"btrips","TID");
                if (mysql_num_rows(res) == 1)
                {
                    MYSQL_ROW row = mysql_fetch_row(res);
                    system("cls");
                    cout << "Trip Booked \n";
                    cout << "Driver Details: \n";
                    string did = row[1];
                    res = read(did, "driver", "ID");
                    row= mysql_fetch_row(res);
                    display(row);
                    cout << "You are riding with....." << row[1] << "\n";
                    while (ctr)
                    {
                        res = read(data[0], "ptrips", "TID");
                        if (mysql_num_rows(res) == 1)
                        {
                            cout << "Trip Successfully Completed \n";
                            cout << "Please rate your driver(1-10): ";
                            string rating = row[11];
                            double prating = stod(rating);
                            double nrating;
                            cin >> nrating;
                            nrating = (nrating + prating) / 2.0;                       
                            modify(did, "driver", "Reviews", to_string(nrating), "ID");
                            cout << "Reviewed Successfully \n";
                            cout << "Thanks for Travelling with US \n";
                            ctr = 0;
                        }
                    }
                    Sleep(2000);
                }
            }
        }
        else {
            cout << "Some Error Occured(404) \n";
            Sleep(20000);
        }
    }
    else if (choice == 2)
    {
        MYSQL_RES* res;
        MYSQL_ROW row;

        res = read(id, "btrips", "CID");
        while(row = mysql_fetch_row(res))
            displayCustomerTrip(row);
        _getch();
    }
    else if (choice == 3)
    {
        MYSQL_RES* res;
        MYSQL_ROW row;

        res = read(id, "ptrips", "CID");
        while (row = mysql_fetch_row(res))
            displayCustomerTrip(row);
        _getch();
    }
    else if (choice == 4)
    {
        MYSQL_RES* res = read(id, "ntrips", "CID");
        if (mysql_num_rows(res) == 0)
            cout << "No Existing Trip/ Already Confirmed!! \n";
        else {
            if (remove(id,"ntrips","CID"))
                cout << "Successfully Cancelled \n";
            else cout << "Error Occured \n";
        }
        Sleep(2000);
    }

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