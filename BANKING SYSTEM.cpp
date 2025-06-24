#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

// Transaction class
class Transaction {
public:
    string actionType;
    float amount;
    string dateTime;

    Transaction(string type, float amt) {
        actionType = type;
        amount = amt;
        time_t now = time(0);
        dateTime = ctime(&now);
        dateTime.pop_back(); // Remove newline
    }

    void displayTransaction() {
        cout << actionType << " of $" << amount << " on " << dateTime << endl;
    }
};

// Bank account class
class BankAccount {
private:
    int accNumber;
    float accBalance;
    vector<Transaction> transHistory;

public:
    BankAccount(int accNo) {
        accNumber = accNo;
        accBalance = 0.0f;
    }

    void makeDeposit(float amt) {
        if (amt <= 0) {
            cout << "Error: Deposit amount must be positive.\n";
            return;
        }
        accBalance += amt;
        transHistory.push_back(Transaction("Deposit", amt));
        cout << "Deposited $" << amt << ". New Balance: $" << accBalance << endl;
    }

    bool makeWithdrawal(float amt, bool log = true) {
        if (amt <= 0) {
            cout << "Error: Withdrawal amount must be positive.\n";
            return false;
        }
        if (amt > accBalance) {
            cout << "Error: Insufficient balance!" << endl;
            return false;
        }
        accBalance -= amt;
        if (log)
            transHistory.push_back(Transaction("Withdrawal", amt));
        cout << "Withdrew $" << amt << ". New Balance: $" << accBalance << endl;
        return true;
    }

    void transferTo(BankAccount &recipient, float amt) {
        if (makeWithdrawal(amt, false)) {
            recipient.makeDeposit(amt);
            transHistory.push_back(Transaction("Transfer to Account " + recipient.getAccountNumberStr(), amt));
            recipient.addTransaction("Received from Account " + getAccountNumberStr(), amt);
            cout << "Transferred $" << amt << " to Account " << recipient.getAccountNumber() << endl;
        }
    }

    void showHistory() {
        cout << "=== Transactions for Account " << accNumber << " ===\n";
        for (Transaction t : transHistory)
            t.displayTransaction();
    }

    float getBalance() {
        return accBalance;
    }

    int getAccountNumber() {
        return accNumber;
    }

    string getAccountNumberStr() {
        return to_string(accNumber);
    }

    void addTransaction(string type, float amt) {
        transHistory.push_back(Transaction(type, amt));
    }
};

// Customer class
class Client {
private:
    string clientName;
    int clientID;
    BankAccount account;

public:
    Client(string name, int id) : account(id) {
        clientName = name;
        clientID = id;
    }

    void showClientInfo() {
        cout << "\nClient ID: " << clientID
             << "\nName: " << clientName
             << "\nAccount No: " << account.getAccountNumber()
             << "\nBalance: $" << account.getBalance() << "\n";
    }

    BankAccount& getAccount() {
        return account;
    }

    int getClientID() {
        return clientID;
    }

    string getName() {
        return clientName;
    }
};

// Find client by ID
Client* findClientByID(vector<Client>& clients, int id) {
    for (auto& c : clients) {
        if (c.getClientID() == id)
            return &c;
    }
    return nullptr;
}

// Main Program
int main() {
    vector<Client> clientList;
    int choice;

    cout << "=== Welcome to CLI Bank System ===\n";

    while (true) {
        cout << "\n1. Create Account";
        cout << "\n2. Deposit";
        cout << "\n3. Withdraw";
        cout << "\n4. Transfer";
        cout << "\n5. Show Account Info";
        cout << "\n6. Show Transaction History";
        cout << "\n0. Exit";
        cout << "\nChoose an option (0 to exit): ";
        cin >> choice;

        if (choice == 0) break;

        if (choice == 1) {
            string name;
            int id;
            cin.ignore(); // Clear newline
            cout << "Enter full name: ";
            getline(cin, name);
            cout << "Enter unique ID: ";
            cin >> id;

            if (findClientByID(clientList, id)) {
                cout << "Error: ID already exists!" << endl;
            } else {
                clientList.push_back(Client(name, id));
                cout << "Account created for " << name << " with ID " << id << endl;
            }
        }

        else if (choice >= 2 && choice <= 6) {
            int id;
            cout << "Enter your ID: ";
            cin >> id;

            Client* client = findClientByID(clientList, id);
            if (!client) {
                cout << "Client not found!" << endl;
                continue;
            }

            if (choice == 2) {
                float amt;
                cout << "Enter amount to deposit: ";
                cin >> amt;
                client->getAccount().makeDeposit(amt);
            }

            else if (choice == 3) {
                float amt;
                cout << "Enter amount to withdraw: ";
                cin >> amt;
                client->getAccount().makeWithdrawal(amt);
            }

            else if (choice == 4) {
                int toID;
                float amt;
                cout << "Enter recipient ID: ";
                cin >> toID;
                cout << "Enter amount to transfer: ";
                cin >> amt;

                Client* recipient = findClientByID(clientList, toID);
                if (!recipient) {
                    cout << "Recipient not found!" << endl;
                } else {
                    client->getAccount().transferTo(recipient->getAccount(), amt);
                }
            }

            else if (choice == 5) {
                client->showClientInfo();
            }

            else if (choice == 6) {
                client->getAccount().showHistory();
            }
        }

        else {
            cout << "Invalid option!" << endl;
        }
    }

    cout << "\nThank you for using CLI Bank System. Goodbye!" << endl;
    return 0;
}
