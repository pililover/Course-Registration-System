#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>

using namespace std;

struct Student
{
    string student_num;
    string studentID;
    string firstname;
    string lastname;
    string gender;
    string birthday;
    string socialID;
};

struct Classes
{
    string class_name;
    Student *data_student;
    int student_num;
    int student_capacity;
};

struct SchoolYear
{
    string year_name;
    Classes *data_classes;
    int class_num;
    int class_capacity;
};

void init_school_year(SchoolYear *&arr)
{
    arr = new SchoolYear;
    arr->data_classes = new Classes[1];
    arr->class_num = 0;
    arr->class_capacity = 1;
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

void push_back_class(SchoolYear *&arr, Classes *value)
{
    if (arr->class_num == arr->class_capacity)
    {
        int new_capacity = arr->class_capacity + 1;
        resize_school_year(arr, new_capacity);
    }
    arr->data_classes[arr->class_num] = Classes(*value);
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

void push_back_student(Classes *&arr, Student value)
{
    if (arr->student_num == arr->student_capacity)
    {
        int new_capacity = arr->student_capacity + 15;
        resize_class(arr, new_capacity);
    }
    arr->data_student[arr->student_num] = value;
    arr->student_num++;
}

void view_class_in_schoolyear(SchoolYear *school_year)
{
    for (int i = 0; i < school_year->class_num; i++)
        cout << school_year->data_classes[i].class_name << endl;
}


void import_student_csv(Classes* &data_classes) {
	ifstream in("student.csv");
	if(!in.is_open()) {
		cout<<"Can not open file!"<<endl;
		return;
	}
	while(!in.good()) {
		Student tmp;
		getline(in, tmp.student_num, ',');
		getline(in, tmp.studentID, ',');
		getline(in, tmp.firstname, ',');
		getline(in, tmp.lastname, ',');
		getline(in, tmp.gender, ',');
		getline(in, tmp.birthday, ',');
		getline(in, tmp.socialID, '\n');
	    push_back_student(data_classes, tmp);
	}
    in.close();
}

void input_student(Classes* &data_classes) {
	Student tmp;
	cout<<"Enter student information"<<endl;
	cout<<"No: ";
	cin>>tmp.student_num;
	cout<<"Student ID: ";
	cin>>tmp.studentID;
	cout<<"First name: ";
	cin>>tmp.firstname;
	cout<<"Last name: ";
	cin>>tmp.lastname;
	cout<<"Gender: ";
	cin>>tmp.gender;
	cout<<"Date of birth: ";
	cin>>tmp.birthday;
	cout<<"Social ID: ";
	cin>>tmp.socialID;
	push_back_student(data_classes, tmp);
}

void add_classes(SchoolYear* &school_year) {	
    Classes *tmp;
    init_class(tmp);
    cout<<"Class name: ";
	cin>>tmp->class_name;
	int x;
	cout<<"Enter student information"<<endl;
	cout<<"Import file (1)	  Input a student (2)"<<endl;
	cin>>x;
	while(x!=1 && x!=2) {
		cout<<"Please enter 1 or 2"<<endl;
		cin>>x;
	}
	while(x==1 || x==2) {
		cin.ignore();
		if(x==1) import_student_csv(tmp);
		if(x==2) input_student(tmp);
		cout<<"Do you want to add more students?"<<endl;
		cout<<"Import file (1)    Input a student (2)    No (0)"<<endl;
		cin>>x;
		while(x!=1 && x!=2 && x!=0) {
			cout<<"Please enter 1 or 2 or 0"<<endl;
			cin>>x;
		}
	}
    push_back_class(school_year, tmp);
    cout <<"Class "<< school_year->data_classes[school_year->class_num - 1].class_name << " added to SchoolYear " << school_year->year_name << "." <<endl<<endl;
}


int main()
{
    SchoolYear *school_year;
    init_school_year(school_year);
    cout << "School year: ";
    cin >> school_year->year_name;
    cout<<"Add 1st-year classes"<<endl;
    int x;
    do
    {
        add_classes(school_year);
        cout<<"Do you want to add more classes? Yes(1) / No(0)    ";
        cin>>x;
        while(x!=1 && x!=0)
        {
            cout<<"Pleae enter 1 or 0:  "; 
            cin>>x;
        } 
    } while (x!=0);
    
    view_class_in_schoolyear(school_year);


    for (int i = 0; i < school_year->class_capacity; i++)
    {
        delete[] school_year->data_classes[i].data_student;
    }
    delete[] school_year->data_classes;
    delete school_year;
    return 0;
}
