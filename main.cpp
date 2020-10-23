#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "packages/Date.h"  // https://github.com/Avikalp7/Date-Class

using namespace std;

const string ADMIN_PASSWORD = "1234";
const double FINE_PER_DAY = 100;

const Date NULL_DATE(D01, Jan, 1950);

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

    friend bool operator==(const Student &student1, const Student &student2) {
        return student1.roll_Id == student2.roll_Id && student1.name == student2.name && student1.branch == student2.branch && student1.password == student2.password;
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

    friend bool operator==(const Book &book1, const Book &book2) {
        return book1.isbnNumber == book2.isbnNumber && book1.name == book2.name && book1.author == book2.author && book1.publisher == book2.publisher && book1.genere == book2.genere && book1.quantity == book2.quantity;
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

    friend bool operator==(const Issue &issue1, const Issue &issue2) {
        return issue1.bookISBN == issue2.bookISBN && issue1.studentRollID == issue2.studentRollID && (Date)issue1.issueDate == (Date)issue2.issueDate && (Date)issue1.returnDate == (Date)issue2.returnDate && issue1.isReturned == issue2.isReturned && issue1.isFinePaid == issue2.isFinePaid && issue1.fineAmount == issue2.fineAmount;
    }

    friend ostream &operator<<(ostream &output, const Issue &issueObj) {}
};

/* Issue Class => End */

/* NullChecker Class => Start */

class NullChecker {
  public:
    static const Student NULL_STUDENT;
    static const Book NULL_BOOK;
    static const Issue NULL_ISSUE;

    static bool isStudentNull(Student student) {
        return student == NULL_STUDENT;
    }
    static bool isBookNull(Book book) {
        return book == NULL_BOOK;
    }
    static bool isIssueNull(Issue issue) {
        return issue == NULL_ISSUE;
    }
};

const Student NullChecker::NULL_STUDENT = Student("", "", "", "");
const Book NullChecker::NULL_BOOK = Book("", "", "", "", "", 0);
const Issue NullChecker::NULL_ISSUE = Issue("", "", NULL_DATE);


/* NullChecker Class => End */

/* FileManager Class => Start */

class FileManager {
    static const string studentFileName;
    static const string bookFileName;
    static const string issueFileName;

   public:
    static void writeStudents(vector<Student> students) {
        ofstream fout(FileManager::studentFileName.c_str(), ios::out);

        fout << "RollID,Name,Branch,Password" << endl;

        for (int i = 0; i < students.size(); i++) {
            fout << students[i] << endl;
        }

        fout.close();
    }
    static void writeBooks(vector<Book> books) {
        ofstream fout(FileManager::bookFileName.c_str(), ios::out);

        fout << "ISBN,Name,Author,Publisher,Genere,Quantity" << endl;

        for (int i = 0; i < books.size(); i++) {
            fout << books[i] << endl;
        }

        fout.close();
    }
    static void writeIssues(vector<Issue> issues) {
        ofstream fout(FileManager::issueFileName.c_str(), ios::out);

        fout << "BookISBN,StudentRollID,IssueDate,ReturnDate,IsReturned,FineAmount,IsFinePaid" << endl;

        for (int i = 0; i < issues.size(); i++) {
            fout << issues[i] << endl;
        }

        fout.close();
    }

    static vector<Student> getAllStudents() {
        vector<Student> students;

        ifstream fin(FileManager::studentFileName.c_str(), ios::in);

        string _;
        getline(fin, _);

        while(!fin.eof()) {
            students.push_back(Student::getStudentObjFromInputStream(fin));
        }

        return students;
    }
    static vector<Book> getAllBooks() {
        vector<Book> books;

        ifstream fin(FileManager::bookFileName.c_str(), ios::in);

        string _;
        getline(fin, _);

        while(!fin.eof()) {
            books.push_back(Book::getBookObjFromInputStream(fin));
        }

        return books;
    }
    static vector<Issue> getAllIssues() {
        vector<Issue> issues;

        ifstream fin(FileManager::issueFileName.c_str(), ios::in);

        string _;
        getline(fin, _);

        while(!fin.eof()) {
            issues.push_back(Issue::getIssueObjFromInputStream(fin));
        }

        return issues;
    }
};

const string FileManager::studentFileName = "Students.csv";
const string FileManager::bookFileName = "Books.csv";
const string FileManager::issueFileName = "Issues.csv";

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
        return NullChecker::NULL_STUDENT;
    }

    static Book getBookByISBN(vector<Book> books, string isbn) {
        for (int i = 0; i < books.size(); i++) {
            if (books[i].getISBN() == isbn) {
                return books[i];
            }
        }
        return NullChecker::NULL_BOOK;
    }

    static vector<Book> getBooksByName(vector<Book> books, string name) {
        vector<Book> resultBooks;
        for (int i = 0; i < books.size(); i++) {
            if (books[i].getName() == name) {
                resultBooks.push_back(books[i]);
            }
        }
        return resultBooks;
    }
    static vector<Book> getBooksByAuthor(vector<Book> books, string author) {
        vector<Book> resultBooks;
        for (int i = 0; i < books.size(); i++) {
            if (books[i].getAuthor() == author) {
                resultBooks.push_back(books[i]);
            }
        }
        return resultBooks;
    }
    static vector<Book> getBooksByPublisher(vector<Book> books, string publisher) {
        vector<Book> resultBooks;
        for (int i = 0; i < books.size(); i++) {
            if (books[i].getPublisher() == publisher) {
                resultBooks.push_back(books[i]);
            }
        }
        return resultBooks;
    }
    static vector<Book> getBooksByGenere(vector<Book> books, string genere) {
        vector<Book> resultBooks;
        for (int i = 0; i < books.size(); i++) {
            if (books[i].getGenere() == genere) {
                resultBooks.push_back(books[i]);
            }
        }
        return resultBooks;
    }

    static vector<Issue> getIssuesByPendingReturn(vector<Issue> issues) {
        vector<Issue> resultIssues;
        for (int i = 0; i < issues.size(); i++) {
            if (issues[i].getIsReturned() == false) {
                resultIssues.push_back(issues[i]);
            }
        }
        return resultIssues;
    }
    static vector<Issue> getIssuesByPendingFine(vector<Issue> issues) {
        vector<Issue> resultIssues;
        for (int i = 0; i < issues.size(); i++) {
            if (issues[i].getIsFinePaid() == false) {
                resultIssues.push_back(issues[i]);
            }
        }
        return resultIssues;
    }
    static vector<Issue> getIssuesByStudentRollID(vector<Issue> issues, string studentRollID) {
        vector<Issue> resultIssues;
        for (int i = 0; i < issues.size(); i++) {
            if (issues[i].getStudentRollID() == studentRollID) {
                resultIssues.push_back(issues[i]);
            }
        }
        return resultIssues;
    }
    static vector<Issue> getIssuesByBookISBN(vector<Issue> issues, string bookISBN) {
        vector<Issue> resultIssues;
        for (int i = 0; i < issues.size(); i++) {
            if (issues[i].getBookISBN() == bookISBN) {
                resultIssues.push_back(issues[i]);
            }
        }
        return resultIssues;
    }
};

/* Query Class => End */

/* State Class => Start */

class State {
  protected:
    vector<Student> students;
    vector<Book> books;
    vector<Issue> issues;
};

/* State Class => End */

/* App Class => Start */

class App : protected State {

   public:
    App() {
        this->State::students = FileManager::getAllStudents();
        this->State::books = FileManager::getAllBooks();
        this->State::issues = FileManager::getAllIssues();
    }

    ~App() {
        FileManager::writeStudents(this->State::students);
        FileManager::writeBooks(this->State::books);
        FileManager::writeIssues(this->State::issues);
    }

    void start() {}
};

/* App Class => End */

int main() {
    // Define the format in which Date objects are input and output
    DateFormat form("dd-mm-yyyy");
    Date::setFormat(form);

    // App app;
    // app.start();

    return 0;
}
