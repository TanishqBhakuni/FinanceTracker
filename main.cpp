#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

// Include the header file for our application's engine.
// This gives main() access to the TransactionManager class.
#include "TransactionManager.h"
using namespace std;

// A global constant for the filename makes it easy to change if needed.
const string FILENAME = "transactions.csv";

// Function to display the main menu to the user.
void displayMenu()
{
    cout << "\n===== Personal Finance Tracker =====\n";
    cout << "1. Add Transaction\n";
    cout << "2. View All Transactions\n";
    cout << "3. Financial Summary\n";
    cout << "4. Edit Transaction\n";
    cout << "5. Delete Transaction\n";
    cout << "6. Filter by Category\n";
    cout << "7. Filter by Date Range\n";
    cout << "8. Exit\n";
    cout << "====================================\n";
    cout << "Enter your choice: ";
}

/**
 * @brief The main entry point of the application.
 *
 * This function contains the main application loop. It initializes the
 * TransactionManager, handles user input, and calls the appropriate
 * manager methods based on the user's choice.
 */
int main()
{
    TransactionManager manager;
    manager.loadFromFile(FILENAME);
    int choice = 0;

    // This is the main event loop for the console application.
    // It will continue to run until the user chooses to exit.
    while (true)
    {
        displayMenu();
        cin >> choice;

        if (cin.fail())
        {
            cout << "\n[Error] Invalid input. Please enter a number corresponding to a menu option.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            continue;
        }

        // This switch statement acts as the main command router for the UI.
        switch (choice)
        {
        case 1:
        {
            string date, type, category, description;
            double amount;

            cout << "Enter date (YYYY-MM-DD): ";
            cin >> date;

            cout << "Enter type (income/expense): ";
            cin >> type;

            cout << "Enter amount: ";
            cin >> amount;

            cout << "Enter category: ";
            cin >> category;

            cout << "Enter description: ";
            cin.ignore();

            getline(cin, description);
            manager.addTransaction(date, type, amount, category, description);
            cout << "\nTransaction added successfully!\n";
            break;
        }

        case 2:
            manager.viewAllTransactions();
            break;

        case 3:
            manager.generateSummary();
            break;

        case 4:
            manager.editTransaction(FILENAME);
            break;

        case 5:
            manager.deleteTransaction(FILENAME);
            break;

        case 6:
        {
            cout << "Enter category to filter by: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            string category;
            getline(std::cin, category);
            manager.viewByCategory(category);
            break;
        }

        case 7:
        {
            cout << "Enter start date (YYYY-MM-DD): ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string startDate;
            getline(cin, startDate);

            cout << "Enter end date (YYYY-MM-DD): ";
            string endDate;
            getline(cin, endDate);

            manager.viewByDateRange(startDate, endDate);
            break;
        }

        case 8:
            manager.saveToFile(FILENAME);
            cout << "\nThankyou for using the Personal Finance Tracker. Goodbye !!";
            return 0;

        default:
            cout << "\nInvalid choice. Please try again.\n";
            break;
        }
    }

    return 0;
}