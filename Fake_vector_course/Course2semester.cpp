#include "Schoolyear_header.h"

void init_course(Course *&arr)
{
    arr = new Course;
    arr->enrolled_student = new Student[50];
    arr->size_student = 0;
    arr->max_students = 50;
}

void resize_course(Course *&arr, int new_capacity)
{
    Student *new_data = new Student[50];
    for (int i = 0; i < arr->size_student; i++)
    {
        new_data[i] = arr->enrolled_student[i];
    }
    delete[] arr->enrolled_student;
    arr->enrolled_student = new_data;
    arr->max_students = 50;
}

void push_back_course(Semester *&arr, Course *value)
{
    if (arr->course_num == arr->course_capacity)
    {
        int new_capacity = arr->course_num + 5;
        resize_semeter(arr, new_capacity);
    }
    arr->data_course[arr->course_num] = Course(*value);
    arr->course_num++;
}

void add_course_to_semester(Semester *&arr, Course value)
{
    Course *new_course = nullptr;
    init_course(new_course);
    new_course->course_id = value.course_id;
    new_course->course_name = value.course_name;
    new_course->class_name = value.class_name;
    new_course->teacher_name = value.teacher_name;
    new_course->max_students = 50;
    new_course->credits = value.credits;
    new_course->day_of_week = value.day_of_week;
    new_course->session = value.session;
    push_back_course(arr, new_course);
    cout << "Course: " << arr->data_course[arr->course_num - 1].course_name << " - "
         << arr->data_course[arr->course_num - 1].course_id
         << " added to Semester " << arr->semester_id << endl;
}

void view_couse_in_semester(SchoolYear *school_year)
{
    for (int i = 0; i < school_year->data_semester[school_year->current_semester].course_num; i++)
    {
        cout << school_year->data_semester[school_year->current_semester].data_course[i].course_id << " - "
             << school_year->data_semester[school_year->current_semester].data_course[i].course_name << endl;
    }
}