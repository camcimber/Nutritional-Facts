#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <queue>
#include <thread>
#include <chrono>
#include <iomanip>
#include "Food.h"
#include "heapSort.h"

using namespace std;

void parseData(map<string, vector<Food>>& data, string fileName) {
    ifstream file(fileName);

    // Read and discard the header row
    string line;
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        vector<string> row;

        // Read the relevant columns
        string item;

        // Category
        getline(ss, item, ',');
        row.push_back(item);

        // Description
        getline(ss, item, ',');
        // If the description is in quotes, read until the end of the quotes
        if (item.front() == '\"') {
            // Read until the end of the quotes
            while (item.back() != '\"') {
                string temp;
                getline(ss, temp, ',');
                item += "," + temp;
            }

            // Remove the quotes from the description
            item.erase(0, 1);
            item.pop_back();
            row.push_back(item);

        } else {
            row.push_back(item);
        }

        // Skip the next 4 columns
        for (int i = 0; i < 4; i++) {
            getline(ss, item, ',');
        }

        // Carbohydrates
        getline(ss, item, ',');
        row.push_back(item);

        // Skip the next 2 columns
        for (int i = 0; i < 2; i++) {
            getline(ss, item, ',');
        }

        // Fiber
        getline(ss, item, ',');
        row.push_back(item);

        // Skip the next 3 columns
        for (int i = 0; i < 3; i++) {
            getline(ss, item, ',');
        }

        // Protein
        getline(ss, item, ',');
        row.push_back(item);

        // Skip the next 3 columns
        for (int i = 0; i < 3; i++) {
            getline(ss, item, ',');
        }

        // Sugar
        getline(ss, item, ',');
        row.push_back(item);

        // Skip the next 12 columns
        for (int i = 0; i < 12; i++) {
            getline(ss, item, ',');
        }

        // Sodium
        getline(ss, item, ',');
        row.push_back(item);

        // Extract the data from the row
        string category = row[0];
        string description = row[1];

        // Convert the string data to double
        double carbohydrates = stod(row[2]);
        double fiber = stod(row[3]);
        double protein = stod(row[4]);
        double sugar = stod(row[5]);
        double sodium = stod(row[6]);

        // Create a new Food object and add it to the vector
        Food food(category, description, carbohydrates, fiber, protein, sugar, sodium);

        // Add the food to the map
        data[category].push_back(food);

    }
}

void printSortedData(const vector<Food>& data, int fieldNumber, string measurement) {
    cout << endl;
    //get the longest description length for formatting
    size_t maxDesLength = 0;
    for (const auto& food : data) {
        size_t descriptionLength = food.description().size();
        if (descriptionLength > maxDesLength) {
            maxDesLength = descriptionLength;
        }
    }
    // Print the data of the chosen category
    cout << fixed << setprecision(2);
    cout << left;  // Set left alignment for the description field

    size_t fieldWidth = maxDesLength + 4;
    for (int i = 0; i < data.size(); i++) {
        cout << setw(3) << i + 1 << ". ";
        cout << setw(fieldWidth) << data[i].description()
        << setw(8) << right << data[i].fieldValueGetter(fieldNumber) << " " << setw(4) << left << measurement << endl;
    }
}

int main() {
    cout << "Welcome to Macro-Tracker! " << endl;

    // Stop for a 5 seconds
    //this_thread::sleep_for(chrono::milliseconds(5000));

    // Create a map to store the data
    map<string, vector<Food>> data;

    // Parse the data
    parseData(data, "food.csv");

    // User input
    cout <<"\nPlease click the link to choose a category! " << endl;
    cout << "https://docs.google.com/spreadsheets/d/1EgpY9CooYl7U-zW8W-Q3s64Vcg45VvcGiG8rpqVAysk/edit?usp=sharing" << endl;
    string chosenCategory = "";

    cout << endl;
    cout << "Select a catergory (Case sensitive): ";
    cin >> chosenCategory;

    // Check if the category exists and ask for another category if it doesn't
    while (data.find(chosenCategory) == data.end()) {
        cout << "Category does not exist. Choose another category: ";
        cin >> chosenCategory;
    }

    cout << "\nGreat! What macronutrient would you like to see? Please type number 1-5" << endl;
    cout << "1. Carbohydrates" << endl;
    cout << "2. Fiber" << endl;
    cout << "3. Protein" << endl;
    cout << "4. Sugar" << endl;
    cout << "5. Sodium" << endl;
    int macroNum;
    cin >> macroNum;

    string measurement = "";
    string macroChosen = " ";
    if (macroNum == 1) {
        macroChosen = "carbohydrates";
        measurement = "g";

    } else if(macroNum == 2) {
        macroChosen = "fiber";
        measurement = "g";

    } else if(macroNum == 3) {
        macroChosen = "protein";
        measurement = "g";

    } else if(macroNum == 4) {
        macroChosen = "sugar";
        measurement = "g";

    } else if (macroNum == 5) {
        macroChosen = "sodium";
        measurement = "mg";
    }


    while (macroNum < 1 || macroNum > 5) {
        cout << "That number is out of bounds. Select another number: ";
        cin >> macroNum;
    }

    cout << "\nWould you like the highest or lowest values? Please type either 1 or 2" << endl;
    cout << "1. Highest" << endl;
    cout << "2. Lowest" << endl;
    int rank;
    cin >> rank;

    string decision = "";
    if (rank == 1) {
        decision = "highest";

    } else if (rank == 2) {
        decision = "lowest";
    }

    while (rank < 1 || rank > 2) {
        cout << "That number is out of bounds. Select another number: ";
        cin >> rank;
    }

    int count = 0;
    //get the total number of items in specified category
    for (Food food : data[chosenCategory]) {
        count++;
    }

    cout << "\nThere is a total number of items in " << chosenCategory << ": " << count << ", size: " << data[chosenCategory].size() << endl;
    cout << "How many of the " << chosenCategory << " items would you like to see? (i.e. Top 10 Items)" << endl;
    int numItems;
    cin >> numItems;

    while (numItems > count || numItems < 0) {
        cout << "That number is out of bounds. Select another number: ";
        cin >> numItems;
    }

    cout << endl;
    cout << "Top " << numItems << " items with the " << decision << " "<< macroChosen << " value in the " << chosenCategory << " category:"<< endl;

    vector<Food> heapSortVector;
    vector<Food> timSortVector;

    if (rank == 1) {
        heapSortVector = kLargest(data[chosenCategory], numItems, macroNum);

    } else {
        heapSortVector = kSmallest(data[chosenCategory], numItems, macroNum);
    }

    printSortedData(heapSortVector, macroNum, measurement);

    return 0;
}