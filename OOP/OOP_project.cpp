#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <regex>
using namespace std;

vector<string> expenseCategories = {
        "Food",
        "Transportation",
        "Entertainment",
        "Utilities",
        "Shopping",
        "Healthcare",
        "Travel",
        "Education",
        "Gifts",
        "Hobbies",
        "Rent",
        "Subscriptions",
        "Charity",
        "Personal Care",
};

class Transaction {
private:
    double amount;
    string category;
    time_t timestamp;
public:
    Transaction(double amount, const string& category)
            : amount(amount), category(category), timestamp(time(nullptr)) {}

    double getAmount() const {
        return amount;
    }

    const string& getCategory() const {
        return category;
    }

    time_t getTimestamp() const {
        return timestamp;
    }
};

class Card {
private:
    string name;
    double balance;
public:
    Card(const string& name) : name(name), balance(0.0) {}

    void deposit(double amount) {
        balance += amount;
    }

    bool withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            return true;
        }
        return false;
    }

    double getBalance() const {
        return balance;
    }

    const string& getName() const {
        return name;
    }
};

class Wallet {
private:
    string name;
    double balance;
public:
    Wallet(const string& name) : name(name), balance(0.0) {}

    void deposit(double amount) {
        balance += amount;
    }

    bool withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            return true;
        }
        return false;
    }

    double getBalance() const {
        return balance;
    }

    const string& getname() const {
        return name;
    }


};

class FinanceManager {
private:
    vector<Wallet> wallets;
    vector<Card> cards;
    vector<Transaction> transactions;

    string date(time_t timestamp) const {
        tm* timeInfo = localtime(&timestamp);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeInfo);
        return buffer;
    }



    void reportsSave(const vector<Transaction>& transactions, time_t startTime, time_t endTime) {
        ofstream file("financial_reports.txt");
        if (file.is_open()) {
            file << "Financial Reports for "
                 << date(startTime) << " - "
                 << date(endTime) << ":\n";

            file << "Detailed Transactions:\n";
            for (const Transaction& transaction : transactions) {
                file << "Date: " << date(transaction.getTimestamp())
                     << " | Amount: $" << transaction.getAmount()
                     << " | Category: " << transaction.getCategory() << "\n";
            }

            file.close();
            cout << "Reports saved to 'financial_reports.txt'." << endl;
        } else {
            cout << "Error: Unable to save reports to file." << endl;
        }
    }
public:
    void addWallet(const Wallet& wallet) {
        wallets.push_back(wallet);
    }

    vector<Wallet>& getWallets() {
        return wallets;
    }

    void removeWallet(const string& walletName) {
        auto it = remove_if(wallets.begin(), wallets.end(),
                            [&walletName](const Wallet& wallet) {
                                return wallet.getname() == walletName;
                            });

        if (it != wallets.end()) {
            wallets.erase(it, wallets.end());
            cout << "Wallet removed successfully." << endl;
        } else {
            cout << "Wallet not found." << endl;
        }
    }

    void addCard(const Card& card) {
        cards.push_back(card);
    }

    void removeCard(const string& cardName) {
        auto it = remove_if(cards.begin(), cards.end(),
                            [&cardName](const Card& card) {
                                return card.getName() == cardName;
                            });

        if (it != cards.end()) {
            cards.erase(it, cards.end());
            cout << "Card removed successfully." << endl;
        } else {
            cout << "Card not found." << endl;
        }
    }

    vector<Card>& getCards() {
        return cards;
    }

    void addTransaction(const Transaction& transaction) {
        transactions.push_back(transaction);
    }

    vector<Transaction> getTransactionsForPeriod(time_t startTime, time_t endTime) const {
        vector<Transaction> selectedTransactions;
        for (const Transaction& transaction : transactions) {
            if (transaction.getTimestamp() >= startTime && transaction.getTimestamp() <= endTime) {
                selectedTransactions.push_back(transaction);
            }
        }
        return selectedTransactions;
    }

    void generateTopExpenses(const vector<Transaction>& transactions, const string& period, time_t startTime, time_t endTime) {
        cout << "Top 3 Expenses in " << period << ":\n";

        map<double, string, greater<double>> expenseMap;

        for (const Transaction& transaction : transactions) {
            if (transaction.getTimestamp() >= startTime && transaction.getTimestamp() <= endTime) {
                expenseMap[transaction.getAmount()] = transaction.getCategory();
            }
        }

        int count = 0;
        for (const auto& expense : expenseMap) {
            if (count >= 3) break;
            cout << setw(15) << expense.second << ": $" << expense.first << endl;
            count++;
        }
    }

    void generateTopCategories(const vector<Transaction>& transactions, const string& period, time_t startTime, time_t endTime) {
        cout << "Top 3 Categories in " << period << ":\n";

        map<string, double> categoryMap;

        for (const Transaction& transaction : transactions) {
            if (transaction.getTimestamp() >= startTime && transaction.getTimestamp() <= endTime) {
                categoryMap[transaction.getCategory()] += transaction.getAmount();
            }
        }

        vector<pair<string, double>> categoryList;
        for (const auto& category : categoryMap) {
            categoryList.push_back(category);
        }

        sort(categoryList.begin(), categoryList.end(), [](const pair<string, double>& a, const pair<string, double>& b) {
            return a.second > b.second;
        });

        int count = 0;
        for (const auto& category : categoryList) {
            if (count >= 3) break;
            cout << setw(15) << category.first << ": $" << category.second << endl;
            count++;
        }
    }

    void generateReports(time_t startTime, time_t endTime) {
        vector<Transaction> selectedTransactions = getTransactionsForPeriod(startTime, endTime);

        cout << "Financial Reports for "
             << date(startTime) << " - "
             << date(endTime) << ":\n";

        generateTopExpenses(selectedTransactions, "Week", startTime, endTime);
        generateTopExpenses(selectedTransactions, "Month", startTime, endTime);

        generateTopCategories(selectedTransactions, "Week", startTime, endTime);
        generateTopCategories(selectedTransactions, "Month", startTime, endTime);

        reportsSave(selectedTransactions, startTime, endTime);
    }


};

