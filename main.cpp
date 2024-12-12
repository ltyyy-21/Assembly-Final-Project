#include <iostream>
#include <cstring>
using namespace std;

#define MAX_STUDENTS 100
#define MAX_NAME_LEN 50
#define MAX_ID_LEN 10

struct Student {
    char id[MAX_ID_LEN];
    char name[MAX_NAME_LEN];
    int age;
    double grade;
};

struct StudentManager {
    struct Student students[MAX_STUDENTS] = {
        {"1", "Alice", 20, 80},
        {"2", "Bob", 19, 73},
        {"3", "Charlie", 21, 85},
        {"4", "John", 20, 94},
        {"5", "Zack", 23, 60}
    };
    int studentCount = 5;

    void init() {
        studentCount = 5;
    }

    void addStudent(const char* id, const char* name, int age, double grade) {
        if (studentCount >= MAX_STUDENTS) {
            cout << "has reached the limit of student" << endl;
            return;
        }
        strcpy(students[studentCount].id, id);
        strcpy(students[studentCount].name, name);
        students[studentCount].age = age;
        students[studentCount].grade = grade;
        studentCount++;
        cout << "student add successfully" << endl;
    }

    void displayAllStudents() {
        for (int i = 0; i < studentCount; i++) {
            cout << "ID: " << students[i].id << ", Name: " << students[i].name
                 << ", Age: " << students[i].age << ", Grade: " << students[i].grade << endl;
        }
    }

    void quickSortByName(int left, int right) {
        if (left >= right) return;
        char pivot[MAX_NAME_LEN];
        strcpy(pivot, students[left + (right - left) / 2].name);
        int i = left, j = right;

        while (i <= j) {
            while (strcmp(students[i].name, pivot) < 0) i++;
            while (strcmp(students[j].name, pivot) > 0) j--;
            if (i <= j) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
                i++;
                j--;
            }
        }
        if (left < j) quickSortByName(left, j);
        if (i < right) quickSortByName(i, right);
    }

    void sortByGrade() {
        for (int i = 0; i < studentCount - 1; i++) {
            for (int j = 0; j < studentCount - i - 1; j++) {
                if (students[j].grade > students[j + 1].grade) {
                    Student temp = students[j];
                    students[j] = students[j + 1];
                    students[j + 1] = temp;
                }
            }
        }
    }

    void searchStudentById(const char* id) {
        int left = 0, right = studentCount - 1;

        for (int i = 0; i < studentCount - 1; i++) {
            for (int j = 0; j < studentCount - i - 1; j++) {
                if (strcmp(students[j].id, students[j + 1].id) > 0) {
                    Student temp = students[j];
                    students[j] = students[j + 1];
                    students[j + 1] = temp;
                }
            }
        }

        while (left <= right) {
            int mid = left + (right - left) / 2;
            int cmp = strcmp(students[mid].id, id);
            if (cmp == 0) {
                cout << "Find student:\n ID: " << students[mid].id
                     << ", Name:  " << students[mid].name
                     << ", Age: " << students[mid].age
                     << ", Grade: " << students[mid].grade << endl;
                return;
            }
            if (cmp < 0) left = mid + 1;
            else right = mid - 1;
        }
        cout << "Doesn't find the student with ID: " << id << endl;
    }
};

int main() {
    StudentManager manager;
    manager.init();

    while(true) {
        int choice;
        cout << "\n=== Function lists===\n";
        cout << "1. Show all student\n";
        cout << "2. Add student\n";
        cout << "3. Sort with name and display\n";
        cout << "4. Sort with grade and display\n";
        cout << "5. Search student ( by ID )\n";
        cout << "6. End program\n";
        cout << "Choose a function: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            manager.displayAllStudents();
        } else if (choice == 2) {
            char id[MAX_ID_LEN], name[MAX_NAME_LEN];
            int age;
            double grade;

            cout << "Enter new student's ID: ";
            cin.getline(id, MAX_ID_LEN);
            cout << "Enter new student's name: ";
            cin.getline(name, MAX_NAME_LEN);
            cout << "Enter new student's age: ";
            cin >> age;
            cout << "Enter new student's grade: ";
            cin >> grade;
            cin.ignore();

            manager.addStudent(id, name, age, grade);
        } else if (choice == 3) {
            manager.quickSortByName(0, manager.studentCount - 1);
            manager.displayAllStudents();
        } else if (choice == 4) {
            manager.sortByGrade();
            manager.displayAllStudents();
        } else if (choice == 5) {
            char searchId[MAX_ID_LEN];
            cout << "Enter the ID to Search: ";
            cin.getline(searchId, MAX_ID_LEN);
            manager.searchStudentById(searchId);
        } else if (choice == 6) {
            cout << "Program has ended." << endl;
            break;
        } else {
            cout << "Invalid input, please try again." << endl;
        }
    }
    return 0;
}
