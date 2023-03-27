#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>

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
};

struct Score
{
    int student_id;
    float score;
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
    Classes *data_classes = nullptr;
    Semester *data_semester1 = nullptr;
    Semester *data_semester2 = nullptr;
    Semester *data_semester3 = nullptr;
    int class_num;
    int class_capacity;
    // SchoolYear *next;
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

void update_course(Course *&update)
{
    // Updating course information
    int flag = -1;
    while (flag != 0)
    {
        cout << "What information of the course do you want to changed?" << endl;
        cout << "Enter 1 to change the course ID." << endl;
        cout << "Enter 2 to change the course name." << endl;
        cout << "Enter 3 to change the class name." << endl;
        cout << "Enter 4 to change the teacher name." << endl;
        cout << "Enter 5 to change the course credit." << endl;
        cout << "Enter 6 to change the course max students." << endl;
        cout << "Enter 7 to change the course day of week." << endl;
        cout << "Enter 8 to change the course sessions." << endl;
        cout << "Enter 9 to add a student to course." << endl;
        cout << "Enter 10 to remove a student from course." << endl;
        cout << "Enter 11 to remove course." << endl;
        cin >> flag;
        string temp_remove;
        switch (flag)
        {
        case 1:
            cout << "Enter the new course ID: ";
            cin >> update->course_id;
            break;

        case 2:
            cout << "Enter the new course name: ";
            cin >> update->course_name;
            break;

        case 3:
            cout << "Enter the new class name: ";
            cin >> update->class_name;
            break;

        case 4:
            cout << "Enter the new teacher name: ";
            cin >> update->teacher_name;
            break;

        case 5:
            cout << "Enter the new credit: ";
            cin >> update->credits;
            break;

        case 6:
            cout << "Enter the new max students: ";
            cin >> update->max_students;
            update->capacity_student = update->max_students;
            break;

        case 7:
            cout << "Enter the new days of week: ";
            cin >> update->day_of_week;
            break;

        case 8:
            cout << "Enter the new sessions: ";
            cin >> update->session;
            break;

        case 9:
            if (update->size_student < update->max_students)
            {
                Student temp;
                cout << "Enter the student number: ";
                cin >> temp.student_num;
                cout << "Enter the student ID: ";
                cin >> temp.studentID;
                cout << "Enter the student first name: ";
                cin >> temp.firstname;
                cout << "Enter the student last name: ";
                cin >> temp.lastname;
                cout << "Enter the student gender: ";
                cin >> temp.gender;
                cout << "Enter the student date of birth: ";
                cin >> temp.birthday;
                cout << "Enter the student social ID: ";
                cin >> temp.socialID;
                push_back_student_to_course(update, temp);
                cout << "Adding student completed" << endl;
            }
            else
            {
                cout << "The number of student had exceeded the max number of student" << endl;
            }
            break;

        case 10:
            cout << "Enter the student ID: ";
            cin >> temp_remove;

            int x = 0;
            int stop = 1;
            while (x < update->size_student && stop != 0)
            {
                x++;
                if (update->enrolled_student[x].studentID == temp_remove)
                {
                    stop = 0;
                    for (int n = x; n < update->size_student; n++)
                    {
                        update->enrolled_student[n] = update->enrolled_student[n + 1];
                    }
                }
            }

            update->size_student--;

            cout << "Erase student completed" << endl;

            if (stop == 1)
                cout << "Student ID does not exist" << endl;

            break;

        case 11:
            delete[] update->enrolled_student;
            delete update;
            cout << "Course has been deleted";
            flag = 0;
            break;

        case 0:
            cout << "Ending updating course information.";
            break;

        default:
            cout << "Invalid input! Please enter an option.";
            break;
        }
        system("pause");
        cout << endl;
    }
}