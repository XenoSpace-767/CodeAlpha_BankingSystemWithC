#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "bank_accounts.dat"

// Account Structure
typedef struct {
    int accountNumber;
    char name[50];
    double balance;
} Account;

// Function Prototypes
void createAccount();
void depositMoney();
void withdrawMoney();
void checkBalance();
void displayAllAccounts();

int main() {
    int choice;

    do {
        printf("\n===========================================\n");
        printf("         C BANK MANAGEMENT SYSTEM          \n");
        printf("===========================================\n");
        printf("1. Create New Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Balance Enquiry\n");
        printf("5. Display All Accounts\n");
        printf("6. Exit\n");
        printf("===========================================\n");
        printf("Enter your choice (1-6): ");

        if (scanf("%d", &choice) != 1) {
            printf("[ERROR] Invalid choice input.\n");
            break;
        }

        switch (choice) {
            case 1: createAccount(); break;
            case 2: depositMoney(); break;
            case 3: withdrawMoney(); break;
            case 4: checkBalance(); break;
            case 5: displayAllAccounts(); break;
            case 6: printf("Exiting Banking System. Goodbye!\n"); break;
            default: printf("[ERROR] Invalid choice! Please enter a number between 1 and 6.\n");
        }
    } while (choice != 6);

    return 0;
}

// Function to create a new bank account
void createAccount() {
    Account acc;
    FILE *file = fopen(FILENAME, "ab");

    if (!file) {
        printf("[ERROR] Could not open database file.\n");
        return;
    }

    printf("\n--- Create New Account ---\n");
    printf("Enter Account Number: ");
    scanf("%d", &acc.accountNumber);

    printf("Enter Customer Name: ");
    scanf(" %[^\n]", acc.name);

    printf("Enter Initial Deposit Amount: $");
    scanf("%lf", &acc.balance);

    if (acc.balance < 0) {
        printf("[ERROR] Deposit amount cannot be negative.\n");
        fclose(file);
        return;
    }

    fwrite(&acc, sizeof(Account), 1, file);
    fclose(file);

    printf("[SUCCESS] Account created successfully for %s!\n", acc.name);
}

// Function to deposit money into an account
void depositMoney() {
    Account acc;
    int accNum, found = 0;
    double amount;

    FILE *file = fopen(FILENAME, "rb+");
    if (!file) {
        printf("[ERROR] No accounts found. Create an account first.\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &accNum);

    while (fread(&acc, sizeof(Account), 1, file)) {
        if (acc.accountNumber == accNum) {
            printf("Current Balance: $%.2lf\n", acc.balance);
            printf("Enter Deposit Amount: $");
            scanf("%lf", &amount);

            if (amount <= 0) {
                printf("[ERROR] Amount must be positive.\n");
                fclose(file);
                return;
            }

            acc.balance += amount;
            fseek(file, -((long)sizeof(Account)), SEEK_CUR);
            fwrite(&acc, sizeof(Account), 1, file);

            printf("[SUCCESS] Deposited $%.2lf. New Balance: $%.2lf\n", amount, acc.balance);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("[ERROR] Account Number %d not found.\n", accNum);
    }

    fclose(file);
}

// Function to withdraw money from an account
void withdrawMoney() {
    Account acc;
    int accNum, found = 0;
    double amount;

    FILE *file = fopen(FILENAME, "rb+");
    if (!file) {
        printf("[ERROR] No accounts found. Create an account first.\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &accNum);

    while (fread(&acc, sizeof(Account), 1, file)) {
        if (acc.accountNumber == accNum) {
            printf("Current Balance: $%.2lf\n", acc.balance);
            printf("Enter Withdrawal Amount: $");
            scanf("%lf", &amount);

            if (amount <= 0) {
                printf("[ERROR] Amount must be positive.\n");
                fclose(file);
                return;
            }

            if (amount > acc.balance) {
                printf("[ERROR] Insufficient balance!\n");
                fclose(file);
                return;
            }

            acc.balance -= amount;
            fseek(file, -((long)sizeof(Account)), SEEK_CUR);
            fwrite(&acc, sizeof(Account), 1, file);

            printf("[SUCCESS] Withdrew $%.2lf. Remaining Balance: $%.2lf\n", amount, acc.balance);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("[ERROR] Account Number %d not found.\n", accNum);
    }

    fclose(file);
}

// Function to check account balance
void checkBalance() {
    Account acc;
    int accNum, found = 0;

    FILE *file = fopen(FILENAME, "rb");
    if (!file) {
        printf("[ERROR] No accounts found. Create an account first.\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &accNum);

    while (fread(&acc, sizeof(Account), 1, file)) {
        if (acc.accountNumber == accNum) {
            printf("\n===========================================\n");
            printf("             ACCOUNT DETAILS               \n");
            printf("===========================================\n");
            printf("Account Number : %d\n", acc.accountNumber);
            printf("Account Holder : %s\n", acc.name);
            printf("Current Balance: $%.2lf\n", acc.balance);
            printf("===========================================\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("[ERROR] Account Number %d not found.\n", accNum);
    }

    fclose(file);
}

// Function to display all registered accounts
void displayAllAccounts() {
    Account acc;

    FILE *file = fopen(FILENAME, "rb");
    if (!file) {
        printf("[ERROR] No accounts found. Create an account first.\n");
        return;
    }

    printf("\n==================================================\n");
    printf("%-15s %-20s %-15s\n", "Account No", "Name", "Balance");
    printf("--------------------------------------------------\n");

    while (fread(&acc, sizeof(Account), 1, file)) {
        printf("%-15d %-20s $%-14.2lf\n", acc.accountNumber, acc.name, acc.balance);
    }

    printf("==================================================\n");
    fclose(file);
}
