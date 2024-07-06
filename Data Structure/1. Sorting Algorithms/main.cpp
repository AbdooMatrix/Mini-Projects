// Include necessary libraries
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include "Student.h"  // Include the Student class
#include "SortingFunctions.h"  // Include the sorting functions

using namespace std;
using namespace std::chrono;

// Function to read student data from a file
void readFromFile(vector<Student> &students) {
    ifstream inputFile("students.txt");  // Open the file
    if (!inputFile.is_open()) {  // Check if the file is open
        cout << "Failed to open the file.\n";
        return;
    }

    int numStudents;  // Number of students
    inputFile >> numStudents;  // Read the number of students
    inputFile.ignore();  // Ignore the newline character

    // Read each student's data
    for (int i = 0; i < numStudents; ++i) {
        string studentName;  // Student's name
        string studentID;  // Student's ID
        double studentGPA;  // Student's GPA
        string line;  // Line of text
        getline(inputFile, line);  // Read a line of text
        if (line.empty())getline(inputFile, line);  // If the line is empty, read the next line
        int j;
        for (j = 0; j < line.size(); ++j) {  // Parse the student's name
            if (isalpha(line[j]) || line[j] == ' ')studentName += line[j];
            else break;
        }
        if (studentName[0] == ' ')studentName.erase(0, 1);  // Remove leading spaces
        if (j < line.size()) {  // If there is more data on the line
            studentName.erase(studentName.size() - 1, 1);  // Remove trailing spaces
            for (j; j < line.size(); ++j) {  // Parse the student's ID
                studentID += line[j];
            }
        } else getline(inputFile, studentID);  // If there is no more data on the line, read the next line for the student's ID

        inputFile >> studentGPA;  // Read the student's GPA
        students.emplace_back(studentName, studentID, studentGPA);  // Add the student to the vector
    }
}

// Function to sort the students and measure the time taken
void sortAndMeasureTime(void (*sort)(vector<Student> &, int &, bool (*comp)(Student a, Student b)),
                        const vector<Student> &students,
                        const string &algorithmName, bool byName, ostream &output) {
    vector<Student> temp = students;  // Copy the students vector
    int comparisons = 0;  // Number of comparisons made by the sorting algorithm
    auto start = high_resolution_clock::now();  // Start time
    if (byName) {  // If sorting by name
        sort(temp, comparisons, defaultComp);  // Sort the students
    } else  // If not sorting by name
        sort(temp, comparisons, compByGPA);  // Sort the students
    auto end = high_resolution_clock::now();  // End time
    auto duration = duration_cast<milliseconds>(end - start);  // Duration of the sorting process
    output << "Algorithm: " << algorithmName << endl;  // Output the name of the sorting algorithm
    output << "Number of comparisons: " << comparisons << endl;  // Output the number of comparisons
    output << "Running Time: " << duration.count() << " milliseconds" << endl;  // Output the running time
    output << "Sorted Students: \n";  // Output the sorted students
    if (byName) {  // If sorted by name
        for (const auto &student: temp) {  // For each student
            output << student << endl;  // Output the student
        }
        output << endl;
    } else {  // If not sorted by name
        for (int i = temp.size() - 1; i >= 0; --i) {  // For each student
            output << temp[i] << endl;  // Output the student
        }
        output << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<Student> students;  // Vector to store the students
    readFromFile(students);  // Read the students from the file

    ofstream sortedByName("SortedByName.txt");  // File to output the students sorted by name
    ofstream sortedByGPA("SortedByGPA.txt");  // File to output the students sorted by GPA

    if (!sortedByName.is_open() || !sortedByGPA.is_open()) {  // Check if the files are open
        cout << "Error opening output files.\n";
        return 1;
    }

    // Sort the students by name and measure the time taken
    sortAndMeasureTime(insertionSort, students, "Insertion Sort", true, sortedByName);
    sortAndMeasureTime(selectionSort, students, "Selection Sort", true, sortedByName);
    sortAndMeasureTime(bubbleSort, students, "Bubble Sort", true, sortedByName);
    sortAndMeasureTime(shellSort, students, "Shell Sort", true, sortedByName);
    sortAndMeasureTime(quickSort, students, "Quick Sort", true, sortedByName);
    sortAndMeasureTime(mergeSort, students, "Merge Sort", true, sortedByName);


    // Sort the students by GPA and measure the time taken
    sortAndMeasureTime(insertionSort, students, "Insertion Sort", false, sortedByGPA);
    sortAndMeasureTime(selectionSort, students, "Selection Sort", false, sortedByGPA);
    sortAndMeasureTime(bubbleSort, students, "Bubble Sort", false, sortedByGPA);
    sortAndMeasureTime(shellSort, students, "Shell Sort", false, sortedByGPA);
    sortAndMeasureTime(quickSort, students, "Quick Sort", false, sortedByGPA);

    sortedByName.close();  // Close the file
    sortedByGPA.close();  // Close the file

    return 0;  // End of the program
}
