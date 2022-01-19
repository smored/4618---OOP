#include<stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

void add_student();
void edit_student();
void print_menu();
void print_grades();
void Quit();
int x = 0;
typedef struct student_info
{
    int numberofstudents;
    char studentnumber[1000];
    float labgrade;
    float quizgrade;
    float midtermgrade;
    float finalexamgrade;
} student;


int main()
{
    while (true) {
        print_menu();
    }
    return 0;
}

void print_menu()
{
    char selector;
    printf("*******************************************");
    printf("\n \n ELEX4618 Grade System, by DANIAL BOZORGTAR");
    printf("\n \n *******************************************");
    printf("\n\n");
    printf(" (A)dd student\n (E)dit student\n (P)rint grade\n (Q)uit\n");
    printf("\nCMD> ");
    scanf_s("%c", &selector);

    switch (selector)
    {
    case 'A': add_student();
        break;
    case 'E': edit_student();
        break;
    case 'P': print_grades();
        break;
    case 'Q': Quit();
        break;
    default:printf("Invalid choice!\n");
        break;
    }

}
student studentlist[100];
void add_student()
{
    if (x >= 100) {
        printf("maximum size of list reached");
        return;
    }
    else {
        printf("\n Adding Student\n\n");
        printf("Student Number: ");
        scanf_s("%s", studentlist[x].studentnumber, 10);
        printf("Lab Grade: ");
        scanf_s("%f", &studentlist[x].labgrade);
        printf("Quiz Grade: ");
        scanf_s("%f", &studentlist[x].quizgrade);
        printf("Midterm Grade: ");
        scanf_s("%f", &studentlist[x].midtermgrade);
        printf("Final Exam Grade: ");
        scanf_s("%f", &studentlist[x].finalexamgrade);
        x++;
        printf("%d", x);

    }

}
void Quit()
{
    return;
}
void edit_student()
{
    printf("\n Final Exam Grade: ");
    return;

}
void print_grades()
{
    printf("\n Final Exam Grade: ");
    return;
}