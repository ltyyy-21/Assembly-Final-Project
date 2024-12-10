#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
using namespace std;

// 學生類別
class Student {
public:
    string id;       // 學號
    string name;     // 姓名
    int age;         // 年齡
    double grade;    // 成績

    Student(string id, string name, int age, double grade)
        : id(id), name(name), age(age), grade(grade) {}
};

// 學生管理類別
class StudentManager {
private:
    vector<Student> students;

    // Quick Sort 排序名字
    void quickSortByName(int left, int right) {
        if (left >= right) return;
        string pivot = students[left + (right - left) / 2].name;
        int i = left, j = right;
        while (i <= j) {
            while (students[i].name < pivot) i++;
            while (students[j].name > pivot) j--;
            if (i <= j) {
                swap(students[i], students[j]);
                i++;
                j--;
            }
        }
        if (left < j) quickSortByName(left, j);
        if (i < right) quickSortByName(i, right);
    }

    // Bubble Sort 排序成績
    void bubbleSortByGrade() {
        int n = students.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (students[j].grade > students[j + 1].grade) {
                    swap(students[j], students[j + 1]);
                }
            }
        }
    }

public:
    // 新增學生
    void addStudent(const Student& student) {
        students.push_back(student);
    }

    // 顯示所有學生資料
    void displayAllStudents() const {
        for (const auto& student : students) {
            cout << "學號: " << student.id << ", 姓名: " << student.name
                 << ", 年齡: " << student.age << ", 成績: " << student.grade << endl;
        }
    }

    // 查詢學生（使用 Binary Search）
    void searchStudentById(const string& id) {
        sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            return a.id < b.id;
        });
        int left = 0, right = students.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (students[mid].id == id) {
                cout << "找到學生: 學號: " << students[mid].id
                     << ", 姓名: " << students[mid].name
                     << ", 年齡: " << students[mid].age
                     << ", 成績: " << students[mid].grade << endl;
                return;
            }
            if (students[mid].id < id) left = mid + 1;
            else right = mid - 1;
        }
        cout << "未找到學號為 " << id << " 的學生。" << endl;
    }

    // 排序學生
    void sortByName() {
        quickSortByName(0, students.size() - 1);
    }
    void sortByGrade() {
        bubbleSortByGrade();
    }

    // 編輯學生資料
    void editStudent(const string& id, const string& newName, int newAge, double newGrade) {
        for (auto& student : students) {
            if (student.id == id) {
                student.name = newName;
                student.age = newAge;
                student.grade = newGrade;
                cout << "學生資料已更新。" << endl;
                return;
            }
        }
        cout << "未找到學號為 " << id << " 的學生。" << endl;
    }

    // 儲存資料到檔案
    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (!file) {
            cout << "無法開啟檔案進行寫入。" << endl;
            return;
        }
        for (const auto& student : students) {
            file << student.id << "," << student.name << "," << student.age << "," << student.grade << endl;
        }
        file.close();
        cout << "學生資料已儲存到檔案。" << endl;
    }

    // 從檔案讀取資料
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cout << "無法開啟檔案進行讀取。" << endl;
            return;
        }
        students.clear();
        string line;
        while (getline(file, line)) {
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            size_t pos3 = line.find(',', pos2 + 1);
            string id = line.substr(0, pos1);
            string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
            int age = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
            double grade = stod(line.substr(pos3 + 1));
            students.emplace_back(id, name, age, grade);
        }
        file.close();
        cout << "學生資料已從檔案讀取。" << endl;
    }
};

int main() {
    StudentManager manager;
    manager.addStudent({"001", "Alice", 20, 85.5});
    manager.addStudent({"002", "Bob", 21, 90.0});
    manager.addStudent({"003", "Charlie", 19, 78.0});

    cout << "=== 所有學生資料 ===" << endl;
    manager.displayAllStudents();

    cout << "\n=== 查詢學號 002 ===" << endl;
    manager.searchStudentById("002");

    cout << "\n=== 按成績排序後的學生資料 ===" << endl;
    manager.sortByGrade();
    manager.displayAllStudents();

    cout << "\n=== 編輯學號 002 的學生資料 ===" << endl;
    manager.editStudent("002", "Bobby", 22, 92.0);
    manager.displayAllStudents();

    cout << "\n=== 儲存和讀取檔案範例 ===" << endl;
    manager.saveToFile("students.txt");
    manager.loadFromFile("students.txt");
    manager.displayAllStudents();

    return 0;
}
