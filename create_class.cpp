#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstring>

using namespace std;

struct student{
    string student_num;
    string studentID;
    string firstname;
    string lastname;
    string gender;
    string birthday;
    string socialID;
    student *next;
};

struct Class{
    string classname;
    Class *next;
    student *studentHead;
};

struct ClassYear{
    Class *first;
    Class *second;
    Class *third;
    Class *fourth;
};


void import_student_csv(student* &studentHead, student* &cur){
    ifstream in("student.csv");
    if(!in.is_open()) {
        cout<<"Can not open file!";
        return;
    }

    while(!in.eof()){
        cur = new student;
        if(studentHead == NULL) studentHead=cur;

        getline(in, cur->student_num, ',');
        getline(in, cur->studentID, ',');
        getline(in, cur->firstname, ',');
        getline(in, cur->lastname, ',');
        getline(in, cur->gender, ',');
        getline(in, cur->birthday, ',');
        getline(in, cur->socialID, '\n');
        cur->next=NULL;
        cur = cur->next;
    } 
    in.close();
} 

void input_student(student* &cur){
    cur=new student; 
    cout<<"Enter student information"<<endl;
    cout<<"No: "; cin>>cur->student_num;
    cout<<"Student ID: "; cin>>cur->studentID;
    cout<<"First name: "; cin>>cur->firstname;
    cout<<"Last name: "; cin>>cur->lastname;
    cout<<"Gender: "; cin>>cur->gender;
    cout<<"Date of birth: "; cin>>cur->birthday;
    cout<<"Social ID: "; cin>>cur->socialID;
    cur->next=NULL;
    cur = cur->next;
}

void create_class(Class* &classHead){
    Class *tmp; 
    int n;
    cout<<"Enter the number of classes: "; cin>>n;
    for(int i=0; i<n; i++){
        tmp = new Class;
        if(classHead == NULL) classHead=tmp;
        cout<<"Enter the class name: ";
        cin>>tmp->classname;
        tmp->next=NULL;
        tmp->studentHead=NULL;
        tmp=tmp->next;
    }
}

void delete_student(student* &studentHead){
    while(studentHead!=NULL){
       student *tmp=studentHead;
       studentHead = studentHead->next;
       delete tmp;
    }
}

void delete_class(Class* &classHead){
    while(classHead!=NULL){
        Class *tmp = classHead;
        delete_student(classHead->studentHead);
        classHead=classHead->next;
        delete tmp;
    }
}
