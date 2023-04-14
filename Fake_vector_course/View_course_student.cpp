#include "Schoolyear_header.h"

void view_list_of_course(SchoolYear *school_year)
{
    cout << "\t\t\t\tLIST OF COURSE IN THIS SEMESTER" << endl;
    if (school_year->data_semester[school_year->current_semester].course_num == 0)
    {
        cout << "Course not found" << endl;
        return;
    }
    for (int i = 0; i < school_year->data_semester[school_year->current_semester].course_num; i++)
    {
        cout << "\t" << setw(4) << i + 1 << setw(5) << ". " << '\t'
             << setw(25) << school_year->data_semester[school_year->current_semester].data_course[i].course_id
             << setw(35) << school_year->data_semester[school_year->current_semester].data_course[i].course_name << endl;
    }
}

void view_student_in_course(SchoolYear *school_year, int cur_course)
{
    cout << "\t\t\t\t\t" << school_year->data_semester[school_year->current_semester].data_course[cur_course].course_id << " - "
         << school_year->data_semester[school_year->current_semester].data_course[cur_course].course_name << endl;
    if (school_year->data_semester[school_year->current_semester].data_course[cur_course].size_student != 0)
    {
        for (int j = 0; j < school_year->data_semester[school_year->current_semester].data_course[cur_course].size_student; j++)
        {
            cout << '\t' << '\t' << setw(4) << j + 1 << setw(4) << ". " << setw(20)
                 << school_year->data_semester[school_year->current_semester].data_course[cur_course].enrolled_student[j].studentID << setw(20)
                 << school_year->data_semester[school_year->current_semester].data_course[cur_course].enrolled_student[j].firstname << setw(20)
                 << school_year->data_semester[school_year->current_semester].data_course[cur_course].enrolled_student[j].lastname << endl;
        }
    }
    else
    {
        cout << "Student not found" << endl;
    }
}

void export_student_from_course_to_file(SchoolYear *school_year, string courseid) // id của course muốn xuất danh sách học sinh nhập ở main
{
    string filename;
    filename = courseid + ".csv";
    ofstream op(filename, ios::out);
    if (!op)
    {
        cout << "Cannot open the file" << endl;
        return;
    }
    for (int i = 0; i < school_year->data_semester[school_year->current_semester].course_num; i++)
    {
        if (school_year->data_semester[school_year->current_semester].data_course[i].course_id == courseid)
        {
            for (int j = 0; j < school_year->data_semester[school_year->current_semester].data_course[i].size_student; j++)
            {
                op << school_year->data_semester[school_year->current_semester].data_course[i].enrolled_student[j].student_num << ","
                   << school_year->data_semester[school_year->current_semester].data_course[i].enrolled_student[j].studentID << ","
                   << school_year->data_semester[school_year->current_semester].data_course[i].enrolled_student[j].firstname << ","
                   << school_year->data_semester[school_year->current_semester].data_course[i].enrolled_student[j].lastname << endl;
            }
        }
    }
    op.close();
}
