#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "account_creation.h"

void mysql_ValuePrinter();
void mysql_ValueChanger(const char *accNO);
int regex_appler(const char *pattern, const char *input);
char value[MAX_ROWS][20][MAX_LENGTH];
int no_of_rows = 0;
regex_t regex_value; // Globle variable
const char *pattern;
int main_menu_continue;

int main()
{
    // mysql_query_excuter("select * from account_information","accounts",1,value,&no_of_rows);

    int option;
    int exit__;
    char account_number_input[20];
    char account_passwd_input[10];

    printf("\n\n\n-----------------Welcome To Bank------------------\n\n");
    while (1)
    {

        printf("01) Account Creation\n");
        printf("02) Account Checker\n");
        printf("03) Exit\n\n");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            user_menu();
            continue;

        case 2:
            pattern = "^[0-9]{12}$";
            regcomp(&regex_value, pattern, REG_EXTENDED);
            int no_of_tries = 3;
            buffer();
            while (1)
            {
                int tester1 = 0;
                if (no_of_tries <= 0)
                {
                    printf("\n\tTo much incorrect attemt\n\n");
                    break;
                }
                printf("Enter your Account Number :");
                fgets(account_number_input, sizeof(account_number_input), stdin);
                account_number_input[strcspn(account_number_input, "\n")] = '\0';
                if (regexec(&regex_value, account_number_input, 0, NULL, 0) != 0)
                {
                    printf("\nInvalid Account Number \n\n");
                    no_of_tries = no_of_tries - 1;
                    if (no_of_tries != 0)
                        printf("no of tries left is %d\n", no_of_tries);
                    continue;
                }
                mysql_query_excuter("select account_no,password_hash from account_information", "accounts", 1, value, &no_of_rows);
                for (int i = 0; i <= no_of_rows; i++)
                {
                    if (strcmp(account_number_input, value[i][0]) != 0)
                    {
                        continue;
                    }
                    tester1 = 1;
                    break;
                }
                if (tester1 == 0)
                {
                    printf("No match found\n");
                    no_of_tries = no_of_tries - 1;
                    if (no_of_tries != 0)
                        printf("no of tries left is %d\n", no_of_tries);
                    printf("try again\n");
                    continue;
                }
                pattern = "^(\\S){6}$";
                regcomp(&regex_value, pattern, REG_EXTENDED);
                no_of_tries = 3;
                while (1)
                {
                    int tester2 = 0;
                    if (no_of_tries <= 0)
                    {
                        printf("\n\tTo much incorrect attemt\n\n");
                        break;
                    }
                    printf("Enter your Account passwd :");
                    hideInput();
                    fgets(account_passwd_input, sizeof(account_passwd_input), stdin);
                    account_passwd_input[strcspn(account_passwd_input, "\n")] = '\0';
                    showInput();
                    if (regexec(&regex_value, account_passwd_input, 0, NULL, 0) != 0)
                    {
                        printf("\nInvalid Account Passwd \n\n");
                        no_of_tries = no_of_tries - 1;
                        if (no_of_tries != 0)
                            printf("no of tries left is %d\n", no_of_tries);
                        continue;
                    }
                    for (int i = 0; i <= no_of_rows; i++)
                    {
                        if (strcmp(account_passwd_input, value[i][1]) != 0)
                        {
                            continue;
                        }
                        tester2 = 1;
                        break;
                    }
                    if (tester2 == 0)
                    {
                        printf("No match found\n");
                        no_of_tries = no_of_tries - 1;
                        if (no_of_tries != 0)
                            printf("no of tries left is %d\n", no_of_tries);
                        printf("try again\n");
                        continue;
                    }
                    break;
                }

                char Query[100];
                snprintf(Query, sizeof(Query), "select * from account_information where account_no = %s", account_number_input);
                mysql_query_excuter(Query, "accounts", 1, value, &no_of_rows);
                mysql_ValuePrinter();
                mysql_ValueChanger(account_number_input);
                
                break;
            }
        if (main_menu_continue == 0) continue;

        case 3:
            exit__ = 1;
            break;
        }
        if (exit__ == 1) break;
    }
    return 0;
}

