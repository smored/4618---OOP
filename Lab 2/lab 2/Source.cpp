// Student Grade Calculator (Updated)
// By Kurt Querengesser
// A01169042  Set 4S

#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <regex>
#include "CCourse.h"


using namespace std;
// How large to draw the asterix box
#define BOX_SIZE 111


// Function Prototypes
bool print_menu();
CCourse course;

// Main loop
int main() {
    // Run print menu as long as user doesn't quit
    int k = 27, m = 987654321, n = -4321;
    cout << setw(9);
    cout << setfill(' ');
    cout << k << m << n;
    //cout << fixed << setprecision(5) << a << ' ' << b << ' ' << c
    //while (print_menu());
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
    cout << "\n(A)dd student\n(E)dit student\n(P)rint grades\n(D)elete grades\n(S)ave\n(L)oad\n(Q)uit\n\n\CMD> ";
    string inputChar;
    cin >> inputChar;

    if (!regex_match(inputChar, regex("[AEPDSLQaepdslq]"))) return 1;
    inputChar = toupper(inputChar[0]);

    // what to do based on users input
    switch (inputChar[0]) {
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
    case('S'):
        course.save_file();
        break;
    case('L'):
        course.load_file();
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