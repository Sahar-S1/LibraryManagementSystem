#include<iostream>

using namespace std;

// Student class  

class Student {

    private:
    int roll_Id;
    string studentName;
    string branch;
    int studentPassword;

    public:

// Student constructor

    Student(){

            cout << "Enter your roll no: "<<endl;
            cin  >> roll_Id;

            cout << "Enter your name: "<<endl;
            cin  >> studentName;

            cout << "Enter your branch: "<<endl;
            cin  >> branch;

            cout << "Enter your password: "<<endl;
            cin  >> studentPassword;       

    }  

};

int main(){

    Student s1;
    return 0;
}