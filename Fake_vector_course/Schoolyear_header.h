#ifndef _SCHOOLYEAR_HEADER_H_
#define _SCHOOLYEAR_HEADER_H_

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

struct Student
{
    string student_num; 
    string studentID;
    string firstname;
    string lastname;
    string gender;
    string birthday;
    string socialID;
    float score; // score for course, gpa for class
    float other;
    float midterm;
    float final;
    float gpa_4_year = 0; // gpa of all four year for class
};

struct Course
{
    string course_id;
    string course_name;
    string class_name;
    string teacher_name;
    int credits;
    int max_students; // student capacity in a course
    string day_of_week;
    string session;
    Student *enrolled_student;
    int size_student = 0; 
    int capacity_student = 0;
    float percent_other = 0;
    float percent_midterm = 0;
    float percent_final = 0;
};

struct Semester
{
    Course *data_course = nullptr;
    int course_num = 0;
    int course_capacity = 0;
    int semester_id;
    string start_day;
    string end_day;
};

struct Classes
{
    string class_name;
    Student *data_student = nullptr; // dynamic
    int student_num = 0;             // size
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
// Schoolyear.cpp
void init_system(System &arr);
void resize_school_year(SchoolYear *&arr, int new_capacity);
void push_back_schoolyear(System &arr, SchoolYear *value);
void create_school_year(System &system, string year_name);
void view_school_year_and_class_in_each_year(System system);

void push_back_class(SchoolYear *&arr, Classes *value);
void init_class(Classes *&arr);
void resize_class(Classes *&arr, int new_capacity);
bool check_classname_in_a_year(SchoolYear year, string classname, int &index);
void add_class_to_schoolyear(System system, SchoolYear *school_year, string classname);
void view_class_in_schoolyear(System system);

// Student2class.cpp
void push_back_student_to_class(Classes *&arr, Student value);
void import_students_csv_to_class(SchoolYear *&school_year, string classname, string filename);
void input_student_to_class(SchoolYear *&school_year, string classname);
bool check_class_is_empty(SchoolYear *school_year);
void view_student_in_class(System system);

// void init_semester_in_schoolyear(SchoolYear *&arr);
void resize_shoolyear_for_semester(SchoolYear *&arr, int new_capacity);
void push_back_semester(SchoolYear *&arr, Semester *value);
void init_semester(Semester *&arr);
void resize_semeter(Semester *&arr, int new_capacity);
void create_semester(System systems, Semester sem);

void init_course(Course *&arr);
void resize_course(Course *&arr, int new_capacity);
void push_back_course(Semester *&arr, Course *value);
void add_course_to_semester(Semester *&arr, Course value);
void view_couse_in_semester(SchoolYear *school_year);
void view_course_in_schoolyear(System systems, string year_name);

void push_back_student_to_course(Course *&arr, Student value);
void import_students_csv_to_course(SchoolYear *&school_year, string filename, string courseid);
void input_student_to_course(SchoolYear *&school_year, string courseid);
bool check_course_is_empty(SchoolYear *school_year);
void update_course(Course *&update, SchoolYear *&year);

// display
void view_list_of_course(SchoolYear *school_year);
void view_student_in_course(SchoolYear *school_year, int cur_course);
void export_student_from_course_to_file(SchoolYear *school_year, string courseid); // id của course muốn xuất danh sách học sinh nhập ở main;

void import_scoreboard_of_a_course(SchoolYear *school_year);
void view_scoreboard_of_a_course(SchoolYear *school_year);
void update_student_result(SchoolYear *school_year);
void personal_registered_course(SchoolYear *school_year, string ID);

void cal_GPA_all_student_in_class(System &system, Classes *classes);
void cal_GPA_current(SchoolYear *year, Classes *classes, int cur);
void show_score_semester_student(Classes *classes, Semester semester, string show);
void class_to_csv_1(SchoolYear *year, Classes *classes, int cur);
void class_to_csv_2(Classes *classes, Semester semester, string show);
void show_scores_class(SchoolYear *year, Classes *classes, int cur);
void find_score_class(string classname);
void find_score_student(string classname, string ID);

#endif
