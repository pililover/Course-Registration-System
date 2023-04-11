/*#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
using namespace std;

// struct Score
// {
//     int student_id;
//     float score;
// };
struct Student
{
    string student_num;
    string studentID;
    string firstname;
    string lastname;
    string gender;
    string birthday;
    string socialID;
    float score;      // score for course, gpa for class
    float gpa_4_year; // gpa of all four year for class
};
struct Course
{
    string course_id;
    string course_name;
    string class_name;
    string teacher_name;
    int credits;
    int max_students = 50;
    string day_of_week;
    string session;
    Student *enrolled_student;
    int size_student;
    int capacity_student;
    // Score *scores;
};
struct Semester
{
    Course *data_course = nullptr;
    string start_day;
    string end_day;
    int course_num = 0;
    int capacity_course = 0;
};
struct Classes
{
    string class_name;
    Student *data_student = nullptr; // dynamic
    int student_num;                 // size
    int student_capacity;
};

struct SchoolYear
{
    string year_name;
    Classes *data_classes;
    Semester *data_semester;
    int semester_num = 0;
    int current_semester = 0;
    int semester_capacity = 0;
    int class_num = 0;
    int class_capacity;
};

struct System
{
    SchoolYear *data_schoolyear;
    int year_num = 0;
    int year_capacity = 1;
};
*/
// All years
#include "Schoolyear_header.h"

void cal_GPA_all_student_in_class(System &system, Classes *classes)
{
    for (int i = 0; i < classes->student_num; i++)
    {
        double gpa = 0;
        double n = 0;
        for (int j = 0; j < system.year_num; j++)
        {
            for (int z = 0; z < system.data_schoolyear[j].class_num; z++)
            {
                if (system.data_schoolyear[j].data_classes[z].class_name == classes->class_name)
                {
                    if (system.data_schoolyear[j].data_classes[z].data_student[i].score != -1)
                    {
                        gpa = system.data_schoolyear[j].data_classes[z].data_student[i].score;
                        n++;
                    }
                }
            }
        }
        classes->data_student[i].gpa_4_year = gpa / n;
    }
}

// Current year
void cal_GPA_current(SchoolYear *year, Classes *classes, int cur)
{
    for (int i = 0; i < classes->student_num; i++)
    {
        double gpa = 0;
        double n = 0;
        for (int j = 0; j < year->data_semester[cur].course_num; j++)
        {
            for (int z = 0; z < year->data_semester[cur].data_course[j].size_student; z++)
            {
                if (year->data_semester[cur].data_course[j].enrolled_student[z].studentID == classes->data_student[i].studentID)
                {
                    if (year->data_semester[cur].data_course[j].enrolled_student[z].score != -1)
                    {
                        gpa += year->data_semester[cur].data_course[j].enrolled_student[z].score;
                        n++;
                    }
                }
            }
        }
        classes->data_student[i].score = gpa / n;
    }
}

// The show variable is student ID value
// This function output the score of a semester to csv file
void show_score_semester_student(Classes *classes, Semester semester, string show)
{
    string temp = show + "_scores.csv";
    ofstream in(temp, ios::app);

    // The first line in csv is the courses names
    for (int i = 0; i < semester.course_num; i++)
    {
        in << semester.data_course[i].course_name << ',';
        cout << semester.data_course[i].course_name << "  |  ";
    }
    in << "Overall GPA" << endl;
    cout << "Overall GPA" << endl;

    // The second line is the score
    for (int i = 0; i < semester.course_num; i++)
    {
        int flag = 1;
        for (int j = 0; j < semester.data_course[i].size_student; j++)
        {
            if (semester.data_course[i].enrolled_student[j].studentID == show)
            {
                flag = 0;
                in << semester.data_course[i].enrolled_student[j].score << ',';
                cout << semester.data_course[i].enrolled_student[j].score << "  |  ";
            }
        }

        if (flag == 1)
        {
            in << 'X' << ',';
            cout << 'X' << "  |  ";
        }
    }
    for (int i = 0; i < classes->student_num; i++)
    {
        if (classes->data_student[i].studentID == show)
        {
            in << classes->data_student[i].score << endl;
            cout << classes->data_student[i].score << endl;
        }
    }

    in.close();
}

// This function output the score and gpa of a student to csv file and terminal
// cur is the current semester
// classes is the class the student is in
// use loop to change the semester through cur
void show_score_student(SchoolYear *year, int cur, Classes *classes, string show)
{
    string temp = show + "_scores.csv";

    if (year->data_semester)
    {
        ofstream in(temp);
        in << "Semester" << cur + 1 << endl;
        in.close();
        cout << "Semester " << cur + 1 << endl;

        show_score_semester_student(classes, year->data_semester[cur], show);
        ofstream in1(temp, ios::app);
        for (int i = 0; i < classes->student_num; i++)
        {
            if (classes->data_student[i].studentID == show)
            {
                in1 << "GPA until current year," << classes->data_student[i].gpa_4_year << endl;
                cout << "GPA until current year  | " << classes->data_student[i].gpa_4_year << endl;
                break;
            }
        }
        in1.close();
    }
}

// cur is the current semester
// use loop to change the semester through cur
void show_scores_class(SchoolYear *year, Classes *classes, int cur)
{
    string temp = classes->class_name + "_scores.csv";

    ofstream in(temp);
    in << "Class" << classes->class_name << endl;
    cout << "Class " << classes->class_name << endl;
    in.close();

    for (int i = 0; i < classes->student_num; i++)
    {
        ofstream in1(temp, ios::app);
        in1 << classes->data_student[i].firstname << ' ' << classes->data_student[i].lastname << ',';
        cout << classes->data_student[i].firstname << " " << classes->data_student[i].lastname << "  |  ";
        in1.close();

        show_score_semester_student(classes, year->data_semester[cur], classes->data_student[i].studentID);
    }
}