#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <conio.h>

#include "packages/Date.h"  // https://github.com/Avikalp7/Date-Class

using namespace std;

const string ADMIN_PASSWORD = "pass";
const double FINE_PER_DAY = 100;

DateFormat DATE_FORMAT("dd-mm-yyyy");
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

bool string2bool(const string &v) {
    return !v.empty() && (atoi(v.c_str()) != 0);
}

string date2string(const Date &date) {
    ostringstream ss;
    ss << date;
    return ss.str();
}

string getPasswordFromUser() {
    const char BACKSPACE = 8;//ASCII code for BACKSPACE Key
    const char ENTER = 13;//ASCII code for ENTER Key
    string pass = "";//initialize string
    char c = ' ';//initialize character 

    while ((c = _getch()) != ENTER)
    {
        if (c == BACKSPACE)
        {
            if (pass.length() != 0)
            {
                cout << "\b \b";
                pass.resize(pass.length() - 1); //resize the length of pass 
            }
        }
        // else if (c == 0 || c == 224)//when user press esc key
        // {
        //     _getch();
        //     continue;
        // }
        else
        {
            pass.push_back(c);
            cout << '*';
        }
    }
    cout << endl;
    return pass;
}

void clearConsole() {
    cout.flush();  // Flush the output stream
#if defined _WIN32
    system("cls");
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined(__APPLE__)
    system("clear");
#endif
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    // cout << "\x1B[2J\x1B[H";
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
        cin.ignore();
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
        cin.ignore();
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

    static Issue getIssueObjDetailsFromUser() {
        string studentRollID;
        string bookISBN;
        Date issueDate;

        cout << "Enter Student's Roll ID: ";
        cin.ignore();
        getline(cin, studentRollID);

        cout << "Enter Book's ISBN Number: ";
        getline(cin, bookISBN);

        cout << "Enter Issue Date in format dd-mm-yyyy: ";
        issueDate = getDateFromUser();

        Issue obj(studentRollID, bookISBN, issueDate);
        return obj;
    }

    static Issue getIssueObjFromInputStream(istream &inputStream) {
        string str;

        inputStream.ignore();
        getline(inputStream, str);

        vector<string> issueAttr = split(str, ',');

        Issue issue(issueAttr[0], issueAttr[1], Date(issueAttr[2].c_str()), Date(issueAttr[3].c_str()), string2bool(issueAttr[4]), StringToNumber<double>(issueAttr[5]), string2bool(issueAttr[6]));
        return issue;
    }

    friend bool operator==(const Issue &issue1, const Issue &issue2) {
        return issue1.bookISBN == issue2.bookISBN && issue1.studentRollID == issue2.studentRollID && (Date)issue1.issueDate == (Date)issue2.issueDate && (Date)issue1.returnDate == (Date)issue2.returnDate && issue1.isReturned == issue2.isReturned && issue1.isFinePaid == issue2.isFinePaid && issue1.fineAmount == issue2.fineAmount;
    }

    friend ostream &operator<<(ostream &output, const Issue &issueObj) {
        string str = "";

        str += issueObj.studentRollID;
        str += ',' + issueObj.bookISBN;
        str += ',' + date2string(issueObj.issueDate);
        str += ',' + date2string(issueObj.returnDate);
        str += ',' + issueObj.isReturned;
        str += ',' + NumberToString<double>(issueObj.fineAmount);
        str += ',' + issueObj.isFinePaid;

        output << str;

        return output;
    }
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

        fout << "RollID,Name,Branch,Password";

        for (int i = 0; i < students.size(); i++) {
            fout << endl
                 << students[i];
        }

        fout.close();
    }
    static void writeBooks(vector<Book> books) {
        ofstream fout(FileManager::bookFileName.c_str(), ios::out);

        fout << "ISBN,Name,Author,Publisher,Genere,Quantity";

        for (int i = 0; i < books.size(); i++) {
            fout << endl
                 << books[i];
        }

        fout.close();
    }
    static void writeIssues(vector<Issue> issues) {
        ofstream fout(FileManager::issueFileName.c_str(), ios::out);

        fout << "BookISBN,StudentRollID,IssueDate,ReturnDate,IsReturned,FineAmount,IsFinePaid";

        for (int i = 0; i < issues.size(); i++) {
            fout << endl
                 << issues[i];
        }

        fout.close();
    }

    static vector<Student> getAllStudents() {
        vector<Student> students;

        ifstream fin(FileManager::studentFileName.c_str(), ios::in);

        if (fin.fail()) {
            return students;
        }

        string _;
        getline(fin, _);

        while (!fin.eof()) {
            students.push_back(Student::getStudentObjFromInputStream(fin));
        }

        return students;
    }
    static vector<Book> getAllBooks() {
        vector<Book> books;

        ifstream fin(FileManager::bookFileName.c_str(), ios::in);

        if (fin.fail()) {
            return books;
        }

        string _;
        getline(fin, _);

        while (!fin.eof()) {
            books.push_back(Book::getBookObjFromInputStream(fin));
        }

        return books;
    }
    static vector<Issue> getAllIssues() {
        vector<Issue> issues;

        ifstream fin(FileManager::issueFileName.c_str(), ios::in);

        if (fin.fail()) {
            return issues;
        }

        string _;
        getline(fin, _);

        while (!fin.eof()) {
            issues.push_back(Issue::getIssueObjFromInputStream(fin));
        }

        return issues;
    }
};

