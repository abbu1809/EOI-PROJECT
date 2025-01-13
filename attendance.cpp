#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
using namespace std;

struct Student {
    int id;
    string name;
    map<string, bool> attendance; 
};

class AttendanceManager {
private:
    vector<Student> students;

public:
    void addStudent(int id, string name) {
        Student newStudent = {id, name};
        students.push_back(newStudent);
        cout << "Student added successfully!\n";
    }

    void markAttendance(int id, const string &date, bool presence) {
        for (auto &student : students) {
            if (student.id == id) {
                student.attendance[date] = presence;
                cout << "Attendance updated for " << student.name << " on " << date << "\n";
                return;
            }
        }
        cout << "Student with ID " << id << " not found!\n";
    }

    void displayAttendance(const string &date = "") {
        cout << left << setw(10) << "ID" << setw(20) << "Name";
        if (!date.empty()) {
            cout << "Attendance (" << date << ")";
        } else {
            cout << "Attendance Records";
        }
        cout << endl;
        cout << string(50, '-') << endl;

        for (const auto &student : students) {
            cout << left << setw(10) << student.id << setw(20) << student.name;
            if (!date.empty()) {
                if (student.attendance.count(date)) {
                    cout << (student.attendance.at(date) ? "Present" : "Absent");
                } else {
                    cout << "No Record";
                }
            } else {
                for (const auto &record : student.attendance) {
                    cout << "\n  " << record.first << ": " << (record.second ? "Present" : "Absent");
                }
            }
            cout << endl;
        }
    }

    void displayAttendancePercentage() {
        cout << left << setw(10) << "ID" << setw(20) << "Name" << "Attendance (%)" << endl;
        cout << string(50, '-') << endl;

        for (const auto &student : students) {
            int totalDays = student.attendance.size();
            int presentDays = 0;
            for (const auto &record : student.attendance) {
                if (record.second) {
                    presentDays++;
                }
            }

            double percentage = totalDays > 0 ? (presentDays * 100.0 / totalDays) : 0.0;

            cout << left << setw(10) << student.id << setw(20) << student.name << fixed << setprecision(2) << percentage << "%" << endl;
        }
    }
};

int main() {
    AttendanceManager manager;
    int choice;

    do {
        cout << "\n========== Attendance Management System ==========" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Mark Attendance" << endl;
        cout << "3. Display Attendance" << endl;
        cout << "4. Display Attendance Percentage" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id;
                string name;
                cout << "Enter Student ID: ";
                cin >> id;
                cin.ignore(); 
                cout << "Enter Student Name: ";
                getline(cin, name);
                manager.addStudent(id, name);
                break;
            }
            case 2: {
                int id;
                string date;
                char presence;
                cout << "Enter Student ID: ";
                cin >> id;
                cout << "Enter Date (YYYY-MM-DD): ";
                cin >> date;
                cout << "Is the student present? (y/n): ";
                cin >> presence;
                manager.markAttendance(id, date, presence == 'y' || presence == 'Y');
                break;
            }
            case 3: {
                string date;
                cout << "Enter Date to Display Attendance (or leave empty to see all records): ";
                cin.ignore();
                getline(cin, date);
                manager.displayAttendance(date);
                break;
            }
            case 4:
                manager.displayAttendancePercentage();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again!\n";
        }
    } while (choice != 5);

    return 0;
}
