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
    Student students[MAX_STUDENTS];
    int studentCount;

    void init() {
        studentCount = 0;
    }

    void addStudent(const char* id, const char* name, int age, double grade) {
        if (studentCount >= MAX_STUDENTS) {
            cout << "學生數量已達上限，無法新增！" << endl;
            return;
        }
        strcpy(students[studentCount].id, id);
        strcpy(students[studentCount].name, name);
        students[studentCount].age = age;
        students[studentCount].grade = grade;
        studentCount++;
        cout << "新增學生成功！" << endl;
    }

    void displayAllStudents() {
        for (int i = 0; i < studentCount; i++) {
            cout << "學號: " << students[i].id << ", 姓名: " << students[i].name
                 << ", 年齡: " << students[i].age << ", 成績: " << students[i].grade << endl;
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
                cout << "找到學生: 學號: " << students[mid].id
                     << ", 姓名: " << students[mid].name
                     << ", 年齡: " << students[mid].age
                     << ", 成績: " << students[mid].grade << endl;
                return;
            }
            if (cmp < 0) left = mid + 1;
            else right = mid - 1;
        }
        cout << "未找到學號為 " << id << " 的學生。" << endl;
    }
};

int main() {
    StudentManager manager;
    manager.init();

    int n;
    cout << "請輸入初始學生數量: ";
    cin >> n;
    cin.ignore();  // 清除輸入緩衝區

    for (int i = 0; i < n; i++) {
        char id[MAX_ID_LEN], name[MAX_NAME_LEN];
        int age;
        double grade;

        cout << "請輸入學生 " << i + 1 << " 的學號: ";
        cin.getline(id, MAX_ID_LEN);
        cout << "請輸入學生 " << i + 1 << " 的姓名: ";
        cin.getline(name, MAX_NAME_LEN);
        cout << "請輸入學生 " << i + 1 << " 的年齡: ";
        cin >> age;
        cout << "請輸入學生 " << i + 1 << " 的成績: ";
        cin >> grade;
        cin.ignore();  // 清除輸入緩衝區

        manager.addStudent(id, name, age, grade);
    }

    while (true) {
        int choice;
        cout << "\n=== 功能選單 ===\n";
        cout << "1. 顯示所有學生\n";
        cout << "2. 新增學生\n";
        cout << "3. 按名字排序並顯示\n";
        cout << "4. 按成績排序並顯示\n";
        cout << "5. 查詢學生 (依學號)\n";
        cout << "6. 結束程式\n";
        cout << "請選擇功能: ";
        cin >> choice;
        cin.ignore();  // 清除輸入緩衝區

        if (choice == 1) {
            manager.displayAllStudents();
        } else if (choice == 2) {
            char id[MAX_ID_LEN], name[MAX_NAME_LEN];
            int age;
            double grade;

            cout << "請輸入新學生的學號: ";
            cin.getline(id, MAX_ID_LEN);
            cout << "請輸入新學生的姓名: ";
            cin.getline(name, MAX_NAME_LEN);
            cout << "請輸入新學生的年齡: ";
            cin >> age;
            cout << "請輸入新學生的成績: ";
            cin >> grade;
            cin.ignore();  // 清除輸入緩衝區

            manager.addStudent(id, name, age, grade);
        } else if (choice == 3) {
            manager.quickSortByName(0, manager.studentCount - 1);
            manager.displayAllStudents();
        } else if (choice == 4) {
            manager.sortByGrade();
            manager.displayAllStudents();
        } else if (choice == 5) {
            char searchId[MAX_ID_LEN];
            cout << "請輸入要查詢的學號: ";
            cin.getline(searchId, MAX_ID_LEN);
            manager.searchStudentById(searchId);
        } else if (choice == 6) {
            cout << "程式結束，感謝使用！" << endl;
            break;
        } else {
            cout << "無效的選項，請重新輸入！" << endl;
        }
    }

    return 0;
}