const string FileManager::studentFileName = "data/Students.csv";
const string FileManager::bookFileName = "data/Books.csv";
const string FileManager::issueFileName = "data/Issues.csv";

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
   private:
    vector<Student> students;
    vector<Book> books;
    vector<Issue> issues;

   protected:
    void readStateFromFiles() {
        this->students = FileManager::getAllStudents();
        this->books = FileManager::getAllBooks();
        this->issues = FileManager::getAllIssues();
    }

    void writeStateInFiles() {
        FileManager::writeStudents(this->students);
        FileManager::writeBooks(this->books);
        FileManager::writeIssues(this->issues);
    }

    void addStudent(Student student) {
        this->students.push_back(student);
        FileManager::writeStudents(this->students);
    }

    void addBook(Book book) {
        this->books.push_back(book);
        FileManager::writeBooks(this->books);
    }

    void addIssue(Issue issue) {
        this->issues.push_back(issue);
        FileManager::writeIssues(this->issues);
    }

    bool validateAdmin(string password) {
        if(password == ADMIN_PASSWORD) return true;
        else return false;
    }

    bool validateStudent(string rollID, string password) {
        return true;
    }
};

/* State Class => End */

/* App Class => Start */

class App : protected State {
    void showMenu() {
        int userInput;

        string password;
        string rollId;

        do {
            cout << "1.Student \n2.Admin \n3.Exit" << endl;
            cout << "Login As: ";
            cin >> userInput;

            clearConsole();

            switch (userInput) {
                case 1:
                    cout << "Enter Roll ID: ";
                    cin >> rollId;
                    cout << "Enter Password: ";
                    password = getPasswordFromUser();

                    if (State::validateStudent(rollId, password))
                        this->showStudentMenu();
                    else
                        cout << "Authentication Failed" << endl;

                    break;

                case 2:;
                    cout << "Enter Password: ";
                    password = getPasswordFromUser();

                    if (State::validateAdmin(password))
                        this->showAdminMenu();
                    else
                        cout << "Authentication Failed" << endl;

                    break;

                case 3:
                    this->stop();
                    break;

                default:
                    cout << "Enter a valid choice" << endl;
                    break;
            }
        } while (userInput != 1 && userInput != 2 && userInput != 3);
    }

    void showStudentMenu() {
        clearConsole();
        int userInput;
    
        do{
            cout << "1.Search \n2.Issue history \n3.Pending Books to be returned \n4.Fine Log \n5.Reset Password \n6.Exit" << endl ;
            cout << "Enter your choice: ";
            cin >> userInput;

            switch(userInput) {
                case 1:
                    this->showSearchBookMenu();
                    break;
                
                case 2:
                    // Issue history
                    break;

                case 3:
                    // Pending books to be returned
                    break;

                case 4:
                    // Fine log
                    break;

                case 5:
                    // Restet password
                    break;

                case 6:
                    this->stop();
                    break;

                default:
                    cout << "Enter a valid choice" << endl;
                    break;
            }
        } while(userInput != 6);
    }

