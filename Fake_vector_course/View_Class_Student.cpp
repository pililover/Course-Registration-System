#include "Schoolyear_header.h"

void view_class_in_schoolyear(SchoolYear *school_year) {
	cout <<"School year: " << school_year->year_name << endl;
	if (check_class_is_empty(school_year)) {
		cout << "No class available" << endl;
		return;
	}
	for (int i = 0; i < school_year->class_num; i++)	
		cout << school_year->data_classes[i].class_name << endl;
}

void view_student_in_class(SchoolYear *school_year) {

	string classname;
	int index = -1;
	cout<<"Class name: "; cin>>classname;
	do{
		for (int i=0; i < school_year->class_num; i++) {
			if(school_year->data_classes[i].class_name == classname){
				index = i; break;
			}
		}
		if(index == -1) {
			cout<<"Not found. Please choose a different name: ";
			cin>>classname;
		}
	}while(index==-1);

	if(school_year->data_classes[index].student_num == 0) {
		cout<<"No student in class"<<endl; return;
	}
	cout<<"No "<<"ID "<<"First name "<<"Last name "<<"Gender "<<"Birthday "<<"Social ID"<<endl;
	for(int i=0; i<school_year->data_classes[index].student_num; i++) {
		cout << school_year->data_classes[index].data_student[i].student_num<< " ";
		cout << school_year->data_classes[index].data_student[i].studentID << " ";
        cout << school_year->data_classes[index].data_student[i].firstname << " ";
        cout << school_year->data_classes[index].data_student[i].lastname << " ";
		cout << school_year->data_classes[index].data_student[i].gender << " ";
		cout << school_year->data_classes[index].data_student[i].birthday << " ";
		cout << school_year->data_classes[index].data_student[i].socialID << endl;
	}
}
