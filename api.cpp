//  g++ api.cpp -o api.cgi -L/usr/include/mysql -lmysqlclient -lcgicc
#include <iostream>
#include <mysql/mysql.h>
#include <cgicc/Cgicc.h>
#include <cstring>
#include <string>
#include "config_connect.h"

using namespace std;
using namespace cgicc;

MYSQL* db, * conn;
MYSQL_RES* res_set;
MYSQL_ROW row;

int editf() {
    Cgicc cgi;
    string id = cgi("id");

    char to[strlen(id.c_str()) * 2 + 1];
    mysql_real_escape_string(conn, to, id.c_str(), strlen(id.c_str()));
    string idc = to;
    string query = "SELECT 1 FROM Staff WHERE id = " + idc;
    mysql_query(conn, query.c_str());
    res_set = mysql_store_result(conn);

    //num_fields = mysql_num_fields(res_set);
    bool rowExist = false;

    while ((row = mysql_fetch_row(res_set)))
    {
        unsigned long* lengths;
        lengths = mysql_fetch_lengths(res_set);

        for (int i = 0; i < 1; i++)
        {
            
            if (row[i]) rowExist = true;
        }

    }

    if (rowExist) {
        string name = cgi("name");
        char nameTo[strlen(name.c_str()) * 2 + 1];
        mysql_real_escape_string(conn, nameTo, name.c_str(), strlen(name.c_str()));
        string namec = nameTo;

        string position = cgi("position");
        char positionTo[strlen(position.c_str()) * 2 + 1];
        mysql_real_escape_string(conn, positionTo, position.c_str(), strlen(position.c_str()));
        string positionc = positionTo;

        string birthday = cgi("birthday");
        char birthdayTo[strlen(birthday.c_str()) * 2 + 1];
        mysql_real_escape_string(conn, birthdayTo, birthday.c_str(), strlen(birthday.c_str()));
        string birthdayc = birthdayTo;

        query = "UPDATE Staff SET name = '" 
            + namec + "', position = " 
            + positionc + ", birthday = '" 
            + birthdayc + "' WHERE id = " + idc;
        
        mysql_query(conn, query.c_str());
    }

    mysql_free_result(res_set);
    mysql_close(conn);

    return 0;
}

int main() {

    db = mysql_init(NULL);
    if (!db) return 1;
	
    struct connection c1;

    conn = mysql_real_connect(db, c1.host, c1.user, c1.password, c1.dbname, c1.port, NULL, 0);
    if (!conn) {
        fprintf(stderr, "Failed to connect to database: Error: %s\n", mysql_error(db));
        mysql_close(conn);
        return 2;
    }

    cout << "Content-Type: text/json" << endl << endl;

    Cgicc cgi;
    string id = cgi("id");
    string edit = cgi("edit");
    if (edit == "1") {
        editf();
        return 0;
    }
    string query = "SELECT * FROM Staff";
    if (strlen(id.c_str()) > 0) {
        char to[strlen(id.c_str()) * 2 + 1];
        mysql_real_escape_string(conn, to, id.c_str(), strlen(id.c_str()));
        string idc = to;
        query += " WHERE id = " + idc;
    }

    mysql_query(conn, query.c_str());
    res_set = mysql_store_result(conn); 
    
    MYSQL_FIELD *mfield;
    unsigned int num_fields;
    unsigned int i;

    num_fields = mysql_num_fields(res_set);

    cout << "[" << endl;
    while ((row = mysql_fetch_row(res_set)))
    {
        unsigned long *lengths;
        lengths = mysql_fetch_lengths(res_set);
        
        for(i = 0; i < num_fields; i++)
        {
            if (i == 0) cout << "[";
            printf("\"%.*s\"", (int) lengths[i],
                    row[i] ? row[i] : "NULL");
            if (num_fields - 1 > i) cout << ", ";
        }
        cout << "], ";
    }
    cout << "]" << endl;
    mysql_free_result(res_set);
    mysql_close(conn);
    return 0;
}
