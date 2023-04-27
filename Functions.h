#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <iomanip>
#include "Food.h"

using namespace std;

void parseData(unordered_map<string, vector<Food>>& data, string fileName) {
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

void printSortedData(const vector<Food>& data, int fieldNumber, string measurement, string macroChosen) {
    
    // Capitalize the first letter of the macro
    macroChosen[0] = toupper(macroChosen[0]);

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

    // FIXME: Print the data in a table format
    cout << "Rank" << setw(fieldWidth) << "Description" << setw(8) << right << macroChosen << " " << setw(4) << left << "(" << measurement << ")" << endl;
    for (int i = 0; i < data.size(); i++) {
        cout << setw(3) << i + 1 << ". ";
        cout << setw(fieldWidth) << data[i].description()
        << setw(8) << right << data[i].fieldValueGetter(fieldNumber) << " " << setw(4) << left << measurement << endl;
    }
}