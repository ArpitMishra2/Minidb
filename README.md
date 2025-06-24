# Minidb   
During my recent learning phase, I built a MiniDBMS — a file-based database management system — entirely in C++. This project simulates the core features of a real database engine, like creating tables, inserting and selecting data, updating records, and deleting them using SQL-like commands.

    The system starts with a command-line interface where users can either create a new table with custom column names or load an existing one from file. Once a table is loaded, the user can perform operations such as INSERT INTO, SELECT * WHERE, UPDATE ... SET ... WHERE, DELETE ... WHERE, and even a SHOW ALL to display all rows. The records are stored in a .tbl file inside a storage/ folder, ensuring persistence even after the program is closed.

    One of the most interesting challenges I solved was building a custom parser that tokenizes user input just like SQL does — supporting quoted strings, numeric values, and space-separated inputs. I used STL containers like vectors to store the table structure in memory, and file streams to manage persistent data.

    The project is fully modular — the logic is encapsulated inside a Table class, while the CLI and parser logic are handled separately. Through this, I’ve practiced and demonstrated OOP principles, STL mastery, file I/O handling, and a real-world application of database design — all without using any database libraries.

    If given more time, I’d love to extend this into a multi-table system with JOIN support, type validation, and maybe a metadata system for schemas. Overall, this project not only sharpened my C++ but also helped me deeply understand how backend database systems really work under the hood.
