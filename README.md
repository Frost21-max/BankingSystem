# BankingSystem
<br>
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