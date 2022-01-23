#include "CCourse.h"
#include <vector>
#include <iostream>
#include <regex>
#include <iomanip>
#include <fstream>

using namespace std;

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
            studentToChange.labGrade * LAB_WEIGHT +
            studentToChange.quizGrade * QUIZ_WEIGHT +
            studentToChange.midGrade * MID_WEIGHT +
            studentToChange.finalExam * FINAL_WEIGHT;

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

    bool CCourse::validStudent(string *studentIndex, int *edit) {
        // Check if input is a number
        if (!regex_match(*studentIndex, regex("[0-9]*"))) return false;
        *edit = stoi(*studentIndex);
        // Check if input is in bounds
        if (*edit > v_students.size() || v_students.size() == 0) return false;
        return true;
    }


    // Add student method
    void CCourse::add_student() {
        int vsize = v_students.size();
        // Request grade data from user
        reqData(-1);
    }
    // Edit Student method
    void CCourse::edit_student() {
        if (v_students.size() <= 0) return;
        string input;
        int edit;
            do {
                cout << "Student to Edit\n";
                cin >> input;
            } while (!validStudent(&input, &edit));
        reqData(edit-1);
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
        if (v_students.size() <= 0) return;
        string input;
        int edit;
        do {
            cout << "Student to Delete:\n";
            cin >> input;
        } while (!validStudent(&input, &edit));
        v_students.erase(v_students.begin() + edit - 1);
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

    // Method to save student to a txt file
    void CCourse::save_file() {
        string str;
        ofstream outfile;
        cout << "Name the file: ";
        // Take input for file name
        cin >> str;

        if (!regex_match(str, regex("[a-z]*.txt")) && !regex_match(str, regex("[A-Z]*.txt"))) {
            cout << "\nFile must end in \".txt\"\n";
            return;
        }
        outfile.open(str);
        if (!outfile.is_open()) {
            cout << "\nFile could not be opened\n";
            return;
        }
        
        // Saves a student vector to file using a stream
        CStudent s;
        for (int i = 0; i < v_students.size(); i++) {
            s = v_students.at(i);
            outfile << s.finalExam << " " << s.finalGrade << " " << s.labGrade
                << " " << s.midGrade << " " << s.quizGrade << " " << s.studentNum;
            // Adds a newline n-1 times, so eof is read properly
            if (i != v_students.size()-1) outfile << endl;
        }
    }

    // Method to Load student from a txt file
    void CCourse::load_file() {
        ifstream infile;
        string str;
        cout << "File to open: ";
        cin >> str;
        if (!regex_match(str, regex("[a-z]*.txt")) && !regex_match(str, regex("[A-Z]*.txt"))) {
            cout << "\nFile must end in \".txt\"\n";
            return;
        }
        infile.open(str);
        if (!infile.is_open()) {
            cout << "\nFile could not be opened\n";
            return;
        }

        // Make sure current list is empty to prevent duplication
        v_students.clear();

        int i = 0;
        string datain;
        CStudent tempStudent;
        // Read lines of file
        while(!infile.eof()) {
            infile >> tempStudent.finalExam >> tempStudent.finalGrade
                >> tempStudent.labGrade >> tempStudent.midGrade
                >> tempStudent.quizGrade >> tempStudent.studentNum;
            v_students.push_back(tempStudent);
        }
    }