void Wallet_deposit(FinanceManager& financeManager) {
    string walletName;
    double amount;
    for (Wallet& wallet : financeManager.getWallets()) {
        cout << wallet.getname() << endl;
    }
    cout << "Select a wallet: " << endl;
    cin.ignore();
    getline(cin, walletName);
    cout << "Enter deposit amount: ";
    cin >> amount;

    bool walletFound = false;
    for (Wallet& wallet : financeManager.getWallets()) {
        if (wallet.getname() == walletName) {
            wallet.deposit(amount);
            cout << "Deposit successful. New balance: $" << wallet.getBalance() << endl;

            financeManager.addTransaction(Transaction(amount, "Deposit"));

            walletFound = true;
            break;
        }
    }

    if (!walletFound) {
        cout << "Wallet not found." << endl;
    }
}

void Wallet_withdraw(FinanceManager& financeManager) {
    string walletName;
    double amount;
    for (Wallet& wallet : financeManager.getWallets()) {
        cout << wallet.getname() << endl;
    }
    cout << "Select a wallet: " << endl;
    cin.ignore();
    getline(cin, walletName);
    cout << "Enter withdrawal amount: ";
    cin >> amount;

    bool walletFound = false;
    for (Wallet& wallet : financeManager.getWallets()) {
        if (wallet.getname() == walletName) {
            if (wallet.withdraw(amount)) {
                cout << "Withdrawal successful. New balance: $" << wallet.getBalance() << endl;

                financeManager.addTransaction(Transaction(-amount, "Withdrawal"));

            } else {
                cout << "Insufficient balance." << endl;
            }
            walletFound = true;
            break;
        }
    }

    if (!walletFound) {
        cout << "Wallet not found." << endl;
    }
}

