#include "Schoolyear_header.h"

void init_school_year(SchoolYear *&arr)
{
    arr = new SchoolYear;
    arr->data_classes = new Classes[1];
    arr->class_num = 0;
    arr->class_capacity = 1;

    arr->data_semester = new Semester[1]; // for semester
    arr->semester_num = 0;
    arr->semester_capacity = 1;
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
    // SchoolYear *schoolyear = new SchoolYear;
    SchoolYear *school_year = nullptr;
    init_school_year(school_year); // mowis theem
    school_year->year_name = year_name;
    return school_year;
}

void push_back_class(SchoolYear *&arr, Classes *value)
{
    if (arr->class_num == arr->class_capacity)
    {
        int new_capacity = arr->class_capacity + 5; // just add one class
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

void add_class_to_schoolyear(SchoolYear *school_year, string classname)
{
    Classes *new_class = nullptr;
    init_class(new_class);
    new_class->class_name = classname;
    push_back_class(school_year, new_class);
    cout << "Class " << school_year->data_classes[school_year->class_num - 1].class_name << " added to SchoolYear " << school_year->year_name << "." << endl;
}

void view_class_in_schoolyear(SchoolYear *school_year) // thêm vào để check thôi chứ không có trong yêu cầu
{
    for (int i = 0; i < school_year->class_num; i++)
        cout << school_year->data_classes[i].class_name << endl;
}