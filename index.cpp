#include<iostream>
#include"position.h"
#include"driver.h"
#include"employee.h"
#include"customer.h"

using namespace std;

void password()
{
    system("cls");
    string pass;
    cout << "Enter Password :: ";
    cin >> pass;
    if (pass == "ubervalley")
        employee();
    else cout << " Wrong Password ";
}

int main()
{
start:
    system("cls");
    int choice;
    gotoxy(35, 0);
    cout << " --CAB_BUDDY.COM-- " << endl;
    cout << "1. Employee \n";
    cout << "2. Driver \n";
    cout << "3. Customer \n";
    cout << "Your choice? ";
    cin >> choice;

    switch (choice) {
        case 1: password(); break;
        case 2: driver(); break;
        case 3: customer(); break;
        default: cout << "Wrong Choice !! \n";
    }
    goto start;

    return 0;
}