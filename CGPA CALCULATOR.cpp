//TASK  - 1 CGPA CALCULATOR
#include <iostream>
#include <iomanip>
using namespace std;

// Function to convert letter grade to grade points
float getGradePoint(string grade) {
    if (grade == "A" || grade == "a") return 4.0;
    else if (grade == "B" || grade == "b") return 3.0;
    else if (grade == "C" || grade == "c") return 2.0;
    else if (grade == "D" || grade == "d") return 1.0;
    else if (grade == "F" || grade == "f") return 0.0;
    else return -1; // Invalid grade
}

int main() {
    int numCourses;
    float credit, totalCredits = 0, totalGradePoints = 0;
    string grade;

    cout << "===== CGPA CALCULATOR =====" << endl;
    cout << "Enter number of courses: ";
    cin >> numCourses;

    for (int i = 1; i <= numCourses; ++i) {
        cout << "\nCourse " << i << ":" << endl;

        cout << "Enter grade (A, B, C, D, F): ";
        cin >> grade;

        float gp = getGradePoint(grade);
        if (gp == -1) {
            cout << "Invalid grade. Please enter A, B, C, D, or F." << endl;
            i--; // Repeat this course input
            continue;
        }

        cout << "Enter credit hours: ";
        cin >> credit;

        totalGradePoints += gp * credit;
        totalCredits += credit;

        cout << "Grade Point: " << gp << ", Grade Points Earned: " << gp * credit << endl;
    }

    // Calculate CGPA
    float cgpa = totalGradePoints / totalCredits;

    cout << fixed << setprecision(2);
    cout << "\n========== RESULT ==========" << endl;
    cout << "Total Credits: " << totalCredits << endl;
    cout << "Total Grade Points: " << totalGradePoints << endl;
    cout << "CGPA: " << cgpa << endl;

    return 0;
}
