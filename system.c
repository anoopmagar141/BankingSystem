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

// Function to find account index by account number
int findAccountIndex(const struct Account accounts[], int totalAccounts, int accountNumber) {
    for (int i = 0; i < totalAccounts; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            return i;
        }
    }
    return -1; // Account not found
}

// Function to create a new account
void createAccount(struct Account accounts[], int *totalAccounts) {
    if (*totalAccounts >= MAX_ACCOUNTS) {
        printf("Account limit reached. Cannot create more accounts.\n");
        return;
    }

    struct Account newAccount;
    newAccount.accountNumber = *totalAccounts + 1;

    printf("Enter Name: ");
    fgets(newAccount.name, sizeof(newAccount.name), stdin);
    newAccount.name[strcspn(newAccount.name, "\n")] = 0;

    printf("Enter Initial Balance: ");
    if (scanf("%f", &newAccount.balance) != 1 || newAccount.balance < 0) {
        printf("Invalid initial balance. Account creation failed.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    time_t now = time(NULL);
    struct tm *timeInfo = localtime(&now);
    strftime(newAccount.creationDate, 20, "%d-%m-%Y", timeInfo);

    newAccount.transactionCount = 0;

    accounts[*totalAccounts] = newAccount;
    (*totalAccounts)++;

    printf("Account created successfully! Please note your Account Number: %d\n", newAccount.accountNumber);
}

// Function to deposit money
void depositMoney(struct Account accounts[], int totalAccounts) {
    int accNum;
    float amount;

    printf("Enter Account Number: ");
    scanf("%d", &accNum);

    int index = findAccountIndex(accounts, totalAccounts, accNum);
    if (index == -1) {
        printf("Account not found.\n");
        return;
    }

    printf("Enter Deposit Amount: ");
    if (scanf("%f", &amount) != 1 || amount <= 0) {
        printf("Invalid deposit amount.\n");
        clearInputBuffer();
        return;
    }

    accounts[index].balance += amount;

    struct Transaction newTransaction = {"Deposit", amount};
    accounts[index].transactions[accounts[index].transactionCount % MAX_TRANSACTIONS] = newTransaction;
    accounts[index].transactionCount++;

    printf("Deposit successful! New Balance: %.2f\n", accounts[index].balance);
}

// Function to withdraw money
void withdrawMoney(struct Account accounts[], int totalAccounts) {
    int accNum;
    float amount;

    printf("Enter Account Number: ");
    scanf("%d", &accNum);

    int index = findAccountIndex(accounts, totalAccounts, accNum);
    if (index == -1) {
        printf("Account not found.\n");
        return;
    }

    printf("Enter Withdrawal Amount: ");
    if (scanf("%f", &amount) != 1 || amount <= 0) {
        printf("Invalid withdrawal amount.\n");
        clearInputBuffer();
        return;
    }

    if (accounts[index].balance < amount) {
        printf("Insufficient balance.\n");
        return;
    }

    accounts[index].balance -= amount;

    struct Transaction newTransaction = {"Withdraw", amount};
    accounts[index].transactions[accounts[index].transactionCount % MAX_TRANSACTIONS] = newTransaction;
    accounts[index].transactionCount++;

    printf("Withdrawal successful! New Balance: %.2f\n", accounts[index].balance);
}

// Function to display all accounts
void displayAccounts(const struct Account accounts[], int totalAccounts) {
    if (totalAccounts == 0) {
        printf("No accounts to display.\n");
        return;
    }

    printf("\nDisplaying all accounts:\n");
    for (int i = 0; i < totalAccounts; i++) {
        printf("Account Number: %d\nName: %s\nBalance: %.2f\nCreation Date: %s\n\n",
               accounts[i].accountNumber, accounts[i].name, accounts[i].balance, accounts[i].creationDate);
    }
}

// Function to apply interest
void applyInterest(struct Account accounts[], int totalAccounts) {
    float rate = getInterestRate();
    printf("Applying %.2f%% interest to all accounts...\n", rate);

    for (int i = 0; i < totalAccounts; i++) {
        accounts[i].balance += accounts[i].balance * (rate / 100);
        printf("Account Number: %d, Name: %s, New Balance: %.2f\n",
               accounts[i].accountNumber, accounts[i].name, accounts[i].balance);
    }
}

// Function to get interest rate from the user
int getInterestRate() {
    int rate;
    printf("Enter interest rate: ");
    while (scanf("%d", &rate) != 1 || rate < 0) {
        printf("Invalid rate. Please enter a positive number: ");
        clearInputBuffer();
    }
    return rate;
}

// Function to search for an account
void searchAccount(const struct Account accounts[], int totalAccounts) {
    int accNum;
    printf("Enter Account Number: ");
    scanf("%d", &accNum);

    int index = findAccountIndex(accounts, totalAccounts, accNum);
    if (index == -1) {
        printf("Account not found.\n");
        return;
    }

    printf("Account Found!\nAccount Number: %d\nName: %s\nBalance: %.2f\nCreation Date: %s\n",
           accounts[index].accountNumber, accounts[index].name, accounts[index].balance, accounts[index].creationDate);
}

// Function to show last 3 transactions
void showLastTransactions(const struct Account accounts[], int totalAccounts) {
    int accNum;
    printf("Enter Account Number: ");
    scanf("%d", &accNum);

    int index = findAccountIndex(accounts, totalAccounts, accNum);
    if (index == -1) {
        printf("Account not found.\n");
        return;
    }

    int count = accounts[index].transactionCount < 3 ? accounts[index].transactionCount : 3;
    printf("Last %d Transactions:\n", count);

    for (int i = accounts[index].transactionCount - 1, j = 0; j < count; i--, j++) {
        int transactionIndex = i % MAX_TRANSACTIONS;
        printf("%s: %.2f\n", accounts[index].transactions[transactionIndex].type, accounts[index].transactions[transactionIndex].amount);
    }
}
