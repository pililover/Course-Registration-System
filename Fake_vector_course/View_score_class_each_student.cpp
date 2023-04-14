#include "Schoolyear_header.h"

void cal_GPA_all_student_in_class(System &system, Classes *classes)
{
    for (int i = 0; i < classes->student_num; i++)
    {
        double gpa = 0;
        double n = 0;
        for (int j = 0; j < system.year_num; j++)
        {
            for (int z = 0; z < system.data_schoolyear[j].class_num; z++)
            {
                if (system.data_schoolyear[j].data_classes[z].class_name == classes->class_name)
                {
                    if (system.data_schoolyear[j].data_classes[z].data_student[i].score != -1)
                    {
                        gpa = system.data_schoolyear[j].data_classes[z].data_student[i].score;
                        n++;
                    }
                }
            }
        }
        classes->data_student[i].gpa_4_year = gpa / n;
    }
}

// Current year
void cal_GPA_current(SchoolYear *year, Classes *classes, int cur)
{
    for (int i = 0; i < classes->student_num; i++)
    {
        double gpa = 0;
        double n = 0;
        for (int j = 0; j < year->data_semester[cur].course_num; j++)
        {
            for (int z = 0; z < year->data_semester[cur].data_course[j].size_student; z++)
            {
                if (year->data_semester[cur].data_course[j].enrolled_student[z].studentID == classes->data_student[i].studentID)
                {
                    if (year->data_semester[cur].data_course[j].enrolled_student[z].score != -1)
                    {
                        gpa += year->data_semester[cur].data_course[j].enrolled_student[z].score;
                        n++;
                    }
                }
            }
        }
        classes->data_student[i].score = gpa / n;
    }
}

// The show variable is student ID value
// This function output the score of a semester to csv file
void show_score_semester_student(Classes *classes, Semester semester, string show)
{
    string temp = show + "_scores.csv";
    ofstream in(temp, ios::app);

    // The second line is the score
    for (int i = 0; i < semester.course_num; i++)
    {
        int flag = 1;
        for (int j = 0; j < semester.data_course[i].size_student; j++)
        {
            if (semester.data_course[i].enrolled_student[j].studentID == show)
            {
                flag = 0;
                in << semester.data_course[i].enrolled_student[j].other << ',';
                cout << setw(10) << left << semester.data_course[i].enrolled_student[j].other;
                in << semester.data_course[i].enrolled_student[j].midterm << ',';
                cout << setw(10) << left << semester.data_course[i].enrolled_student[j].midterm;
                in << semester.data_course[i].enrolled_student[j].final << ',';
                cout << setw(10) << left << semester.data_course[i].enrolled_student[j].final;
                in << semester.data_course[i].enrolled_student[j].score << ',';
                cout << setw(10) << left << semester.data_course[i].enrolled_student[j].score;
            }
        }

        if (flag == 1)
        {
            in << 'X' << ',' << 'X' << ',' << 'X' << 'X' << ',' << ',';
            cout << setw(10) << left << 'X' << setw(10) << left << 'X' << setw(10) << left << 'X' << setw(10) << left << 'X';
        }
    }
    for (int i = 0; i < classes->student_num; i++)
    {
        if (classes->data_student[i].studentID == show)
        {
            in << classes->data_student[i].score << "," << classes->data_student[i].gpa_4_year << endl;
            cout << setw(10) << left << classes->data_student[i].score << setw(10) << left << classes->data_student[i].gpa_4_year << endl;
            
        }
    }

    in.close();
}

