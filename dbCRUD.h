#pragma once

#include<mysql.h>
#include<vector>
#include<string>
#include"connect.h"

using namespace std;

void upper(string &str) {
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] <= '9' && str[i] >= '0')
			continue;
		else str[i] = toupper(str[i]);
	}
}

void display(MYSQL_ROW row) {
	for (auto it : dtable)
	{
		if (it.first == 14)
			continue;
		cout << it.second << ": ";
		cout << row[it.first] << "\n";
	}
	cout << "\n";
}

void displayCustomer(MYSQL_ROW row) {
	for (auto it : ctable)
	{
		if (it.first == 3)
			continue;
		cout << it.second << ": ";
		cout << row[it.first] << "\n";
	}
	cout << "\n";
}

bool insert(vector<string> data,string tableName) {

	//Formulating Query
	string query = "INSERT into " + tableName + " values (";
	for (auto it : data)
	{
		if (it == "")
			query += "NULL";
		else query += "'" + it + "'";
		query += ",";
	}

	//Removing extra ,
	if (query[query.size() - 1] == ',')
		query.pop_back();
	query += ")";

	//Processing Query
	const char* q = query.c_str();
	int qstate = mysql_query(conn, q);

	return !qstate;
}

bool remove(string id,string tableName,string queryColumn) {

	string query = "DELETE from " + tableName + " WHERE " + queryColumn + " = '" + id+ "' ";
	const char* q = query.c_str();
	int qstate = mysql_query(conn, q);
	return !qstate;
}

MYSQL_RES* read(string id,string tableName,string queryColumn) {

	string query = "SELECT * from " + tableName + " WHERE " + queryColumn + " = '" + id + "' ";
	const char* q = query.c_str();
	int qstate = mysql_query(conn, q);

	if (!qstate)
		return mysql_store_result(conn);
	return NULL;
}

MYSQL_RES* read(string tableName) {

	string query = "SELECT * from " + tableName;
	const char* q = query.c_str();
	int qstate = mysql_query(conn, q);

	if (!qstate)
		return mysql_store_result(conn);
	return NULL;
}

bool modify(string id,string tableName,string columnName,string newVal,string queryColumn) {

	string query = "UPDATE " + tableName + " SET " + columnName + " = '" + newVal + "' WHERE " + queryColumn + " = ' " + id + "' ";
	const char* q = query.c_str();
	int qstate = mysql_query(conn, q);
	return !qstate;
}
