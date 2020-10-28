#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <conio.h>
#include <time.h>

#include <stdlib.h>

#include <cmath>
#include <cstring>
#include <ctime>
#include <stdexcept>

using namespace std;


typedef enum Day {
    D01 = 1,
    D02 = 2,
    D03 = 3,
    D04 = 4,
    D05 = 5,
    D06 = 6,
    D07 = 7,
    D08 = 8,
    D09 = 9,
    D10 = 10,
    D11 = 11,
    D12 = 12,
    D13 = 13,
    D14 = 14,
    D15 = 15,
    D16 = 16,
    D17 = 17,
    D18 = 18,
    D19 = 19,
    D20 = 20,
    D21 = 21,
    D22 = 22,
    D23 = 23,
    D24 = 24,
    D25 = 25,
    D26 = 26,
    D27 = 27,
    D28 = 28,
    D29 = 29,
    D30 = 30,
    D31 = 31
};

typedef enum WeekDay {
    Mon = 1,
    Tue = 2,
    Wed = 3,
    Thr = 4,
    Fri = 5,
    Sat = 6,
    Sun = 7
};

// A week starts on Monday and ends on Sunday. Weeks are numbered in a year from 1 to 52
// (or 53). Week 1 (W01) of a year starts contains the first Thursday of the year. Hence
// W01 of 2016 starts on 04/Jan and ends on 10/Jan as 07/Jan is the first Thursday.
// 01/Jan, 02/Jan, and 03/Jan therefore belongs to the last week of 2015.
typedef enum WeekNumber {
    W01 = 1,
    W02 = 2,
    W03 = 3,
    W04 = 4,
    W05 = 5,
    W06 = 6,
    W07 = 7,
    W08 = 8,
    W09 = 9,
    W10 = 10,
    W11 = 11,
    W12 = 12,
    W13 = 13,
    W14 = 14,
    W15 = 15,
    W16 = 16,
    W17 = 17,
    W18 = 18,
    W19 = 19,
    W20 = 20,
    W21 = 21,
    W22 = 22,
    W23 = 23,
    W24 = 24,
    W25 = 25,
    W26 = 26,
    W27 = 27,
    W28 = 28,
    W29 = 29,
    W30 = 30,
    W31 = 31,
    W32 = 32,
    W33 = 33,
    W34 = 34,
    W35 = 35,
    W36 = 36,
    W37 = 37,
    W38 = 38,
    W39 = 39,
    W40 = 40,
    W41 = 41,
    W42 = 42,
    W43 = 43,
    W44 = 44,
    W45 = 45,
    W46 = 46,
    W47 = 47,
    W48 = 48,
    W49 = 49,
    W50 = 50,
    W51 = 51,
    W52 = 52,
    W53 = 53
};

typedef enum Month {
    Jan = 1,
    Feb = 2,
    Mar = 3,
    Apr = 4,
    May = 5,
    Jun = 6,
    Jul = 7,
    Aug = 8,
    Sep = 9,
    Oct = 10,
    Nov = 11,
    Dec = 12
};

typedef unsigned int Year;

// This class defines the format in which a date is output or input
class DateFormat {
   public:
    // Making Date class a friend to provide access necessary for ostream
    // Ostream requires to know dateFormat, monthFormat and yearFormat.
    // Private getters are introduced in Date class to access these attributes
    // This doesn't break encapsulation or lead to unauthorized access
    friend class Date;

    // The parameters below takes designated values with the specified format semantics
    // dateFormat:
    //     0: No date. This is valid for output only.
    //     "d": single digit date in one digit, double digit date in two digits (7, 23)
    //     "dd": all dates in two digits with single digit dates with leading 0 (07, 23)
    // monthFormat:
    //     0: each month in its full name (February, November). This is valid for output only.
    //     "m": single digit month in one digit, double digit month in two digits (2, 11)
    //     "mm": all months in two digits with single digit months with leading 0 (02, 11)
    //     "mmm": each month with first three letters of its name (Feb, Nov). This is valid for output only.
    // yearFormat:
    //     0: No year. This is valid for output only.
    //     "yy": year in last two digits (1961 as 61, 2016 as 16)
    //     "yyyy": year in four digits (1961 as 1961, 2016 as 2016)
    DateFormat(const char* dateFormat, const char* monthFormat, const char* yearFormat);

    // Single C-string format where dateFormat, monthFormat, and yearFormat are separated by ’-’
    // Example: "dd-mmm-yy", "d-mm-yyyy", etc
    DateFormat(const char* format);

    // Default DateFormat created as "dd-mmm-yy"
    DateFormat();

    ~DateFormat();

    DateFormat& operator=(const DateFormat&);

    // Added only for convenience in understanding output of TestDate()
    void printDateFormat() {
        cout << ((dateFormat == NULL) ? "NULL" : dateFormat) << ", " << ((monthFormat == NULL) ? "NULL" : monthFormat) << ", " << ((yearFormat == NULL) ? "NULL" : yearFormat);
    }

   private:
    char* dateFormat;   // C-string specifying format of date
    char* monthFormat;  // C-string specifying format of month
    char* yearFormat;   // C-string specifying format of year
};

// This class defines a date within 01/Jan/1950 and 31/Dec/2049
class Date {
   public:
    // CONSTRUCTORS
    Date(Day d, Month m, Year y)  // Construct a Date from (d, m, y)
        throw(
            invalid_argument,  // One or more of the arguments d or m is/are invalid (27, 13, 13)
            domain_error,      // (d, m, y) as a triplet does not define a valid date (30, 2, 61)
            out_of_range);     // Date is out of range (4, 7, 2053)

    explicit Date(const char* date)  // date in string format -- to be parsed as static format member
        throw(invalid_argument, domain_error, out_of_range);
    // "13-03-77" for "dd-mm-yy"
    // "2-7-2018" for "d-m-yyyy"

    Date()  // Default Constructor - construct 'today' (get from system)
        throw(domain_error, out_of_range);

    Date(const Date&);  // Copy Constructor

    // DESTRUCTOR
    ~Date();  // No virtual destructor needed

    // BASIC ASSIGNMENT OPERATOR
    Date& operator=(const Date&);

    // UNARY ARITHMETIC OPERATORS
    Date& operator++();     // Next day
    Date operator++(int);   // Same day next week
    Date& operator--();     // Previous day
    Date& operator--(int);  // Same day previous week

    // BINARY ARITHMETIC OPERATORS
    unsigned int operator-(const Date& otherDate);  // Number of days between otherDate and current date

    Date operator+(int noOfDays)            // Day noOfDays after (before) the current date
        throw(domain_error, out_of_range);  // (sign of noOfDays decides ahead or behind)

    // CAST OPERATORS
    operator WeekNumber() const;  // Cast to the week number of the year in which the current date falls
    operator Month() const;       // Cast to the month of the year in which the current date falls
    operator WeekDay() const;     // Cast to the day of the week of the current date

    bool leapYear() const;  // True if the year of the current date is a leap year

    // BINARY RELATIONAL OPERATORS
    bool operator==(const Date& otherDate);
    bool operator!=(const Date& otherDate);
    bool operator<(const Date& otherDate);
    bool operator<=(const Date& otherDate);
    bool operator>(const Date& otherDate);
    bool operator>=(const Date& otherDate);

    // BASIC I/O using FRIEND FUNCTIONS
    // These functions use Date::format to write or read
    friend ostream& operator<<(ostream&, const Date&);
    friend istream& operator>>(istream&, Date&);

    // Format Function
    static void setFormat(DateFormat&);
    static const DateFormat& getFormat();

   private:
    // Format to represent Date
    static DateFormat format;
    // Data members for Date
    Day d;
    Month m;
    Year y;

