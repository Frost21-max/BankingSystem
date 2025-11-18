#include <stdio.h>
#include <mysql/mysql.h>

#define PASSWD "Mydatabases@123"
#define USER "root"


void mysql_query_excuter(const char *, const char *);   //function prototype for connection
void account_creation();


int main() {

    int userInputFor1Menu ,userInputForExit=0;
    printf("--welcome to random internet banking--\n\n");
    while(1){
        printf("01:) Do you want to create a new account\n");
        printf("02:) Do you want to access you account\n");
        printf("03:) Do you want to exit the menu\n\n");      
        printf(":");
        scanf("%d",&userInputFor1Menu);
        switch (userInputFor1Menu)
        {
        case 1:
            // here we will call the function for the new account create
            mysql_query_excuter("create database if not exists accounts",NULL);
            mysql_query_excuter(
                "CREATE TABLE IF NOT EXISTS account_information ("
                "account_no BIGINT PRIMARY KEY,"
                "name VARCHAR(100) NOT NULL,"
                "age INT NOT NULL,"
                "gender ENUM('Male', 'Female', 'Other') NOT NULL,"
                "date_of_birth DATE NOT NULL,"
                "Aadhar_no VARCHAR(20),"
                "Pan_no VARCHAR(20),"
                "phone VARCHAR(15),"
                "email VARCHAR(100),"
                "balance DECIMAL(30,2) NOT NULL DEFAULT 0,"
                "account_type ENUM('Savings','Current') DEFAULT 'Savings',"
                "password_hash VARCHAR(255) NOT NULL,"
                "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
                "updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP"
                ")",
                "accounts");

            // printf("new account\n");
            break;
        
        case 2:
            /*
            Here we will call the funtion for the exisiting account and redirect the user from there
            */
            
            printf("exiting account\n");
            break;
        case 3:
            printf("Thank you for using the random interenet banking \n\n");
            userInputForExit = 1;
            
            break;
        default:
            printf("Invalid Input\n\n");
            continue;
            break;
        }

        if (userInputForExit == 1){break;}
    }
    
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

// void account_creation(){
    
// }


// struct AccountInformation{
//     unsigned int accountNumber;
//     unsigned int age;
//     unsigned int dob;
//     double balance;
//     char name[100];
// };