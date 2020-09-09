#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;


template <typename T> T StringToNumber (const string &str) {
    istringstream ss(str);
    T num;
    ss >> num;
    return num;
}

template <typename T> string NumberToString ( T num ) {
    ostringstream ss;
    ss << num;
    return ss.str();
}

vector<string> split (const string &s, char delim) {
    vector<string> result;
    istringstream ss (s);
    string item;

    while (getline (ss, item, delim)) {
        result.push_back(item);
    }

    return result;
}


/* Student class => Start */ 

class Student {

    public:
    string roll_Id;
    string name;
    string branch;
    string password;

    public:

    // Student constructor

    Student(string roll_Id, string name, string branch, string password) {   
        this -> roll_Id = roll_Id;
        this -> name = name;
        this -> branch = branch;
        this -> password = password;
    }

    static Student getStudentObjDetailsFromUser() {
        string roll_Id;
        string name;
        string branch;
        string password;

        cout << "Enter your roll no: ";
        getline(cin, roll_Id);

        cout << "Enter your name: ";
        getline(cin, name);

        cout << "Enter your branch: ";
        getline(cin, branch);

        cout << "Enter your password: ";
        getline(cin, password);

        Student obj(roll_Id, name, branch, password);
        return obj;
    }

    static string objToStr(Student obj) {
        string str = "";
        str += obj.roll_Id; 
        str += ',' + obj.name;
        str += ',' + obj.branch;
        str += ',' + obj.password;
        return  str;
    }

    static Student strToObj(string str) {
        vector<string> studentAttr = split(str, ',');

        string roll_Id = studentAttr[0];
        string name = studentAttr[1];
        string branch = studentAttr[2];
        string password = studentAttr[3];
        
        Student obj(roll_Id, name, branch, password);
        return obj;
    }

    friend ostream & operator << ( ostream &output, const Student &studentObj ) { 
        string str = "";
        
        str += studentObj.roll_Id; 
        str += ',' + studentObj.name;
        str += ',' + studentObj.branch;
        str += ',' + studentObj.password;

        output << str; 

        return output;             
    }

    friend istream & operator >> ( istream  &input, Student &studentObj ) { 
        string str;

        input >> str; 

        vector<string> studentAttr = split(str, ',');

        studentObj.roll_Id = studentAttr[0];
        studentObj.name = studentAttr[1];
        studentObj.branch = studentAttr[2];
        studentObj.password = studentAttr[3];
        
        return input;            
    }

};

/* Student class => End */ 

int main(){
    Student s1 = Student::getStudentObjDetailsFromUser();

    string str = Student::objToStr(s1);
    cout << str << endl;

    Student s1Copy = Student::strToObj(str);
    cout << Student::objToStr(s1Copy) << endl;

    /* Using Insertion and Extraction Operator */

    cout << s1 << endl;

    cin >> s1;
    cout << s1 << endl;

    return 0;
}
