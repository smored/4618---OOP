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