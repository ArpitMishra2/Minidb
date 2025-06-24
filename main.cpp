// #include <iostream>
// #include "table.h"
// using namespace std;

// int main() {
//     vector<string> columns = {"ID", "Name", "Age"};

//     // Create table
//     Table users("users", columns);

//     // Show schema
//     users.displaySchema();

//     // Insert some records
//     users.insertRecord({"1", "Arpit", "22"});
//     users.insertRecord({"2", "Anubhav", "24"});
//     users.insertRecord({"3", "Arif", "24"});
//     users.insertRecord({"4", "Anuj", "24"});

//     // Checking if where clause is working or not
//     users.selectWhere("Name", "Arif");
//     users.selectWhere("Age", "24");
//     users.selectWhere("Name", "Unknown"); // for checking non-existing record

//     // Delete records where Name is "Arif"
//     users.deleteWhere("Name", "Arif");
//     users.displayRecords(); // Verify Arif is gone
//     users.deleteWhere("Name", "Unknown"); // Try deleting a non-existing record

//     // Checking update functionality
//     // Update Arpit's age to 25
//     users.updateWhere("Name", "Arpit", "Age", "25");
//     // Update Anuj's name to Anuj Singh
//     users.updateWhere("Name", "Anuj", "Name", "Anuj Singh");
//     // Test: try updating a non-existent match
//     users.updateWhere("Name", "XYZ", "Age", "30");  



//     // Show all records
//     users.displayRecords();

//     return 0;
// }


            // Now creating sql parsing functionality
#include <iostream>
#include <sstream>
#include <vector>
#include "table.h"
using namespace std;

void runCLI(Table& table) {
    string input;
    cout << "\nWelcome to MiniDB CLI. Type commands like:\n";
    cout << " - INSERT INTO users VALUES \"Aman\", \"101\", \"22\"\n";
    cout << " - SELECT * FROM users WHERE Name = \"Aman\"\n";
    cout << " - DELETE FROM users WHERE Age = \"24\"\n";
    cout << " - UPDATE users SET Age = \"26\" WHERE Name = \"Aman\"\n";
    cout << " - SHOW ALL   (displays entire table)\n";
    cout << " - NOTE --> Use double quotes for all string and numeric values in commands.\n";
    cout << " - EXIT\n\n";
    

    while (true) {
        cout << "MiniDB > ";
        getline(cin, input);

        if (input == "EXIT") break;

        // Remove punctuation helpers
        for (char& c : input)
            if (c == ',' || c == ';') c = ' ';

        istringstream iss(input);
        string command;
        iss >> command;


if (command == "SHOW") {
    string nextWord;
    iss >> nextWord;
    if (nextWord == "ALL") {
        table.displayRecords();
    } else {
        cout << "Unknown SHOW command. Try: SHOW ALL\n";
    }
}


if (command == "INSERT") {
    string into, tableName, valuesKeyword;
    iss >> into >> tableName >> valuesKeyword;

    string valueLine;
    getline(iss, valueLine); // Get everything after "VALUES"

    vector<string> record;
    string token;
    bool insideQuotes = false;
    string current;

    for (char ch : valueLine) {
        if (ch == '"') {
            insideQuotes = !insideQuotes;
            if (!insideQuotes) { // When closing quote found
                while (!current.empty() && current.front() == ' ') current.erase(current.begin());
                while (!current.empty() && current.back() == ' ') current.pop_back();
                if (!current.empty()) {
                    record.push_back(current);
                    current.clear();
                }
            }
            continue;
        }

        if ((ch == ' ' || ch == ',') && !insideQuotes) {
            if (!current.empty()) {
                while (!current.empty() && current.front() == ' ') current.erase(current.begin());
                while (!current.empty() && current.back() == ' ') current.pop_back();
                if (!current.empty()) {
                    record.push_back(current);
                    current.clear();
                }
            }
        } else {
            current += ch;
        }
    }

    // Push last value if exists
    while (!current.empty() && current.front() == ' ') current.erase(current.begin());
    while (!current.empty() && current.back() == ' ') current.pop_back();
    if (!current.empty()) {
        record.push_back(current);
    }

    cout << "\nParsed Values (" << record.size() << "): ";
    for (string s : record) cout << "[" << s << "] ";
    cout << "\n";

    table.insertRecord(record);
}





        else if (command == "SELECT") {
            string star, from, tableName, where, col, eq, val;
            iss >> star >> from >> tableName >> where >> col >> eq;

            getline(iss, val, '"');
            getline(iss, val, '"');

            table.selectWhere(col, val);
        }

        else if (command == "DELETE") {
            string from, tableName, where, col, eq, val;
            iss >> from >> tableName >> where >> col >> eq;

            getline(iss, val, '"');
            getline(iss, val, '"');

            table.deleteWhere(col, val);
        }

        else if (command == "UPDATE") {
            string tableName, set, targetCol, equalSign, newVal, where, searchCol, searchEq, searchVal;
            iss >> tableName >> set >> targetCol >> equalSign;

            getline(iss, newVal, '"'); // Skip up to first quote
            getline(iss, newVal, '"'); // Get actual new value

            iss >> where >> searchCol >> searchEq;
            getline(iss, searchVal, '"');
            getline(iss, searchVal, '"');

            table.updateWhere(searchCol, searchVal, targetCol, newVal);
        }

        else {
            cout << "Invalid command.\n";
        }
    }
}


int main() {
    string choice;
    cout << "Do you want to (1) Load an existing table or (2) Create a new one? ";
    cin >> choice;

    if (choice == "1") {
        string tableName;
        cout << "Enter existing table name: ";
        cin >> tableName;

        // Default/fixed schema for existing tables
        // Customize this based on the actual structure of your existing files
        vector<string> columns = {"ID", "Name", "Age"};  // for users.tbl

        Table table(tableName, columns);
        runCLI(table);
    }
    else if (choice == "2") {
        string tableName;
        int colCount;

        cout << "Enter new table name: ";
        cin >> tableName;

        cout << "Enter number of columns: ";
        cin >> colCount;

        cin.ignore(); // clear newline

        vector<string> columns;
        for (int i = 0; i < colCount; ++i) {
            string col;
            cout << "Enter name of column " << i + 1 << ": ";
            getline(cin, col);
            columns.push_back(col);
        }

        Table table(tableName, columns);
        runCLI(table);
    }
    else {
        cout << "Invalid choice.\n";
    }

    return 0;
}