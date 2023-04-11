#include "Schoolyear_header.h"

void View_scoreboard_of_a_course(SchoolYear *ssss, string courseid)
{
    Semester a = ssss->data_semester[ssss->current_semester];
    Course b;
    for (int i = 0; i < a.course_num; i++)
    {
        if (a.data_course[i].course_name == courseid)
        {
            b = a.data_course[i];
            break;
        }
    }
    // Student
    for (int i = 0; i < b.size_student; i++)
    {
        Student c = b.enrolled_student[i];
        cout << c.studentID << "   ";
        cout << c.firstname << " " << c.lastname << "   ";
        cout << c.score << endl;
    }
}