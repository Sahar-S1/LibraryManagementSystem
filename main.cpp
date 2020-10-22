#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "packages/Date.h"  // https://github.com/Avikalp7/Date-Class

using namespace std;

const string ADMIN_PASSWORD = "1234";
const double FINE_PER_DAY = 100;

const string studentFileName = "Student.txt";
const string bookFileName = "Book.txt";
const string issueFileName = "Issue.txt";

const Date NULL_DATE(D01, Jan, 1950);
const Student NULL_STUDENT("", "", "", "");
const Book NULL_BOOK("", "", "", "", "", NULL);
const Issue NULL_ISSUE("", "", NULL_DATE);

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

    string getRollID() {
        return this->roll_Id;
    }

    string getName() {
        return this->name;
    }

    string getBranch() {
        return this->branch;
    }

    string getPassword() {
        return this->password;
    }

    void resetPassword(string newPassword) {
        this->password = newPassword;
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

    string getISBN() {
        return this->isbnNumber;
    }

    string getName() {
        return this->name;
    }

    string getAuthor() {
        return this->author;
    }

    string getPublisher() {
        return this->author;
    }

    string getGenere() {
        return this->genere;
    }

    int getQuantity() {
        return this->quantity;
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
    bool isReturned;
    double fineAmount;
    bool isFinePaid;

   public:
    // Issue Constructor
    Issue(string studentRollID, string bookISBN, Date issueDate) {
        this->studentRollID = studentRollID;
        this->bookISBN = bookISBN;
        this->issueDate = issueDate;

        this->returnDate = NULL_DATE;
        this->isReturned = false;
        this->fineAmount = 0;
        this->isFinePaid = true;
    }
    Issue(string studentRollID, string bookISBN, Date issueDate, Date returnDate, bool isReturned, double fineAmount, bool isFinePaid) {
        this->studentRollID = studentRollID;
        this->bookISBN = bookISBN;
        this->issueDate = issueDate;
        this->returnDate = returnDate;
        this->isReturned = isReturned;
        this->fineAmount = fineAmount;
        this->isFinePaid = isFinePaid;
    }

    string getStudentRollID() {
        return this->studentRollID;
    }

    string getBookISBN() {
        return this->bookISBN;
    }

    Date getIssueDate() {
        return this->issueDate;
    }

    Date getReturnDate() {
        return this->returnDate;
    }

    bool getIsReturned() {
        return this->isReturned;
    }

    double getFineAmount() {
        return this->fineAmount;
    }

    bool getIsFinePaid() {
        return this->isFinePaid;
    }

    void returnBook(Date returnDate) {
        int dateDiff = returnDate - issueDate;

        this->returnDate = returnDate;
        this->isReturned = true;
        this->fineAmount = (dateDiff > 7) ? (dateDiff - 7) * FINE_PER_DAY : 0;
        this->isFinePaid = (fineAmount > 0) ? false : true;
    }

    static Issue getIssueObjDetailsFromUser() {}

    static Issue getIssueObjFromInputStream(istream &inputStream) {}

    friend ostream &operator<<(ostream &output, const Issue &issueObj) {}
};

/* Issue Class => End */

/* FileManager Class => Start */

class FileManager {
   public:
    static void writeStudents(vector<Student> students) {}
    static void writeBooks(vector<Book> books) {}
    static void writeIssues(vector<Issue> issues) {}

    static vector<Student> getAllStudents() {}
    static vector<Book> getAllBooks() {}
    static vector<Issue> getAllIssues() {}
};

/* FileManager Class => End */

/* Query Class => Start */

class Query {
   public:
    static Student getStudentByRollID(vector<Student> students, string rollID) {
        for (int i = 0; i < students.size(); i++) {
            if (students[i].getRollID() == rollID) {
                return students[i];
            }
        }
        return NULL_STUDENT;
    }

    static Book getBookByISBN(vector<Book> books, string isbn) {}

    static vector<Book> getBooksByName(vector<Book> books, string name) {}
    static vector<Book> getBooksByAuthor(vector<Book> books, string author) {}
    static vector<Book> getBooksByPublisher(vector<Book> books, string publisher) {}
    static vector<Book> getBooksByGenere(vector<Book> books, string genere) {}

    static vector<Issue> getIssuesByPendingReturn(vector<Issue> issues) {}
    static vector<Issue> getIssuesByPendingFine(vector<Issue> issues) {}
    static vector<Issue> getIssuesByStudentRollID(vector<Issue> issues, string studentRollID) {}
    static vector<Issue> getIssuesByBookISBN(vector<Issue> issues, string bookISBN) {}
};

/* Query Class => End */

/* App Class => Start */

class App {
    vector<Student> students;
    vector<Book> books;
    vector<Issue> issues;

   public:
    App() {
        this->students = FileManager::getAllStudents();
        this->books = FileManager::getAllBooks();
        this->issues = FileManager::getAllIssues();
    }
};

/* App Class => End */

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
