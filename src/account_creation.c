#include <stdio.h>
#include <mysql/mysql.h>

#define PASSWD "Mydatabases@123"
#define USER "root"
typedef enum {
    MALE=0,
    FEMALE=1,
    OTHER=3
} Gender;
typedef enum {
    SAVINGS=0,
    CURRENT=1
} Account_type;

typedef struct{
    unsigned long long account_no;
    char name;
    unsigned int age;
    Gender gender;
    char date_of_birth[11];
    char aadhar_no[18];
    char pan_no[18];
    char phone[15];
    char email[20];
    unsigned long long balance;
    Account_type type;
} Account;


void mysql_query_excuter(const char *, const char *);   //function prototype for connection


int user_menu();


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

int main(int argc, char const *argv[])
{
    
    return 0;
}

Account acc;
int user_menu() {
    printf("Write down your name.");
    scanf("%c",acc.name);
    printf("Write down your age.");
    scanf("%d",acc.age);
    printf("Write down your Date of Birth(YYYY-MM-DD).");
    scanf("%10s",acc.date_of_birth);
    printf("Write down your Gender(Male=0,Female=1,Other=Any Number).");
    scanf("%d",acc.gender);
    Gender g;
    switch (g)
    {
    case 0:
        return "Male";
    case 1:
        return "Female";
    default:
        return "Other";
    }
    printf("Write down your Aadhar Number.");
    scanf("%s",acc.aadhar_no);
    printf("Write down your Pan Number.");
    scanf("%s",acc.pan_no);
    printf("Write down your Phone Number.");
    scanf("%s",acc.phone);
    printf("Write down your age.");
    scanf("%s",acc.email);
    printf("Write down your Type of Account(Savings=0,Current=1).");
    scanf("%s",acc.type);
    Account_type t;
    switch (t)
    {
    case 0:
        return "Savings";
    case 1:
        return "Current";
    default:
        return "Savings";
    }

    return 0;
}