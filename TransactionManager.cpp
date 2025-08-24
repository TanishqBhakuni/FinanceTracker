#include "TransactionManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <algorithm>
using namespace std;

TransactionManager::TransactionManager() : nextID(1) {}

//1
void TransactionManager::addTransaction(const string &date, const string &type, double amount, const string &category, const string &description)
{
    Transaction newTransaction(nextID, date, type, amount, category, description);
    transactions.push_back(newTransaction);
    nextID++;
}

//2
void TransactionManager::viewAllTransactions() const
{
    if (transactions.empty())
    {
        cout << "No transactions to display." << endl;
        return;
    }

    cout << "\n========== All Transactions ==========" << endl;
    for (const auto &transaction : transactions)
    {
        transaction.display();
    }
    cout << "========== End of List ===========\n"
         << endl;
}

// 3
void TransactionManager::saveToFile(const string &filename) const
{
    ofstream outputFile(filename);
    if (!outputFile.is_open())
    {
        cerr << "Error: Could not open the file for writing: " << filename << endl;
        return;
    }

    for (const auto &transaction : transactions)
    {
        outputFile << transaction.getID() << ","
                   << transaction.getDate() << ","
                   << transaction.getType() << ","
                   << transaction.getAmount() << ","
                   << transaction.getCategory() << ","
                   << transaction.getDescription() << ","
                   << endl;
    }
}

// 4
void TransactionManager::loadFromFile(const string &filename)
{
    ifstream inputFile(filename);
    int maxID = 0;

    if (inputFile.is_open())
    {
        string line;

        while (getline(inputFile, line))
        {
            stringstream ss(line);
            string idStr, date, type, amountStr, category, description;

            if (getline(ss, idStr, ',') &&
                getline(ss, date, ',') &&
                getline(ss, type, ',') &&
                getline(ss, amountStr, ',') &&
                getline(ss, category, ',') &&
                getline(ss, description))
            {
                try
                {
                    int id = stoi(idStr);
                    double amount = stod(amountStr);

                    Transaction transaction(id, date, type, amount, category, description);
                    transactions.push_back(transaction);

                    maxID = max(maxID, id);
                }
                catch (const invalid_argument &e)
                {
                    cerr << "Warning: Skipping corrupted line (invalid number format): " << line << endl;
                }
                catch (const out_of_range &e)
                {
                    cerr << "Warning: Skipping corrupted line (number out of range): " << line << endl;
                }
            }
        }
    }
    nextID = maxID + 1;
}

// 5
void TransactionManager::generateSummary() const
{

    if (transactions.empty())
    {
        cout << "\nNo transactions available to generate a summary. Please add some first.\n";
        return;
    }

    double totalIncome = 0.0;
    double totalExpenses = 0.0;

    for (const auto &transaction : transactions)
    {
        if (transaction.getType() == "income")
        {
            totalIncome += transaction.getAmount();
        }
        else if (transaction.getType() == "expense")
        {
            totalExpenses += transaction.getAmount();
        }
    }

    double netBalance = totalIncome - totalExpenses;

    cout << "\n\n--- Financial Summary ---\n";

    cout << fixed << setprecision(2);

    cout << "Total Income:    ₹" << totalIncome << endl;
    cout << "Total Expenses:  ₹" << totalExpenses << endl;
    cout << "-------------------------" << endl;
    cout << "Net Balance:     ₹" << netBalance << endl;
    cout << "-------------------------\n"
         << endl;
}

// 6
vector<Transaction>::iterator TransactionManager::findTransactionById(int id)
{
    for (auto it = transactions.begin(); it != transactions.end(); ++it)
    {
        if (it->getID() == id)
        {
            return it;
        }
    }
    return transactions.end();
}

// 7
void TransactionManager::deleteTransaction(const string &filename)
{
    int idToDelete = 0;
    cout << "\nEnter the ID of the transaction to delete: ";
    cin >> idToDelete;

    if (cin.fail())
    {
        cout << "[Error] Invalid ID. Please enter a number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    auto it = findTransactionById(idToDelete);
    if (it != transactions.end())
    {
        cout << "\nTransaction found: \n";
        it->display();

        char confirmation;
        cout << "\nAre you sure you want to delete this transaction? (y/n): ";
        cin >> confirmation;

        if (confirmation == 'y' || confirmation == 'Y')
        {
            transactions.erase(it);

            saveToFile(filename);

            cout << "Transaction deleted successfully.\n";
        }
        else
        {
            cout << "Deletion cancelled.\n";
        }
    }
    else
    {
        cout << "Transaction with ID " << idToDelete << " not found.\n";
    }
}

// 8
void TransactionManager::editTransaction(const string &filename)
{
    int idToEdit = 0;
    cout << "\nEnter the ID of the transaction to edit";
    cin >> idToEdit;

    if (cin.fail())
    {
        cout << "[Error] Invalid ID. Please enter a number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    auto it = findTransactionById(idToEdit);

    if (it != transactions.end())
    {
        cout << "\nCurrent transaction details:\n ";
        it->display();

        cout << "\nWhich field would you like to edit?\n";
        cout << "1. Date\n";
        cout << "2. Amount\n";
        cout << "3. Category\n";
        cout << "4. Description\n";
        cout << "0. Cancel\n";
        cout << "Enter your choice: ";

        int fieldChoice;
        cin >> fieldChoice;

        if (cin.fail())
        {
            cout << "[Error] Invalid choice. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (fieldChoice)
        {
        case 1:
        {
            string newDate;
            cout << "Enter new date (YYYY-MM-DD): ";
            getline(cin, newDate);
            it->setDate(newDate);
            break;
        }
        case 2:
        {
            double newAmount;
            cout << "Enter new amount: ";
            cin >> newAmount;
            if (cin.fail())
            {
                cout << "[Error] Invalid amount.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return;
            }
            it->setAmount(newAmount);
            break;
        }
        case 3:
        {
            string newCategory;
            cout << "Enter new category: ";
            getline(cin, newCategory);
            it->setCategory(newCategory);
            break;
        }
        case 4:
        {
            string newDescription;
            cout << "Enter new description: ";
            getline(cin, newDescription);
            it->setDescription(newDescription);
            break;
        }
        case 0:
            cout << "Edit cancelled !!";
            return;

        default:
            cout << "Invalid field choice. Edit cancelled.\n";
            return;
        }
        saveToFile(filename);
        cout << "Transaction updated successfully.\n";
    }
    else
    {
        cout << "Transaction with ID " << idToEdit << " not found.\n";
    }
}

// 9
void TransactionManager::viewByCategory(const string &category) const
{
    cout << "\n--- Transactions in Category: " << category << " ---\n";
    bool foundOne = false;

    for (const auto &transaction : transactions)
    {
        if (transaction.getCategory() == category)
        {
            transaction.display();
            foundOne = true;
        }
    }

    if (!foundOne)
    {
        cout << "No transactions found for this category.\n";
    }
    cout << "-------------------------------------------\n";
}

// 10
void TransactionManager::viewByDateRange(const string &startDate, const string &endDate) const
{
    cout << "\n--- Transactions from " << startDate << " to " << endDate << " ---\n";
    bool foundOne = false;

    for (const auto &transaction : transactions)
    {
        if (transaction.getDate() >= startDate && transaction.getDate() <= endDate)
        {
            transaction.display();
            foundOne = true;
        }
    }

    if (!foundOne)
    {
        cout << "No transactions found in this date range.\n";
    }
    cout << "---------------------------------------------------\n";
}
