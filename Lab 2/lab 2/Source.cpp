// Student Grade Calculator (Updated)
// By Kurt Querengesser
// A01169042  Set 4S

#include <iostream>
#include <iomanip>
#include <string>
#include <regex>

using namespace std;

// How to weight assignments
#define LAB_WEIGHT 0.4f
#define QUIZ_WEIGHT 0.1f
#define MID_WEIGHT 0.2f
#define FINAL_WEIGHT 0.3f
// How large to draw the asterix box
#define BOX_SIZE 111
// Regex filters
#define STRFILTER "A0[01][0-9]{6}"
#define NUMFILTER "[+-]?([0-9]*[.])?[0-9]+"

// Student class
class CStudent {
public:
    string studentNum;
    float labGrade;
    float quizGrade;
    float midGrade;
    float finalExam;
    float finalGrade;
};

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

    // Delete Student Method
    void delete_student() {
        cout << "Student to Delete: ";
        int edit;
        cin >> edit;
        // Array is zero-indexed, thus, subtract one
       // v_students.erase(0);
    }


    // Get student vector
    vector<CStudent> m_getVStudent() {
        return v_students;
    }
    // Set student vector
    void m_setVStudent(vector<CStudent> v_students) {
        this->v_students = v_students;
    }

} course;

// Function Prototypes
bool print_menu();
//CStudent reqData(CStudent studentToChange);
//string validString(string regextype);

// Main loop
int main() {
    // Run print menu as long as user doesn't quit
    while (print_menu());
    return 0;
}

// This function prints the options menu
bool print_menu() {
    cout << "\n";
    // Draw the asterix box
    for (int i = 0; i < BOX_SIZE; i++) {
        if (i == BOX_SIZE / 2) {
            cout << "\n\nELEX4618 Grade System by Kurt Querengesser\n\n";
            continue;
        }
        cout << "*";
    }
    // Ask for users input
    cout << "\n(A)dd student\n(E)dit student\n(P)rint grades\n(D)elete grades\n(Q)uit\n\n\CMD> ";
    char inputChar;
    cin >> inputChar;

    // What to do based on users input
    switch (toupper(inputChar)) {
    case('A'):
        course.add_student();
        break;
    case('E'):
        course.edit_student();
        break;
    case('P'):
        course.print_student();
        break;
    case('D'):
        course.delete_student();
        break;
    case('Q'):
        // 0 is the condition to stop looping
        return(0);
    default:
        cout << "\nError, please type in one of the above values\n\n";
    }
    // 1 is the condition to loop again
    return(1);
}
//
// This function adds a student based on the users grade input
//void add_student() {
//    //cout << "Adding Student...";
//    // Request grade data from user
//    reqData(studentIndex);
//    // Next Student
//    studentIndex++;
//}
//
//
//// This function edits a student's grade data
//void edit_student() {
//    cout << "Student to Edit: ";
//    int edit;
//    cin >> edit;
//    // Array is zero-indexed, thus, subtract one
//    reqData(edit - 1);
//}
//
//
//// This function prints out the list of students which is equal to how many students have been added to the database
//void print_student() {
//    cout << "\n#     Student      Lab      Quiz     Midterm     Final Exam     Final Grade\n\n";
//    for (int i = 0; i < studentIndex; i++) {
//
//        cout << i + 1 << "     "
//            << setfill(' ') << left << setw(13)
//            << students[i].studentNum << setw(9)
//            << students[i].labGrade << left << setw(9)
//            << students[i].quizGrade << left << setw(12)
//            << students[i].midGrade << left << setw(15)
//            << students[i].finalExam
//            << students[i].finalGrade
//            << endl;
//
//    }
//}
//
//
//// This function simply calculates the final grade based on weighting
//float calc_final(float labGrade, float quizGrade, float midGrade, float finalExam) {
//    return (
//        labGrade * LAB_WEIGHT +
//        quizGrade * QUIZ_WEIGHT +
//        midGrade * MID_WEIGHT +
//        finalExam * FINAL_WEIGHT
//        );
//}

// This function gets data from the user for filling out grade info
//CStudent reqData(CStudent studentToChange) {
//    // Request grade data from user
//    cout << "\nStudent Number\n";
//    studentToChange.studentNum = validString(STRFILTER);
//    cout << "\nLab Grade\n";
//    studentToChange.labGrade = stof(validString(NUMFILTER));
//    cout << "\nQuiz Grade\n";
//    studentToChange.quizGrade = stof(validString(NUMFILTER));
//    cout << "\nMidterm Grade\n";
//    studentToChange.midGrade = stof(validString(NUMFILTER));
//    cout << "\nFinal Exam Grade\n";
//    studentToChange.finalExam = stof(validString(NUMFILTER));
//
//    // Calculate and store final grade
//    studentToChange.finalGrade =
//        studentToChange.labGrade * LAB_WEIGHT,
//        studentToChange.quizGrade* QUIZ_WEIGHT,
//        studentToChange.midGrade* MID_WEIGHT,
//        studentToChange.finalExam* FINAL_WEIGHT;
//    return studentToChange;
//}

// Function that returns a string if it is valid based on the input parameter
//string validString(string regextype) {
//    string inputStr;
//    do {
//        do {
//            cout << "Enter Data: ";
//            cin >> inputStr;
//            inputStr[0] = toupper(inputStr[0]);
//        } while (!regex_match(inputStr, regex(regextype)));
//    } while (regextype == NUMFILTER && !(stof(inputStr) <= 100 && stof(inputStr) >= 0));
//    return (inputStr);
//}