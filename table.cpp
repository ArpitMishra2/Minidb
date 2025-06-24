#include "table.h"
#include <iostream>
#include <fstream>
using namespace std;

// Constructor
Table::Table(string name, vector<string> cols)     
    : name(name), columns(cols), filename("storage/" + name + ".tbl") {
    loadFromFile();
}

// Show schema
void Table::displaySchema() const {
    cout << "Table: " << name << "\nColumns: ";
    for (const auto& col : columns)
        cout << col << "  ";
    cout << "\n";
}

// Insert record
// Main point of bug;
void Table::insertRecord(vector<string> record) {
    if (record.size() != columns.size()) {
        cout << "Error: Column count mismatch\n";
        return;
    }
    records.push_back(record);
    saveToFile();
}

// Show all rows
void Table::displayRecords() const {
    cout << "\nRecords in '" << name << "' table:\n";

    // Print the header
    for (const auto& col : columns)
        cout << col << "\t";
    cout << "\n-----------------------------------\n";

    // Print each row of the recordss.
    for (const auto& row : records) {
        for (const auto& val : row)
            cout << val << "\t";
        cout << "\n";
    }
}

// Save records to file
void Table::saveToFile() const {
    ofstream fout(filename);
    for (const auto& row : records) {
        for (int i = 0; i < row.size(); ++i) {
            fout << row[i];
            if (i != row.size() - 1) fout << ",";
        }
        fout << "\n";
    }
}

// Load existing records from file
void Table::loadFromFile() {
    ifstream fin(filename);
    string line;

    while (getline(fin, line)) {
        vector<string> row;
        string val;
        for (char ch : line) {
            if (ch == ',') {
                row.push_back(val);
                val = "";
            } else {
                val += ch;
            }
        }
        if (!val.empty())
            row.push_back(val);

        if (!row.empty())
            records.push_back(row);
    }
}

string Table::getName() const {
    return name;
}

// Select records where column matches value
void Table::selectWhere(string columnName, string value) {
    int colIndex = -1;

    // Find index of columnName
    for (int i = 0; i < columns.size(); ++i) {
        if (columns[i] == columnName) {
            colIndex = i;
            break;
        }
    }

    if (colIndex == -1) {
        cout << "Column '" << columnName << "' not found.\n";
        return;
    }

    cout << "\nFilter: " << columnName << " = " << value << "\n";
    for (const auto& col : columns)
        cout << col << "\t";
    cout << "\n-----------------------------------\n";

    bool found = false;
    for (const auto& row : records) {
        if (row[colIndex] == value) {
            for (const auto& val : row)
                cout << val << "\t";
            cout << "\n";
            found = true;
        }
    }

    if (!found)
        cout << "No matching records found.\n";
}


        // Delete records where column matches value
    
void Table::deleteWhere(string columnName, string value) {
    int colIndex = -1;

    // Find column index
    for (int i = 0; i < columns.size(); ++i) {
        if (columns[i] == columnName) {
            colIndex = i;
            break;
        }
    }

    if (colIndex == -1) {
        cout << "Column '" << columnName << "' not found.\n";
        return;
    }

    int before = records.size();
    int deleted = 0;

    // Keep only records that don't match the condition
    vector<vector<string>> newRecords;
    for (const auto& row : records) {
        if (row[colIndex] != value) {
            newRecords.push_back(row);
        } else {
            deleted++;
        }
    }

    records = newRecords;
    saveToFile();

    cout << "Deleted " << deleted << " record(s) where " << columnName << " = " << value << ".\n";
}


// Update records where searchColumn matches searchValue

void Table::updateWhere(string searchColumn, string searchValue, string targetColumn, string newValue) {
    int searchIndex = -1, targetIndex = -1;

    // Find indexes of the search and target columns
    for (int i = 0; i < columns.size(); ++i) {
        if (columns[i] == searchColumn)
            searchIndex = i;
        if (columns[i] == targetColumn)
            targetIndex = i;
    }

    if (searchIndex == -1 || targetIndex == -1) {
        cout << "One or both columns not found.\n";
        return;
    }

    int updated = 0;
    for (auto& row : records) {
        if (row[searchIndex] == searchValue) {
            row[targetIndex] = newValue;
            updated++;
        }
    }

    saveToFile();

    cout << "Updated " << updated << " record(s) where " 
         << searchColumn << " = " << searchValue << ".\n";
}