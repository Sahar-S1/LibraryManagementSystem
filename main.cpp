#include <iostream>
#include <string>

using namespace std;

/* Student class => Start */ 

class Student {

    private:
    int roll_Id;
    string studentName;
    string branch;
    string studentPassword;

    public:

    // Student constructor

    Student(int roll_id, string studentName, string branch, string studentPassword) {   
        this -> roll_Id = roll_Id;
        this -> studentName = studentName;
        this -> branch = branch;
        this -> studentPassword = studentPassword;
    }

    static Student getStudentObjFromUser() {
        int roll_Id;
        string studentName;
        string branch;
        string studentPassword;

        cout << "Enter your roll no: "<<endl;
        cin  >> roll_Id;

        cout << "Enter your name: "<<endl;
        cin  >> studentName;

        cout << "Enter your branch: "<<endl;
        cin  >> branch;

        cout << "Enter your password: "<<endl;
        cin  >> studentPassword; 

        return Student(roll_Id, studentName, branch, studentPassword);
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
