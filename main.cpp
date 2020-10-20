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

        input.ignore();
        getline(input, str);

        vector<string> studentAttr = split(str, ',');

        studentObj.roll_Id = studentAttr[0];
        studentObj.name = studentAttr[1];
        studentObj.branch = studentAttr[2];
        studentObj.password = studentAttr[3];
        
        return input;            
    }

};

/* Student class => End */ 

/* Book Class => Start */

class Book {
    string isbnNumber;
    string name;
    string author;
    string publisher;
    string genere;
    int quantity;

    public:

    // Book Constructor
    Book(string isbnNumber, string name, string author, string publisher, string genere, int quantity) {
        this -> isbnNumber = isbnNumber;
        this -> name = name;
        this -> author = author;
        this -> publisher = publisher;
        this -> genere = genere;
        this -> quantity = quantity;
    }

    static Book getBookObjDetailsFromUser() {
        string isbnNumber;
        string name;
        string author;
        string publisher;
        string genere;
        int quantity;

        cout << "Enter Book's ISBN Number: ";
        getline(cin, isbnNumber);

        cout << "Enter Book's name: ";
        getline(cin, name);

        cout << "Enter Book's author: ";
        getline(cin, author);

        cout << "Enter Book's publisher: ";
        getline(cin, publisher);

        cout << "Enter Book's genere: ";
        getline(cin, genere);

        cout << "Enter Book's quantity: ";
        cin >> quantity;

        Book obj(isbnNumber, name, author, publisher, genere, quantity);
        return obj;
    }

    friend ostream & operator << ( ostream &output, const Book &bookObj ) { 
        string str = "";
        
        str += bookObj.isbnNumber; 
        str += ',' + bookObj.name;
        str += ',' + bookObj.author;
        str += ',' + bookObj.publisher;
        str += ',' + bookObj.genere;
        str += ',' + NumberToString<int>(bookObj.quantity);

        output << str; 

        return output;             
    }

    friend istream & operator >> ( istream  &input, Book &bookObj ) { 
        string str;

        input.ignore();
        getline(input, str);

        vector<string> bookAttr = split(str, ',');

        bookObj.isbnNumber = bookAttr[0];
        bookObj.name = bookAttr[1];
        bookObj.author = bookAttr[2];
        bookObj.publisher = bookAttr[3];    
        bookObj.genere = bookAttr[4];
        bookObj.publisher = StringToNumber<int>(bookAttr[5]);
        
        return input;            
    }

};

/* Book Class => End */


int main(){
    Book s1 = Book::getBookObjDetailsFromUser();

    /* Using Insertion and Extraction Operator */

    cout << s1 << endl;

    cin >> s1;
    cout << s1 << endl;

    return 0;
}
