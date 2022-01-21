#pragma once



// Course Class (Vector of Students)
class CCourse {
private:
    vector<CStudent> v_students;

    void reqData(int index) {
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

    string validString(string regextype) {
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

public:
    // Add student method
    void add_student() {
        int vsize = v_students.size();
        // Request grade data from user
        reqData(-1);
    }
    // Edit Student method
    void edit_student() {
        cout << "Student to Edit: ";
        int edit;
        cin >> edit;
        edit--;
        reqData(edit);
    }
    // Print Student Method
    void print_student() {
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