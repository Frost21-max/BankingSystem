#include <stdio.h>
#include "banking.h"

int main(){
    printf("----------------- WELCOME TO OUR BANKING SYSTEM -----------------");
    int choice;

    while (1) 
    {
        printf("\n==============================\n");
        printf("      ONLINE BANKING MENU     \n");
        printf("==============================\n");
        printf("1. Create Account\n");
        printf("2. Account Login\n");
        printf("3. View Account Details\n");
        printf("4. Deposit Money\n");
        printf("5. Withdraw Money\n");
        printf("6. Transfer Funds\n");
        printf("7. Transaction History\n");
        printf("8. Request Loan\n");
        printf("9. Loan Approval (Manager)\n");
        printf("0. Exit\n");
        printf("==============================\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                createAccount();
                break;

            case 2:
                loginMenu();
                break;

            case 3:
                viewAccountDetails();
                break;

            case 4:
                depositMoney();
                break;

            case 5:
                withdrawMoney();
                break;

            case 6:
                transferFunds();
                break;

            case 7:
                transactionHistory();
                break;

            case 8:
                requestLoan();
                break;

            case 9:
                loanApproval();
                break;

            case 0:
                printf("\nThank you for using Online Banking System!\n");
                exit(0);

            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }
    return 0;
}