void mysql_ValuePrinter()
{
    printf("\n\n");
    printf("1) Account Holder : %s\n", value[0][1]);
    printf("2) Phone Number   : %s\n", value[0][6]);
    printf("3) Holder Email   : %s\n", value[0][7]);
    printf("4) Holder passwd  : %s\n", "******");
    printf("---Holder Balance  : %s  ---\n", value[0][8]);
    printf("\n\n");
}
void mysql_ValueChanger(const char *accNO)
{
    const char *Header_Array[5] = {
        "name",
        "phone",
        "email",
        "password_hash",
        "balance"};

    const char *Display_Array[5] = {
        "Account Holder",
        "Phone Number",
        "Holder Email",
        "Holder passwd",
        "balance"};

    const char *Regex_Array[5] = {
        "^[A-Za-z]+(\\s[A-Za-z]+)*$", // name
        "^[0-9]{10}$",                // phone
        "^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$",
        "^[a-zA-Z0-9_]+$", // password
        "^[0-9]*$"         // balance
    };

    // First menu: A / B / X
    pattern = "^[ABCXabcx]{1}$";
    regcomp(&regex_value, pattern, REG_EXTENDED);

    char input_For_Changes[5];

    while (1)
    {
        printf("A: For making changes in data \n");
        printf("B: For add money in Account \n");
        printf("C: For withdrowl money in Account \n");
        printf("X: For Exit to main menu \n\n");
        printf(": ");

        fgets(input_For_Changes, sizeof(input_For_Changes), stdin);
        input_For_Changes[strcspn(input_For_Changes, "\n")] = '\0';

        if (regexec(&regex_value, input_For_Changes, 0, NULL, 0) == 0)
            break;

        printf("Invalid choice!\n\n");
    }
    char Input_Input[50];

    input_For_Changes[0] = toupper(input_For_Changes[0]);
    // Only for option A we go inside
    if (strcmp(input_For_Changes, "A") == 0)
    {
        // Ask which field (1–4)
        pattern = "^[1-4]{1}$";
        regcomp(&regex_value, pattern, REG_EXTENDED);

        char Number_input[10];

        while (1)
        {
            printf("Enter the number corresponding to your desired change (1-4): ");
            fgets(Number_input, sizeof(Number_input), stdin);
            Number_input[strcspn(Number_input, "\n")] = '\0';

            if (regexec(&regex_value, Number_input, 0, NULL, 0) == 0)
                break;

            printf("Invalid input! Please enter only ONE digit (1-4).\n");
        }

        regfree(&regex_value);

        int temp_value = (int)strtoul(Number_input, NULL, 10) - 1;

        const char *mysql_database_key_value = Header_Array[temp_value];
        const char *regex_pattern = Regex_Array[temp_value];

        while (1)
        {
            printf("Enter the new %s: ", Display_Array[temp_value]);
            fgets(Input_Input, sizeof(Input_Input), stdin);
            Input_Input[strcspn(Input_Input, "\n")] = '\0';

            if (!regex_appler(regex_pattern, Input_Input))
            {
                printf("Invalid format\n");
                continue;
            }
            break;
        }

        char QUery[256];
        snprintf(QUery, sizeof(QUery),
                 "UPDATE account_information SET %s = '%s' WHERE account_no = %s",
                 mysql_database_key_value, Input_Input, accNO);

        mysql_query_excuter(QUery, "accounts", 0, NULL, 0);
    }
    if (strcmp(input_For_Changes, "B") == 0)
    {
        char ii[50];

        while (1)
        {
            printf("Enter the add %s: ", Display_Array[4]);
            fgets(ii, sizeof(ii), stdin);
            ii[strcspn(ii, "\n")] = '\0';
            if (!regex_appler(Regex_Array[4], ii))
            {
                printf("Invalid format\n");
                continue;
            }
            break;
        }
        char QUEry[256];
        unsigned long long new_balance;

        new_balance = strtoull(value[0][8], NULL, 10) + strtoull(ii, NULL, 10);

        char buffer[50];
        snprintf(buffer, sizeof(buffer), "%llu", new_balance);
        snprintf(QUEry, sizeof(QUEry),
                 "UPDATE account_information SET balance = '%llu' WHERE account_no = %s",
                 new_balance, accNO);
        mysql_query_excuter(QUEry, "accounts", 0, NULL, 0);
    }
    if (strcmp(input_For_Changes, "C") == 0)
    {
        char ii[50];

        while (1)
        {
            printf("Enter the withdraw amount from %s: ", Display_Array[4]);
            fgets(ii, sizeof(ii), stdin);
            ii[strcspn(ii, "\n")] = '\0';
            if (!regex_appler(Regex_Array[4], ii))
            {
                printf("Invalid format\n");
                continue;
            }
            break;
        }
        char QUEry[256];
        unsigned long long new_balance;

        new_balance = strtoull(value[0][8], NULL, 10) - strtoull(ii, NULL, 10);

        char buffer[50];
        snprintf(buffer, sizeof(buffer), "%llu", new_balance);
        snprintf(QUEry, sizeof(QUEry),
                 "UPDATE account_information SET balance = '%llu' WHERE account_no = %s",
                 new_balance, accNO);
        mysql_query_excuter(QUEry, "accounts", 0, NULL, 0);
    } 
    regfree(&regex_value);
}

int regex_appler(const char *pattern, const char *input)
{

    int ret;

    ret = regcomp(&regex_value, pattern, REG_EXTENDED);
    if (ret != 0)
    {
        regfree(&regex_value);
        return 0;
    }

    ret = regexec(&regex_value, input, 0, NULL, 0);
    regfree(&regex_value);

    return (ret == 0); // 1 = valid, 0 = invalid
}



