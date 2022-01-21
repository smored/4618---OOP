#include "CCourse.h"
#include <vector>
#include <iostream>
#include <regex>
#include <iomanip>

using namespace std;

// Course Class (Vector of Students)

    //CCourse::vector<CStudent> v_students;

    void CCourse::reqData(int index) {
        CStudent studentToChange;
        cout << "\nStudent Number\n";
        studentToChange.studentNum = validString(STRFILTER);
        cout << "\nLab Grade\n";
        studentToChange.labGrade = stof(validString(NUMFILTER));
        cout << "\nQuiz Grade\n";
        studentToChange.quizGrade = stof(validString(NUMFILTER));
        cout << "\nMidterm Grade\n";
        studentToChange.midGrade = stof(validString(NUMFILTER));
        cout << "\nFinal Exam Grade\n";
        studentToChange.finalExam = stof(validString(NUMFILTER));

        // Calculate and store final grade
        studentToChange.finalGrade =
            studentToChange.labGrade * LAB_WEIGHT,
            studentToChange.quizGrade* QUIZ_WEIGHT,
            studentToChange.midGrade* MID_WEIGHT,
            studentToChange.finalExam* FINAL_WEIGHT;

        if (index == -1) {
            v_students.push_back(studentToChange);
        }
        else {
            v_students.at(index) = studentToChange;
        }
    }

    string CCourse::validString(string regextype) {
        string inputStr;
        do {
            do {
                cout << "Enter Data: ";
                cin >> inputStr;
                inputStr[0] = toupper(inputStr[0]);
            } while (!regex_match(inputStr, regex(regextype)));
        } while (regextype == NUMFILTER && !(stof(inputStr) <= 100 && stof(inputStr) >= 0));
        return (inputStr);
    }


    // Add student method
    void CCourse::add_student() {
        int vsize = v_students.size();
        // Request grade data from user
        reqData(-1);
    }
    // Edit Student method
    void CCourse::edit_student() {
        cout << "Student to Edit: ";
        int edit;
        cin >> edit;
        edit--;
        reqData(edit);
    }
    // Print Student Method
    void CCourse::print_student() {
        cout << "\n#     Student      Lab      Quiz     Midterm     Final Exam     Final Grade\n\n";
        for (int i = 0; i < v_students.size(); i++) {

            cout << i + 1 << "     "
                << setfill(' ') << left << setw(13)
                << v_students.at(i).studentNum << setw(9)
                << v_students.at(i).labGrade << left << setw(9)
                << v_students.at(i).quizGrade << left << setw(12)
                << v_students.at(i).midGrade << left << setw(15)
                << v_students.at(i).finalExam
                << v_students.at(i).finalGrade
                << endl;
        }
    }

    // Delete Student Method
    void CCourse::delete_student() {
        cout << "Student to Delete: ";
        int edit;
        cin >> edit;
        // Array is zero-indexed, thus, subtract one
       // v_students.erase(0);
    }

    //// Get student vector
    //vector<CStudent> m_getVStudent() {
    //    return v_students;
    //}
    //// Set student vector
    //void m_setVStudent(vector<CStudent> v_students) {
    //    this->v_students = v_students;
    //}

    // Constructor
    CCourse::CCourse() {

    }

    // Deconstructor
    CCourse::~CCourse() {

    }