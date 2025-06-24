#ifndef TABLE_H      // prevent multiple inclusion of the header file
#define TABLE_H

#include <string>    
#include <vector>
#include <map>
using namespace std;


// Main class for database table management
class Table {
private:
    string name;                         // Name of the table
    vector<string> columns;              // Column headers
    vector<vector<string>> records;      // All table rows
    string filename;                     // File to store records

public:
    Table(string name, vector<string> cols);

    void displaySchema() const;  // show the whole schema.
    void insertRecord(vector<string> record);   // Data structure to store records
    void displayRecords() const;      // Display all records in the table

    void saveToFile() const;          // Save records to file and const is for preventing modifications.
    void loadFromFile();              // Load existing records from file

    void selectWhere(string columnName, string value);   // Select records where column matches value

    void deleteWhere(string columnName, string value);   // Delete records where column matches value

    void updateWhere(string searchColumn, string searchValue, string targetColumn, string newValue);  // Update records where searchColumn matches searchValue, setting targetColumn to newValue


    string getName() const;  // Get the name of the table
};

#endif  
