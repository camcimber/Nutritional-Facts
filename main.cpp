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

using namespace std;

class Food {

    string category_;
    string description_;
    double carbohydrates_;
    double fiber_;
    double protein_;
    double sugar_;
    double sodium_;

public:
    // Constructor to initialize the fields
    Food(string category, string description, double carbohydrates, double fiber, double protein, double sugar, double sodium)
            : category_(category), description_(description), carbohydrates_(carbohydrates), fiber_(fiber), protein_(protein), sugar_(sugar), sodium_(sodium) {}

    // Accessors
    string category() const {
        return category_;
    }

    string description() const {
        return description_;
    }

    double carbohydrates() const {
        return carbohydrates_;
    }

    double fiber() const {
        return fiber_;
    }

    double protein() const {
        return protein_;
    }

    double sugar() const {
        return sugar_;
    }

    double sodium() const {
        return sodium_;
    }

    // Define the less-than operator to compare based on the macronutrient
    bool operator<(const Food& other) const {
        return carbohydrates_ < other.carbohydrates_;
    }


};

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

double fieldValueGetter(const Food& food, int field) {
    switch (field) {
        case 1:
            return food.carbohydrates();

        case 2:
            return food.fiber();

        case 3:
            return food.protein();

        case 4:
            return food.sugar();

        case 5:
            return food.sodium();
    }

    return 0;
}

vector<Food> kLargest(const vector<Food>& data, int k, int fieldNumber) {
    // vector to return
    vector<Food> newData;

    // priority queue to store the k largest elements
    // Min heap
    priority_queue<pair<double, Food>, vector<pair<double, Food>>, greater<pair<double, Food>>> pq;

    // iterate through the data
    for (const Food& food : data) {
        // get the field value
        double field = fieldValueGetter(food, fieldNumber);
        // if the priority queue is full and the field value is greater than the top element, skip
        if (pq.size() == k && field < pq.top().first) {
            continue;
        }
        // push the element into the priority queue
        pq.push(make_pair(field, food));
        // if the priority queue is full, pop the top element, which is the smallest element
        if (pq.size() > k) {
            pq.pop();
        }
    }

    // iterate through the priority queue and add the elements to the vector
    while (!pq.empty()) {
        auto temp = pq.top();
        newData.push_back(temp.second);
        pq.pop();
    }
    // reverse the vector
    reverse(newData.begin(), newData.end());
    return newData;
}

vector<Food> kSmallest(const vector<Food>& data, int k, int fieldNumber) {
    // vector to return
    vector<Food> newData;

    // priority queue to store the k smallest elements
    // Max heap
    priority_queue<pair<double, Food>> pq;

    // iterate through the data
    for (const Food& food : data) {
        // get the field value
        double field = fieldValueGetter(food, fieldNumber);
        // if the priority queue is full and the field value is smaller than the top element, skip
        if (pq.size() == k && field < pq.top().first) {
            continue;
        }
        // push the element into the priority queue
        pq.push(make_pair(field, food));
        // if the priority queue is full, pop the top element, which is the largest element
        if (pq.size() > k) {
            pq.pop();
        }
    }
    // iterate through the priority queue and add the elements to the vector
    while (!pq.empty()) {
        auto temp = pq.top();
        newData.push_back(temp.second);
        pq.pop();
    }
    // reverse the order of elements in the final vector
    reverse(newData.begin(), newData.end());
    return newData;
}

void insertionSort(vector<Food> data, int fieldNumber){
    for (int i = 1; i < data.size(); i++) {
        //temp food object
        Food& key = data[i];

        int j = i - 1;
        double currValue = fieldValueGetter(data[j], fieldNumber);
        double keyValue = fieldValueGetter(key, fieldNumber);

        //checks stay in bounds and if curr element is greater than key element
        while (j >= 0 && currValue > keyValue) {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = key;
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
    cout << "https://docs.google.com/spreadsheets/d/1EgpY9CooYl7U-zW8W-Q3s64Vcg45VvcGiG8rpqVAysk/edit?usp=sharing ";
    string chosenCategory = "";

    cout << endl;
    cout << "\nWhat category would you like to choose? (Case sensitive)" << endl;
    cin >> chosenCategory;

    // Check if the category exists and ask for another category if it doesn't
    while (data.find(chosenCategory) == data.end()) {
        cout << "Category does not exist. Choose another category:" << endl;
        cin >> chosenCategory;
    }

    cout << "\nGreat! What macronutrient would you like to see? Please type number 1-6" << endl;
    cout << "1. Carbohydrates" << endl;
    cout << "2. Fiber" << endl;
    cout << "3. Protein" << endl;
    cout << "4. Sugar" << endl;
    cout << "5. Sodium" << endl;
    int macroNum;
    cin >> macroNum;

    string measurement = "";
    if(macroNum == 1 || macroNum == 3 || macroNum == 4 || macroNum == 2){
        measurement = "g";
    }
    else if(macroNum == 5){
        measurement = "mg";
    }

    while(macroNum < 1 || macroNum > 5){
        cout << "That number is out of bounds. Select another number: ";
        cin >> macroNum;
    }

    cout << "\nWould you like the highest or lowest values? Please type either 1 or 2" << endl;
    cout << "1. Highest" << endl;
    cout << "2. Lowest" << endl;
    int rank;
    cin >> rank;
    string decision = "";
    if (rank == 1){
        decision = "top";
    }
    else if(rank == 2){
        decision = "bottom";
    }

    while(rank < 1 || rank > 2){
        cout << "That number is out of bounds. Select another number: ";
        cin >> rank;
    }

    int count = 0;
    //get the total number of items in specified category
    for (Food food : data[chosenCategory]) {
        count++;
    }
    cout << "\nThere is a total number of items in " << chosenCategory << ": " << count << endl;
    cout << "How many of the " << chosenCategory << " items would you like to see? (i.e. Top 10 Items)" << endl;
    int numItems;
    cin >> numItems;

    while(numItems > count || numItems < 0){
        cout << "That number is out of bounds. Select another number: ";
        cin >> numItems;
    }

    cout << "Displaying the " << decision << " " << numItems << " items in the " << chosenCategory << " category:"<< endl;
    // call sort function here !
    // then the data to print will be in the correct order
    // Print the data of the chosen category

    int tempCount = 1;
//    for (Food food : data[chosenCategory]) {
      //  cout << \n << tempCount  << ". "<< food.description() << "          " << food.carbohydrates() << measurement << endl;
//        tempCount++;
//    }




    vector<Food> largestCarbs = kLargest(data[chosenCategory], 5, 1);

     for (int i = 0; i < largestCarbs.size(); i++) {
         cout << largestCarbs[i].category() << " " << largestCarbs[i].description() << " " << largestCarbs[i].carbohydrates() << endl;
     }

    return 0;
}