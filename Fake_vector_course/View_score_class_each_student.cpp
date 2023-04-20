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
        if (n == 0){
            classes->data_student[i].gpa_4_year = 0;
            return;
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
        if (n == 0){
            classes->data_student[i].score = 0;
            return;
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
            in << 'X' << ',' << 'X' << ',' << 'X' << ',' << 'X' << ',';
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

//The old version, new version is find_score
/*
void show_score_student(SchoolYear *year, int cur, Classes *classes, string show)
{
    string temp = show + "_scores.csv";

    ofstream in(temp);
    in << "Semester" << cur + 1 << endl;
    cout << "Semester " << cur + 1 << endl;
    // The first line in csv is the courses names
    in << "Num,"
       << "Student ID,"
       << "Student name,";
    cout << setw(5) << left << "Num" << setw(15) << left << "Student ID" << setw(20) << left << "Student name";
    for (int i = 0; i < year->data_semester[cur].course_num; i++)
    {
        in << year->data_semester[cur].data_course[i].course_name << ',';
        cout << setw(40) << left << year->data_semester[cur].data_course[i].course_name;
    }
    in << ",,,";
    cout << setw(40) << "Score type";
    for (int i = 0; i < year->data_semester[cur].course_num; i++)
    {
        in << "Other,"
           << "Mid term,"
           << "Final,"
           << "Total,";
        cout << setw(10) << left << "Other" << setw(10) << left << "Mid term" << setw(10) << left << "Final" << setw(10) << left << "Total";
    }
    in << "GPA," << endl;
    cout << setw(10) << left << "GPA" << endl;
    in << "Overall GPA," << endl;
    cout << setw(10) << left << "Overall GPA" << endl;
    in.close();
    for (int i = 0; i < classes->student_num; i++)
    {
        if (classes->data_student[i].studentID == show)
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
}*/

// cur is the current semester
// use loop to change the semester through cur
void show_scores_class(SchoolYear *year, Classes *classes, int cur)
{
    string temp = classes->class_name + "_scores.csv";

    ofstream in(temp);
    cout << setw(50) << right << "Score board of class " << classes->class_name << endl;
    // The first line in csv is the courses names
    in << "Num,"
       << "Student ID,"
       << "Student name,";
    cout << setw(5) << left << "Num" << setw(15) << left << "Student ID" << setw(20) << left << "Student name";
    for (int i = 0; i < year->data_semester[cur].course_num; i++)
    {
        in << year->data_semester[cur].data_course[i].course_name << ',';
        cout << setw(40) << left << year->data_semester[cur].data_course[i].course_name;
    }
    in << endl;
    cout << endl;
    in << "Score type,X,X,";
    cout << setw(40) << left << "Score type";
    for (int i = 0; i < year->data_semester[cur].course_num; i++)
    {
        in << "Other,"
           << "Mid term,"
           << "Final,"
           << "Total,";
        cout << setw(10) << left << "Other" << setw(10) << left << "Mid term" << setw(10) << left << "Final" << setw(10) << left << "Total";
    }
    in << "GPA," << endl;
    cout << setw(10) << left << "GPA";
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
        string name = classes->data_student[i].firstname + ' ' + classes->data_student[i].lastname;
        cout << setw(20) << left << name;
        in1.close();
        show_score_semester_student(classes, year->data_semester[cur], classes->data_student[i].studentID);
    }
}

//Not tested yet
void find_score_student(string classname, string ID){
    string class_old = classname + "_scores.csv";
    ifstream in(class_old);
    if (!in.is_open()){
        cout<<"Error! This class does not exist"<<endl;
        return;
    }

    int exist = 0, pos = 0;
    string temp;
    getline(in, temp);
    getline(in, temp);
    while (!in.eof()){
        getline(in, temp, ',');
        getline(in, temp, ',');
        if (temp == ID){
            exist = 1;
            break;
        }
        getline(in, temp);
        pos++;
    }
    in.close();
    
    if (exist == 0){
        cout << "This ID does not exist in this class"<<endl;
    }
    else{
        ifstream in1(class_old);
        cout << setw(5) << left << "Num" << setw(15) << left << "Student ID" << setw(20) << left << "Student name";
        getline(in1, temp, ',');
        getline(in1, temp, ',');
        getline(in1, temp, ',');
        int n = 0;
        while (in1.peek() != '\n' || in1.peek() != '\r'){
            getline(in1, temp, ',');
            cout << setw(40) << left << temp;
            n++;
        }
        getline(in1, temp);
        cout << setw(40) << left <<"Score type";
        for (int i = 0; i < n; i++)
        {
            cout << setw(10) << left << "Other" << setw(10) << left << "Mid term" << setw(10) << left << "Final" << setw(10) << left << "Total";
        }
        cout << setw(10) << left << "GPA";
        cout << setw(10) << left << "Overall GPA" << endl;
        for (int i = 1; i < pos; i++)
        {
            getline(in1, temp);
        }
        getline(in1, temp, ',');
        cout << setw(5) << left << temp;
        getline(in1, temp, ',');
        cout << setw(15) << left << temp;
        getline(in1, temp, ',');
        cout << setw(20) << left << temp;
        for (int i = 0; i < n; i++)
        {
            getline(in1, temp, ',');
            cout << setw(10) << left << temp;
        }
        getline(in1, temp, ',');
        cout << setw(10) << left << temp;
        getline(in1, temp);
        cout << setw(10) << left << temp;
    }
}

//This is for class if staff want the old year
void find_score_class(string classname){
    string class_old = classname + "_scores.csv";
    ifstream in(class_old);
    if (!in.is_open()){
        cout<<"Error! This class does not exist"<<endl;
        return;
    }
    string temp;
    cout << setw(50) << right << "Score board of class " << classname << endl;
    cout << setw(5) << left << "Num" << setw(15) << left << "Student ID" << setw(20) << left << "Student name";
    getline(in, temp, ',');
    getline(in, temp, ',');
    getline(in, temp, ',');
    int n = 0;
    while (in.peek() != '\n' || in.peek() != '\r'){
        getline(in, temp, ',');
        cout << setw(40) << left << temp;
        n++;
    }
    getline(in, temp);
    cout << endl;
    cout << setw(40) << left <<"Score type";
    for (int i = 0; i < n; i++)
    {
        cout << setw(10) << left << "Other" << setw(10) << left << "Mid term" << setw(10) << left << "Final" << setw(10) << left << "Total";
    }
    cout << setw(10) << left << "GPA";
    cout << setw(10) << left << "Overall GPA" << endl;
    while (!in.eof()){
        getline(in, temp, ',');
        cout << setw(5) << left << temp;
        getline(in, temp, ',');
        cout << setw(15) << left << temp;
        getline(in, temp, ',');
        cout << setw(20) << left << temp;
        for (int i = 0; i < n; i++)
        {
            getline(in, temp, ',');
            cout << setw(10) << left << temp;
        }
        getline(in, temp, ',');
        cout << setw(10) << left << temp;
        getline(in, temp);
        cout << setw(10) << left << temp;
    }
    in.close();
}

//To csv file only
void class_to_csv_2(Classes *classes, Semester semester, string show)
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
                in << semester.data_course[i].enrolled_student[j].midterm << ',';
                in << semester.data_course[i].enrolled_student[j].final << ',';
                in << semester.data_course[i].enrolled_student[j].score << ',';
            }
        }

        if (flag == 1)
        {
            in << 'X' << ',' << 'X' << ',' << 'X' << ',' << 'X' << ',';
        }
    }
    for (int i = 0; i < classes->student_num; i++)
    {
        if (classes->data_student[i].studentID == show)
        {
            in << classes->data_student[i].score << "," << classes->data_student[i].gpa_4_year << endl;
        }
    }

    in.close();
}

void class_to_csv_1(SchoolYear *year, Classes *classes, int cur){
    string temp = classes->class_name + "_scores.csv";

    ofstream in(temp);
    // The first line in csv is the courses names
    in << "Num,"
       << "Student ID,"
       << "Student name,";
    for (int i = 0; i < year->data_semester[cur].course_num; i++)
    {
        in << year->data_semester[cur].data_course[i].course_name << ',';
    }
    in << endl;
    in << "Score type,X,X,";
    for (int i = 0; i < year->data_semester[cur].course_num; i++)
    {
        in << "Other,"
           << "Mid term,"
           << "Final,"
           << "Total,";
    }
    in << "GPA," << endl;
    in << "Overall GPA," << endl;
    in.close();

    for (int i = 0; i < classes->student_num; i++)
    {
        ofstream in1(temp, ios::app);
        in1 << classes->data_student[i].student_num << ',';
        in1 << classes->data_student[i].studentID << ',';
        in1 << classes->data_student[i].firstname << ' ' << classes->data_student[i].lastname << ',';
        in1.close();
        class_to_csv_2(classes, year->data_semester[cur], classes->data_student[i].studentID);
    }
}