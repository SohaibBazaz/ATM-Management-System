#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct User
{
    string username;
    string pin;
    double balance;
};

User currentUser;  // Declare currentUser as a global variable

void saveUser(const User& user)
{
    ofstream file("users.txt", ios::app);

    if (file.is_open())
    {
        file << user.username << "," << user.pin << "," << user.balance << "\n";
        file.close();
        cout << "User account created successfully.\n";
    }
    else {
        cerr << "Unable to open the file.\n";
    }
}

bool userExists(const string& username)
{
    ifstream file("users.txt");

    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            size_t pos = line.find(",");
            string savedUsername = line.substr(0, pos);

            if (username == savedUsername)
            {
                file.close();
                return true;
            }
        }
        file.close();
    }
    else {
        cout << "Unable to open the file.\n";
    }

    return false;
}

bool authenticateUser(const string& username, const string& pin, User& user) {
    ifstream file("users.txt");

    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            int pos = line.find(",");
            string savedUsername = line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find(",");
            string savedPin = line.substr(0, pos);
            line.erase(0, pos + 1);

            double savedBalance = stod(line);

            if (username == savedUsername && pin == savedPin)
            {
                user.username = savedUsername;
                user.pin = savedPin;
                user.balance = savedBalance;
                file.close();
                return true;
            }
        }
        file.close();
    }
    else {
        cout << "Unable to open the file.\n";
    }

    return false;
}

void displayMenu(User& user)
{
    int choice;
    double amount;

    do {
        cout << "\nATM Menu:\n";
        cout << "\n----------------\n";
        cout << "1. Withdraw\n";
        cout << "2. Deposit\n";
        cout << "3. Check Balance\n";
        cout << "4. Exit\n";
        cout << "----------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter the amount to withdraw: ";
            cin >> amount;
            if (amount > 0 && amount <= currentUser.balance)
            {
                currentUser.balance -= amount;
                cout << "Withdrawal successful. Current balance: $" << currentUser.balance << endl;
            }
            else {
                cout << "Invalid amount or insufficient funds.\n";
            }
            break;
        case 2:
            cout << "Enter the amount to deposit: ";
            cin >> amount;
            if (amount > 0) {
                currentUser.balance += amount;
                cout << "Deposit successful. Current balance: $" << currentUser.balance << endl;
            }
            else {
                cout << "Invalid amount.\n";
            }
            break;
        case 3:
            cout << "Current balance: $" << currentUser.balance << endl;
            break;
        case 4:
            cout << "Exiting ATM.\n";
            break;
        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while (choice != 4);
}
int main()
{
    int choice;
    system("Color 30");

    while (true) {
        cout << "\n\t\t\t\t\t\tWelcome to the ATM!\n";
        cout << "\n----------------\n";
        cout << "1. Log In\n";
        cout << "2. Create Account\n";
        cout << "3. Exit\n";
        cout << "----------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Username: ";
            cin >> currentUser.username;

            cout << "Enter PIN: ";
            cin >> currentUser.pin;

            if (userExists(currentUser.username) && authenticateUser(currentUser.username, currentUser.pin, currentUser)) {
                cout << "Authentication successful. Welcome, " << currentUser.username << "!\n";
                displayMenu(currentUser);
            }
            else {
                cout << "Authentication failed. Invalid username or PIN.\n";
            }
            break;
        case 2:
            cout << "Enter Username: ";
            cin >> currentUser.username;

            cout << "Enter PIN: ";
            cin >> currentUser.pin;

            cout << "Enter deposit amount : ";
            cin >> currentUser.balance;
            // Set balance to zero only if it's a new account
           // currentUser.balance = 0.0;

            saveUser(currentUser);
            break;
        case 3:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }
        if (choice == 3)
            break;
    }

    return 0;
}