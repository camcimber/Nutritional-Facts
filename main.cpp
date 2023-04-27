#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include "Food.h"
#include "heapSort.h"
#include "timSort.h"
#include "Functions.h"

using namespace std;

int main() {
    // Welcome message
    cout << "Welcome to Macro-Tracker! " << endl;

    // Create a map to store the data
    unordered_map<string, vector<Food>> data;

    // Parse the data
    parseData(data, "food.csv");

    char again = 'Y';

    while (again == 'Y' || again == 'y') {
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

        while (macroNum < 1 || macroNum > 5) {
            cout << "That number is out of bounds. Select another number: ";
            cin >> macroNum;
        }

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

        cout << "\nWould you like the highest or lowest values? Please type either 1 or 2" << endl;
        cout << "1. Highest" << endl;
        cout << "2. Lowest" << endl;
        int rank;
        cin >> rank;

        while (rank < 1 || rank > 2) {
            cout << "That number is out of bounds. Select another number: ";
            cin >> rank;
        }

        string decision1 = "";
        string decision2 = "";
        if (rank == 1) {
            decision1 = "Top";
            decision2 = "highest";

        } else if (rank == 2) {
            decision1 = "Bottom";
            decision2 = "lowest";
        }

        cout << "\nThere is a total number of items in " << chosenCategory << ": " << data[chosenCategory].size() << endl;
        cout << "How many of the " << chosenCategory << " items would you like to see? (i.e. Top 10 Items)" << endl;
        int numItems;
        cin >> numItems;

        while (numItems > data[chosenCategory].size() || numItems <= 0) {
            cout << "That number is out of bounds. Select another number: ";
            cin >> numItems;
        }

        cout << endl;

        vector<Food> heapSortVector;
        vector<Food> timSortVector;

        chrono::duration<double, milli> diffHeap;
        chrono::duration<double, milli> diffTim;
        if (rank == 1) {
            // Time the heap sort
            auto start = chrono::steady_clock::now();
            heapSortVector = kLargest(data[chosenCategory], numItems, macroNum);
            auto end = chrono::steady_clock::now();
            diffHeap = end - start;

            // Time the Tim sort
            start = chrono::steady_clock::now();
            timSortVector = timSort(data[chosenCategory], macroNum, true);
            end = chrono::steady_clock::now();
            diffTim = end - start;

        } else {
            // Time the heap sort
            auto start = chrono::steady_clock::now();
            // Heap sort
            heapSortVector = kSmallest(data[chosenCategory], numItems, macroNum);
            auto end = chrono::steady_clock::now();
            diffHeap = end - start;

            // Time the Tim sort
            start = chrono::steady_clock::now();
            // Tim sort
            timSortVector = timSort(data[chosenCategory], macroNum, false);
            end = chrono::steady_clock::now();
            diffTim = end - start;
        }

        // Print the time difference
        cout << "Heap sort time: " << chrono::duration <double, milli> (diffHeap).count() << " ms" << endl;
        cout << "Tim sort time: " << chrono::duration <double, milli> (diffTim).count() << " ms" << endl;
        if (diffHeap == diffTim) {
            cout << "Both algorithms took the same amount of time." << endl;
        } else if (diffHeap < diffTim) {
            cout << "Heap sort was faster by " << chrono::duration <double, milli> (diffTim - diffHeap).count() << " ms" << endl;
        } else {
            cout << "Tim sort was faster by " << chrono::duration <double, milli> (diffHeap - diffTim).count() << " ms" << endl;
        }

        cout << endl;
        cout << decision1 << " " << numItems << " items with the " << decision2 << " " << macroChosen << " value in the " << chosenCategory << " category:" << endl;
        
        cout << endl;
        printSortedData(heapSortVector, macroNum, numItems, measurement, macroChosen);
        cout << endl;

        // Test to see if the two algorithms produce the same results
        printSortedData(timSortVector, macroNum, numItems, measurement, macroChosen);
        cout << endl;

        cout << "Would you like to see another category? (Y/N): ";
        cin >> again;
    }

    cout << endl;
    cout << "Thank you for using Macro-Tracker!" << endl;

    return 0;
}