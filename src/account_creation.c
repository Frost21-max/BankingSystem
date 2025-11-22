#include <stdio.h>
#include <mysql/mysql.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <regex.h>

#define PASSWD "Mydatabases@123"
#define USER "root"
#define MAX_ROWS 100
#define MAX_LENGTH 100

typedef struct
{
    unsigned long long account_no;
    char name[20];
    char gender[10];
    char date_of_birth[11];
    char aadhar_no[18];
    char pan_no[18];
    char phone[15];
    char email[20];
    long double balance;
    char account_type[10];
    char password[10];
} Account;

void buffer();
void mysql_query_excuter(const char *query,
                         const char *database,
                         int permission,
                         char data[MAX_ROWS][20][MAX_LENGTH],
                         int* rows_out); // function prototype for connection
void hideInput();
void showInput();
int user_menu();

void buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) // remove buffer
    {
    }
}

void hideInput()
{
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

void showInput()
{
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

void mysql_query_excuter(const char *query,
                         const char *database,
                         int permission,
                         char data[MAX_ROWS][20][MAX_LENGTH],
                         int* rows_out)
{
    MYSQL *conn = mysql_init(NULL);
    MYSQL_RES *res;
    MYSQL_ROW row;
    int row_count = 0;

    // Check initialization
    if (conn == NULL)
    {
        printf("mysql_init failed\n");
        return;
    }

    // Connect to server
    if (!mysql_real_connect(conn, "localhost", USER, PASSWD, database, 0, NULL, 0))
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
    if (permission == 0)
    {
        mysql_close(conn);
    }
    else
    {
        // Data fetcher
        res = mysql_store_result(conn);
        int num_cols = mysql_num_fields(res); // <- detects number of selected columns
        int no_of_rows = mysql_num_rows(res);
        // printf("Columns returned: %d\n\n", num_cols);
        // printf("rows returned: %d\n\n", no_of_rows);

        while ((row = mysql_fetch_row(res)) && row_count < MAX_ROWS)
        {

            for (int col = 0; col < num_cols; col++)
            {
                if (row[col])
                    strncpy(data[row_count][col], row[col], MAX_LENGTH - 1);
                else
                    strcpy(data[row_count][col], "NULL");

                data[row_count][col][MAX_LENGTH - 1] = '\0';
            }

            row_count++;
        }

        mysql_free_result(res);
        mysql_close(conn);

        
    }
}

// int main()
// {
//     // user_menu();
//     char dataa[MAX_ROWS][20][MAX_LENGTH];
//     int no_of_row;
//     mysql_query_excuter("select * from account_information","accounts",1,dataa,&no_of_row);
//     printf("%s",dataa[0][0]);
//     return 0;
// }

Account acc;
char x[100];
int user_menu()
{
    mysql_query_excuter("create database if not exists accounts", NULL, 0 , NULL , 0 );
    mysql_query_excuter(
        "CREATE TABLE IF NOT EXISTS account_information ("
        "account_no BIGINT PRIMARY KEY,"
        "name VARCHAR(100) NOT NULL,"
        "gender ENUM('Male', 'Female', 'Other') NOT NULL,"
        "date_of_birth DATE NOT NULL,"
        "Aadhar_no VARCHAR(20) UNIQUE NOT NULL,"
        "Pan_no VARCHAR(20) UNIQUE NOT NULL,"
        "phone VARCHAR(15) NOT NULL,"
        "email VARCHAR(100),"
        "balance DECIMAL(30,2) NOT NULL DEFAULT 0.00,"
        "account_type ENUM('Savings','Current') DEFAULT 'Savings',"
        "password_hash VARCHAR(100) NOT NULL,"
        "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
        "updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP"
        ")",
        "accounts", 0 , NULL , 0);
    printf("\n\n-----------------Registration Starts!---------------------\n\n");
    // ---------------------- account no ----------------------
    srand(time(NULL));
    char n[13];
    for (int i = 0; i < 12; i++)
        n[i] = '0' + rand() % 10;
    n[12] = '\0';
    acc.account_no = strtoull(n, NULL, 10); // here 10 means base decimal of 10

    // printf("%llu\n", acc.account_no);

    // ---------------------- NAME ----------------------
    printf("Enter your Name: ");
    fgets(acc.name, sizeof(acc.name), stdin); // for name
    acc.name[strcspn(acc.name, "\n")] = 0;
    strcpy(acc.name, x);
    // printf("%s\n", acc.name);
    buffer();

    // ---------------------- GENDER ----------------------
    char genderS[10];
    regex_t rre;
    const char *parrrtern = "^[a-zA-Z]+$";
    while (1)
    {

        printf("Enter your Gender: ");
        fgets(genderS, sizeof(genderS), stdin);
        genderS[strcspn(genderS, "\n")] = '\0';
        regcomp(&rre, parrrtern, REG_EXTENDED);
        if (regexec(&rre, genderS, 0, NULL, 0) == 0)
        {
            break;
        }
        printf("invalid input\n");
    }

    for (int i = 0; genderS[i]; i++)
    {
        genderS[i] = tolower(genderS[i]);
    }
    genderS[0] = toupper(genderS[0]);
    if (strcmp(genderS, "Male") == 0)
    {
        strcpy(acc.gender, "Male");
    }
    else if (strcmp(genderS, "Female") == 0)
    {
        strcpy(acc.gender, "Female");
    }
    else
    {
        strcpy(acc.gender, "Other");
    }
    regfree(&rre);
    // printf("%s",acc.gender);

    // ---------------------- DATE OF BIRTH ----------------------

    printf("Enter the date of birth (yyyy-mm-dd): ");

    while (1)
    {
        fgets(acc.date_of_birth, sizeof(acc.date_of_birth), stdin);
        acc.date_of_birth[strcspn(acc.date_of_birth, "\n")] = '\0'; // remove newline

        int year, month, day;

        // Check correct format
        if (sscanf(acc.date_of_birth, "%4d-%2d-%2d", &year, &month, &day) == 3)
        {
            // Basic logical checks
            if (year >= 1900 && year <= 2025 &&
                month >= 1 && month <= 12 &&
                day >= 1 && day <= 31)
            {
                // -------------------------
                //   CHECK AGE >= 18
                // -------------------------
                time_t t = time(NULL);
                struct tm *now = localtime(&t);

                int curr_year = now->tm_year + 1900;
                int curr_month = now->tm_mon + 1;
                int curr_day = now->tm_mday;

                int age = curr_year - year;

                // If birthday not reached yet
                if (curr_month < month ||
                    (curr_month == month && curr_day < day))
                {
                    age--;
                }

                if (age >= 18)
                {
                    break;
                }
                else
                {
                    printf("You must be at least 18 years old!\n Enter again: ");
                    continue;
                }
            }
        }

        printf("Invalid format! Enter again (yyyy-mm-dd): ");
    }

    buffer();

    // ---------------------- aadhar no ----------------------
    // int duplcate = 0;
    while (1)
    {

        printf("Enter the aadhar Number :");
        fgets(acc.aadhar_no, sizeof(acc.aadhar_no), stdin);
        acc.aadhar_no[strcspn(acc.aadhar_no, "\n")] = 0;
        int ok = 1;
        if (strlen(acc.aadhar_no) == 12)
        {
            for (int i = 0; i < 12; i++)
                if (!isdigit(acc.aadhar_no[i]))
                    ok = 0;

            if (ok)
            {
                break;
            }
        }
        printf("Invalid Aadhar! Try again.\n");
    }
    // printf("%s", acc.aadhar_no);

    // ---------------------- pan no ----------------------
    regex_t tt;
    const char *pattern = "^[A-Z]{5}[0-9]{4}[A-Z]{1}";
    while (1)
    {

        printf("Enter the PAN Number :");
        fgets(acc.pan_no, sizeof(acc.pan_no), stdin);
        acc.pan_no[strcspn(acc.pan_no, "\n")] = 0;
        regcomp(&tt, pattern, REG_EXTENDED);
        if (regexec(&tt, acc.pan_no, 0, NULL, 0) == 0)
        {
            break;
        }
        printf("Invalid PAN! Try again.\n");
    }
    regfree(&tt);
    // ---------------------- phone no ----------------------
    while (1)
    {
        printf("Enter your Phone Number: ");
        fgets(acc.phone, sizeof(acc.phone), stdin);
        acc.phone[strcspn(acc.phone, "\n")] = 0;

        int ok = 1;
        if (strlen(acc.phone) == 10)
        {
            for (int i = 0; i < 10; i++)
            {
                if (!isdigit(acc.phone[i]))
                {
                    ok = 0;
                    break;
                }
            }

            if (ok)
            {
                break;
            }
        }

        printf("Invalid Phone Number! Try again.\n");
    }
    // ---------------------- email ---------------------------
    regex_t r;
    const char *pat = "^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$";
    while (1)
    {
        printf("Enter email: ");
        fgets(acc.email, sizeof(acc.email), stdin);
        acc.email[strcspn(acc.email, "\n")] = 0;
        regcomp(&r, pat, REG_EXTENDED);
        if (regexec(&r, acc.email, 0, NULL, 0) == 0)
            break;
        printf("Invalid Email ! Try again\n");
    }
    regfree(&r);
    // ---------------------- ACCOUNT TYPE ----------------------
    char typeS[10];

    const char *partten = "^[a-zA-Z]+$";
    while (1)
    {
        printf("Choose the type of Account: ");
        fgets(typeS, sizeof(typeS), stdin);
        typeS[strcspn(typeS, "\n")] = '\0';
        regcomp(&tt, partten, REG_EXTENDED);
        if (regexec(&tt, typeS, 0, NULL, 0) == 0)
        {
            break;
        }
        printf("invaid input\n");
    }
    regfree(&tt);

    for (int i = 0; typeS[i]; i++)
    {
        typeS[i] = tolower(typeS[i]);
    }
    typeS[0] = toupper(typeS[0]);
    if (strcmp(typeS, "Savings") == 0)
    {
        strcpy(acc.account_type, "Savings");
    }
    else if (strcmp(typeS, "Current") == 0)
    {
        strcpy(acc.account_type, "Current");
    }
    else
    {
        strcpy(acc.account_type, "Savings");
    }
    // printf("%s",acc.account_type);

    // ---------------------- PASSWORD ----------------------

    while (1)
    {
        printf("Create Password (exactly 6 characters): ");
        hideInput();
        fgets(acc.password, sizeof(acc.password), stdin);
        showInput();
        // printf("\n");

        acc.password[strcspn(acc.password, "\n")] = 0; // remove newline

        if (strlen(acc.password) != 6)
        {
            printf("Password must be exactly 6 characters!\n");
            printf("Try again!\n");
            continue;
        }

        break; // valid password
    }
    showInput();
    printf("\n\n-----------------Registration complete!---------------------\n");
    char query[1000];

    snprintf(query, sizeof(query),
             "INSERT INTO account_information ("
             "account_no, name, gender, date_of_birth, Aadhar_no, Pan_no, phone, email, "
             "balance, account_type, password_hash"
             ") VALUES ("
             "%llu, '%s', '%s', '%s', '%s', '%s', '%s', '%s', %.2Lf, '%s', '%s'"
             ");",
             acc.account_no,
             acc.name,
             acc.gender,
             acc.date_of_birth,
             acc.aadhar_no,
             acc.pan_no,
             acc.phone,
             acc.email,
             acc.balance, // long double → %.2Lf
             acc.account_type,
             acc.password);
    mysql_query_excuter(query, "accounts", 0 , NULL , 0);

    printf("-------------Your account-------------\n\n\n");
    printf("\t\t Account Number  : %lld\n",acc.account_no);
    printf("\t\t Account Holder  : %s\n",x);
    printf("\t\t Account Type    : %s\n",acc.account_type);
    printf("\t\t Account Balance : %.2Lf\n",acc.balance);
    printf("\n\n");
    
}
