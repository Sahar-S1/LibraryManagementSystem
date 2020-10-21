#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "packages/Date.h"  // https://github.com/Avikalp7/Date-Class

using namespace std;

const string ADMIN_PASSWORD = "1234";
const Date NULL_DATE("01-01-1800");
const double FINE_PER_DAY = 100;

template <typename T>
T StringToNumber(const string &str) {
    istringstream ss(str);
    T num;
    ss >> num;
    return num;
}

template <typename T>
string NumberToString(T num) {
    ostringstream ss;
    ss << num;
    return ss.str();
}

vector<string> split(const string &s, char delim) {
    vector<string> result;
    istringstream ss(s);
    string item;

    while (getline(ss, item, delim)) {
        result.push_back(item);
    }

    return result;
}

Date getDateFromUser() {
    string dateInput;
    cin >> dateInput;
    Date date(dateInput.c_str());
    return date;
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
        this->roll_Id = roll_Id;
        this->name = name;
        this->branch = branch;
        this->password = password;
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

    static Student getStudentObjFromInputStream(istream &inputStream) {
        string str;

        inputStream.ignore();
        getline(inputStream, str);

        vector<string> studentAttr = split(str, ',');

        Student studentObj(studentAttr[0], studentAttr[1], studentAttr[2], studentAttr[3]);
        return studentObj;
    }

    void resetPassword(string password) {
        this->password = password;
    }

    friend ostream &operator<<(ostream &output, const Student &studentObj) {
        string str = "";

        str += studentObj.roll_Id;
        str += ',' + studentObj.name;
        str += ',' + studentObj.branch;
        str += ',' + studentObj.password;

        output << str;

        return output;
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
        this->isbnNumber = isbnNumber;
        this->name = name;
        this->author = author;
        this->publisher = publisher;
        this->genere = genere;
        this->quantity = quantity;
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

    static Book getBookObjFromInputStream(istream &inputStream) {
        string str;

        inputStream.ignore();
        getline(inputStream, str);

        vector<string> bookAttr = split(str, ',');

        Book bookObj(bookAttr[0], bookAttr[1], bookAttr[2], bookAttr[3], bookAttr[4], StringToNumber<int>(bookAttr[5]));
        return bookObj;
    }

    friend ostream &operator<<(ostream &output, const Book &bookObj) {
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
};

/* Book Class => End */

/* Issue Class => Start */

class Issue {
    string studentRollID;
    string bookISBN;
    Date issueDate;
    Date returnDate;
    double fineAmount;
    bool isFinePaid;

   public:
    // Issue Constructor
    Issue(string studentRollID, string bookISBN, Date issueDate) {
        this->studentRollID = studentRollID;
        this->bookISBN = bookISBN;
        this->issueDate = issueDate;
        this->returnDate = NULL_DATE;
    }

    void setReturnDate(Date returnDate) {
        int dateDiff = (returnDate - issueDate);

        this->returnDate = returnDate;
        this->fineAmount = (dateDiff > 7) ? (dateDiff - 7) * FINE_PER_DAY : 0;
        this->isFinePaid = (fineAmount > 0) ? false : true;
    }

    static Issue getIssueObjDetailsFromUser() {}

    static Issue getIssueObjFromInputStream(istream &inputStream) {}

    friend ostream &operator<<(ostream &output, const Issue &issueObj) {}
};

/* Issue Class => End */

int main() {
    // Define the format in which Date objects are input and output
    DateFormat form("dd-mm-yyyy");
    Date::setFormat(form);

    // Testing

    Book s1 = Book::getBookObjDetailsFromUser();

    cout << s1 << endl;

    Book s2 = Book::getBookObjFromInputStream(cin);
    cout << s1 << endl;

    // Testing End

    return 0;
}
