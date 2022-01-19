// Student Grade Calculator 
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

// Function Prototypes
bool print_menu();
void add_student();
void edit_student();
void print_student();
float calc_final(float labGrade, float quizGrade, float midGrade, float finalGrade);
void reqData(int studentToChange);
string validString(string regextype);

// How many students are currently indexed
int studentIndex = 0;

// Declare struct
struct student {
    string studentNum;
    float labGrade;
    float quizGrade;
    float midGrade;
    float finalExam;
    float finalGrade;
};
student students[100];

// Main loop
int main() {
    // Run print menu as long as user doesn't quit
    while (print_menu());
    return 0;
}

// This function 
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
    cout << "\n(A)dd student\n(E)dit student\n(P)rint grades\n(Q)uit\n\n\CMD> ";
    char inputChar;
    cin >> inputChar;

    // What to do based on users input
    switch (toupper(inputChar)) {
    case('A'):
        add_student();
        break;
    case('E'):
        edit_student();
        break;
    case('P'):
        print_student();
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

// This function adds a student based on the users grade input
void add_student() {
    //cout << "Adding Student...";
    // Request grade data from user
    reqData(studentIndex);
    // Next Student
    studentIndex++;
}


// This function edits a student's grade data
void edit_student() {
    cout << "Student to Edit: ";
    int edit;
    cin >> edit;
    // Array is zero-indexed, thus, subtract one
    reqData(edit - 1);
}


// This function prints out the list of students which is equal to how many students have been added to the database
void print_student() {
    cout << "\n#     Student      Lab      Quiz     Midterm     Final Exam     Final Grade\n\n";
    for (int i = 0; i < studentIndex; i++) {

        cout << i + 1 << "     "
            << setfill(' ') << left << setw(13)
            << students[i].studentNum << setw(9)
            << students[i].labGrade << left << setw(9)
            << students[i].quizGrade << left << setw(12)
            << students[i].midGrade << left << setw(15)
            << students[i].finalExam
            << students[i].finalGrade
            << endl;

    }
}


// This function simply calculates the final grade based on weighting
float calc_final(float labGrade, float quizGrade, float midGrade, float finalExam) {
    return (
        labGrade * LAB_WEIGHT +
        quizGrade * QUIZ_WEIGHT +
        midGrade * MID_WEIGHT +
        finalExam * FINAL_WEIGHT
        );
}

// This function gets data from the user for filling out grade info
void reqData(int studentToChange) {
    // Request grade data from user
    
    cout << "\nStudent Number\n";
    students[studentToChange].studentNum = validString(STRFILTER);
    // Get Lab Grade
    cout << "\nLab Grade\n";
    students[studentToChange].labGrade = stof(validString(NUMFILTER));
    cout << "\nQuiz Grade\n";
    students[studentToChange].quizGrade = stof(validString(NUMFILTER));
    cout << "\nMidterm Grade\n";
    students[studentToChange].midGrade = stof(validString(NUMFILTER));
    cout << "\nFinal Exam Grade\n";
    students[studentToChange].finalExam = stof(validString(NUMFILTER));

    // Calculate and store final grade
    students[studentToChange].finalGrade = calc_final(
        students[studentToChange].labGrade,
        students[studentToChange].quizGrade,
        students[studentToChange].midGrade,
        students[studentToChange].finalExam
    );
}

// Function that returns a string if it is valid based on the input parameter
string validString(string regextype) {
    string inputStr;
    do {
        do {
            cout << "\Enter Data: ";
            cin >> inputStr;
            inputStr[0] = toupper(inputStr[0]);
        } while (!regex_match(inputStr, regex(regextype)));
    } while (regextype == NUMFILTER && !(stof(inputStr) <= 100 && stof(inputStr) >= 0));
    return (inputStr);
}