#include <iostream>
#include <string>
#include <vector>
#include <iomanip> // for std::setprecision and std::fixed

using namespace std;

// Class to represent a bank account
class BankAccount {
private:
    string ownerName;
    int accountNumber;
    double balance;
    string password;

public:
    // Constructor
    BankAccount(string name, int number, double initialBalance, string pwd) {
        ownerName = name;
        accountNumber = number;
        balance = initialBalance;
        password = pwd;
    }

    // Function to deposit money
    void deposit(double amount) {
        balance += amount;
        cout << "Deposited $" << amount << " into account " << accountNumber << endl;
    }

    // Function to withdraw money
    bool withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            cout << "Withdrawn $" << amount << " from account " << accountNumber << endl;
            return true;
        } else {
            cout << "Insufficient funds in account " << accountNumber << endl;
            return false;
        }
    }

    // Function to check balance
    double getBalance() const {
        return balance;
    }

    // Function to display account information
    void display() const {
        cout << "Account Information\n";
        cout << "Owner Name: " << ownerName << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: $" << fixed << setprecision(2) << balance << endl;
    }

    // Function to authenticate user
    bool authenticate(string pwd) const {
        return password == pwd;
    }

    // Function to get account number
    int getAccountNumber() const {
        return accountNumber;
    }

    // Function to transfer funds to another account
    bool transfer(BankAccount& recipient, double amount) {
        if (amount <= balance) {
            balance -= amount;
            recipient.deposit(amount);
            cout << "Transferred $" << amount << " to account " << recipient.getAccountNumber() << endl;
            return true;
        } else {
            cout << "Insufficient funds in account " << accountNumber << endl;
            return false;
        }
    }
};

// Function to find an account by account number
BankAccount* findAccount(vector<BankAccount>& accounts, int accountNumber) {
    for (auto& account : accounts) {
        if (accountNumber == account.getAccountNumber()) {
            return &account;
        }
    }
    return nullptr;
}

int main() {
    vector<BankAccount> accounts;

    // Creating some sample accounts with passwords
    BankAccount account1("User1", 001, 500.0, "pass123");
    BankAccount account2("User2", 002, 1000.0, "pass456");

    // Adding them to the vector of accounts
    accounts.push_back(account1);
    accounts.push_back(account2);

    // Authentication loop
    bool authenticated = false;
    int attempts = 0;
    while (!authenticated && attempts < 3) {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        // Find account by username and authenticate
        for (auto& account : accounts) {
            if (account.authenticate(password)) {
                authenticated = true;
                cout << "Authentication successful!\n";
                break;
            }
        }

        if (!authenticated) {
            cout << "Authentication failed. Please try again.\n";
            attempts++;
        }
    }

    if (authenticated) {
        int choice;
        do {
            // Menu for banking operations
            cout << "\nSelect an option:\n";
            cout << "1. Deposit\n";
            cout << "2. Withdraw\n";
            cout << "3. Transfer\n";
            cout << "4. Check Balance\n";
            cout << "5. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    double amount;
                    cout << "Enter deposit amount: $";
                    cin >> amount;
                    account1.deposit(amount); // Example with account1, can be expanded to handle multiple accounts
                    break;
                }
                case 2: {
                    double amount;
                    cout << "Enter withdrawal amount: $";
                    cin >> amount;
                    account1.withdraw(amount); // Example with account1, can be expanded to handle multiple accounts
                    break;
                }
                case 3: {
                    int recipientAccountNumber;
                    double amount;
                    cout << "Enter recipient's account number: ";
                    cin >> recipientAccountNumber;
                    BankAccount* recipient = findAccount(accounts, recipientAccountNumber);
                    if (recipient != nullptr) {
                        cout << "Enter transfer amount: $";
                        cin >> amount;
                        account1.transfer(*recipient, amount); // Example transferring from account1 to recipient
                    } else {
                        cout << "Recipient account not found.\n";
                    }
                    break;
                }
                case 4:
                    account1.display(); // Example with account1, can be expanded to handle multiple accounts
                    break;
                case 5:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
                    break;
            }
        } while (choice != 5);
    } else {
        cout << "Authentication failed. Exiting...\n";
    }

    return 0;
}
