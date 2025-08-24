#include "Transaction.h"
#include <iostream>
#include <iomanip>
using namespace std;

Transaction::Transaction(int id, const string& date, const string& type, double amount, const string& category, const string& description)
    : id(id), date(date), type(type), amount(amount), category(category), description(description) {
}

int Transaction::getID() const {
    return id;
}

// Implementation of the getDate getter method.
string Transaction::getDate() const {
    return date;
}

// Implementation of the getType getter method.
string Transaction::getType() const {
    return type;
}

// Implementation of the getAmount getter method.
double Transaction::getAmount() const {
    return amount;
}

// Implementation of the getCategory getter method.
string Transaction::getCategory() const {
    return category;
}

// Implementation of the getDescription getter method.
string Transaction::getDescription() const {
    return description;
}

// Implementation of the setDate setter method.
void Transaction::setDate(const string& newDate) {
    date = newDate;
}

// Implementation of the setAmount setter method.
void Transaction::setAmount(double newAmount) {
    amount = newAmount;
}

// Implementation of the setCategory setter method.
void Transaction::setCategory(const string& newCategory) {
    category = newCategory;
}

// Implementation of the setDescription setter method.
void Transaction::setDescription(const string& newDescription) {
    description = newDescription;
}

// Implementation of the display method.
void Transaction::display() const {
    cout << left
              << setw(5) << id
              << setw(15) << date
              << setw(12) << type
              << setw(15) << fixed << setprecision(2) << amount
              << setw(20) << category
              << setw(30) << description << endl;
}

