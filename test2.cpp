//  g++ test2.cpp -o page1.cgi -L/usr/include/mysql -lmysqlclient
#include <iostream>
#include <mysql/mysql.h>
#include "config_connect.h"

using namespace std;

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

    cout << "Content-Type: text/html" << endl << endl;
    cout << "<link rel=\"stylesheet\" href=\"/main.css\" />" << endl;
    cout << "<h1>Staff</h1>" << endl;

    mysql_query(conn, "SELECT * FROM Staff");
    res_set = mysql_store_result(conn); 
    
    MYSQL_FIELD *mfield;
    unsigned int num_fields;
    unsigned int i;

    num_fields = mysql_num_fields(res_set);

    cout << "<p>" << endl;
    while ((row = mysql_fetch_row(res_set)))
    {
        unsigned long *lengths;
        lengths = mysql_fetch_lengths(res_set);
        for(i = 0; i < num_fields; i++)
        {
            printf("[%.*s] ", (int) lengths[i],
                    row[i] ? row[i] : "NULL");
        }
        printf("<br>");
    }
    cout << "</p>" << endl;
    mysql_free_result(res_set);
    mysql_close(conn);
    return 0;
}