    // Date Class made as a friend class of DateFormat
    // Private function member getters used by ostream
    // Can't be accessed by the user.
    static const char* getDateFormat() {
        return format.dateFormat;
    }

    static const char* getMonthFormat() {
        return format.monthFormat;
    }

    static const char* getYearFormat() {
        return format.yearFormat;
    }
};

/*
* Author : Avikalp Srivastava
*/

/*********************************** C++ Headers ************************************/

// Included on top

/***************************** Misc Functions *****************************/

// Initializing static member 'format' of Date class with the default constructor
// dayFormat = "dd", monthFormat = "mmm", yearFormat = "yy"
DateFormat Date::format;

/*    Name: findDashPosition_DateFormat()
      Input: pos[] - integer array with size >= 2, format - const char* depicting DateFormat
      Output: None.
      Description: The pos array is assigned the 0-index positions of the two '-' in format.
                   Assigned -1 if no '-' or less than two '-' are there.
*/
void findDashPosition_DateFormat(int pos[], const char* format) {
    // Let dash_pos point to first occurence of '-' in format
    char* dash_pos = strchr(const_cast<char*>(format), '-');
    // If no '-' found, return pos[0] and pos[1] as -1
    if (dash_pos == NULL) {
        pos[0] = pos[1] = -1;
        return;
    }
    // The index of first '-' is given by dash_pos - format
    pos[0] = dash_pos - format;

    // Repeating for second '-'
    dash_pos = strchr(dash_pos + 1, '-');
    // Second '-' must be present, else return pos[0] and pos[1] as -1
    if (dash_pos == NULL) {
        pos[0] = pos[1] = -1;
        return;
    }
    pos[1] = dash_pos - format;
}

/*    Name: isLeapYear()
      Input: enum Year / unsigned int year
      Output: True - if year is leap year. False if not.
      Description: Returns False if year is not divisible by 4 or is divisible by 100 but not 400.
*/
bool isLeapYear(Year year) {
    int y = year;

    if ((y % 4 != 0) || (y % 100 == 0 && y % 400 != 0)) {
        return false;
    } else {
        return true;
    }
}

/*    Name: dateHasInvalidArgs
      Input: enum Day, Month and Year
      Output: True - if day and month parameters are within valid range. False if not.
      Description: Returns True if given date has valid args for month and Day.
*/
bool dateHasInvalidArgs(Day day, Month month, Year year) {
    int d = day, m = month;

    // For easy changes, expansion, re-usability
    int minDay = 1, maxDay = 31;
    int minMonth = 1, maxMonth = 12;

    if (d < minDay || d > maxDay) {
        return true;
    } else if (m < minMonth || m > maxMonth) {
        return true;
    } else {
        return false;
    }
}

