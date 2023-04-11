#include "Schoolyear_header.h"

void update_student_result(SchoolYear *ssss, string courseid, string stuid)
{
    Semester a = ssss->data_semester[ssss->current_semester];
    Course b;
    for (int i = 0; i < a.course_num; i++)
    {
        if (a.data_course[i].course_id == courseid)
        {
            b = a.data_course[i];
            break;
        }
    }
    float new_scores = 0;
    cout << "Enter new scores: ";
    cin >> new_scores;
    for (int i = 0; i < b.capacity_student; i++)
    {
        Student c = b.enrolled_student[i];
        if (c.studentID == stuid)
        {
            c.score = new_scores;
        }
    }
}