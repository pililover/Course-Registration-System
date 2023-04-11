#include "Schoolyear_header.h"

void import_scoreboard_of_a_course(SchoolYear *ssss)
{
    string stmp;
    cout << "Enter name course want to import: ";
    cin >> stmp;
    Semester a = ssss->data_semester[ssss->current_semester]; // semester hien tai
    Course b;                                                 // course can import
    for (int i = 0; i < a.course_num; i++)
    {
        if (a.data_course[i].course_name == stmp)
        {
            b = a.data_course[i];
        }
    }

    cout << "Enter file want to import score: ";
    cin >> stmp;
    ifstream fin;
    fin.open(stmp);
    while (!fin.is_open())
    {
        cout << "File want to import not invaluable, enter again: ";
        cin >> stmp;
        fin.open(stmp);
    }

    int stt = 0;
    float score_st = 0;

    while (!fin.eof())
    {
        getline(fin, stmp, ',');
        getline(fin, stmp, ',');
        getline(fin, stmp, ',');
        getline(fin, stmp, '\n');
        Student c = b.enrolled_student[stt];
        c.score = score_st;
        stt++;
    }
    fin.close();
}