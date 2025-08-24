#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <string>
using namespace std;

/**
 * @class Transaction
 * @brief Represents a single financial transaction (either income or expense).
 *
 * This class encapsulates all the properties of a transaction, such as its ID,
 * date, type, amount, category, and a description. It provides methods to
 * access and modify these properties, as well as a method to display the
 * transaction's details.
 */

class Transaction {
private:
    int id;
    string date;
    string type; 
    double amount;
    string category;
    string description;

public:
     /**
     * @brief Constructs a new Transaction object.
     * @param id The unique identifier for the transaction.
     * @param date The date of the transaction (in YYYY-MM-DD format).
     * @param type The type of transaction ("income" or "expense").
     * @param amount The monetary value of the transaction.
     * @param category A user-defined category for the transaction (e.g., "Groceries").
     * @param description A brief description of the transaction.
     */
    Transaction(int id, const string& date, const string& type, double amount, const string& category, const string& description);

    // --- Getters (Accessors) ---
    int getID() const;
    string getDate() const;
    string getType() const;
    double getAmount() const;
    string getCategory() const;
    string getDescription() const;
    
    // --- Setters (Mutators) ---
    void setDate(const string& newDate);
    void setAmount(double newAmount);
    void setCategory(const string& newCategory);
    void setDescription(const string& newDescription);

    /**
     * @brief Displays the details of the transaction to the console.
     * @details Formats and prints all member variables in a single, readable line.
     */
    void display() const;
};

#endif