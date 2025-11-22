#include <stdio.h>

#include "account_creation.h"


int main() {
    char value[MAX_ROWS][20][MAX_LENGTH];
    int no_of_rows;
    mysql_query_excuter("select * from account_information","accounts",1,value,&no_of_rows);
    printf("%s\n\n",value[0][0]);
    return 0;
}