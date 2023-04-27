#pragma once
#include <vector>
#include "Food.h"

void insertionSort(vector<Food> data, int fieldNumber){
    for (int i = 1; i < data.size(); i++) {
        //temp food object
        Food& key = data[i];

        int j = i - 1;
        double currValue = data[j].fieldValueGetter(fieldNumber);
        double keyValue = key.fieldValueGetter(fieldNumber);

        //checks stay in bounds and if curr element is greater than key element
        while (j >= 0 && currValue > keyValue) {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = key;
    }
}