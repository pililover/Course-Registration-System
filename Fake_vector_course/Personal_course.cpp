#include "Schoolyear_header.h"

void personal_registered_course(SchoolYear *school_year, string ID)
{
    if (school_year)
    {
        cout << "\t\t\tList of registered courses: " << endl;
        for (int i = 0; i < school_year->data_semester[school_year->current_semester].course_num; i++)
        {
            for (int j = 0; j < school_year->data_semester[school_year->current_semester].data_course[i].size_student; j++)
            {
                if (school_year->data_semester[school_year->current_semester].data_course[i].enrolled_student[j].studentID == ID)
                {
                    cout << "\t\t\t\t" << school_year->data_semester[school_year->current_semester].data_course[i].course_id
                         << " - " << school_year->data_semester[school_year->current_semester].data_course[i].course_name << endl;
                }
            }
        }
    }
}