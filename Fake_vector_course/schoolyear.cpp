#include "Schoolyear_header.h"

void init_system(System &arr)
{
    arr.data_schoolyear = new SchoolYear[1];
    arr.year_capacity = 1;
    arr.year_num = 0;
}

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

void push_back_schoolyear(System &arr, SchoolYear *value)
{
    if (arr.year_num == arr.year_capacity)
    {
        int new_capacity = arr.year_capacity + 1;
        SchoolYear *new_data = new SchoolYear[new_capacity];
        for (int i = 0; i < arr.year_num; i++)
        {
            new_data[i] = arr.data_schoolyear[i];
        }
        delete[] arr.data_schoolyear;
        arr.data_schoolyear = new_data;
        arr.year_capacity = new_capacity;
    }
    arr.data_schoolyear[arr.year_num] = SchoolYear(*value);
    arr.year_num++;
}

void create_school_year(System &system, string year_name)
{
    // SchoolYear *schoolyear = new SchoolYear;
    SchoolYear *new_school_year = nullptr;
    init_school_year(new_school_year); // mowis theem
    new_school_year->year_name = year_name;
    push_back_schoolyear(system, new_school_year);
    cout << "Current school year " << system.data_schoolyear[system.year_num - 1].year_name << endl;
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

/*bool check_valid_classname(SchoolYear *school_year, string classname)
{
    for (int i = 0; i < school_year->class_num; i++)
    {
        if (school_year->data_classes[i].class_name == classname)
        {
            return true;
        }
    }
    return false;
}*/

bool check_classname_in_a_year(SchoolYear year, string classname, int &index)
{
    for (int i = 0; i < year.class_num; i++)
    {
        if (year.data_classes[i].class_name == classname)
        {
            index = i;
            return true;
        }
    }
    return false;
}

void add_class_to_schoolyear(System system, SchoolYear *school_year, string classname)
{
    int check;
    do
    {
        check = -1;
        for (int i = 0; i < system.year_num; i++)
            if (check_classname_in_a_year(system.data_schoolyear[i], classname, check))
            {
                cout << "Already have this class. Please use a new class name: ";
                cin >> classname;
                break;
            }
    } while (check != -1);

    Classes *new_class = nullptr;
    init_class(new_class);
    new_class->class_name = classname;
    push_back_class(school_year, new_class);
    cout << "Class " << school_year->data_classes[school_year->class_num - 1].class_name << " added to SchoolYear " << school_year->year_name << "." << endl;
}

void view_school_year_and_class_in_each_year(System system)
{
    for (int i = 0; i < system.year_num; i++)
    {
        cout << system.data_schoolyear[i].year_name << endl;
        for (int j = 0; j < system.data_schoolyear[i].class_num; j++)
        {
            cout << system.data_schoolyear[i].data_classes[j].class_name << endl;
            for (int k = 0; k < system.data_schoolyear[i].data_classes[j].student_num; k++)
            {
                cout << system.data_schoolyear[i].data_classes[j].data_student[k].studentID << '\t'
                     << system.data_schoolyear[i].data_classes[j].data_student[k].firstname << " "
                     << system.data_schoolyear[i].data_classes[j].data_student[k].lastname << endl;
            }
        }
    }
}
/*void view_class_in_schoolyear(SchoolYear *school_year) // thêm vào để check thôi chứ không có trong yêu cầu
{
    for (int i = 0; i < school_year->class_num; i++)
        cout << school_year->data_classes[i].class_name << endl;
}
*/
/*void view_class_in_schoolyear(SchoolYear *school_year) // thêm vào để check thôi chứ không có trong yêu cầu
{
    for (int i = 0; i < school_year->class_num; i++)
        cout << school_year->data_classes[i].class_name << endl;
}
*/