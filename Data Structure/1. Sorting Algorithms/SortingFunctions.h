#ifndef DATASTUCTUREASS_SORTINGFUNCTIONS_H
#define DATASTUCTUREASS_SORTINGFUNCTIONS_H

#include <vector>
#include <algorithm>
#include "Student.h"

using namespace std;

// Default comparison function
template<typename T>
bool defaultComp(T a, T b) {
    return a < b;
}

// Comparison function by GPA
template<typename T>
bool compByGPA(T a, T b) {
    return a.getGpa() < b.getGpa();
}

// Insertion sort algorithm
template<typename T>
void insertionSort(vector<T> &arr, int &comparisons, bool (*comp)(T a, T b)) {
    for (int i = 1, j; i < arr.size(); ++i) {
        T temp = arr[i];
        for (j = i - 1; j > -1; --j) {
            ++comparisons;
            if (comp(temp, arr[j])) {
                arr[j + 1] = arr[j];
            } else break;
        }
        arr[j + 1] = temp;
    }
}

// Selection sort algorithm
template<typename T>
void selectionSort(vector<T> &arr, int &comparisons, bool (*comp)(T a, T b) = defaultComp) {
    int n = arr.size();
    for (int i = 0; i < n; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (comp(arr[j], arr[minIndex])) {
                minIndex = j;
            }
            ++comparisons;
        }
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}

// Bubble sort algorithm
template<typename T>
void bubbleSort(vector<T> &arr, int &comparisons, bool (*comp)(T a, T b) = defaultComp) {
    int n = arr.size();
    bool swapped;

    for (int i = 0; i < n - 1; ++i) {
        swapped = false;
        // Last i elements are already sorted, no need to check them
        for (int j = 0; j < n - i - 1; ++j) {
            // Swap if the element found is greater than the next element
            if (comp(arr[j + 1], arr[j])) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
                ++comparisons;
            }
        }

        // If no two elements were swapped in the inner loop, the array is sorted
        if (!swapped)
            break;
    }
}

// Shell sort algorithm
template<typename T>
void shellSort(vector<T> &arr, int &comparisons, bool (*comp)(T a, T b) = defaultComp) {
    int n = arr.size();

    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Do a gapped insertion sort for this gap size.
        // The first gap elements arr[0..gap-1] are already in gapped order
        // keep adding one more element until the entire array is gap sorted
        for (int i = gap; i < n; i += 1) {
            // add arr[i] to the elements that have been gap sorted
            // save arr[i] in temp and make a hole at position i
            T temp = arr[i];

            // shift earlier gap-sorted elements up until the correct location for arr[i] is found
            int j;
            for (j = i; j >= gap && comp(temp, arr[j - gap]); j -= gap) {
                arr[j] = arr[j - gap];
                ++comparisons;
            }
            // put temp (the original arr[i]) in its correct location
            arr[j] = temp;
        }
    }
}

// Partition function for quicksort
template<typename T>
int partition(std::vector<T> &arr, int low, int high, int &comparisons, bool (*comp)(T a, T b)) {
    T pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; ++j) {
        if (comp(arr[j], pivot)) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
        ++comparisons;
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Quicksort algorithm
template<typename T>
void quickSort(std::vector<T> &arr, int &comparisons, bool (*comp)(T a, T b)) {
    int low = 0;
    int high = arr.size() - 1;
    quickSort(arr, low, high, comparisons, comp);
}

// Quicksort algorithm with low and high parameters
template<typename T>
void quickSort(std::vector<T> &arr, int low, int high, int &comparisons, bool (*comp)(T a, T b)) {
    if (low < high) {
        int pi = partition(arr, low, high, comparisons, comp);
        quickSort(arr, low, pi - 1, comparisons, comp);
        quickSort(arr, pi + 1, high, comparisons, comp);
    }
}

template <typename T>
void merge(vector<T>& arr, int l, int m, int r, int &comparisons, bool (*comp)(T a, T b)) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<T> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0;
    int j = 0;
    int k = l;

    while (i < n1 && j < n2) {
        comparisons++;
        if (comp(L[i], R[j])) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

template <typename T>
void mergeSort(vector<T>& arr, int l, int r, int &comparisons, bool (*comp)(T a, T b)) {
    if (l >= r)
        return;

    int m = l + (r - l) / 2;
    mergeSort(arr, l, m, comparisons, comp);
    mergeSort(arr, m + 1, r, comparisons, comp);
    merge(arr, l, m, r, comparisons, comp);
}

template <typename T>
void mergeSort(vector<T>& arr, int &comparisons, bool (*comp)(T a, T b)=defaultComp) {
    int l = 0;
    int r = arr.size() - 1;
    mergeSort(arr, l, r, comparisons, comp);  // Call the correct mergeSort function
}

#endif //DATASTUCTUREASS_SORTINGFUNCTIONS_H
