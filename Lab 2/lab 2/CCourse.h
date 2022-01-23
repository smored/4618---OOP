#pragma once

#include "CStudent.h"
#include <vector>
using namespace std;

// How to weight assignments
#define LAB_WEIGHT 0.4f
#define QUIZ_WEIGHT 0.1f
#define MID_WEIGHT 0.2f
#define FINAL_WEIGHT 0.3f
// Regex filters
#define STRFILTER "A0[01][0-9]{6}"
#define NUMFILTER "[+-]?([0-9]*[.])?[0-9]+"

class CCourse {
private:
    vector<CStudent> v_students;
    void reqData(int index);
    string validString(string regextype);

public:
  
    void add_student();
    void edit_student();
    void print_student();
    void delete_student();
    bool validStudent(string *studentIndex, int *edit);
    void save_file();
    void load_file();
    //vector<CStudent> m_getVStudent();
    //void m_setVStudent();
    
    // Constructor
    CCourse();

    // Deconstructor
    ~CCourse();
};