#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;

struct Student
{
    int student_id;
    string first_name;
    string last_name;
    string gender;
    string birth;
    string social_id;
};

// Struct to represent a course
struct Course
{
    int course_id;
    string course_name;
    int credits;
    int max_students = 50;
    string class_name;
    string teacher_name;
    string day_of_week;
    string session;
    Student *enrolled_students;
    int num_students;
    Course *next;
};

// Struct to represent a semester
struct Semester
{
    int semester_num; // 1,2,3
    string start_date;
    string end_date;
    Course *courses;
    int num_courses;
    Semester *next;
};

// Struct to represent a school year
struct schoolyear
{
    string year_name;
    Semester *semesters;
    int num_cursemesters;
};

void add_course2semester(schoolyear *&school_year)
{
    int course_id, credit_num;
    string course_name, class_name, teacher, dayofweek, session;
    cout << setw(40) << setfill(' ') << "ADD COURSE TO SEMETER" << endl;
    cout << "Enter the course information: " << endl;
    cout << "Course ID: ";
    cin >> course_id;
    cout << "Name of course: ";
    cin >> course_name;
    cout << "Class name: ";
    cin >> class_name;
    cout << "Name of teacher: ";
    cin >> teacher;
    cout << "Number of credit: ";
    cin >> credit_num;
    cout << "Day of week: ";
    cin >> dayofweek;
    cout << "Session of course: ";
    cin >> session;
    Semester *cur_semester = school_year->semesters;
    while (cur_semester != NULL)
    {
        Course *cur_course = cur_semester->courses;
        for (int i = 0; i < cur_semester->num_courses; i++)
        {
            if (cur_course->course_id == course_id)
            {
                cout << "Course ID already exists." << endl;
                return;
            }
            if (cur_course->class_name == class_name && cur_course->day_of_week == dayofweek && cur_course->session == session)
            {
                cout << "Class already has a course in this session on this day" << endl;
                return;
            }
            cur_course = cur_course->next;
        }
        Course *new_course = new Course;
        new_course->course_id = course_id;
        new_course->course_name = course_name;
        new_course->class_name = class_name;
        new_course->teacher_name = teacher;
        new_course->credits = credit_num;
        new_course->day_of_week = dayofweek;
        new_course->session = session;
        new_course->enrolled_students = new Student[50];
        new_course->next = NULL;

        if (cur_semester->num_courses == 0)
        {
            cur_semester->courses = new_course;
        }
        else
        {
            Course *last = cur_semester->courses;
            while (last->next != NULL)
            {
                last = last->next;
            }
            last->next = new_course;
        }
        cur_semester->num_courses += 1;
        cout << "ADDED SUCCESSFULLY" << endl; //"Course " << course_name << " added to Semester " << cur_semester->semester_num << " in SchoolYear " << school_year->year_name << "." << endl;
        return;
        cur_semester = cur_semester->next;
    }
    cout << "Cannot add course to current semester." << endl;
}

int main()
{
    schoolyear *school_year = new schoolyear;
    school_year->year_name = NULL; //Đợi có mấy function kia rồi thì year_name sẽ là năm hiện tại, mới run được
    school_year->semesters = NULL;
    school_year->num_cursemesters = 0;
    add_course2semester(school_year);
    delete school_year;
    return 0;
}