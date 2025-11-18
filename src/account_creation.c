#include <stdio.h>
#include <mysql/mysql.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

#define PASSWD "Mydatabases@123"
#define USER "root"

typedef struct
{
    unsigned long long account_no;
    char name[20];
    unsigned int age;
    char gender[10];
    char date_of_birth[11];
    char aadhar_no[18];
    char pan_no[18];
    char phone[15];
    char email[20];
    unsigned long long balance;
    char account_type[10];
} Account;

void mysql_query_excuter(const char *, const char *); // function prototype for connection

int user_menu();

void mysql_query_excuter(const char *query, const char *databases)
{
    MYSQL *conn = mysql_init(NULL);

    // Check initialization
    if (conn == NULL)
    {
        printf("mysql_init failed\n");
        return;
    }

    // Connect to server
    if (!mysql_real_connect(conn, "localhost", USER, PASSWD, databases, 0, NULL, 0))
    {
        printf("Connection failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    // Execute query
    if (mysql_query(conn, query))
    {
        printf("Query execution failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    mysql_close(conn);
}

int main(int argc, char const *argv[])
{
    user_menu();
    return 0;
}

Account acc;
int user_menu()
{
    printf("Enter your Name: ");
    fgets(acc.name, sizeof(acc.name), stdin); // for name
    acc.name[strcspn(acc.name, "\n")] = 0;
    // printf("%s\n", acc.name);

    char ageStr[10];

    printf("Enter your age: ");
    fgets(ageStr, sizeof(ageStr), stdin);   // for age
    ageStr[strcspn(ageStr, "\n")] = '\0';     // this replace the \n with string terminater      
    acc.age = (unsigned int)strtoul(ageStr, NULL, 10); // strtoul convert str to unsinged long int
    // printf("%u\n", acc.age);

    char genderS[10];

    printf("Enter your Gender: ");
    fgets(genderS, sizeof(genderS),stdin);
    genderS[strcspn(genderS, "\n")] = '\0';
    for (int i = 0; genderS[i]; i++) {
        genderS[i] = tolower(genderS[i]);
    }
    genderS[0] = toupper(genderS[0]);
    if (strcmp(genderS,"Male") == 0)
    {
        strcpy(acc.gender,"Male");
    }
    else if (strcmp(genderS,"Female") == 0)
    {
        strcpy(acc.gender,"Female");
    }
    else
    {
        strcpy(acc.gender,"Other");
    }
    // printf("%s",acc.gender);

    printf("Enter the date of birth (yyyy-mm-dd):");
    fgets(acc.date_of_birth, sizeof(acc.date_of_birth),stdin);
    acc.date_of_birth[strcspn(acc.date_of_birth, "\n")] = '\0';
    // printf("%s",acc.date_of_birth);

    // do the for loop here and get hte dob right

// code check kar
// #include <stdio.h>
// #include <mysql/mysql.h>
// #include <termios.h>
// #include <unistd.h>
// #include <ctype.h>
// #include <string.h>

// #define PASSWD "PiyushBisht8275@"
// #define USER "root"

// typedef struct
// {
//     unsigned long long account_no;
//     char name[20];
//     unsigned int age;
//     char gender[10];
//     char date_of_birth[11];
//     char aadhar_no[18];
//     char pan_no[18];
//     char phone[15];
//     char email[20];
//     unsigned long long balance;
//     char account_type[10];
// } Account;

// void mysql_query_excuter(const char *, const char *); // function prototype for connection

// int user_menu();

// void mysql_query_excuter(const char *query, const char *databases)
// {
//     MYSQL *conn = mysql_init(NULL);

//     // Check initialization
//     if (conn == NULL)
//     {
//         printf("mysql_init failed\n");
//         return;
//     }

//     // Connect to server
//     if (!mysql_real_connect(conn, "localhost", USER, PASSWD, databases, 0, NULL, 0))
//     {
//         printf("Connection failed: %s\n", mysql_error(conn));
//         mysql_close(conn);
//         return;
//     }

//     // Execute query
//     if (mysql_query(conn, query))
//     {
//         printf("Query execution failed: %s\n", mysql_error(conn));
//         mysql_close(conn);
//         return;
//     }

//     mysql_close(conn);
// }

// int main(int argc, char const *argv[])
// {
//     user_menu();
//     return 0;
// }

// Account acc;
// int user_menu()
// {  // ---------------------- NAME ----------------------
//     printf("Enter your Name: ");
//     fgets(acc.name, sizeof(acc.name), stdin); // for name
//     acc.name[strcspn(acc.name, "\n")] = 0;
//     // printf("%s\n", acc.name);

//    // ---------------------- AGE ----------------------
//     char ageStr[10];
//     unsigned long ageNum;

//     printf("Enter your age: ");
//     while(1){
//     fgets(ageStr, sizeof(ageStr), stdin);   // for age
//     ageStr[strcspn(ageStr, "\n")] = '\0';     // this replace the \n with string terminater
//     ageNum=strtoul(ageStr, NULL, 10);
//     if (ageNum >= 18)
//     {
//         acc.age = (unsigned int)ageNum;// strtoul convert str to unsinged long int
//         break;
//     }
//     else{
//         printf("Invalid age! Enter again: ");
//     }
//     // printf("%u\n", acc.age);
// }

//    // ---------------------- GENDER ----------------------
//     char genderS[10];

//     printf("Enter your Gender: ");
//     fgets(genderS, sizeof(genderS),stdin);
//     genderS[strcspn(genderS, "\n")] = '\0';
//     for (int i = 0; genderS[i]; i++) {
//         genderS[i] = tolower(genderS[i]);
//     }
//     genderS[0] = toupper(genderS[0]);
//     if (strcmp(genderS,"Male") == 0)
//     {
//         strcpy(acc.gender,"Male");
//     }
//     else if (strcmp(genderS,"Female") == 0)
//     {
//         strcpy(acc.gender,"Female");
//     }
//     else
//     {
//         strcpy(acc.gender,"Other");
//     }
//     // printf("%s",acc.gender);

//     // ---------------------- DATE OF BIRTH ----------------------

//     printf("Enter the date of birth (yyyy-mm-dd): ");

//     while (1)
//     {
//         fgets(acc.date_of_birth, sizeof(acc.date_of_birth), stdin);
//         acc.date_of_birth[strcspn(acc.date_of_birth, "\n")] = '\0'; // remove newline

//         int year, month, day;

//         if (sscanf(acc.date_of_birth, "%4d-%2d-%2d", &year, &month, &day) == 3) // check format yyyy-mm-dd
//         {

//             // basic range checks
//             if (year >= 1900 && year <= 2025 &&
//                 month >= 1 && month <= 12 &&
//                 day >= 1 && day <= 31)
//             {
//                 // VALID
//                 break;
//             }
//         }

//         printf("Invalid format! Enter again (yyyy-mm-dd): ");
//     }
// }

}