void Add_expence(FinanceManager& financeManager) {
    double amount;
    int categoryChoice;
    string accountName;

    cout << "Enter expense amount: ";
    cin >> amount;

    cout << "Select account type (1. Wallet, 2. Card): ";
    int accountTypeChoice;
    cin >> accountTypeChoice;

    if (accountTypeChoice == 1) {
        cout << "Select wallet: ";
        cin.ignore();
        getline(cin, accountName);
    } else if (accountTypeChoice == 2) {
        cout << "Select card: ";
        cin.ignore();
        getline(cin, accountName);
    } else {
        cout << "Invalid account type choice." << endl;
        return;
    }

    cout << "Select expense category:" << endl;
    for (int i = 0; i < expenseCategories.size(); ++i) {
        cout << i + 1 << ". " << expenseCategories[i] << endl;
    }
    cin >> categoryChoice;

    if (categoryChoice >= 1 && categoryChoice <= expenseCategories.size()) {
        string category = expenseCategories[categoryChoice - 1];

        if (accountTypeChoice == 1) {
            for (Wallet& wallet : financeManager.getWallets()) {
                if (wallet.getname() == accountName) {
                    if (wallet.withdraw(amount)) {
                        financeManager.addTransaction(Transaction(-amount, category));
                        cout << "Expense added successfully." << endl;
                        return;
                    } else {
                        cout << "Insufficient balance in the selected wallet." << endl;
                        return;
                    }
                }
            }
            cout << "Selected wallet not found." << endl;
        } else if (accountTypeChoice == 2) {
            for (Card& card : financeManager.getCards()) {
                if (card.getName() == accountName) {
                    if (card.withdraw(amount)) {
                        financeManager.addTransaction(Transaction(-amount, category));
                        cout << "Expense added successfully." << endl;
                        return;
                    } else {
                        cout << "Insufficient balance in the selected card." << endl;
                        return;
                    }
                }
            }
            cout << "Selected card not found." << endl;
        }
    } else {
        cout << "Invalid category choice." << endl;
    }
}

void Reports(FinanceManager& financeManager) {
    time_t startTime, endTime;
    cout << "Enter start date and time (YYYY-MM-DD HH:MM:SS): ";
    string startDateTimeStr;
    getline(cin, startDateTimeStr);
    tm startDateTime = {};
    istringstream ssStart(startDateTimeStr);
    ssStart >> get_time(&startDateTime, "%Y-%m-%d %H:%M:%S");
    startTime = mktime(&startDateTime);

    cout << "Enter end date and time (YYYY-MM-DD HH:MM:SS): ";
    string endDateTimeStr;
    getline(cin, endDateTimeStr);
    tm endDateTime = {};
    istringstream ssEnd(endDateTimeStr);
    ssEnd >> get_time(&endDateTime, "%Y-%m-%d %H:%M:%S");
    endTime = mktime(&endDateTime);

    financeManager.generateReports(startTime, endTime);
    cout << "Reports generated and saved." << endl;
}

void Add_wallet(FinanceManager& financeManager) {
    string walletName;
    cout << "Enter wallet name: ";
    cin.ignore();
    getline(cin, walletName);

    Wallet newWallet(walletName);
    financeManager.addWallet(newWallet);

    cout << "Wallet added successfully." << endl;
}

void Remove_wallet(FinanceManager& financeManager) {
    string walletName;
    cout << "Enter wallet name to remove: ";
    cin.ignore();
    getline(cin, walletName);

    financeManager.removeWallet(walletName);
}

void Deposit_to_card(FinanceManager& financeManager) {
    string cardName;
    double amount;
    for (Card& card : financeManager.getCards()) {
        cout << card.getName() << endl;
    }
    cout << "Select a card: " << endl;
    cin.ignore();
    getline(cin, cardName);
    cout << "Enter deposit amount: ";
    cin >> amount;

    bool cardFound = false;
    for (Card& card : financeManager.getCards()) {
        if (card.getName() == cardName) {
            card.deposit(amount);
            cout << "Deposit successful. New balance: $" << card.getBalance() << endl;

            financeManager.addTransaction(Transaction(amount, "Card Deposit"));

            cardFound = true;
            break;
        }
    }

    if (!cardFound) {
        cout << "Card not found." << endl;
    }
}

void Withdraw_from_card(FinanceManager& financeManager) {
    string cardName;
    double amount;
    for (Card& card : financeManager.getCards()) {
        cout << card.getName() << endl;
    }
    cout << "Select a card: " << endl;
    cin.ignore();
    getline(cin, cardName);
    cout << "Enter withdrawal amount: ";
    cin >> amount;

    bool cardFound = false;
    for (Card& card : financeManager.getCards()) {
        if (card.getName() == cardName) {
            if (card.withdraw(amount)) {
                cout << "Withdrawal successful. New balance: $" << card.getBalance() << endl;

                financeManager.addTransaction(Transaction(-amount, "Card Withdrawal"));

            } else {
                cout << "Insufficient balance." << endl;
            }
            cardFound = true;
            break;
        }
    }

    if (!cardFound) {
        cout << "Card not found." << endl;
    }
}

