#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <queue>

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

    for (const Food& food : data) {
        double field = fieldValueGetter(food, fieldNumber);
        if (pq.size() == k && field < pq.top().first) {
            continue;
        }
        pq.push(make_pair(field, food));
        if (pq.size() > k) {
            pq.pop();
        }
    }

    while (!pq.empty()) {
        auto temp = pq.top();
        newData.push_back(temp.second);
        pq.pop();
    }
    reverse(newData.begin(), newData.end());
    return newData;
}

vector<Food> kSmallest(const vector<Food>& data, int k, int fieldNumber) {
    // vector to return
    vector<Food> newData;

    // priority queue to store the k smallest elements
    // Max heap
    priority_queue<pair<double, Food>, vector<pair<double, Food>>, less<pair<double, Food>>> pq;

    for (const Food& food : data) {
        double field = fieldValueGetter(food, fieldNumber);
        if (pq.size() == k && field < pq.top().first) {
            continue;
        }
        pq.push(make_pair(field, food));
        if (pq.size() > k) {
            pq.pop();
        }
    }
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
    // Create a map to store the data
    map<string, vector<Food>> data;

    // Parse the data
    parseData(data, "food.csv");

    // User input
    string chosenCategory = "Milk";

    // Print the data of the chosen category
    int count = 0;
    for (Food food : data[chosenCategory]) {
        cout << food.category() << ": " << food.description() << " " << food.carbohydrates() << " " << food.protein() << " " << food.sodium() << " " << food.fiber() << " " << food.sugar() << endl;
        count++;
    }
    cout << "Total number of items in " << chosenCategory << ": " << count << endl;

    //example of how to call klargest function
    //vector<Food> largestCarbs = kLargest(data[chosenCategory], 5, 1);

    // Print the data
    // for (Food food : data) {
    //   cout << food.category() << " " << food.description() << " " << food.carbohydrates() << " " << food.protein() << " " << food.sodium() << " " << food.fiber() << " " << food.sugar() << endl;
    // }

    // for (int i = 0; i < largestCarbs.size(); i++) {
    //     cout << largestCarbs[i].category() << " " << largestCarbs[i].description() << " " << largestCarbs[i].carbohydrates() << endl;
    // }

    return 0;
}