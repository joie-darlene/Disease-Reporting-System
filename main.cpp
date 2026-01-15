#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string LOCATIONS_FILE = "locations.csv";
string CASES_FILE = "cases.csv";

// Function to open input file
ifstream openInputFile(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Could not open " << filename << endl;
    }
    return file;
}

// Function to open output file
ofstream openOutputFile(const string &filename, bool append = true) {
    ofstream file;
    if (append)
        file.open(filename, ios::app);
    else
        file.open(filename);
    
    if (!file.is_open()) {
        cout << "Could not open " << filename << endl;
    }
    return file;
}

// Split CSV line
vector<string> splitLine(string line, char delimiter = ',') {
    vector<string> tokens;
    stringstream ss(line);
    string token;
    while (getline(ss, token, delimiter))
        tokens.push_back(token);
    return tokens;
}

// Join strings into CSV line
string joinLine(vector<string> parts, char delimiter = ',') {
    string result;
    for (size_t i = 0; i < parts.size(); ++i) {
        result += parts[i];
        if (i != parts.size() - 1) result += delimiter;
    }
    return result;
}

// Check duplicate in a file
bool isDuplicate(const string &filename, const string &keyword, int column) {
    ifstream file = openInputFile(filename);
    string line;
    while (getline(file, line)) {
        auto parts = splitLine(line);
        if (parts.size() > column && parts[column] == keyword)
            return true;
    }
    return false;
}

// Delete a line containing keyword
void deleteLine(const string &filename, const string &keyword) {
    ifstream fileIn(filename);
    vector<string> lines;
    string line;
    while (getline(fileIn, line)) {
        if (line.find(keyword) == string::npos)
            lines.push_back(line);
    }
    fileIn.close();

    ofstream fileOut(filename);
    for (string l : lines)
        fileOut << l << endl;
    fileOut.close();
}

// Add location
void addLocation(const string &location) {
    if (!isDuplicate(LOCATIONS_FILE, location, 0)) {
        ofstream file = openOutputFile(LOCATIONS_FILE);
        file << location << endl;
        cout << "Location added: " << location << endl;
    } else {
        cout << "Location already exists." << endl;
    }
}

// Delete location
void deleteLocation(const string &location) {
    if (isDuplicate(LOCATIONS_FILE, location, 0)) {
        deleteLine(LOCATIONS_FILE, location);
        cout << "Deleted location: " << location << endl;
    } else {
        cout << "Location not found." << endl;
    }
}

// List locations
void listLocations() {
    ifstream file = openInputFile(LOCATIONS_FILE);
    string line;
    while (getline(file, line))
        cout << line << endl;
}

// List diseases
void listDiseases() {
    ifstream file = openInputFile(CASES_FILE);
    string line;
    vector<string> diseases;
    while (getline(file, line)) {
        auto parts = splitLine(line);
        if (find(diseases.begin(), diseases.end(), parts[1]) == diseases.end()) {
            diseases.push_back(parts[1]);
            cout << parts[1] << endl;
        }
    }
}

// Record disease case
void recordCase(const string &location, const string &disease, int count) {
    if (!isDuplicate(LOCATIONS_FILE, location, 0)) {
        cout << "Location not found." << endl;
        return;
    }

    ifstream fileIn(CASES_FILE);
    vector<string> lines;
    string line;
    bool updated = false;

    while (getline(fileIn, line)) {
        auto parts = splitLine(line);
        if (parts[0] == location && parts[1] == disease) {
            parts[2] = to_string(count);
            updated = true;
            line = joinLine(parts);
        }
        lines.push_back(line);
    }

    fileIn.close();

    ofstream fileOut(CASES_FILE);
    for (string l : lines)
        fileOut << l << endl;

    if (!updated) {
        fileOut << location << "," << disease << "," << count << endl;
    }

    cout << "Recorded successfully." << endl;
}

// Show where disease exists
void whereDisease(const string &disease) {
    ifstream file = openInputFile(CASES_FILE);
    string line;
    while (getline(file, line)) {
        auto parts = splitLine(line);
        if (parts[1] == disease)
            cout << parts[0] << endl;
    }
}

// Total cases of a disease
void totalCases(const string &disease) {
    ifstream file = openInputFile(CASES_FILE);
    string line;
    int total = 0;
    while (getline(file, line)) {
        auto parts = splitLine(line);
        if (parts[1] == disease)
            total += stoi(parts[2]);
    }
    cout << "Total cases of " << disease << ": " << total << endl;
}

// Cases in a location
void casesInLocation(const string &location, const string &disease) {
    ifstream file = openInputFile(CASES_FILE);
    string line;
    int count = 0;
    while (getline(file, line)) {
        auto parts = splitLine(line);
        if (parts[0] == location && parts[1] == disease)
            count += stoi(parts[2]);
    }
    cout << "Cases in " << location << " of " << disease << ": " << count << endl;
}

// Help
void help() {
    cout << "\nAvailable commands:\n";
    cout << " add <location>\n";
    cout << " delete <location>\n";
    cout << " list locations\n";
    cout << " list diseases\n";
    cout << " record <location> <disease> <count>\n";
    cout << " where <disease>\n";
    cout << " cases <disease>\n";
    cout << " cases <location> <disease>\n";
    cout << " help\n";
    cout << " exit\n\n";
}

// Main loop
int main() {
    cout << "=== Disease Reporting System ===" << endl;
    string input;

    while (true) {
        cout << ">> ";
        getline(cin, input);
        transform(input.begin(), input.end(), input.begin(), ::tolower);
        stringstream ss(input);
        string cmd;
        ss >> cmd;

        if (cmd == "add") {
            string loc;
            ss >> loc;
            addLocation(loc);
        } else if (cmd == "delete") {
            string loc;
            ss >> loc;
            deleteLocation(loc);
        } else if (cmd == "list") {
            string what;
            ss >> what;
            if (what == "locations") listLocations();
            else if (what == "diseases") listDiseases();
            else help();
        } else if (cmd == "record") {
            string loc, dis;
            int num;
            ss >> loc >> dis >> num;
            recordCase(loc, dis, num);
        } else if (cmd == "where") {
            string dis;
            ss >> dis;
            whereDisease(dis);
        } else if (cmd == "cases") {
            string first, second;
            ss >> first >> second;
            if (second.empty())
                totalCases(first);
            else
                casesInLocation(first, second);
        } else if (cmd == "help") {
            help();
        } else if (cmd == "exit") {
            break;
        } else {
            cout << "Unknown command. Type 'help' to see available commands.\n";
        }
    }

    return 0;
}
