#include <stdio.h>
#include <mysql/mysql.h>

#include "account_creation.h"

#define PASSWD "Mydatabases@123"
#define USER "root"
void mysql_value_fetcher(const char* query , const char* databases);
void mysql_value_fetcher(const char* query , const char* databases){
    
}
void mysql_query_excuter(const char *query ,const char *databases ) {
    MYSQL *conn = mysql_init(NULL);

    // Check initialization
    if (conn == NULL) {
        printf("mysql_init failed\n");
        return;
    }

    // Connect to server
    if (!mysql_real_connect(conn, "localhost", USER, PASSWD,databases, 0, NULL, 0)) {
        printf("Connection failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    // Execute query
    if (mysql_query(conn, query)) {
        printf("Query execution failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    mysql_close(conn);
}

void main_account_management();
void main_account_management(){
    
}

int main() {
    printf("compile done");
    printf("compile done");
    printf("compile done");
    printf("compile done");
    return 0;
}