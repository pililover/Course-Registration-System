#include "Schoolyear_header.h"

void update_student_result(SchoolYear *school_year)
{
    string courseid, stuid;
    int check = 0;
    cout << "Enter Student ID: ";
    cin >> stuid;
    cout << "Enter CourseID: ";
    cin >> courseid;
    Course *course = nullptr;
    for (int i = 0; i < school_year->data_semester[school_year->current_semester].course_num; i++)
    {
        if (courseid == school_year->data_semester[school_year->current_semester].data_course[i].course_id)
        {
            course = &(school_year->data_semester[school_year->current_semester].data_course[i]);
            check = 1;
            break;
        }
    }
    if (check == 0)
    {
        cout << "CourseID does not exist" << endl;
        return;
    }
    float new_scores = 0;
    cout << "Enter new scores: ";
    cin >> new_scores;
    for (int i = 0; i < course->size_student; i++)
    {
        if (stuid == course->enrolled_student[i].studentID)
        {
            course->enrolled_student[i].score = new_scores;
            cout << "Update successfully" << endl;
            return;
        }
    }
}