#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

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

};

void parseData(vector<Food>& data, set<string>& categories, string fileName) {
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
    getline(ss, item, '\"');
    getline(ss, item, '\"');
    row.push_back(item);

    // Description
    getline(ss, item, '\"');
    getline(ss, item, '\"');
    row.push_back(item);

    // Skip the next 4 columns
    for (int i = 0; i < 5; i++) {
      getline(ss, item, ',');
    }

    // Carbohydrates
    getline(ss, item, '\"');
    getline(ss, item, '\"');
    row.push_back(item);

    // Skip the next 2 columns
    for (int i = 0; i < 3; i++) {
      getline(ss, item, ',');
    }

    // Fiber
    getline(ss, item, '\"');
    getline(ss, item, '\"');
    row.push_back(item);

    // Skip the next 3 columns
    for (int i = 0; i < 4; i++) {
      getline(ss, item, ',');
    }

    // Protein
    getline(ss, item, '\"');
    getline(ss, item, '\"');
    row.push_back(item);

    // Skip the next 3 columns
    for (int i = 0; i < 4; i++) {
      getline(ss, item, ',');
    }

    // Sugar
    getline(ss, item, '\"');
    getline(ss, item, '\"');
    row.push_back(item);

    // Skip the next 12 columns
    for (int i = 0; i < 13; i++) {
      getline(ss, item, ',');
    }

    // Sodium
    getline(ss, item, '\"');
    getline(ss, item, '\"');
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
    data.push_back(food);

    // Add the category to the set
    categories.insert(category);
  }
}

int main() {
  // Create a vector to store the data
  vector<Food> data;

  // Create a set to store the categories
  set<string> categories;

  // Parse the data
  parseData(data, categories, "food.csv");

  // Print the categories
  // for (string category : categories) {
  //   cout << category << endl;
  // }

  // Print the data
  // for (Food food : data) {
  //   cout << food.category() << " " << food.description() << " " << food.carbohydrates() << " " << food.protein() << " " << food.sodium() << " " << food.fiber() << " " << food.sugar() << endl;
  // }

  return 0;
}