/*    Name: isDateValid
      Input: enum Day, Month, Year
      Output: True - if the give date is valid. False if not.
      Description: Checks that for a given Month, Day < max days in that Month.
                   Robust check for leap year condition.
*/
bool isDateValid(Day day, Month month, Year year) {
    int d = day, m = month, y = year;
    int monthDays[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    // If given year a leap year, change number of days in Feb to 29
    if (isLeapYear(y)) {
        monthDays[2] = 29;
    }
    // Checking that Day > max days in that Month should return false.
    // d < 1 for unseen future expansion - robustness
    if (d > monthDays[m] || d < 1) {
        return false;
    } else {
        return true;
    }
}

/*    Name: isDateInRange
      Input: enum Day, Month, Year
      Output: True - if the give date is in given range. False if not.
      Description: Checks whether the given date lies in range or not
*/
bool isDateInRange(Day day, Month month, Year year) {
    int d = day, m = month, y = year;

    // For easy changes, expansion, re-usability
    int minDay = 1, minMonth = 1, minYear = 1950;
    int maxDay = 31, maxMonth = 12, maxYear = 2049;

    // Checking for lower range.
    if ((y < minYear) || (y == minYear && m < minMonth) || (y == minYear && m == minMonth && d < minDay)) {
        return false;
    }
    // Checking for upper range
    else if ((y > maxYear) || (y == maxYear && m > maxMonth) || (y == maxYear && m == maxMonth && d > maxDay)) {
        return false;
    }
    // Else, Date is with the range, return true
    else {
        return true;
    }
}

/*    Name: dayOfWeek
      Input: int Day, Month, Year
      Output: An integer in the range 1 to 7. 1 -> Monday, 7 -> Sunday
      Description: Uses standard week day finding algorithm
      Source : GeeksForGeeks. Code ReUse
*/
int dayOfWeek(int d, int m, int y) {
    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    y -= m < 3;
    int ans = (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
    return (ans == 0) ? ans + 7 : ans;
}

/*    Name: countLeapDays
      Input: enum Month, Year
      Output: A positive integer
      Description: Returns number of leap / extra days passed since beginning of time 0/0/00
*/
int countLeapDays(Month m, Year y) {
    int month = m, year = y;
    // If the year is leap year but month is <= 2, leap day has not passed.
    if (month <= 2) {
        year--;
    }
    // Num of leap days = Years divisible by 4 or 400 but not 100
    return year / 4 - year / 100 + year / 400;
}

/*    Name: getNumberDaysPassed
      Input: enum Day, Month, Year
      Output: A positive long long integer
      Description: Returns number of days passed since beginning of time 0/0/00 till given Date
*/
long long int getNumberDaysPassed(Day d, Month m, Year y) {
    int day = d, month = m, year = y;
    int monthDays[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    // Adding days contributed by y and d
    long long int days = (static_cast<long long int>(year)) * 365 + static_cast<long long int>(day);
    // Adding days contributed by m
    while (--month) {
        days = days + monthDays[month];
    }
    // Adding days contributed by leap / extra days
    days = days + countLeapDays(m, y);
    return days;
}

/*    Name: addDays
      Input: int numDays <= 365 for normal years and 33 for leap, address of day and month; and year of date.
      Output: None
      Description: For a year, assigns the day and month that occur after numDays
*/
void addDays(int numDays, int& day, int& month, int year) {
    int monthDays[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    // If year is leap, changing monthDays of Feb to 29
    if (isLeapYear(static_cast<Year>(year))) {
        monthDays[2] = 29;
    }

    for (int i = 1; i <= 12; ++i) {
        if (numDays > monthDays[i]) {
            numDays = numDays - monthDays[i];
        } else {
            day = numDays;
            month = i;
            return;
        }
    }
}

/*    Name: getDateFromDays
      Input: long long int numDays, and an integer array infoArr of size >= 3
      Output: None
      Description: Given number of days passed since 0/0/00, finds the date
                   and stores day in infoArr[0], month in infoArr[1], year in infoArr[2]
                   Used by : + and - operators
*/
void getDateFromDays(long long int numDays, int infoArr[]) {
    // Gets a rough approximate of the year
    int tempYear = numDays / 365;
    // Additional number of days
    numDays = numDays % 365;

    // Subtracting leap days (due to years with 366 days)
    int numLeapDays = countLeapDays(Jan, tempYear);
    numDays = numDays - numLeapDays;

    // It may be the case that numDays = numDays - numLeapDays is negative
    // Then, the actual year is lesser than our rough approximate
    while (numDays <= 0) {
        // Since numDays is -ve, we will do tempYear-- and add 365 / 366 to numDays.
        numDays = numDays + 365;
        if (isLeapYear(tempYear - 1)) {
            numDays += 1;
        }
        // Going one year back
        --tempYear;
    }
    // Now, numDays is a number in range 1 to 366 and tempYear is the exact year
    // So, assigning infoArr[2] as tempYear.
    infoArr[2] = tempYear;

    // Getting day and month by passing infoArr[0] & infoArr[1] as references
    addDays(numDays, infoArr[0], infoArr[1], infoArr[2]);
}

/*    Name: getFirstMondayDate
      Input: enum year
      Output: A Date type
      Description: Takes an year input and outputs a date corresponding to the Monday of its Week Number 1
                   Uses the fact that this 'first Monday' can only lie b/w 29 Dec and 4 Jan
                   Used by : Week Number cast operator
*/
Date getFirstMondayDate(Year year) {
    int y = year;

    // finding b/w 29 Dec and 31 Dec
    for (int day = 29; day <= 31; day++) {
        // Check if its Monday
        if (dayOfWeek(day, 12, y - 1) == 1) {
            Date firstMondayDate(static_cast<Day>(day), static_cast<Month>(12), static_cast<Year>(y - 1));
            return firstMondayDate;
        }
    }
    // finding b/w 1 Jan and 4 Jan
    for (int day = 1; day <= 4; day++) {
        if (dayOfWeek(day, 1, y) == 1) {
            Date firstMondayDate(static_cast<Day>(day), static_cast<Month>(1), static_cast<Year>(y));
            return firstMondayDate;
        }
    }

    // For robustness
    Date default_date;
    return (default_date);
}

/***************************** CLASS Members Declarations *****************************/

// CONSTRUCTORS
DateFormat::DateFormat(const char* dateFormat,
                       const char* monthFormat,
                       const char* yearFormat) {
    // Checking dateFormat
    if (dateFormat == NULL) {
        this->dateFormat = NULL;
    } else if (strcmp(dateFormat, "d") == 0 || strcmp(dateFormat, "dd") == 0) {
        this->dateFormat = new char[strlen(dateFormat) + 1];
        strcpy(this->dateFormat, dateFormat);
    }
    // Argument should be 'd' or 'dd' , otherwise throw invalid argument
    else {
        throw invalid_argument("Exception Raised. The argument day provided for Date Format is wrong.");
    }

    // Checking monthFormat
    if (monthFormat == NULL) {
        this->monthFormat = NULL;
    } else if (strcmp(monthFormat, "m") == 0 || strcmp(monthFormat, "mm") == 0 || strcmp(monthFormat, "mmm") == 0) {
        this->monthFormat = new char[strlen(monthFormat) + 1];
        strcpy(this->monthFormat, monthFormat);
    } else {
        throw invalid_argument("Exception Raised. The argument month provided for Date Format is wrong.");
    }

    // Checking yearFormat
    if (yearFormat == NULL) {
        this->yearFormat = NULL;
    } else if (strcmp(yearFormat, "yy") == 0 || strcmp(yearFormat, "yyyy") == 0) {
        this->yearFormat = new char[strlen(yearFormat) + 1];
        strcpy(this->yearFormat, yearFormat);
    } else {
        throw invalid_argument("Exception Raised. The argument year provided for Date Format is wrong.");
    }
}

DateFormat::DateFormat(const char* format) {
    // Array to store position of the 2 '-' in format
    // IMPORTANT : A valid format must have 2 '-' . For null format, use 0-0-0
    int dash_pos[2];
    // Function to aptly populate dash_pos[]
    findDashPosition_DateFormat(dash_pos, format);

    // If - is the first character
    // "-mm-yyyy" etc indicate that dateFormat is to be NULL
    if (dash_pos[0] == 0) {
        this->dateFormat = NULL;
    }
    // Else if there is one character before '-' , it should be '0' or 'd'
    else if (dash_pos[0] == 1) {
        if (format[0] == 'd') {
            dateFormat = new char[2];
            strcpy(dateFormat, "d");
        } else {
            throw invalid_argument("Exception Raised. The argument day provided for Date Format is wrong.");
        }
    }
    // Else if 2 chars before '-', they should be "dd"
    else if (dash_pos[0] == 2) {
        if (format[0] == 'd' && format[1] == 'd') {
            dateFormat = new char[3];
            strcpy(dateFormat, "dd");
        } else {
            throw invalid_argument("Exception Raised. The argument day provided for Date Format is wrong.");
        }
    }
    // dash_pos[0] other than 1 and 2 are invalid
    else {
        throw invalid_argument("Exception Raised. The argument day provided for Date Format is wrong.");
    }

    // Again, dd--yy etc indicate that monthFormat is invalid
    if (dash_pos[1] - dash_pos[0] - 1 == 0) {
        this->monthFormat = NULL;
    }
    // For 1 char b/w first and second '-', it should be '0' or 'm'
    else if (dash_pos[1] - dash_pos[0] - 1 == 1) {
        if (format[dash_pos[0] + 1] == 'm') {
            monthFormat = new char[2];
            strcpy(monthFormat, "m");
        } else {
            // throw invalid_argument("The argument " + format + " provided for Date Format is wrong.");
            throw invalid_argument("Exception Raised. The argument provided for Date Format is wrong.");
        }
    }
    // For 2 chars, should be 'mm'
    else if (dash_pos[1] - dash_pos[0] - 1 == 2) {
        if (format[dash_pos[0] + 1] == 'm' && format[dash_pos[0] + 2] == 'm') {
            monthFormat = new char[3];
            strcpy(monthFormat, "mm");
        } else {
            // throw invalid_argument("The argument " + format + " provided for Date Format is wrong.");
            throw invalid_argument("Exception Raised. The argument provided for Date Format is wrong.");
        }
    }
    // for three, should be 'mmm'
    else if (dash_pos[1] - dash_pos[0] - 1 == 3) {
        if (format[dash_pos[0] + 1] == 'm' && format[dash_pos[0] + 2] == 'm' && format[dash_pos[0] + 3] == 'm') {
            monthFormat = new char[4];
            strcpy(monthFormat, "mmm");
        } else {
            throw invalid_argument("Exception Raised. The argument provided for Date Format is wrong.");
        }
    } else {
        throw invalid_argument("Exception Raised. The argument provided for Date Format is wrong.");
    }

    // Checking yearFormat the same way. dd-mm- indicate null yearFormat
    if (strlen(format) - dash_pos[1] - 1 == 0) {
        this->yearFormat = NULL;
    } else if (strlen(format) - dash_pos[1] - 1 == 2) {
        if (strcmp("yy", format + dash_pos[1] + 1) == 0) {
            yearFormat = new char[3];
            strcpy(yearFormat, "yy");
        } else {
            throw invalid_argument("Exception Raised. The argument provided for Date Format is wrong.");
        }
    } else if (strlen(format) - dash_pos[1] - 1 == 4) {
        if (strcmp("yyyy", format + dash_pos[1] + 1) == 0) {
            yearFormat = new char[5];
            strcpy(yearFormat, "yyyy");
        } else {
            throw invalid_argument("Exception Raised. The argument provided for Date Format is wrong.");
        }
    } else {
        throw invalid_argument("Exception Raised. The argument provided for Date Format is wrong.");
    }
}

// Default DateFormat CONSTRUCTOR
// Uses initializer list to assign the format "dd-mmm-yy"
DateFormat::DateFormat() {
    dateFormat = new char[3];
    strcpy(dateFormat, "dd");
    monthFormat = new char[4];
    strcpy(monthFormat, "mmm");
    yearFormat = new char[3];
    strcpy(yearFormat, "yy");
}

// DateFormat DESTRUCTOR : deletes the memory allocated to the char* attributes
DateFormat::~DateFormat() {
    delete[] dateFormat;
    delete[] monthFormat;
    delete[] yearFormat;
}

// ASSIGNMENT OPERATOR
// Till none of the format is null, assign apt memory to this->dateFormat, monthFormat, yearFormat
DateFormat& DateFormat::operator=(const DateFormat& newDF) {
    if (newDF.dateFormat != NULL) {
        dateFormat = new char[strlen(newDF.dateFormat) + 1];
        strcpy(dateFormat, newDF.dateFormat);
    } else {
        dateFormat = NULL;
    }
    if (newDF.monthFormat != NULL) {
        monthFormat = new char[strlen(newDF.monthFormat) + 1];
        strcpy(monthFormat, newDF.monthFormat);
    } else {
        monthFormat = NULL;
    }
    if (newDF.yearFormat != NULL) {
        yearFormat = new char[strlen(newDF.yearFormat) + 1];
        strcpy(yearFormat, newDF.yearFormat);
    } else {
        yearFormat = NULL;
    }
    return *this;
}

// Date CONSTRUCTOR
Date::Date(Day d, Month m, Year y) throw(invalid_argument,
                                         domain_error,
                                         out_of_range) {
    // Checking for all exceptions
    if (dateHasInvalidArgs(d, m, y)) {
        // Constructing Error Message string for Exception
        string errorMessage = "Exception Raised. Invalid Argument error on Date";
        throw invalid_argument(errorMessage);
    }

    if (!isDateValid(d, m, y)) {
        string errorMessage = "Exception Raised. Domain Error on Date";
        throw domain_error(errorMessage);
    }

    if (!isDateInRange(d, m, y)) {
        string errorMessage = "Exception Raised. Out of Range Error on Date";
        throw out_of_range(errorMessage);
    }

    // If none of the exception is thrown, assigning attributes to data members
    this->d = d;
    this->m = m;
    this->y = y;
}

// Date CONSTRUCTOR
Date::Date(const char* date) throw(invalid_argument, domain_error, out_of_range) {
    if (Date::getDateFormat() == NULL || Date::getMonthFormat() == NULL || strcmp(Date::getMonthFormat(), "mmm") == 0 || Date::getYearFormat() == NULL) {
        throw invalid_argument("Exception Raised. The current format does not support input.");
    }

    char* dayFormat;
    char* monthFormat;
    char* yearFormat;
    // Variable defining maximum year in the 2000-2100 range
    // Made for future changes / expansion / easy re-usability
    int maxIn20 = 49;

    int day, month, year;
    // Finding '-' positions, same as in DateFormat constructor
    int pos[2];
    findDashPosition_DateFormat(pos, date);

    // Checking for invalid positions of '-'
    if (pos[0] == -1 || pos[0] == 0 || pos[1] - pos[0] - 1 <= 0 || !(strlen(date) - pos[1] - 1 == 2 || strlen(date) - pos[1] - 1 == 4)) {
        throw invalid_argument("Exception Raised. The format of input date string is invalid");
    }

    // Fine checking on valid positions of '-'
    if (pos[0] == 1) {
        if (isdigit(date[0])) {
            day = date[0] - '0';
            dayFormat = new char[2];
            strcpy(dayFormat, "d");
        } else {
            throw invalid_argument("Exception Raised. Invalid Argument error on Date");
        }
    }
    if (pos[0] == 2) {
        if (isdigit(date[0]) && isdigit(date[1])) {
            day = (date[0] - '0') * 10 + date[1] - '0';
            if (date[0] == '0' || strcmp(Date::getDateFormat(), "dd") == 0) {
                dayFormat = new char[3];
                strcpy(dayFormat, "dd");
            } else {
                dayFormat = new char[2];
                strcpy(dayFormat, "d");
            }
        } else {
            throw invalid_argument("Exception Raised. Invalid Argument error on Date");
        }
    } else {
        throw invalid_argument("Exception Raised. Invalid Argument error on Date");
    }

    if (pos[1] - pos[0] - 1 == 1) {
        if (isdigit(date[pos[0] + 1])) {
            month = date[pos[0] + 1] - '0';
            monthFormat = new char[2];
            strcpy(monthFormat, "m");
        }
    } else if (pos[1] - pos[0] - 1 == 2) {
        if (isdigit(date[pos[0] + 1]) && isdigit(date[pos[0] + 2])) {
            month = (date[pos[0] + 1] - '0') * 10 + date[pos[0] + 2] - '0';
            if (date[pos[0] + 1] == '0' || strcmp(Date::getMonthFormat(), "mm") == 0) {
                monthFormat = new char[3];
                strcpy(monthFormat, "mm");
            } else {
                monthFormat = new char[2];
                strcpy(monthFormat, "m");
            }

        } else {
            throw invalid_argument("Exception Raised. Invalid Argument error on Date");
        }
    }
    // Below commented out code can help expand class to accept inputs with mmm as well.
    /*  else if(pos[1] - pos[0] - 1 == 3)
    {
        string monthShortName[]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
        // Flag to be set true if one the short month names is found in the string
        bool flag = false;
        for(int i = 0; i < 12; i++)
        {
            if(strncmp((monthShortName[i]).c_str(), date + pos[0] + 1, 3) == 0)
            {
                month = i+1;
                flag = true;
                monthFormat = new char[4];
                strcpy(monthFormat, "mmm");
                break;
            }
        }
        if(flag == false)
        {
            throw invalid_argument("Exception Raised. Invalid Argument error on Date");
        }
    } */

    else {
        throw invalid_argument("Exception Raised. Invalid Argument error on Date");
    }

    if (strlen(date) - pos[1] - 1 == 2) {
        if (isdigit(date[pos[1] + 1]) && isdigit(date[pos[1] + 2])) {
            year = (date[pos[1] + 1] - '0') * 10 + date[pos[1] + 2] - '0';
            // Deciding b/w 21st and 20th century year
            if (year <= maxIn20)
                year += 2000;
            else
                year += 1900;

            yearFormat = new char[3];
            strcpy(yearFormat, "yy");
        } else {
            throw invalid_argument("Exception Raised. Invalid Argument error on Date");
        }
    }

    else if (strlen(date) - pos[1] - 1 == 4) {
        if (isdigit(date[pos[1] + 1]) && isdigit(date[pos[1] + 2]) && isdigit(date[pos[1] + 3]) && isdigit(date[pos[1] + 4])) {
            year = (date[pos[1] + 1] - '0') * 1000 + (date[pos[1] + 2] - '0') * 100 + (date[pos[1] + 3] - '0') * 10 + (date[pos[1] + 4] - '0');
            yearFormat = new char[5];
            strcpy(yearFormat, "yyyy");
        } else {
            throw invalid_argument("Exception Raised. Invalid Argument error on Date");
        }
    }

    else {
        throw invalid_argument("Exception Raised. Invalid Argument error on Date");
    }

    // If the input doesn't match the static member format, raise an invalid argument exception
    if (!(strcmp(dayFormat, Date::getDateFormat()) == 0 && strcmp(monthFormat, Date::getMonthFormat()) == 0 && strcmp(yearFormat, Date::getYearFormat()) == 0)) {
        throw invalid_argument("Exception Raised. Format doesn't match the static member format.");
        cout << "Entered Format : " << dayFormat << "-" << monthFormat << "-" << yearFormat << endl;
        cout << "Expected Format : " << Date::getDateFormat() << "-" << Date::getMonthFormat() << "-" << Date::getYearFormat() << endl;
    }
    // If exception not thrown till now, we have valid date format
    // Converting to enums.
    Day eday = static_cast<Day>(day);
    Month emonth = static_cast<Month>(month);
    Year eyear = static_cast<Year>(year);

    // Checking for exception in the 'to-be-formed' date
    if (dateHasInvalidArgs(eday, emonth, eyear)) {
        throw invalid_argument("Exception Raised. Invalid Argument error on Date");
    }
    if (!isDateValid(eday, emonth, eyear)) {
        throw domain_error("Exception Raised. Domain Error on Date");
    }
    if (!isDateInRange(eday, emonth, eyear)) {
        throw out_of_range("Exception Raised. Out of Range error on Date");
    }
    // No Exception. Assigning attributes
    this->d = eday;
    this->m = emonth;
    this->y = eyear;
}

// Default Constructor
Date::Date() throw(domain_error, out_of_range) {
    // Getting today's date from system
    // Code ReUse from GeeksForGeeks
    time_t t = time(0);
    struct tm* now = localtime(&t);
    int year = now->tm_year + 1900,
        month = now->tm_mon + 1,
        day = now->tm_mday;

    Day eDay = static_cast<Day>(day);
    Month eMonth = static_cast<Month>(month);
    Year eYear = static_cast<Year>(year);

    if (!isDateValid(eDay, eMonth, eYear)) {
        // string errorMessage = "Exception Raised. Domain Error on date : " + to_string(d) + "-" + to_string(m) + "-" + to_string(y);
        string errorMessage = "Exception Raised. Domain Error on Today's Date (Def Constructor)";
        throw domain_error(errorMessage);
    }

    else if (!isDateInRange(eDay, eMonth, eYear)) {
        // string errorMessage = "Exception Raised. Out of Range Error on date : " + to_string(d) + "-" + to_string(m) + "-" + to_string(y);
        string errorMessage = "Exception Raised. Out of Range Error on Today's Date (Def Constructor)";
        throw out_of_range(errorMessage);
    }

    // No exception thrown. Setting data members
    else {
        this->d = eDay;
        this->m = eMonth;
        this->y = eYear;
    }
}

// COPY CONSTRUCTOR
Date::Date(const Date& date) : d(date.d), m(date.m), y(date.y) {
    // Empty Body
}

// DESTRUCTOR
Date::~Date() {
    // Empty body
}

// ASSIGNMENT OPERATOR
Date& Date::operator=(const Date& date) {
    if ((*this) != date) {
        this->d = date.d;
        this->m = date.m;
        this->y = date.y;
    }
    return (*this);
}

// UNARY ARITHMETIC OPERATORS
Date& Date::operator++()  // Next day
{
    // Uses the overloaded '+' operator on Date
    (*this) = (*this) + 1;
    return *this;
}

Date Date::operator++(int)  // Next Week, same day
{
    // Saving the current date, as the postfix operator has to return the old value.
    Date currDate(this->d, this->m, this->y);
    // Uses the overloaded '+' operator on Date
    (*this) = (*this) + 7;
    return currDate;
}

Date& Date::operator--()  // Previous day
{
    // Uses the overloaded '+' operator on Date
    (*this) = (*this) + (-1);
    return *this;
}

Date& Date::operator--(int)  // Same day previous week
{
    // Uses the overloaded '+' operator on Date
    (*this) = (*this) + (-7);
    return *this;
}

// BINARY ARITHMETIC OPERATORS
unsigned int Date::operator-(const Date& otherDate)  // Number of days between otherDate and current date
{
    // Getting no of days passed from 0/0/00 to this date and other date
    long long int currDateNoOfDaysPassed = getNumberDaysPassed(this->d, this->m, this->y);
    long long int otherDateNoOfDaysPassed = getNumberDaysPassed(otherDate.d, otherDate.m, otherDate.y);
    // Taking abs val of difference
    long long int daysBetween = labs(currDateNoOfDaysPassed - otherDateNoOfDaysPassed);
    return static_cast<unsigned int>(daysBetween);
}

Date Date::operator+(int noOfDays)  // Day noOfDays after (before) the current date
    throw(domain_error, out_of_range) {
    // Getting no of days passed from 0/0/00 to this date
    long long int currDateDaysPassed = getNumberDaysPassed(this->d, this->m, this->y);
    // Adding noOfDays to it
    long long int newDateDaysPassed = currDateDaysPassed + static_cast<long long int>(noOfDays);

    // A negative val of noOfDays might have led to a <0 condition
    if (newDateDaysPassed < 0) {
        throw out_of_range("Exception raised. Out of range error on Date.");
    }

    // An array infoArr[3] to store the day, month and year of the new date
    int* infoArr = new int[3];
    // infoArr[0] -> day, infoArr[1] -> month, infoArr[2] -> year of New Date
    getDateFromDays(newDateDaysPassed, infoArr);

    if (!isDateInRange(static_cast<Day>(infoArr[0]), static_cast<Month>(infoArr[1]), static_cast<Year>(infoArr[2]))) {
        throw out_of_range("Exception raised. Out of range error on Date.");
    }

    Date newDate(static_cast<Day>(infoArr[0]), static_cast<Month>(infoArr[1]), static_cast<Year>(infoArr[2]));
    return newDate;
}

Date::operator WeekNumber() const {
    int weekNum;
    // Getting the date corresponding to Monday of the week number 1 of the year this->y
    Date firstMondayDate = getFirstMondayDate(this->y);

    // If this Date is lesser than firstMondayDate, then it lies in week number of previous year
    if (*(const_cast<Date*>(this)) < firstMondayDate) {
        int year = this->y;
        Date firstMondayDate_prevYear = getFirstMondayDate(static_cast<Year>(year - 1));
        weekNum = (*(const_cast<Date*>(this)) - firstMondayDate_prevYear) / 7;
    } else {
        weekNum = (*(const_cast<Date*>(this)) - firstMondayDate) / 7;
    }
    return static_cast<WeekNumber>(weekNum + 1);
}

Date::operator Month() const  // Cast to the month of the year in which the current date falls
{
    return this->m;
}

Date::operator WeekDay() const  // Cast to the day of the week of the current date
{
    int day = this->d, month = this->m, year = this->y;
    int weekday = dayOfWeek(day, month, year);
    return static_cast<WeekDay>(weekday);
}

bool Date::leapYear() const  // True if the year of the current date is a leap year
{
    return isLeapYear(this->y);
}

// BINARY RELATIONAL OPERATORS
bool Date::operator==(const Date& otherDate) {
    int thisday = this->d, thismonth = this->m, thisyear = this->y;
    int otherday = otherDate.d, othermonth = otherDate.m, otheryear = otherDate.y;
    if (thisday == otherday && thismonth == othermonth && thisyear == otheryear)
        return true;
    else
        return false;
}

bool Date::operator!=(const Date& otherDate) {
    if ((*this) == otherDate)
        return false;
    else
        return true;
}

bool Date::operator<(const Date& otherDate) {
    int thisday = this->d, thismonth = this->m, thisyear = this->y;
    int otherday = otherDate.d, othermonth = otherDate.m, otheryear = otherDate.y;

    if (thisyear < otheryear || (thisyear == otheryear && thismonth < othermonth) || (thisyear == otheryear && thismonth == othermonth && thisday < otherday))
        return true;
    else
        return false;
}

bool Date::operator<=(const Date& otherDate) {
    if (*this == otherDate || *this < otherDate)
        return true;
    else
        return false;
}

bool Date::operator>(const Date& otherDate) {
    if (!(*this <= otherDate))
        return true;
    else
        return false;
}

bool Date::operator>=(const Date& otherDate) {
    if (!(*this < otherDate))
        return true;
    else
        return false;
}

ostream& operator<<(ostream& os, const Date& date) {
    int day = date.d, month = date.m, year = date.y;

    // Flush to os according to the static member format
    if (date.getDateFormat() != NULL) {
        if (strcmp(date.getDateFormat(), "d") == 0) {
            os << day << "-";
        } else if (strcmp(date.getDateFormat(), "dd") == 0) {
            if (day < 10)
                os << "0" << day << "-";
            else
                os << day << "-";
        }
    }

    if (date.getMonthFormat() != NULL) {
        if (strcmp(date.getMonthFormat(), "m") == 0) {
            os << month << "-";
        } else if (strcmp(date.getMonthFormat(), "mm") == 0) {
            if (month < 10)
                os << "0" << month << "-";
            else
                os << month << "-";
        } else if (strcmp(date.getMonthFormat(), "mmm") == 0) {
            string monthShortName[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
            os << monthShortName[month - 1] << "-";
        }
    } else {
        string monthFullName[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
        os << monthFullName[month - 1] << "-";
    }

    if (date.getYearFormat() != NULL) {
        if (strcmp(date.getYearFormat(), "yy") == 0) {
            if (year < 2000)
                os << (year % 1900);
            else {
                if (year % 2000 < 10)
                    os << "0" << (year % 2000);
                else
                    os << (year % 2000);
            }

        } else if (strcmp(date.getYearFormat(), "yyyy") == 0) {
            os << year;
        }
    }
    return os;
}

istream& operator>>(istream& is, Date& date) {
    string input;
    cin >> input;
    date = Date(input.c_str());
    return is;
}

void Date::setFormat(DateFormat& form) {
    Date::format = form;
}

const DateFormat& Date::getFormat() {
    return Date::format;
}

/****************************************** END OF Date.h IMPLEMENTATIONS ******************************************/

int _getch() {
   char ch;
   cin >> ch;
   return ch;
}

namespace configuration {
    string ADMIN_PASSWORD = "pass";

    double FINE_PER_DAY = 100;
    int ALLOWED_DAYS_TO_KEEP_BOOK = 7;
}

using namespace configuration;

DateFormat DATE_FORMAT("dd-mm-yyyy");
const Date NULL_DATE(D01, Jan, 1950);

template <typename T>
T stringTo(const string &str) {
    istringstream ss(str);
    T num;
    ss >> num;
    return num;
}

template <typename T>
string toString(T num) {
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

string getPasswordFromUser() {
    string abc;
    cin.ignore();
    getline(cin, abc);
    return abc;
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
    cout << "\x1B[2J\x1B[H";
}

/* Config Class => Start */

class Config {
  public:
    static string getConfigString() {
        string str = "";
        str += ADMIN_PASSWORD;
        str += "," + toString<double>(FINE_PER_DAY);
        str += "," + toString<int>(ALLOWED_DAYS_TO_KEEP_BOOK);
        return str;
    }

    static void setConfig(string config) {
        vector<string> configAttr = split(config, ',');
        ADMIN_PASSWORD = configAttr[0];
        FINE_PER_DAY = stringTo<double>(configAttr[1]);
        ALLOWED_DAYS_TO_KEEP_BOOK = stringTo<int>(configAttr[2]);
    }
};

/* Config Class => End */

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

    bool validatePassword(string pass) {
        return this->password == pass;
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

        getline(inputStream, str);

        vector<string> bookAttr = split(str, ',');

        Book bookObj(bookAttr[0], bookAttr[1], bookAttr[2], bookAttr[3], bookAttr[4], stringTo<int>(bookAttr[5]));
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
        str += ',' + toString<int>(bookObj.quantity);

        output << str;

        return output;
    }
};

/* Book Class => End */

/* Issue Class => Start */

class Issue {
    string issueID;
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
        this->issueID = studentRollID + bookISBN + toString<Date>(issueDate) + toString<long>(time(0));

        this->studentRollID = studentRollID;
        this->bookISBN = bookISBN;
        this->issueDate = issueDate;

        this->returnDate = NULL_DATE;
        this->isReturned = false;
        this->fineAmount = 0;
        this->isFinePaid = true;
    }
    Issue(string issueID, string studentRollID, string bookISBN, Date issueDate, Date returnDate, bool isReturned, double fineAmount, bool isFinePaid) {
        this->issueID = issueID;
        this->studentRollID = studentRollID;
        this->bookISBN = bookISBN;
        this->issueDate = issueDate;
        this->returnDate = returnDate;
        this->isReturned = isReturned;
        this->fineAmount = fineAmount;
        this->isFinePaid = isFinePaid;
    }

    string getIssueID() {
        return this->issueID;
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
        this->fineAmount = (dateDiff > ALLOWED_DAYS_TO_KEEP_BOOK) ? (dateDiff - ALLOWED_DAYS_TO_KEEP_BOOK) * FINE_PER_DAY : 0;
        this->isFinePaid = (fineAmount > 0) ? false : true;
    }

    void payFine() {
        this->isFinePaid = true;
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

    void getReturnDetailsFromUser() {
        cout << "Enter Return Date in format dd-mm-yyyy: ";
        this->returnBook(getDateFromUser());
    }

    static Issue getIssueObjFromInputStream(istream &inputStream) {
        string str;

        getline(inputStream, str);

        vector<string> issueAttr = split(str, ',');

        Issue issue(issueAttr[0], issueAttr[1], issueAttr[2], Date(issueAttr[3].c_str()), Date(issueAttr[4].c_str()), stringTo<bool>(issueAttr[5]), stringTo<double>(issueAttr[6]), stringTo<bool>(issueAttr[7]));
        return issue;
    }

    friend bool operator==(const Issue &issue1, const Issue &issue2) {
        return issue1.bookISBN == issue2.bookISBN && issue1.studentRollID == issue2.studentRollID && (Date)issue1.issueDate == (Date)issue2.issueDate && (Date)issue1.returnDate == (Date)issue2.returnDate && issue1.isReturned == issue2.isReturned && issue1.isFinePaid == issue2.isFinePaid && issue1.fineAmount == issue2.fineAmount;
    }

    friend ostream &operator<<(ostream &output, const Issue &issueObj) {
        string str = "";

        str += issueObj.issueID;
        str += ',' + issueObj.studentRollID;
        str += ',' + issueObj.bookISBN;
        str += ',' + toString<Date>(issueObj.issueDate);
        str += ',' + toString<Date>(issueObj.returnDate);
        str += ',' + toString<bool>(issueObj.isReturned);
        str += ',' + toString<double>(issueObj.fineAmount);
        str += ',' + toString<bool>(issueObj.isFinePaid);

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
    static const string configFileName;
    static const string studentFileName;
    static const string bookFileName;
    static const string issueFileName;

   public:
    static void writeConfig() {
        ofstream fout(FileManager::configFileName.c_str(), ios::out);

        fout << "AdminPassword,FineAmountPerDay,AllowedDaysToKeepFine";

        fout << endl
             << Config::getConfigString();

        fout.close();
    }

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

        fout << "IssueID,StudentRollID,BookISBN,IssueDate,ReturnDate,IsReturned,FineAmount,IsFinePaid";

        for (int i = 0; i < issues.size(); i++) {
            fout << endl
                 << issues[i];
        }

        fout.close();
    }

    static void getSetConfig() {
        ifstream fin(FileManager::configFileName.c_str(), ios::in);

        if (fin.fail()) {
            return;
        }

        string temp;
        getline(fin, temp);
        
        getline(fin, temp);
        Config::setConfig(temp);
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

const string FileManager::configFileName = "Config.txt";
const string FileManager::studentFileName = "Students.txt";
const string FileManager::bookFileName = "Books.txt";
const string FileManager::issueFileName = "Issues.txt";

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

    vector<Student> getStudents() {
        return this->students;
    }
    vector<Book> getBooks() {
        return this->books;
    }
    vector<Issue> getIssues() {
        return this->issues;
    }

    Student* getStudentAt(int index) {
        return &this->students[index];
    }
    Book* getBookAt(int index) {
        return &this->books[index];
    }
    Issue* getIssueAt(int index) {
        return &this->issues[index];
    }

    void addStudent(Student student) {
        bool isStudentUnique = true;
        for (int i = 0; i < this->students.size(); i++) {
            if(this->students[i].getRollID() == student.getRollID()) {
                isStudentUnique = false;
            }
        }

        if (isStudentUnique) {
            this->students.push_back(student);
            FileManager::writeStudents(this->students);
            cout << "Added " << student.getName() << " successfully!" << endl;
        } else {
            cout << "Already a student with rollID " << student.getRollID() << endl;
            cout << "Failed to add " << student.getName() << endl;
        }        
    }

    void addBook(Book book) {
        bool isBookUnique = true;
        for (int i = 0; i < this->books.size(); i++) {
            if(this->books[i].getISBN() == book.getISBN()) {
                isBookUnique = false;
            }
        }

        if (isBookUnique) {
            this->books.push_back(book);
            FileManager::writeBooks(this->books);
            cout << "Added " << book.getName() << " successfully!" << endl;
        } else {
            cout << "Already a book with ISBN number " << book.getISBN() << endl;
            cout << "Failed to add " << book.getName() << endl;
        }        
    }

    void deleteBook(int idx) {
        Book temp = this->books[idx];
        this->books.erase(this->books.begin() + idx);
        FileManager::writeBooks(this->books);
        cout << "Successfully Deleted " << temp.getName() << " book" << endl;
    }
    
    void deleteStudent(int idx) {
        Student temp = this->students[idx];
        this->students.erase(this->students.begin() + idx);
        FileManager::writeStudents(this->students);
        cout << "Successfully Deleted " << temp.getName() << endl;
    }

    void addIssue(Issue issue) {
        bool isStudentValid = false;
        for (int i = 0; i < this->students.size(); i++) {
            if(this->students[i].getRollID() == issue.getStudentRollID()) {
                isStudentValid = true;
                break;
            }
        }

        bool isBookValid = false;
        for (int i = 0; i < this->books.size(); i++) {
            if(this->books[i].getISBN() == issue.getBookISBN()) {
                isBookValid = true;
                break;
            }
        }
        
        bool isBookAvailable = false;
        if (isBookValid) {
            Book thisBook = Query::getBookByISBN(this->books ,issue.getBookISBN());
            vector<Issue> thisBookIssues = Query::getIssuesByBookISBN(this->issues, thisBook.getISBN());
            vector<Issue> thisBookPendingReturnIssues = Query::getIssuesByPendingReturn(thisBookIssues);
            int thisBookPendingReturnIssuesCount = thisBookPendingReturnIssues.size();
            cout << thisBookPendingReturnIssuesCount;
            isBookAvailable = (thisBook.getQuantity() - thisBookPendingReturnIssuesCount >= 1) ? true : false;
        }

        Student thisStudent("", "", "", "");
        Book thisBook("", "", "", "", "", 0);
        if (isStudentValid) {
            thisStudent = Query::getStudentByRollID(this->students ,issue.getStudentRollID());
        }
        if (isBookValid) {
            thisBook = Query::getBookByISBN(this->books ,issue.getBookISBN());
        }

        bool isIssueValid = isStudentValid && isBookValid && isBookAvailable;

        if (isIssueValid) {
            this->issues.push_back(issue);
            FileManager::writeIssues(this->issues);
            cout << "Issue Successful!" << endl;
        } else {
            if (!isStudentValid) {
                cout << "Student with roll id " << issue.getStudentRollID() << " not found" << endl;
            }
            if (!isBookValid) {
                cout << "Book with ISBN " << issue.getBookISBN() << " not found" << endl;
            }
            if (isBookValid && !isBookAvailable) {
                cout << "Sorry!, " << thisBook.getName() << " book is not avaliable" << endl;
            }
            cout << "Issue Failed" << endl;
        }
    }

    string getIssueIDFromUser(vector<Issue> issues, string message) {
        int userInput;
        
        this->displayIssues(issues);
        
        cout << message;
        cin >> userInput;

        return issues[userInput-1].getIssueID();
    }

    void returnBook(string issueID) {
        int issueIdx = -1;

        bool isIssueIdValid = false;
        for (int i = 0; i < this->issues.size(); i++) {
            if (this->issues[i].getIssueID() == issueID) {
                isIssueIdValid = true;
                issueIdx = i;
            }
        }
    
        if(isIssueIdValid) {
            this->issues[issueIdx].getReturnDetailsFromUser();
            cout << "Return Successful!" << endl;
        } else {
            cout << "Return Failed due to some internal error (Invalid issueID = \"" << issueID << "\")" << endl;
        }
    }

    void payFine(string issueID) {
        int issueIdx = -1;

        bool isIssueIdValid = false;
        for (int i = 0; i < this->issues.size(); i++) {
            if (this->issues[i].getIssueID() == issueID) {
                isIssueIdValid = true;
                issueIdx = i;
            }
        }
    
        if(isIssueIdValid) {
            this->issues[issueIdx].payFine();
            cout << "Fine Paid Successful!" << endl;
        } else {
            cout << "Fine Pay Failed due to some internal error (Invalid issueID = \"" << issueID << "\")" << endl;
        }
    }

    void displayStudents(vector<Student> students) {
        cout << "RollID Name Branch" << endl;
        for (int i = 0; i < students.size(); i++) {
            cout << (i+1) << ". ";
            cout << students[i].getRollID() << " ";
            cout << students[i].getName() << " ";
            cout << students[i].getBranch() << endl;
        }
    }
    void displayBooks(vector<Book> books) {
        cout << "ISBN Name Author xQuantity" << endl;
        for (int i = 0; i < books.size(); i++) {
            cout << (i+1) << ". ";
            cout << books[i].getISBN() << " ";
            cout << books[i].getName() << " ";
            cout << books[i].getAuthor() << " ";
            cout << "x" << books[i].getQuantity() << endl;
        }
    }
    void displayIssues(vector<Issue> issues) {
        cout << "BookName StudentName IssueDate ReturnDate" << endl;
        cout << "FineAmount Paid/NotPaid" << endl;
        cout << endl;
        for (int i = 0; i < issues.size(); i++) {
            cout << (i+1) << ". ";
            cout << Query::getBookByISBN(books,issues[i].getBookISBN()).getName() << " ";
            cout << Query::getStudentByRollID(students,issues[i].getStudentRollID()).getName() << " ";
            cout << issues[i].getIssueDate() << " ";
            cout << (issues[i].getIsReturned() ? "Not Returned" : toString<Date>(issues[i].getReturnDate())) << endl;
            
            cout << (i+1) << ". ";
            cout << issues[i].getFineAmount() << " ";
            cout << (issues[i].getIsFinePaid() ? "Paid" : "Not Paid") << endl;

            cout << endl;
        }
    }

    bool validateAdmin(string password) {
        if(password == ADMIN_PASSWORD) return true;
        else return false;
    }
    bool validateStudent(string rollID, string password) {
        if(Query::getStudentByRollID(students, rollID).validatePassword(password)) return true;
        else return false;
    }

    void changePassword(string rollID, string pass) {
        for (int i = 0; i < this->students.size(); i++) {
            if(students[i].getRollID() == rollID) {
                students[i].resetPassword(pass);
                FileManager::writeStudents(this->students);
                return;
            }
        }
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
                        this->showStudentMenu(rollId);
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

    void showStudentMenu(string rollID) {
        clearConsole();
        int userInput;
    
        do{
            cout << "1.Search \n2.Issue history \n3.Pending Books to be returned \n4.Pending Fines \n5.Reset Password \n6.Exit" << endl ;
            cout << "Enter your choice: ";
            cin >> userInput;

            string pass1, pass2;
            switch(userInput) {
                case 1:
                    this->showSearchBookMenu();
                    break;
                
                case 2:
                    clearConsole();
                    State::displayIssues(Query::getIssuesByStudentRollID(State::getIssues(), rollID));
                    cout << "Press any key to exit...";
                    _getch();
                    clearConsole();
                    break;

                case 3:
                    clearConsole();
                    State::displayIssues(Query::getIssuesByPendingReturn(Query::getIssuesByStudentRollID(State::getIssues(), rollID)));
                    cout << "Press any key to exit...";
                    _getch();
                    clearConsole();
                    break;

                case 4:
                    clearConsole();
                    State::displayIssues(Query::getIssuesByPendingFine(Query::getIssuesByStudentRollID(State::getIssues(), rollID)));
                    cout << "Press any key to exit...";
                    _getch();
                    clearConsole();
                    break;

                case 5:
                    clearConsole();
                    cout << "Enter new password: ";
                    pass1 = getPasswordFromUser();
                    cout << "Confirm password: ";
                    pass2 = getPasswordFromUser();
                    if(pass1 == pass2) {
                        State::changePassword(rollID, pass1);
                        cout << "Password changed successfully" << endl;
                    } else {
                        cout << "Invalid Password" << endl;
                    }
                    cout << "Press any key to exit...";
                    _getch();
                    clearConsole();
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
            cout << "1.Issue \n2.Return \n3.Add New \n4.Delete \n5.Issue History \n6.Pending Books to be returned \n7.Manage Fines \n8.Reset Password \n9.Student Login \n10.Exit" << endl ;
            cout << "Enter your choice: ";
            cin >> userInput;

            string pass1, pass2;

            switch(userInput)
            {
                case 1:
                    clearConsole();
                    State::addIssue(Issue::getIssueObjDetailsFromUser());
                    cout << "Press any key to exit...";
                    _getch();
                    clearConsole();
                    break;
                
                case 2:
                    clearConsole();
                    State::returnBook(
                        State::getIssueIDFromUser(
                            Query::getIssuesByPendingReturn(State::getIssues()),
                            "Select Which Book to be Returned: "
                        )
                    );
                    cout << "Press any key to exit...";
                    _getch();
                    clearConsole();
                    break;

                case 3:
                    this->showAddNewMenu();
                    break;

                case 4:
                    this->showDeleteMenu();
                    break;

                case 5:
                    clearConsole();
                    State::displayIssues(State::getIssues());
                    cout << "Press any key to exit...";
                    _getch();
                    clearConsole();
                    break;

                case 6:
                    clearConsole();
                    State::displayIssues(Query::getIssuesByPendingReturn(State::getIssues()));
                    cout << "Press any key to exit...";
                    _getch();
                    clearConsole();
                    break;

                case 7:
                    this->showManageFinesMenu();
                    break;

                case 8:
                    clearConsole();
                    cout << "Enter new password: ";
                    pass1 = getPasswordFromUser();
                    cout << "Confirm password: ";
                    pass2 = getPasswordFromUser();
                    if(pass1 == pass2) {
                        ADMIN_PASSWORD = pass1;
                        FileManager::writeConfig();
                        cout << "Password changed successfully" << endl;
                    } else {
                        cout << "Invalid Password" << endl;
                    }
                    cout << "Press any key to exit...";
                    _getch();
                    clearConsole();
                    break;

                case 9:
                    cout << "\nEnter Roll ID: ";
                    cin >> rollID;

                    this->showStudentMenu(rollID);
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

            string author, publisher, genere, name;

            switch (userInput) {
                case 1:
                    clearConsole();
                    cout << "Enter author name: ";
                    cin >> author;
                    cout << endl;
                    State::displayBooks(Query::getBooksByAuthor(State::getBooks(), author));
                    cout << "Press any key to exit...";
                    _getch();
                    clearConsole();
                break;

                case 2:
                    clearConsole();
                    cout << "Enter publisher name: ";
                    cin >> publisher;
                    cout << endl;
                    State::displayBooks(Query::getBooksByPublisher(State::getBooks(), publisher));
                    cout << "Press any key to exit...";
                    _getch();
                    clearConsole();
                break;

                case 3:
                    clearConsole();
                    cout << "Enter genere name: ";
                    cin >> genere;
                    cout << endl;
                    State::displayBooks(Query::getBooksByGenere(State::getBooks(), genere));
                    cout << "Press any key to exit...";
                    _getch();
                    clearConsole();
                break;

                case 4:
                    clearConsole();
                    cout << "Enter book name: ";
                    cin >> name;
                    cout << endl;
                    State::displayBooks(Query::getBooksByName(State::getBooks(), name));
                    cout << "Press any key to exit...";
                    _getch();
                    clearConsole();
                break;

                case 5:
                    clearConsole();
                    State::displayBooks(State::getBooks());
                    cout << "Press any key to exit...";
                    _getch();
                    clearConsole();
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
                    clearConsole();
                    State::addBook(Book::getBookObjDetailsFromUser());
                    cout << "Press any key to exit...";
                    _getch();
                    clearConsole();
                    break;

                case 2:
                    clearConsole();
                    State::addStudent(Student::getStudentObjDetailsFromUser());
                    cout << "Press any key to exit...";
                    _getch();
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

    void showDeleteMenu() {
        clearConsole();
        int userInput;

        do{
            cout << "1.Book \n2.Student \n3.Exit" << endl;
            cout << "Enter your choice: ";
            cin >> userInput;

            int deleteIdx;

            switch (userInput) {
                case 1:
                    clearConsole();
                    State::displayBooks(State::getBooks());
                    cout << "Select which book to delete: ";
                    cin >> deleteIdx;
                    State::deleteBook((deleteIdx-1));
                    cout << "Press any key to exit...";
                    _getch();
                    clearConsole();
                    break;

                case 2:
                    clearConsole();
                    State::displayStudents(State::getStudents());
                    cout << "Select which student to delete: ";
                    cin >> deleteIdx;
                    State::deleteStudent((deleteIdx-1));
                    cout << "Press any key to exit...";
                    _getch();
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

    void showManageFinesMenu() {
        clearConsole();
        int userInput;

        double fineAmt;
        int allowedDays;

        do{
            cout << "1.Pay Fine \n2.Fine per day \n3.Allowed Days to keep book \n4.Exit" << endl;
            cout << "Enter your choice: ";
            cin >> userInput;

            switch (userInput)
            {
                case 1:
                    clearConsole();
                    State::payFine(
                        State::getIssueIDFromUser(
                            Query::getIssuesByPendingFine(State::getIssues()),
                            "Select Which Fine is to be Paid: "
                        )
                    );
                    cout << "Press any key to exit...";
                    _getch();
                    clearConsole();
                    break;

                case 2:
                    clearConsole();
                    cout << "Enter new fine amount: ";
                    cin >> fineAmt;
                    FINE_PER_DAY = fineAmt;
                    FileManager::writeConfig();
                    cout << "Fine Amount changed successfully" << endl;
                    cout << "Press any key to exit...";
                    _getch();
                    clearConsole();
                    break;
                
                case 3:
                    clearConsole();
                    cout << "Enter new allowed days to keep books: ";
                    cin >> allowedDays;
                    ALLOWED_DAYS_TO_KEEP_BOOK = allowedDays;
                    FileManager::writeConfig();
                    cout << "Fine Amount changed successfully" << endl;
                    cout << "Press any key to exit...";
                    _getch();
                    clearConsole();
                    break;

                case 4:
                    clearConsole();
                    return;
                    break;

                default:
                    cout << "\nEnter a valid choice";
                    break;
            }
        } while(userInput != 4);
    }

   public:
    App() {
        FileManager::getSetConfig();
        State::readStateFromFiles();
    }

    ~App() {
        FileManager::writeConfig();
        State::writeStateInFiles();
    }

    void start() {
        this->showMenu();
    }

    void stop() {
        FileManager::writeConfig();
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
