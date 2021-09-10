#pragma once

#include<mysql.h>
#include<vector>
#include<algorithm>
#include<iostream>
#include"connect.h"

//Function to generate unique id using mex technique
int generate_id(string table) {
    int qstate;
    MYSQL_ROW row;
    MYSQL_RES* res;
    vector<int> v;

    string query = "SELECT id from " + table;
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);

    if (!qstate)
    {
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            int val = stoi(row[0]);
            v.push_back(val);
        }
        sort(v.begin(), v.end());
        int mex = 0;
        for (auto it : v)
        {
            if (it != mex + 1)
                break;
            mex = it;
        }
        return mex + 1;
    }
    else
    {
        cout << "Query failed: " << mysql_error(conn) << endl;
        return -1;
    }
}