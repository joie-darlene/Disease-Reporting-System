# Disease-Reporting-System
A command-line C++ application for managing and analyzing case data by location.
The system allows users to load data from CSV files, query case statistics, and interact with the program using simple text commands.

📌 Overview

This project reads case and location data from CSV files and allows users to:

View total reported cases

Check cases per specific location

List available locations

Interact with the system using typed commands

It is designed for learning file handling, data processing, and command-based interaction in C++.

🚀 Features

📂 Reads data from CSV files (locations.csv, cases.csv)

📍 Lists all available locations

📈 Displays total number of cases

🔍 Shows cases for a specific location

🧠 Simple command-line interface

🛑 Graceful error handling for missing files

🛠️ Technologies Used

Language: C++

Concepts:

File handling (ifstream, ofstream)

Vectors and strings

Command parsing

Data aggregation

Tools: Git, GitHub

📂 Project Structure
case-management-system/
├── main.cpp
├── locations.csv
├── cases.csv
└── README.md

▶️ How to Run the Project
1. Clone the repository
git clone https://github.com/your-username/case-management-system.git

2. Navigate into the project folder
cd case-management-system

3. Compile the program
g++ main.cpp -o case_manager

4. Run the program
./case_manager


⚠️ Make sure locations.csv and cases.csv are in the same directory as the executable.

💻 Available Commands

Once the program is running, you can use the following commands:

Command	Description
locations	Displays all available locations
total	Shows the total number of cases
cases <location>	Displays cases for a specific location
help	Shows all available commands
exit	Exits the program
Example:
cases Kigali

📖 What I Learned

How to read and process CSV files in C++

How to structure a command-driven program

Handling user input and errors cleanly

Using vectors and strings for real-world data

🔮 Future Improvements

Add data validation for CSV files

Support more detailed statistics

Allow adding new cases via the program

Improve performance for large datasets

👤 Author

joie-darlene
GitHub: https://github.com/joie-darlene

📄 License

This project is for educational and personal use