// This function output the score and gpa of a student to csv file and terminal
// cur is the current semester
// classes is the class the student is in
// use loop to change the semester through cur
void show_score_student(SchoolYear *year, int cur, Classes *classes, string show)
{
    string temp = show + "_scores.csv";

    ofstream in(temp);
    in << "Semester" << cur + 1 << endl;
    cout << "Semester " << cur + 1 << endl;
    // The first line in csv is the courses names
    in << "Num," << "Student ID," << "Student name,";
    cout << setw(5) << left << "Num" <<setw(15) << left <<"Student ID" << setw(20) << left << "Student name";
    for (int i = 0; i < year->data_semester[cur].course_num; i++)
    {
        in << year->data_semester[cur].data_course[i].course_name << ',';
        cout << setw(40) << left << year->data_semester[cur].data_course[i].course_name;
    }
    in << ",,,";
    cout << setw(40) << "Score type";
    for (int i = 0; i < year->data_semester[cur].course_num; i++)
    {
        in << "Other," << "Mid term," << "Final," << "Total,";
        cout << setw(10) << left << "Other" << setw(10) << left << "Mid term" << setw(10) << left << "Final" << setw(10) << left << "Total";
    }
    in << "GPA," << endl;
    cout << setw(10) << left << "GPA" << endl;
    in << "Overall GPA," << endl;
    cout << setw(10) << left << "Overall GPA" << endl;
    in.close();
    for (int i = 0; i < classes->student_num; i++)
    {
        if (classes->data_student[i].studentID == show){
            ofstream in1(temp, ios::app);
            in1 << classes->data_student[i].student_num << ',';
            cout << setw(5) << left << classes->data_student[i].student_num;
            in1 << classes->data_student[i].studentID << ',';
            cout << setw(15) << left << classes->data_student[i].studentID;
            in1 << classes->data_student[i].firstname << ' ' << classes->data_student[i].lastname << ',';
            string name = classes->data_student[i].firstname + " " + classes->data_student[i].lastname;
            cout << setw(20) << left << name;
            in1.close();
            show_score_semester_student(classes, year->data_semester[cur], classes->data_student[i].studentID);
        }
    }
}

// cur is the current semester
// use loop to change the semester through cur
void show_scores_class(SchoolYear *year, Classes *classes, int cur)
{
    string temp = classes->class_name + "_scores.csv";

    ofstream in(temp);
    in << "Class" << classes->class_name << endl;
    cout << "Class " << classes->class_name << endl;
    // The first line in csv is the courses names
    in << "Num," << "Student ID," << "Student name,";
    cout << setw(5) << left << "Num" <<setw(15) << left <<"Student ID" << setw(20) << left << "Student name";
    for (int i = 0; i < year->data_semester[cur].course_num; i++)
    {
        in << year->data_semester[cur].data_course[i].course_name << ',';
        cout << setw(40) << left << year->data_semester[cur].data_course[i].course_name;
    }
    in<<endl;
    cout<<endl;
    in << "Score type,X,X,";
    cout << setw(40) << "Score type";
    for (int i = 0; i < year->data_semester[cur].course_num; i++)
    {
        in << "Other," << "Mid term," << "Final," << "Total,";
        cout << setw(10) << left << "Other" << setw(10) << left << "Mid term" << setw(10) << left << "Final" << setw(10) << left << "Total";
    }
    in << "GPA," << endl;
    cout << setw(10) << left << "GPA" << endl;
    in << "Overall GPA," << endl;
    cout << setw(10) << left << "Overall GPA" << endl;
    in.close();

    for (int i = 0; i < classes->student_num; i++)
    {
        ofstream in1(temp, ios::app);
        in1 << classes->data_student[i].student_num << ',';
        cout << setw(5) << left << classes->data_student[i].student_num;
        in1 << classes->data_student[i].studentID << ',';
        cout << setw(15) << left << classes->data_student[i].studentID;
        in1 << classes->data_student[i].firstname << ' ' << classes->data_student[i].lastname << ',';
        string name = classes->data_student[i].firstname + " " + classes->data_student[i].lastname;
        cout << setw(20) << left << name;
        in1.close();
        show_score_semester_student(classes, year->data_semester[cur], classes->data_student[i].studentID);
    }
}