void Add_card(FinanceManager& financeManager) {
    string cardName;
    cout << "Enter card name: ";
    cin.ignore();
    getline(cin, cardName);
    regex digitRegex("^[0-9]+$");
    if (regex_match(cardName, digitRegex)) {
        Card newCard(cardName);
        financeManager.addCard(newCard);
        cout << "Card added successfully!" << std::endl;
    } else {
        cout << "Invalid card name. Only digits are allowed." << std::endl;
    }
}

void Remove_card(FinanceManager& financeManager) {
    string cardName;
    cout << "Enter card name to remove: ";
    cin.ignore();
    getline(cin, cardName);

    financeManager.removeCard(cardName);
}

void Top_expence(FinanceManager& financeManager) {
    time_t now = time(nullptr);
    time_t weekAgo = now - 7 * 24 * 60 * 60;
    time_t monthAgo = now - 30 * 24 * 60 * 60;

    cout << "Top Expenses in the Last Week:\n";
    financeManager.generateTopExpenses(financeManager.getTransactionsForPeriod(weekAgo, now), "Week", weekAgo, now);

    cout << "\nTop Expenses in the Last Month:\n";
    financeManager.generateTopExpenses(financeManager.getTransactionsForPeriod(monthAgo, now), "Month", monthAgo, now);
}

void Top_categories(FinanceManager& financeManager) {
    time_t now = time(nullptr);
    time_t weekAgo = now - 7 * 24 * 60 * 60;
    time_t monthAgo = now - 30 * 24 * 60 * 60;

    cout << "Top Categories in the Last Week:\n";
    financeManager.generateTopCategories(financeManager.getTransactionsForPeriod(weekAgo, now), "Week", weekAgo, now);

    cout << "\nTop Categories in the Last Month:\n";
    financeManager.generateTopCategories(financeManager.getTransactionsForPeriod(monthAgo, now), "Month", monthAgo, now);
}

void Wallets_manage(FinanceManager& financeManager) {
    while (true) {
        cout << "\nWallet Management:\n";
        cout << "1. Deposit to Wallet\n";
        cout << "2. Withdraw from Wallet\n";
        cout << "3. Add Wallet\n";
        cout << "4. Remove Wallet\n";
        cout << "5. Back to Main Menu\n";
        cout << "Select an option: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                Wallet_deposit(financeManager);
                break;
            case 2:
                Wallet_withdraw(financeManager);
                break;
            case 3:
                Add_wallet(financeManager);
                break;
            case 4:
                Remove_wallet(financeManager);
                break;
            case 5:
                return;
            default:
                cout << "Invalid choice. Please select a valid option." << endl;
                break;
        }
    }
}

void Cards_manage(FinanceManager& financeManager) {
    while (true) {
        cout << "\nCard Management:\n";
        cout << "1. Deposit to Card\n";
        cout << "2. Withdraw from Card\n";
        cout << "3. Add Card\n";
        cout << "4. Remove Card\n";
        cout << "5. Back to Main Menu\n";
        cout << "Select an option: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                Deposit_to_card(financeManager);
                break;
            case 2:
                Withdraw_from_card(financeManager);
                break;
            case 3:
                Add_card(financeManager);
                break;
            case 4:
                Remove_card(financeManager);
                break;
            case 5:
                return;
            default:
                cout << "Invalid choice. Please select a valid option." << endl;
                break;
        }
    }
}

int main() {
    FinanceManager financeManager;

    Wallet wallet1("1");
    Wallet wallet2("2");

    Card card1("1");
    Card card2("2");

    financeManager.addWallet(wallet1);
    financeManager.addWallet(wallet2);

    financeManager.addCard(card1);
    financeManager.addCard(card2);

    cout << "Personal Finance Management System" << endl;

    while (true) {
        cout << "\nMain Menu:\n";
        cout << "1. Manage Wallets\n";
        cout << "2. Manage Cards\n";
        cout << "3. Add Expense\n";
        cout << "4. Display Top Expenses\n";
        cout << "5. Display Top Categories\n";
        cout << "6. Generate Reports\n";
        cout << "7. Exit\n";
        cout << "Select an option: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                Wallets_manage(financeManager);
                break;
            case 2:
                Cards_manage(financeManager);
                break;
            case 3:
                Add_expence(financeManager);
                break;
            case 4:
                Top_expence(financeManager);
                break;
            case 5:
                Top_categories(financeManager);
                break;
            case 6:
                Reports(financeManager);
                break;
            case 7:
                cout << "Exiting the program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please select a valid option." << endl;
                break;
        }
    }

    return 0;
}