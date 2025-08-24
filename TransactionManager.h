#ifndef TRANSACTION_MANAGER_H
#define TRANSACTION_MANAGER_H

#include <vector>
#include <string>
#include "Transaction.h"
using namespace std;

/**
 * @class TransactionManager
 * @brief Manages a collection of Transaction objects.
 *
 * This class is the core engine of the finance tracker. It handles all
 * business logic, including adding, editing, deleting, and viewing transactions.
 * It is also responsible for file persistence (saving to and loading from a CSV file).
 */
class TransactionManager {
private:
    vector<Transaction> transactions;
    int nextID;

    /**
     * @brief A private helper method to find a transaction by its ID.
     * @param id The ID of the transaction to find.
     * @return An iterator to the found transaction, or transactions.end() if not found.
     */
    vector<Transaction>::iterator findTransactionById(int id);

public:
    /**
     * @brief Constructs a TransactionManager, initializing the next available ID.
    */
    TransactionManager();

    // Core functionality methods
    void addTransaction(const string& date, const string& type, double amount, const string& category, const string& description);
    void viewAllTransactions() const;
    void generateSummary() const;

    // File I/O methods
    void saveToFile(const string& filename) const;
    void loadFromFile(const string& filename);

    // Editing and Deleting methods
    void deleteTransaction(const string& filename);
    void editTransaction(const string& filename);

    // Filtering methods
    void viewByCategory(const string& category) const;
    void viewByDateRange(const string& startDate, const string& endDate) const;
};

#endif