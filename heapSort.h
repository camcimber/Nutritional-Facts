#pragma once
#include <vector>
#include <queue>
#include <algorithm>
#include "Food.h"

vector<Food> kLargest(const vector<Food>& data, int k, int fieldNumber) {
    // vector to return
    vector<Food> newData;

    // priority queue to store the k largest elements
    // Min heap
    priority_queue<pair<double, Food>, vector<pair<double, Food>>, greater<pair<double, Food>>> pq;

    // iterate through the data
    for (const Food& food : data) {
        // get the field value
        double field = food.fieldValueGetter(fieldNumber);
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
        double field = food.fieldValueGetter(fieldNumber);
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