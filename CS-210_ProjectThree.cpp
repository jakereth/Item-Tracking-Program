/* Jacob Rethmeier
   CS-210 Project Three 
   12/10/2023
*/

#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>

using namespace std;

class ItemTracker {
private:
    map<string, int> itemFrequency; // Using a map to store item frequencies

public:
    // Function to load data from the input file and populate the itemFrequency map
    void loadData(const string& filename) {
        ifstream inputFile(filename);
        if (!inputFile.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            exit(EXIT_FAILURE);
        }

        string itemName;

        while (inputFile >> itemName) {
            // Convert the item name to lowercase for user ease
            transform(itemName.begin(), itemName.end(), itemName.begin(), ::tolower);
            // Increment the frequency for each occurrence of the item
            itemFrequency[itemName] += 1;
        }

        inputFile.close();
    }
    // Function to display the menu
    void displayMenu() {
        cout << "Menu:\n";
        cout << "1. Find item frequency\n";
        cout << "2. Display all item frequencies\n";
        cout << "3. Display item frequencies as a histogram\n";
        cout << "4. Exit\n";
    }

    // Function to find and display the frequency of a specific item
    void findItemFrequency() {
        string itemName;
        cout << "Enter the item name: ";
        cin >> itemName;

        // Convert the input item name to lowercase
        transform(itemName.begin(), itemName.end(), itemName.begin(), ::tolower);

        if (itemFrequency.find(itemName) != itemFrequency.end()) {
            cout << "Frequency of " << itemName << ": " << itemFrequency[itemName] << endl;
        }
        else {
            cout << itemName << " not found in records.\n";
        }
    }

    // Function to display all item frequencies
    void displayAllItemFrequencies() {
        for (const auto& pair : itemFrequency) {
            cout << pair.first << " " << pair.second << endl;
        }
    }

    // Function to display item frequencies as a histogram
    void displayHistogram() {
        for (const auto& pair : itemFrequency) {
            cout << pair.first << " ";
            for (int i = 0; i < pair.second; ++i) {
                cout << "*";
            }
            cout << endl;
        }
    }

    // Function to save item frequencies to a backup file
    void saveToBackupFile() {
        ofstream backupFile("frequency.dat");
        for (const auto& pair : itemFrequency) {
            backupFile << pair.first << " " << pair.second << endl;
        }
        backupFile.close();
    }
};

int main() {
    ItemTracker itemTracker;

    // Load data from the input text file: Text file included in Project Zip
    itemTracker.loadData("CS210_Project_Three_Input_File.txt");

    int choice;
    do {
        itemTracker.displayMenu();
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        // Input validation
        while (cin.fail() || choice < 1 || choice > 4) {
            cin.clear(); // clear input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore last input
            cout << "Invalid input. Enter a number between 1 and 4: ";
            cin >> choice;
        }

        switch (choice) {
        case 1:
            itemTracker.findItemFrequency();
            break;
        case 2:
            itemTracker.displayAllItemFrequencies();
            break;
        case 3:
            itemTracker.displayHistogram();
            break;
        case 4:
            itemTracker.saveToBackupFile();
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}