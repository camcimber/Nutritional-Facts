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

    // Define a function to get the field value
    double fieldValueGetter(int field) const;

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
double Food::fieldValueGetter(int field) const {
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

// Define the less-than operator to compare based on the macronutrient
bool Food::operator<(const Food& other) const {
    return carbohydrates_ < other.carbohydrates_;
}