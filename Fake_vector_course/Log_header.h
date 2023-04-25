#ifndef _LOG_HEADER_H_
#define _LOG_HEADER_H_

#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cstdio>
#include <sstream>
#include <windows.h>

using namespace std;

struct user
{
    string username;
    string password;
    int type_of_user;
    string fullname;
    string ID; // Only applied for student
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
int check_login(node *accHead, string &u_name, string &pass, int &usertype, string &ID);
void login(node *accHead, string &u_name, string &pass, int &usertype, int &access, string &ID);
void print_in_file(node *accHead);
void deleteall(node *&accHead);
void display_profile(node *accHead, string u_name, string pass); // đợi lúc có đầy đủ lớp, niên khoá thì add vào
void change_password(node *accHead, string u_name, string &pass);

void set_color(int code);

#endif
