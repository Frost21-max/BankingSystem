#include <stdio.h>

#include "account_creation.h"

char value[MAX_ROWS][20][MAX_LENGTH];
int no_of_rows;

int main() {
    mysql_query_excuter("select * from account_information","accounts",1,value,&no_of_rows);

    int option;
    printf("\n\n\n-----------------Welcome To Bank------------------\n\n");
    while(1)
    {

        printf("01) Account Creation\n");
        printf("02) Account Checker\n");
        printf("03) Exit\n\n");
        scanf("%d",&option);
        switch (option)
        {
            case 1:
            user_menu();
            
            continue;

            case 2:


            
            default:
            break;
        }
    }
    return 0;
}