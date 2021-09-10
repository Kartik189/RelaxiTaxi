#pragma once

#include<string>
#include<mysql.h>
#include<unordered_map>

using namespace std;

MYSQL* conn;

//Driver Table Structure
const unordered_map<int,string> dtable = {
  { 0, "ID" },
  { 1, "Name" },
  { 2, "Age" },
  { 3, "Phone_Number" },
  { 4, "Car_Type" },
  { 5, "Number_Of_Seats" },
  { 6, "Pool" },
  { 7, "Car_Name" },
  { 8, "Location" },
  { 9, "RC_Number" },
  { 10, "Salary" },
  { 11, "Reviews" },
  { 12, "Number_Of_Trips" },
  { 13, "Booked" },
  { 14, "Password" }
};

//Pending Driver Table Structure
const unordered_map<int, string> pdtable = {
  { 0, "ID" },
  { 1, "Name" },
  { 2, "Age" },
  { 3, "Phone_Number" },
  { 4, "Car_Type" },
  { 5, "Number_Of_Seats" },
  { 6, "Pool" },
  { 7, "Car_Name" },
  { 8, "Location" },
  { 9, "RC_Number" },
  { 10, "Salary" },
  { 11, "Reviews" },
  { 12, "Number_Of_Trips" },
  { 13, "Booked" },
  { 14, "Password" }
};

//trip data structure
const unordered_map<int, string> trip = {
  { 0, "TID" },
  { 1, "DID" },
  { 2, "CID" },
  { 3, "Source" },
  { 4, "Destination" }
};

//Customer Table
const unordered_map<int, string> ctable = {
  { 0, "ID" },
  { 1, "Name" },
  { 2, "Phone_Number" },
  { 3, "Password" }
};

bool connect() {

	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "189189", "cabservice", 3306, NULL, 0);

	if (conn)
		return 1;
	return 0;
}