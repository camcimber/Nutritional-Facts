// #include <iostream>
// #include <string>
// #include <fstream>
// #include <sstream>

// using namespace std;

// class Minerals{
// private:
//     //string carb, protein, sodium, fiber, sugar;
//     string category, description;
//     unsigned int finder, finder2; // used for parsing "description"

// public:

//    void parsing(){
//         ifstream inputFile;
//         inputFile.open("nutritional-facts.csv");

//         string line = "";
//         while(getline(inputFile, line)){

//             stringstream inputString(line);
//             getline(inputString, category, ',');

//             //parse to get description
//             getline(inputString, description, ',');

//             //some descriptions have quotes and other do not
//             if (description.front() == '"') {
//                 finder = line.find('"');
//                 description = line.substr( finder + 1);
//                 finder2 = description.find('"');
//                 description = description.substr(0, finder2);
//             }

//             //parse to get carbohydrates
//             string carb = "";
//             for (int i = 0; i < 6; i++) {
//                 getline(inputString, carb, ',');
//             }

//             //parse for cholesterol -> in progress, not printing correct value
//             string cholesterol = "";
//             for (int i = 0; i < 7; i++) {
//                 getline(inputString, cholesterol, ',');
//             }
//             cout << cholesterol << endl;

//         }
//    }


// };
// int main() {
//     Minerals nutrition;

//     nutrition.parsing();
//     return 0;
// }

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

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

  string category() const { 
    return category_;
  }

  string description() const {
    return description_;
  }
  double carbohydrates() const { return carbohydrates_; }
  double fiber() const { return fiber_; }
  double protein() const { return protein_; }
  double sugar() const { return sugar_; }
  double sodium() const { return sodium_; }

};

int main() {
  vector<Food> data;

  ifstream file("food.csv");

  // Read and discard the header row
  string line;
  getline(file, line);

  while (getline(file, line)) {
    stringstream ss(line);
    vector<string> row;

    // Read the relevant columns
    string item;
    getline(ss, item, '\"'); // category
    getline(ss, item, '\"');
    row.push_back(item);

    getline(ss, item, '\"'); // description
    getline(ss, item, '\"');
    row.push_back(item);

    for (int i = 0; i < 5; i++) {
      getline(ss, item, ','); // skip 4 columns
    }

    getline(ss, item, '\"'); // carbohydrates
    getline(ss, item, '\"');
    row.push_back(item);

    for (int i = 0; i < 3; i++) {
      getline(ss, item, ','); // skip 2 columns
    }

    getline(ss, item, '\"'); // fiber
    getline(ss, item, '\"');
    row.push_back(item);

    for (int i = 0; i < 4; i++) {
      getline(ss, item, ','); // skip 3 columns
    }

    getline(ss, item, '\"'); // protein
    getline(ss, item, '\"');
    row.push_back(item);

    for (int i = 0; i < 4; i++) {
      getline(ss, item, ','); // skip 3 columns
    }

    getline(ss, item, '\"'); // sugar
    getline(ss, item, '\"');
    row.push_back(item);

    for (int i = 0; i < 13; i++) {
      getline(ss, item, ','); // skip 12 columns
    }

    getline(ss, item, '\"'); // sodium
    getline(ss, item, '\"');
    row.push_back(item);

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
  }

    // Print the data
    for (Food food : data) {
      cout << food.category() << " " << food.description() << " " << food.carbohydrates() << " " << food.protein() << " " << food.sodium() << " " << food.fiber() << " " << food.sugar() << endl;
    }

  return 0;
}
