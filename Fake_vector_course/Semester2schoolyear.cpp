#include "Schoolyear_header.h"

/*void init_semester_in_schoolyear(SchoolYear *&arr)
{
    arr->data_semester = new Semester[1]; // for semester
    arr->semester_num = 0;
    arr->semester_capacity = 12;
}*/

void resize_shoolyear_for_semester(SchoolYear *&arr, int new_capacity)
{
    Semester *new_data = new Semester[new_capacity];
    for (int i = 0; i < arr->semester_num; i++)
    {
        new_data[i] = arr->data_semester[i];
    }
    delete[] arr->data_semester;
    arr->data_semester = new_data;
    arr->semester_capacity = new_capacity;
}

void push_back_semester(SchoolYear *&arr, Semester *value)
{
    if (arr->semester_num == arr->semester_capacity)
    {
        int new_capacity = arr->semester_capacity + 1;
        resize_shoolyear_for_semester(arr, new_capacity);
    }
    arr->data_semester[arr->semester_num] = Semester(*value);
    arr->semester_num++;
    arr->current_semester = arr->semester_num - 1;
}

void init_semester(Semester *&arr)
{
    arr = new Semester;
    arr->data_course = new Course[1];
    arr->course_num = 0;
    arr->course_capacity = 1;
}

void resize_semeter(Semester *&arr, int new_capacity)
{
    Course *new_data = new Course[new_capacity];
    for (int i = 0; i < arr->course_num; i++)
    {
        new_data[i] = arr->data_course[i];
    }
    delete[] arr->data_course;
    arr->data_course = new_data;
    arr->course_capacity = new_capacity;
}

void create_semester(SchoolYear *&school_year, Semester sem)
{
    Semester *new_semester = nullptr;
    init_semester(new_semester);
    new_semester->semester_id = sem.semester_id;
    new_semester->start_day = sem.start_day;
    new_semester->end_day = sem.end_day;
    push_back_semester(school_year, new_semester);
    cout << "Semester " << school_year->current_semester + 1 << " add to school year successfully" << endl;
}