    void showAdminMenu() {
        clearConsole();
        int userInput;
        string rollID;
    
        do {
            cout << "1.Issue \n2.Return \n3.Add New \n4.Manage \n5.Issue History \n6.Pending Books to be returned \n7.Manage Fines \n8.Reset Password \n9.Student Details \n10.Exit" << endl ;
            cout << "Enter your choice: ";
            cin >> userInput;

            switch(userInput)
            {
                case 1:
                    // Issue
                    break;
                
                case 2:
                    // Return
                    break;

                case 3:
                    this->showAddNewMenu();
                    break;

                case 4:
                    this->showManageMenu();
                    break;

                case 5:
                    // Issue History
                    break;

                case 6:
                    // Pending Books to be returned
                    break;

                case 7:
                    this->showManageFinesMenu();
                    break;

                case 8:
                    // Reset Password 
                    break;

                case 9:
                    cout << "\nEnter Roll ID: ";
                    cin >> rollID;

                    this->showStudentDetailsMenu(rollID);
                    break;

                case 10:
                    this->stop();
                    break;

                default:
                    cout << "Enter a valid choice" << endl;
                    break;
            }
        } while(userInput != 10);
    }

    void showSearchBookMenu() {
        clearConsole();
        int userInput;

        do{
            cout << "1.By Author \n2.By Publisher \n3.By Genre \n4.By Name \n5.All \n6.Exit" << endl;
            cout << "Enter your choice: ";
            cin >> userInput;

            switch (userInput) {
                case 1:
                    // By Author
                break;

                case 2:
                    // By Publisher
                break;

                case 3:
                    // By Genre
                break;

                case 4:
                    // By Name
                break;

                case 5:
                    // All
                break;

                case 6:
                    clearConsole();
                    return;
                    break;

                default:
                    cout << "\nEnter a valid choice";
                    break;
            }
        } while(userInput != 6);
    }

    void showAddNewMenu() {
        clearConsole();
        int userInput;

        do{
            cout << "1.Book \n2.Student \n3.Exit" << endl;
            cout << "Enter your choice: ";
            cin >> userInput;

            switch (userInput) {
                case 1:
                    State::addBook(Book::getBookObjDetailsFromUser());
                    clearConsole();
                    break;

                case 2:
                    State::addStudent(Student::getStudentObjDetailsFromUser());
                    clearConsole();
                    break;

                case 3:
                    clearConsole();
                    return;
                    break;

                default:
                    cout << "\nEnter a valid choice";
                    break;
            }
        } while(userInput != 3);
    }

    void showManageMenu() {
        clearConsole();
        int userInput;

        do{
            cout << "1.Book \n2.Student \n3.Exit" << endl;
            cout << "Enter your choice: ";
            cin >> userInput;

            switch (userInput) {
                case 1:
                    // Book
                    break;

                case 2:
                    // Student
                    break;

                case 3:
                    clearConsole();
                    return;
                    break;

                default:
                    cout << "\nEnter a valid choice";
                    break;
            }
        } while(userInput != 3);
    }

    void showManageFinesMenu() {
        clearConsole();
        int userInput;

        do{
            cout << "1.Fines paid or not \n2.Fine per day \n3.Exit" << endl;
            cout << "Enter your choice: ";
            cin >> userInput;

            switch (userInput)
            {
                case 1:
                    // Fines paid or not
                    break;

                case 2:
                    // Fines per day
                    break;

                case 3:
                    clearConsole();
                    return;
                    break;

                default:
                    cout << "\nEnter a valid choice";
                    break;
            }
        } while(userInput != 3);
    }

    void showStudentDetailsMenu(string rollID) {
        clearConsole();
        int userInput;
        
        do {
            cout << "1.Issue history \n2.Pending books to be returned \n3.Fine logs \n4.Exit" << endl;
            cout << "Enter your choice: ";
            cin >> userInput;

            switch (userInput) {
                case 1:
                    // Issue history
                    break;

                case 2:
                    // Pending books to be returned
                    break;

                case 3:
                    // Pending books to be returned
                    break;
                
                case 4:
                    clearConsole();
                    return;
                    break;

                default:
                    cout << "\nEnter a valid choice";
                    break;
            }
        }while(userInput != 4);
    }

   public:
    App() {
        State::readStateFromFiles();
    }

    ~App() {
        State::writeStateInFiles();
    }

    void start() {
        this->showMenu();
    }

    void stop() {
        State::writeStateInFiles();
    }
};

/* App Class => End */

int main() {
    // Define the format in which Date objects are input and output
    Date::setFormat(DATE_FORMAT);

    App app;

    app.start();
    
    app.stop();

    return 0;
}
