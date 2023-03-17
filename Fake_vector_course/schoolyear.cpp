#include <iostream>
#include <iomanip>
#include <fstream>
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
};

struct Course
{
    string course_id;
    string course_name;
    string class_name;
    string teacher_name;
    int credits;
    int max_students;
    string day_of_week;
    string session;
    Student *enrolled_student;
};

struct vectors
{
    Course *data;
    int size;
    int capacity;
};



struct Semester
{
    int semester_id;
    string start_day;
    string end_day;
    vectors *courses;
};

struct SchoolYear
{
    string year_name;
    Semester semesters;
};

void init(vectors *&arr)
{
    // allocate memory for the struct and its data array
    arr = new vectors;
    arr->data = new Course[1];
    arr->size = 0;
    arr->capacity = 1;
}

void resize(vectors *&arr, int new_capacity)
{
    // allocate a new array with the desired capacity
    Course *new_data = new Course[new_capacity];

    // copy the old data to the new array
    for (int i = 0; i < arr->size; i++)
    {
        new_data[i] = arr->data[i];
    }

    // free the old array
    delete[] arr->data;

    // update the struct fields
    arr->data = new_data;
    arr->capacity = new_capacity;
}

void push_back(vectors *&arr, Course value)
{
    // if the array is full, double its capacity
    if (arr->size == arr->capacity)
    {
        // int new_capacity = arr->capacity * 2;
        int new_capacity = arr->capacity + 15;
        resize(arr, new_capacity);
    }
    // add the new element at the end of the array
    arr->data[arr->size] = value;
    arr->size++;
}

void pop_back(vectors *&arr)
{
    // if the array is not empty, remove the last element
    if (arr->size > 0)
    {
        arr->size--;

        // if the array is less than 25% full, halve its capacity
        if (arr->size * 4 <= arr->capacity)
        {
            int new_capacity = arr->capacity / 2;
            if (new_capacity < 1)
            {
                new_capacity = 1;
            }
            resize(arr, new_capacity);
        }
    }
}

SchoolYear create_school_year(string year_name)
{
    SchoolYear schoolyear;
    schoolyear.year_name = year_name;
    // Initialize the courses dynamic array
    init(schoolyear.semesters.courses);
    return schoolyear;
}

void add_class_to_schoolyear(SchoolYear &school_year, string class_name)
{
    Semester def_semester = school_year.semesters;
    for (int i = 0; i < def_semester.courses->size; i++)
    {
        Course course = def_semester.courses->data[i];
        if (course.class_name == class_name)
        {
            cout << "Error: Class already exists in current semester." << endl;
            return;
        }
    }
    Course new_course;
    new_course.class_name = class_name;
    push_back(def_semester.courses, new_course);
    school_year.semesters = def_semester;
    cout << "Class " << class_name << " added to SchoolYear " << school_year.year_name << "." << endl;
}
int main()
{
    string year_name, class_name;
    cout << "School year: ";
    cin >> year_name;
    SchoolYear school_year = create_school_year(year_name);
    cout << "Class name (add class to semester): ";
    cin >> class_name;
    add_class_to_schoolyear(school_year, class_name);
    return 0;
}