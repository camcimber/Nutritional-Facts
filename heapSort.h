#pragma once
#include <vector>
#include <queue>
#include <algorithm>
#include "Food.h"

vector<Food> kLargest(vector<Food>& data, int k, int fieldNumber) {
    // vector to return
    vector<Food> newData;

    // priority queue to store the k largest elements
    priority_queue<pair<double, Food>, vector<pair<double, Food>>, greater<pair<double, Food>>> pq; // Min heap

    // iterate through the data
    for (Food& food : data) {
        // get the field value
        double field = food.getMacro(fieldNumber);
        
        food.fieldComparisonSetTrue(fieldNumber);
        // if the priority queue is full and the field value is larger than the top element, skip
        if (pq.size() == k && field < pq.top().first) {
            food.fieldComparisonSetFalse();
            continue;
        }
        
        // push the element into the priority queue
        pq.push(make_pair(field, food));
        
        // if the priority queue is full, pop the top element, which is the smallest element
        if (pq.size() > k) {    
            pq.pop();
        }
        
        // reset the field comparison
        food.fieldComparisonSetFalse();
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

vector<Food> kSmallest(vector<Food>& data, int k, int fieldNumber) {

    // vector to return
    vector<Food> newData;

    // priority queue to store the k smallest elements
    priority_queue<pair<double, Food>> pq; // Max heap

    // iterate through the data
    for (Food& food : data) {
        // get the field value
        double field = food.getMacro(fieldNumber);

        food.fieldComparisonSetTrue(fieldNumber);
        // if the priority queue is full and the field value is smaller than the top element, skip
        if (pq.size() == k && field > pq.top().first) {
            food.fieldComparisonSetFalse();
            continue;
        }
        
        // push the element into the priority queue
        pq.push(make_pair(field, food));
        
        // if the priority queue is full, pop the top element, which is the largest element
        if (pq.size() > k) {
            pq.pop();
        }
        
        // reset the field comparison
        food.fieldComparisonSetFalse();
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