#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>

using namespace std;
struct Score
{
    int student_id;
    float score;
};

struct Student
{
    string student_num;
    string studentID;
    string firstname;
    string lastname;
    string gender;
    string birthday;
    string socialID;
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
    Score *scores;
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
    string year_name; // Ex:2022-2023???
    Classes *data_classes;
    Semester *semester_data;
    int semester_num = 3;
    int current_semester;
    int class_num;
    int class_capacity;
};

void recapacity_student_in_a_course(Course *&course_need_add_student_now, int new_capacity)
{
    Student *array_student_need_add_now = course_need_add_student_now->enrolled_student;
    Student *new_array = new Student[new_capacity];
    for (int i = 0; i < course_need_add_student_now->size_student; i++)
        new_array[i] = array_student_need_add_now[i];
    delete[] array_student_need_add_now;
    course_need_add_student_now->enrolled_student = new_array;
    course_need_add_student_now->capacity_student = new_capacity;
}

void push_back_student_to_course(Course *&course_need_add_student_now, Student &value)
{
    if (course_need_add_student_now->size_student == course_need_add_student_now->capacity_student)
    {
        int new_capacity = (course_need_add_student_now->capacity_student == 0) ? 1 : course_need_add_student_now->capacity_student + 15;
        recapacity_student_in_a_course(course_need_add_student_now, new_capacity);
    }
    course_need_add_student_now->size_student++;
    course_need_add_student_now->enrolled_student[course_need_add_student_now->size_student] = value;
}

void view_list_of_course(SchoolYear *school_year)
{
    cout << "\t\tLIST OF COURSE IN THIS SEMESTER" << endl;
    if (school_year->semester_data[school_year->current_semester].course_num == 0)
    {
        cout << "Course not found" << endl;
        return;
    }
    for (int i = 0; i < school_year->semester_data[school_year->current_semester].course_num; i++)
    {
        cout << i + 1 << ". "
             << school_year->semester_data[school_year->current_semester].data_course->course_id << " \t"
             << school_year->semester_data[school_year->current_semester].data_course->course_name << endl;
    }
}

void export_student_from_course_to_file(SchoolYear *school_year, string courseid) // id của course muốn xuất danh sách học sinh nhập ở main
{
    ofstream op(courseid);
    if (!op)
    {
        cout << "Cannot open the file" << endl;
        return;
    }
    for (int i = 0; i < school_year->semester_data[school_year->current_semester].course_num; i++)
    {
        if (school_year->semester_data[school_year->current_semester].data_course[i].course_id == courseid)
        {
            op << i + 1 << ". " << school_year->semester_data[school_year->current_semester].data_course[i].course_id << " - "
               << school_year->semester_data[school_year->current_semester].data_course[i].course_name << endl;
            for (int j = 0; j < school_year->semester_data[school_year->current_semester].data_course[i].size_student; j++)
            {
                op << school_year->semester_data[school_year->current_semester].data_course[i].enrolled_student[j].studentID << " \t"
                   << school_year->semester_data[school_year->current_semester].data_course[i].enrolled_student[j].firstname << " "
                   << school_year->semester_data[school_year->current_semester].data_course[i].enrolled_student[j].lastname << endl;
            }
        }
    }
    op.close();
}
