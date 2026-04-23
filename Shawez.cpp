/*
 ============================================================
   MINI PROJECT: Student Report Card System
   Language   : C++
   Semester   : 1st Year, 2nd Sem
 ============================================================
*/

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>


using namespace std;

// ─────────────────────────────────────────
//  CLASS DEFINITION
// ─────────────────────────────────────────
class Student {
private:
  string name;
  int rollNo;
  float marks[5]; // marks for 5 subjects
  string subjects[5];
  float total;
  float percentage;
  string grade;

public:
  // Constructor
  Student() {
    subjects[0] = "Mathematics";
    subjects[1] = "Physics";
    subjects[2] = "Chemistry";
    subjects[3] = "C++ Programming";
    subjects[4] = "English";
    total = 0;
    percentage = 0;
  }

  // ── Input student data ──
  void inputData() {
    cout << "\n  Enter Student Name   : ";
    cin.ignore();
    getline(cin, name);

    cout << "  Enter Roll Number    : ";
    cin >> rollNo;

    cout << "\n  Enter marks out of 100 for each subject:\n";
    for (int i = 0; i < 5; i++) {
      cout << "  " << setw(20) << left << subjects[i] << ": ";
      cin >> marks[i];

      // Validate marks
      while (marks[i] < 0 || marks[i] > 100) {
        cout << "  Invalid! Enter marks between 0-100: ";
        cin >> marks[i];
      }
    }
    calculateResult();
  }

  // ── Calculate total, percentage, grade ──
  void calculateResult() {
    total = 0;
    for (int i = 0; i < 5; i++)
      total += marks[i];

    percentage = total / 5.0f;

    if (percentage >= 90)
      grade = "A+  (Outstanding)";
    else if (percentage >= 75)
      grade = "A   (Distinction)";
    else if (percentage >= 60)
      grade = "B   (First Class)";
    else if (percentage >= 50)
      grade = "C   (Second Class)";
    else if (percentage >= 40)
      grade = "D   (Pass)";
    else
      grade = "F   (Fail)";
  }

  // ── Display Report Card ──
  void displayReport() {
    cout << "\n";
    cout << "  ╔══════════════════════════════════════════╗\n";
    cout << "  ║         STUDENT REPORT CARD              ║\n";
    cout << "  ╚══════════════════════════════════════════╝\n";
    cout << "\n";
    cout << "  Name        : " << name << "\n";
    cout << "  Roll No.    : " << rollNo << "\n";
    cout << "\n";
    cout << "  ┌─────────────────────────┬────────┐\n";
    cout << "  │ Subject                 │ Marks  │\n";
    cout << "  ├─────────────────────────┼────────┤\n";

    for (int i = 0; i < 5; i++) {
      cout << "  │ " << setw(24) << left << subjects[i] << "│ " << setw(6)
           << right << marks[i] << " │\n";
    }

    cout << "  ├─────────────────────────┼────────┤\n";
    cout << "  │ " << setw(24) << left << "Total"
         << "│ " << setw(6) << right << total << " │\n";
    cout << "  └─────────────────────────┴────────┘\n";

    cout << "\n";
    cout << fixed << setprecision(2);
    cout << "  Percentage  : " << percentage << " %\n";
    cout << "  Grade       : " << grade << "\n";
    cout << "\n";

    if (percentage >= 40)
      cout << "  Result      : * PASS *\n";
    else
      cout << "  Result      : * FAIL *\n";

    cout << "\n";
  }

  // Getter for roll number (for search)
  int getRollNo() { return rollNo; }
};

// ─────────────────────────────────────────
//  HELPER: Print menu
// ─────────────────────────────────────────
void printMenu() {
  cout << "\n";
  cout << "  ╔══════════════════════════════════╗\n";
  cout << "  ║    REPORT CARD SYSTEM - MENU     ║\n";
  cout << "  ╠══════════════════════════════════╣\n";
  cout << "  ║  1. Add Student Record           ║\n";
  cout << "  ║  2. Display All Report Cards     ║\n";
  cout << "  ║  3. Search by Roll Number        ║\n";
  cout << "  ║  4. Exit                         ║\n";
  cout << "  ╚══════════════════════════════════╝\n";
  cout << "  Enter your choice: ";
}

// ─────────────────────────────────────────
//  MAIN FUNCTION
// ─────────────────────────────────────────
int main() {
  // Set terminal to UTF-8 to fix weird characters on Windows
#ifdef _WIN32
  system("chcp 65001 > nul");
#endif

  const int MAX_STUDENTS = 50;
  Student students[MAX_STUDENTS];
  int count = 0;
  int choice = 0;

  cout << "\n  Welcome to the Student Report Card System!\n";

  do {
    printMenu();
    cin >> choice;

    switch (choice) {

    case 1: // Add student
      if (count >= MAX_STUDENTS) {
        cout << "\n  Maximum student limit reached!\n";
      } else {
        students[count].inputData();
        count++;
        cout << "\n  Student record added successfully!\n";
      }
      break;

    case 2: // Display all
      if (count == 0) {
        cout << "\n  No records found. Please add students first.\n";
      } else {
        for (int i = 0; i < count; i++)
          students[i].displayReport();
      }
      break;

    case 3: // Search by roll number
    {
      if (count == 0) {
        cout << "\n  No records found.\n";
        break;
      }
      int searchRoll;
      cout << "\n  Enter Roll Number to search: ";
      cin >> searchRoll;

      bool found = false;
      for (int i = 0; i < count; i++) {
        if (students[i].getRollNo() == searchRoll) {
          students[i].displayReport();
          found = true;
          break;
        }
      }
      if (!found)
        cout << "\n  Student with Roll No. " << searchRoll << " not found.\n";
      break;
    }

    case 4:
      cout << "\n  Thank you! Exiting program...\n\n";
      break;

    default:
      cout << "\n  Invalid choice! Please enter 1-4.\n";
    }

  } while (choice != 4);

  return 0;
}