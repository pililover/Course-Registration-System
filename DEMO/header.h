#ifndef _HEADER_H_
#define _HEADER_H_

#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cstdio>
#include <sstream>

using namespace std;

struct user
{
    string username;
    string password;
    int type_of_user;
    string fullname;
};

struct node
{
    user *data;
    node *next;
};

node *createnode(user *newacc);
node *addnode(node *p, user *newacc);
void getnode(node *&accHead, user *newacc);
int check_input_usertype();
user *register_acc();
void read_file_acc(node *&accHead);
int check_available_acc(node *accHead, user *newacc);
int check_login(node *accHead, string &u_name, string &pass, int &usertype);
void login(node *accHead, string &u_name, string &pass, int &usertype, int &access);
void print_in_file(node *accHead);
void deleteall(node *&accHead);
void display_profile(node *accHead, string u_name, string pass); // đợi lúc có đầy đủ lớp, niên khoá thì add vào
void change_password(node *accHead, string u_name, string &pass);

struct student
{
    string student_num;
    string studentID;
    string firstname;
    string lastname;
    string gender;
    string birthday;
    string socialID;
    double score;
    student *next;
};

struct Class
{
    string classname;
    Class *next;
    student *studentHead;
};

struct ClassYear
{
    Class *first;
    Class *second;
    Class *third;
    Class *fourth;
};

void import_student_csv(student *&studentHead, student *&curStudent);
void input_student(student *&curStudent);
void delete_student(student *&studentHead);
void delete_class(Class *&classHead);

#endif