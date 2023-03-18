#include <iostream>
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

struct Semester
{
    int semester_id;
    string start_day;
    string end_day;
};

struct Classes
{
    string class_name;
    Student *data_student; // dynamic
    int student_num;       // size
    int student_capacity;
};

struct SchoolYear
{
    string year_name;
    Classes *data_classes;
    int class_num;
    int class_capacity;
};

void init_school_year(SchoolYear *&arr)
{
    arr = new SchoolYear;
    arr->data_classes = new Classes[1];
    arr->class_num = 0;
    arr->class_capacity = 1;
}

void resize_school_year(SchoolYear *&arr, int new_capacity)
{
    Classes *new_data = new Classes[new_capacity];
    for (int i = 0; i < arr->class_num; i++)
    {
        new_data[i] = arr->data_classes[i];
    }
    delete[] arr->data_classes;
    arr->data_classes = new_data;
    arr->class_capacity = new_capacity;
}

SchoolYear *create_school_year(string year_name)
{
    SchoolYear *schoolyear = new SchoolYear;
    schoolyear->year_name = year_name;
    return schoolyear;
}

void push_back_class(SchoolYear *&arr, Classes *value)
{
    if (arr->class_num == arr->class_capacity)
    {
        int new_capacity = arr->class_capacity + 1; // just add one class
        resize_school_year(arr, new_capacity);
    }
    arr->data_classes[arr->class_num] = Classes(*value);
    // move it, not the copy of it
    arr->class_num++;
}

void init_class(Classes *&arr)
{
    arr = new Classes;
    arr->data_student = new Student[1];
    arr->student_num = 0;
    arr->student_capacity = 1;
}

void resize_class(Classes *&arr, int new_capacity)
{
    Student *new_data = new Student[new_capacity];
    for (int i = 0; i < arr->student_num; i++)
    {
        new_data[i] = arr->data_student[i];
    }
    delete[] arr->data_student;
    arr->data_student = new_data;
    arr->student_capacity = new_capacity;
}

void add_class_to_schoolyear(SchoolYear *&school_year, string classname)
{
    Classes *new_class = new Classes;
    init_class(new_class);
    new_class->class_name = classname;
    push_back_class(school_year, new_class);
    cout << "Class " << school_year->data_classes[school_year->class_num - 1].class_name << " added to SchoolYear " << school_year->year_name << "." << endl;
}

void push_back_student(Classes *&arr, Student value)
{
    if (arr->student_num == arr->student_capacity)
    {
        int new_capacity = arr->student_capacity + 15;
        resize_class(arr, new_capacity);
    }
    arr->data_student[arr->student_num] = value; // add to the end
    arr->student_num++;
}

void view_class_in_schoolyear(SchoolYear *school_year)
{
    for (int i = 0; i < school_year->class_num; i++)
        cout << school_year->data_classes[i].class_name << endl;
}

int main()
{
    string year_name, classname;
    int op;
    cout << "School year: ";
    cin >> year_name;
    SchoolYear *school_year = create_school_year(year_name);
    do
    {
        cout << "Option: ";
        cin >> op;
        switch (op)
        {
        case 0:
        {
            break;
        }
        case 1:
        {
            cout << "Class name (add class to schoolyear): ";
            cin >> classname;
            add_class_to_schoolyear(school_year, classname);
            break;
        }
        case 2:
        {
            view_class_in_schoolyear(school_year);
            break;
        }
        }
    } while (op != 0);
    for (int i = 0; i < school_year->data_classes->student_capacity; i++)
    {
        delete[] school_year->data_classes[i].data_student;
    }
    delete[] school_year->data_classes;
    delete school_year;
    return 0;
}
