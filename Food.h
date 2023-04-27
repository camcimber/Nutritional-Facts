#pragma once
#include <iostream>
#include <string>

using namespace std;

class Food {

    string category_;
    string description_;
    double carbohydrates_;
    double fiber_;
    double protein_;
    double sugar_;
    double sodium_;

    bool compare_carbohydrates = false;
    bool compare_fiber = false;
    bool compare_protein = false;
    bool compare_sugar = false;
    bool compare_sodium = false;

public:
    // Constructor to initialize the fields
    Food(string category, string description, double carbohydrates, double fiber, double protein, double sugar, double sodium);

    // Accessors
    string category() const;
    string description() const;
    double carbohydrates() const;
    double fiber() const;
    double protein() const;
    double sugar() const;
    double sodium() const;

    // Get the field value of the food object based on the field number
    double getMacro(int field) const;

    // Set the field comparison to true of the field number
    void fieldComparisonSetTrue(int field);
    // Set all the field comparison to false
    void fieldComparisonSetFalse();

    // Define the less-than operator to compare based on the macronutrient
    bool operator<(const Food& other) const;

};

// Constructor to initialize the fields
Food::Food(string category, string description, double carbohydrates, double fiber, double protein, double sugar, double sodium) {
    category_ = category;
    description_ = description;
    carbohydrates_ = carbohydrates;
    fiber_ = fiber;
    protein_ = protein;
    sugar_ = sugar;
    sodium_ = sodium;
}

// Accessors
string Food::category() const {
    return category_;
}

string Food::description() const {
    return description_;
}

double Food::carbohydrates() const {
    return carbohydrates_;
}

double Food::fiber() const {
    return fiber_;
}

double Food::protein() const {
    return protein_;
}

double Food::sugar() const {
    return sugar_;
}

double Food::sodium() const {
    return sodium_;
}

// Define a function to get the field value
double Food::getMacro(int field) const {
    switch (field) {
        case 1:
            return carbohydrates_;

        case 2:
            return fiber_;

        case 3:
            return protein_;

        case 4:
            return sugar_;

        case 5:
            return sodium_;
    }

    return 0;
}

void Food::fieldComparisonSetTrue(int field) {
    switch (field) {
        case 1:
            compare_carbohydrates = true;
            break;

        case 2:
            compare_fiber = true;
            break;

        case 3:
            compare_protein = true;
            break;

        case 4:
            compare_sugar = true;
            break;

        case 5:
            compare_sodium = true;
            break;
    }
}

void Food::fieldComparisonSetFalse() {
    compare_carbohydrates = false;
    compare_fiber = false;
    compare_protein = false;
    compare_sugar = false;
    compare_sodium = false;

}

// Define the less-than operator to compare based on the macronutrient
bool Food::operator<(const Food& other) const {
    if (compare_carbohydrates) {
        return carbohydrates_ < other.carbohydrates_;
    } else if (compare_fiber) {
        return fiber_ < other.fiber_;
    } else if (compare_protein) {
        return protein_ < other.protein_;
    } else if (compare_sugar) {
        return sugar_ < other.sugar_;
    } else if (compare_sodium) {
        return sodium_ < other.sodium_;
    }
    
    return carbohydrates_ < other.carbohydrates_;
}