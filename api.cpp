//  g++ api.cpp -o api.cgi -L/usr/include/mysql -lmysqlclient -lcgicc
#include <iostream>
#include <mysql/mysql.h>
#include <cgicc/Cgicc.h>
#include <cstring>
#include <string>
#include "config_connect.h"

using namespace std;
using namespace cgicc;


int main() {
    MYSQL *db, *conn;
    MYSQL_RES *res_set;
    MYSQL_ROW row;

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
