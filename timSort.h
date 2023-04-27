#pragma once
#include <vector>
#include "Food.h"

void insertionSort(vector<Food>& arr, int fieldNumber){
    for (int i = 1; i < arr.size(); i++) {
        //temp food object
        Food& key = arr[i];

        int j = i - 1;
        double currValue = arr[j].fieldValueGetter(fieldNumber);
        double keyValue = key.fieldValueGetter(fieldNumber);

        //checks stay in bounds and if curr element is greater than key element
        while (j >= 0 && currValue > keyValue) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Merge function merges the sorted runs
void merge(vector<Food>& arr, int fieldNumber, int l, int m, int r) {
     
    // Original array is broken in two parts
    // left and right array
    int len1 = m - l + 1;
    int len2 = r - m;
    vector<Food> left;
    vector<Food> right;

    for (int i = 0; i < len1; i++)
        left.push_back(arr[l + i]);
    
    for (int i = 0; i < len2; i++)
        right.push_back(arr[m + 1 + i]);
 
    int i = 0;
    int j = 0;
    int k = l;
 
    // After comparing, we
    // merge those two array
    // in larger sub array
    while (i < len1 && j < len2) {

        double leftValue = left[i].fieldValueGetter(fieldNumber);
        double rightValue = right[j].fieldValueGetter(fieldNumber);
        if (leftValue <= rightValue) {
            arr[k] = left[i];
            i++;
        
        } else {
            arr[k] = right[j];
            j++;
        }

        k++;
    }
 
    // Copy remaining elements of left, if any
    while (i < len1) {
        arr[k] = left[i];
        k++;
        i++;
    }
 
    // Copy remaining element of right, if any
    while (j < len2) {
        arr[k] = right[j];
        k++;
        j++;
    }
}
 
// Iterative Timsort function to sort the
// array[0...n-1] (similar to merge sort)
vector<Food> timSort(const vector<Food>& data, int fieldNumber) {
    //copy data into arr
    vector<Food> arr = data;

    // This is minimum size of
    // run array to be merged.
    // minRun is minimum
    // 64. If array size is
    // smaller than 64,
    // insertion sort is
    // used.
    int minRun = 64;
    int n = data.size();

    // Sort individual subarrays of size RUN
    for (int i = 0; i < n; i += 32)
        //insertionSort(arr, i, min((i+31), (n-1)));
 
    // Start merging from size RUN (or 32).
    // It will merge
    // to form size 64, then 128, 256
    // and so on ....
    for (int size = 32; size < n; size = 2*size) {
         
        // pick starting point of
        // left sub array. We
        // are going to merge
        // arr[left..left+size-1]
        // and arr[left+size, left+2*size-1]
        // After every merge, we
        // increase left by 2*size
        for (int left = 0; left < n; left += 2*size) {
             
            // find ending point of
            // left sub array
            // mid+1 is starting point
            // of right sub array
            int mid = left + size - 1;
            int right = min((left + 2*size - 1), (n-1));
 
            // merge sub array arr[left.....mid] &
            // arr[mid+1....right]
            if(mid < right)
                merge(arr, fieldNumber, left, mid, right);
        }
    }

    return arr;
}