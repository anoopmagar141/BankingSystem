#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ACCOUNTS 50
#define MAX_TRANSACTIONS 10

// Structure for Transaction Log
struct Transaction {
    char type[10];
    float amount;
};

// Structure for Account
struct Account {
    int accountNumber;
    char name[50];
    float balance;
    char creationDate[20];
    struct Transaction transactions[MAX_TRANSACTIONS];
    int transactionCount;
};

// Function prototypes
void initializeAccounts(struct Account accounts[], int *totalAccounts);
void createAccount(struct Account accounts[], int *totalAccounts);
void depositMoney(struct Account accounts[], int totalAccounts);
void withdrawMoney(struct Account accounts[], int totalAccounts);
void displayAccounts(const struct Account accounts[], int totalAccounts);
void applyInterest(struct Account accounts[], int totalAccounts);
void searchAccount(const struct Account accounts[], int totalAccounts);
void showLastTransactions(const struct Account accounts[], int totalAccounts);
void clearInputBuffer();
void generateRandomDate(char *dateBuffer, int dayOffset);
int getInterestRate();

// Helper functions
int findAccountIndex(const struct Account accounts[], int totalAccounts, int accountNumber);

// Main Function
int main() {
    struct Account accounts[MAX_ACCOUNTS];
    int totalAccounts = 0, choice;

    initializeAccounts(accounts, &totalAccounts); // Create predefined accounts

    do {
        // Display menu
        printf("\n========== Banking System Menu =========="
               "\n1. Create Account\n2. Deposit Money\n3. Withdraw Money\n4. Display All Accounts"
               "\n5. Apply Interest to All Accounts\n6. Search for an Account\n7. Show Last 3 Transactions of an Account"
               "\n8. Exit\n=========================================\nEnter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                createAccount(accounts, &totalAccounts);
                break;
            case 2:
                depositMoney(accounts, totalAccounts);
                break;
            case 3:
                withdrawMoney(accounts, totalAccounts);
                break;
            case 4:
                displayAccounts(accounts, totalAccounts);
                break;
            case 5:
                applyInterest(accounts, totalAccounts);
                break;
            case 6:
                searchAccount(accounts, totalAccounts);
                break;
            case 7:
                showLastTransactions(accounts, totalAccounts);
                break;
            case 8:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 8);

    return 0;
}

// Function to clear input buffer
void clearInputBuffer() {
    while (getchar() != '\n');
}

// Function to generate random dates
void generateRandomDate(char *dateBuffer, int dayOffset) {
    time_t now = time(NULL);
    struct tm *timeInfo = localtime(&now);
    timeInfo->tm_mday -= dayOffset; // Subtract dayOffset days
    mktime(timeInfo); // Normalize the time structure
    strftime(dateBuffer, 20, "%d-%m-%Y", timeInfo);
}

// Function to initialize predefined accounts
void initializeAccounts(struct Account accounts[], int *totalAccounts) {
    char *names[] = {"Arohi Karki", "Samir Shrestha", "Saru Magar", "Ganga Pradhan Magar", "Sagar Karki"};
    float initialBalances[] = {1200.50, 2000.00, 3000.75, 1500.25, 500.00};
    int dayOffsets[] = {0, 3, 6, 9, 12};

    for (int i = 0; i < 5; i++) {
        generateRandomDate(accounts[*totalAccounts].creationDate, dayOffsets[i]);
        accounts[*totalAccounts].accountNumber = i + 1;
        strcpy(accounts[*totalAccounts].name, names[i]);
        accounts[*totalAccounts].balance = initialBalances[i];
        accounts[*totalAccounts].transactionCount = 0;
        (*totalAccounts)++;
    }
}
