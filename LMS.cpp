//Library Management System developed by 'M. Haseeb Amjad'.

#include <iostream> // For input/output.
#include <cstdlib> // For exit() function

using namespace std;

class User {
protected:
    string username;
    string password;

public:
    //Default Constructor.
    User () = default;

    //Parameterized Constructor.
    User (string username, string password) {

        //validation of Credentails.
        if (username.length() < 5) {
            cout << "Username must be atleast 5 characters long." << endl;
            exit(EXIT_FAILURE);
        }

        if (password.length() < 8) {
            cout << "Password must be atleast 8 characters long." << endl;
            exit(EXIT_FAILURE);
        }

        //Setting the credentials.
        this->username = username;
        this->password = password;
    }

    //Destructor.
    ~User () {}

    //Abstract Method.
    virtual bool login(string username, string password) = 0;

};


class Book {
private:
    string title;
    string author;
    int year;
    Book* next;

public:
    //Default Constructor.
    Book () = default;

    //Parameterized Constructor.
    Book (string title, string author, int year) {
        this->title = title;
        this->author = author;
        this->year = year;
        this->next = nullptr;
    }

    //Destructor.
    ~Book () = default;

    //Setters.
    void setTitle(string title) {
        this->title = title;
    }

    void setAuthor(string author) {
        this->author = author;
    }

    void setYear(int year) {
        this->year = year;
    }

    //Getters.
    string getTitle() {
        return title;
    }

    string getAuthor() {
        return author;
    }

    int getYear() {
        return year;
    }

    friend class Library;

};

class Library {
private:
    Book* head;

public:
    //Constructor.
    Library () {
        head = nullptr;
    }

    // Destructor.
    ~Library() {
        while (head) {
            Book* temp = head;
            head = head->next;
            delete temp;
        }
    }

    //Return a Book Method.
    void returnBook(string& title, string& author, int& year) {
        Book* newBook = new Book(title, author, year);

        if (!head) {
            head = newBook;
        } else {
            Book* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newBook;
        }
        cout << "Book has been returned." << endl;
    }

    //Borrow a Book Method.
    void borrowBook(string& title, string& author, int& year) {

        if (!head) {
            cout<<"Library is Empty.";
            return;
        }

        Book* temp = head;
        Book* prev = nullptr;

        while (!temp) {
            if (temp->getTitle() == title && temp->getAuthor() == author && temp->getYear() == year) {
                if (!prev) {
                    head = temp -> next;
                } else {
                    prev->next = temp->next;
                }

                delete temp;
                cout << "Book has been borrowed." << endl;
                return;
            }
            prev = temp;
            temp = temp -> next;
        }

        cout<<"Book not found.";
    }


    //Display all Books.
    void displayBooks() {
        if (!head) {
            cout<<"Library is empty.";
            return;
        }

        Book* temp = head;
        cout<<"Displaying Books in the Library.\n";
        while (!temp) {
            cout<<"Book1:\n   "<<temp->getTitle()<<"\n   "<<temp->getAuthor()<<"\n   "<<temp->getYear();
            temp = temp -> next;
        }
    }
};



//Inheriting the User class.
class Student : User{
private:
    Library library;

public:

    //Parametrized Constructor.
    Student (string username, string password) : User(username, password) {};

    //Destructor.
    ~Student () = default;

    //Implement the pure virtual function login.
    bool login(string uname, string pwd) override {
        return (username == uname && password == pwd);
    }

    //Setters.
    void setUsername(string username) {
        this->username = username;
    }

    void setPassword(string password) {
        this->password = password;
    }

    //Getters.
    string getUsername() {
        return username;
    }

    string getPassword() {
        return password;
    }



    //Additional Methods for Student Class.
    void borrowBook() {
        string title;
        cout<<"Enter name of the Book: ";
        cin>>title;

        string author;
        cout<<"Enter name of the Author: ";
        cin>>author;

        int year;
        cout<<"Enter the year of publication: ";
        cin>>year;

        if (title.empty()) {
            cout << "Title can't be empty." << endl;
            exit(EXIT_FAILURE);
        }

        if (author.empty()) {
            cout << "Author name can't be empty." << endl;
            exit(EXIT_FAILURE);
        }

        if (year< 1900 || year > 2024) {
            cout << "Year must be of from 1900-2024." << endl;
            exit(EXIT_FAILURE);
        }

        library.borrowBook(title, author, year);
    }

    void returnBook() {
        string title;
        cout<<"Enter name of the Book: ";
        cin>>title;

        string author;
        cout<<"Enter name of the Author: ";
        cin>>author;

        int year;
        cout<<"Enter the year of publication: ";
        cin>>year;

        if (title.empty()) {
            cout << "Title can't be empty." << endl;
            exit(EXIT_FAILURE);
        }

        if (author.empty()) {
            cout << "Author name can't be empty." << endl;
            exit(EXIT_FAILURE);
        }

        if (year< 1900 || year > 2024) {
            cout << "Year must be of from 1900-2024." << endl;
            exit(EXIT_FAILURE);
        }

        library.returnBook(title, author, year);
    }

    void displayBooks() {
        library.displayBooks();
    }

    void displayProfile() {
        cout<<"Displaying User Profile..."<<endl;
        cout<<"Username: "<<username<<endl;
        cout<<"Password: "<<password<<endl;
    }

    void changePassword() {
        string newPassword;
        cout<<"Enter New Password: ";
        cin>>newPassword;

        if (newPassword.length() < 8) {
            cout << "Password must be atleast 8 characters long." << endl;
            exit(EXIT_FAILURE);
        }

        setPassword(newPassword);
        cout<<"Password Changed Successfully."<<endl;
    }
};


int main () {

};