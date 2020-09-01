#include <iostream>
#include <string>

using namespace std;

/* Student class => Start */ 

class Student {

    private:
    int roll_Id;
    string name;
    string branch;
    string password;

    public:

    // Student constructor

    Student(int roll_id, string name, string branch, string password) {   
        this -> roll_Id = roll_Id;
        this -> name = name;
        this -> branch = branch;
        this -> password = password;
    }

    static Student getStudentObjFromUser() {
        int roll_Id;
        string name;
        string branch;
        string password;

        cout << "Enter your roll no: "<<endl;
        cin  >> roll_Id;

        cout << "Enter your name: "<<endl;
        cin  >> name;

        cout << "Enter your branch: "<<endl;
        cin  >> branch;

        cout << "Enter your password: "<<endl;
        cin  >> password; 

        return Student(roll_Id, name, branch, password);
    }

    static string ObjToStr(Student obj) {
        return  "";
    }

};

/* Student class => End */ 

int main(){

    Student s1 = Student::getStudentObjFromUser();
    return 0;
}
