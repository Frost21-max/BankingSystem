#ifndef account_creation_H
#define account_creation_H
#define MAX_ROWS 100
#define MAX_LENGTH 100
int user_menu();
void mysql_query_excuter(const char *query,
                         const char *database,
                         int permission,
                         char data[MAX_ROWS][20][MAX_LENGTH],
                         int* rows_out);
void buffer();
void hideInput();
void showInput();
#endif