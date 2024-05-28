#include <iostream>
using namespace std;

// Forward declarations
class Library;

//Abstract User Class.
class User {
protected:
    string username;
    string password;

public:
    // Default Constructor.
    User() = default;

    //Destructor.
    virtual ~User() = default;

    // Credentials Validation.
    static bool isValidUsername(string uname) {
        return (uname == "user");
    }

    static bool isValidPassword(string pwd) {
        return (pwd == "password");
    }

    // Method to set Username and Password.
    void setCredentials() {
        string uname, pwd;

        cout << "\nEnter Username: ";
        cin >> uname;

        if (isValidUsername(uname)) {
            this->username = uname;
        } else {
            cout << "\nInvalid Username."<< endl;
            return;
        }

        cout << "\nEnter Password: ";
        cin >> pwd;

        if (isValidPassword(pwd)) {
            this->password = pwd;
        } else {
            cout << "\nInvalid Password." << endl;
            return;
        }
    }

    // Abstract Method.
    virtual bool login() = 0;
};


//Book Class.
class Book {
    friend class Library;

protected:
    string title;
    string author;
    int year;
    Book* next;

public:
    //Default Constructor.
    Book() = default;

    //Parameterized Constructor.
    Book(string title, string author, int year) {
        this->title = title;
        this->author = author;
        this->year = year;
        this->next = nullptr;
    }

    //Destructor.
    ~Book() = default;
};


//Student Class just for LinkedList Initialization.
class student : public User {
    friend class Library;

public:
    student* next = nullptr;

    //Default Constructor.
    student () : User() {};

    //Destructor.
    ~student() override = default;

    //Implement the pure virtual function login.
    bool login() override {
        return (username == "user" && password == "password");
    }
};


//Class to store History.
class History {
    friend class Library;

protected:
    string* arr;
    int top;

public:
    //constructor.
    History() {
        arr = new string[10];
        top = -1;
    }

    //Destructor.
    ~History() = default;

    void addHistory(string item) {
        if (top == 9) {
            for (int i = 0; i < 9; i++) {
                arr[i] = arr[i + 1];
            }
            arr[top] = item;
        } else {
            arr[++top] = item;
        }
    }

    void displayHistory() {
        if (top == -1) {
            cout << "No History Found." << endl;
            return;
        }

        cout << "History: " << endl;
        for (int i = 0; i <= top; i++) {
            cout << "  " << arr[i] << endl;
        }

    }

};

//Library Class.
class Library {

protected:
    Book* bHead;
    student* sHead;

public:
    //Initializing History.
    History searchHistory;
    History borrowedHistory;

    //Default Constructor.
    Library() {
        bHead = nullptr;
        sHead = nullptr;
    }

    //Destructor.
    ~Library() = default;


    //Method to add a Book.
    void addBook(string title, string author, int year) {
        Book* newBook = new Book(title, author, year);

        if (!bHead) {
            bHead = newBook;
            cout<<"Book has been added to the Library.\n";
            return;
        }

        Book* temp = bHead;
        while (temp->next) {
            temp = temp->next;
        }

        temp->next = newBook;
        cout<<"Book has been added to the Library.\n";
    }

    //Borrow a Book Method.
    void removeBook(string title,string author,int year) {
        if (!bHead) {
            cout<<"\nLibrary is already Empty.\n";
            return;
        }

        Book* temp = bHead;
        Book* prev = nullptr;

        while (temp) {
            if (temp->title == title && temp->author == author && temp->year == year) {
                if (!prev) {
                    bHead = temp -> next;
                } else {
                    prev->next = temp->next;
                }

                delete temp;
                cout<<"\nBook has been Removed from the Library.\n";
                borrowedHistory.addHistory(title);
                return;
            }
            prev = temp;
            temp = temp -> next;
        }
        cout<<"Book not found.\n";
    }

    //Method to display all Books.
    void displayBooks() {
        if (!bHead) {
            cout << "Library is Empty.\n" << endl;
            return;
        }

        Book* temp = bHead;
        cout << "\nBooks in Library: " << endl;
        while (temp) {
            cout << "  Title: " << temp->title << endl;
            cout << "  Author: " << temp->author << endl;
            cout << "  Year: " << temp->year << endl;
            cout << "----------------------" << endl;
            temp = temp->next;
        }
    }

    //Method to search a Book.
    void searchBook(string title) {
        bool isFound = false;

        if (!bHead) {
            cout << "Library is Empty.\n" << endl;
            return;
        }

        Book* temp = bHead;
        while (temp) {
            if (temp->title == title) {
                cout << "\nBook: " << endl;
                cout << "  Title: " << temp->title << endl;
                cout << "  Author: " << temp->author << endl;
                cout << "  Year: " << temp->year << endl;
                isFound = true;
                searchHistory.addHistory(title);
            }
            temp = temp->next;
        }
        if (!(isFound)) {
            cout << "Book not found." << endl;
        }
    }

    //Method to add a student.
    void addStudent(string username, string password) {
        student* newStudent = new student();
        newStudent->username = username;
        newStudent->password = password;

        if (!sHead) {
            sHead = newStudent;
            cout<<"\nStudent has been Added.\n";
            return;
        }

        student* temp = sHead;
        while (temp->next) {
            temp = temp->next;
        }

        temp->next = newStudent;
        cout<<"\nStudent has been Added.\n";
    }


    //Method to remove a student.
    void removeStudent(string username, string password) {
        if (!sHead) {
            cout<<"\nNo Students Registered yet.\n";
            return;
        }

        student* temp = sHead;
        student* prev = nullptr;

        while (temp) {
            if (temp->username == username && temp->password == password) {
                if (!prev) {
                    sHead = temp -> next;
                } else {
                    prev->next = temp->next;
                }

                delete temp;
                cout<<"\nStudent has been Removed.\n";
                return;
            }
            prev = temp;
            temp = temp -> next;
        }
        cout<<"Student not found.\n";
    }

    //Method to display Borrowed History.
    void displayBorrowedHistory() {
        borrowedHistory.displayHistory();
    }

    //Method to display Search History.
    void displaySearchHistory() {
        searchHistory.displayHistory();
    }

};

//Derived Student Class.
class Student : public User {
public:
    Library library;
    //Default Constructor.
    Student () : User() {};

    //Destructor.
    ~Student() override = default;

    //Implement the pure virtual function login.
    bool login() override {
        return (username == "user" && password == "password");
    }

    //Method to add a book with parameters.
    void addBook(string title, string author, int year) {
        library.addBook(title, author, year);
    }

    //Method to borrow a Book.
    void borrowBook() {
        string title, author;
        int year;

        cin.ignore();

        cout << "\nEnter Title of the Book: ";
        getline(cin, title);

        while (title.empty()) {
            cout<<"Title cannot be empty.\n";
            cout << "\nEnter Title of the Book: ";
            getline(cin, title);
        }

        cout << "\nEnter Author Name: ";
        getline(cin, author);

        while (author.empty()) {
            cout<<"Author Name cannot be empty.\n";
            cout << "\nEnter Author Name: ";
            getline(cin, author);
        }

        cout << "\nEnter the year of publication: ";
        while(!(cin >> year) || year < 1900 || year > 2024) {
            cout << "Year must be from 1900-2024\n";
            cin.clear(); // clear the fail state
            cin.ignore(); // ignore the bad input
            cout << "\nEnter the year of publication: ";
        }

        library.removeBook(title, author, year);
    }


    //Method to return a Book.
    void returnBook() {
        string title, author;
        int year;

        cin.ignore();

        cout << "\nEnter Title of the Book: ";
        getline(cin, title);

        while (title.empty()) {
            cout<<"Title cannot be empty.\n";
            cout << "\nEnter Title of the Book: ";
            getline(cin, title);
        }

        cout << "\nEnter Author Name: ";
        getline(cin, author);

        while (author.empty()) {
            cout<<"Author Name cannot be empty.\n";
            cout << "\nEnter Author Name: ";
            getline(cin, author);
        }

        cout << "\nEnter the year of publication: ";
        while(!(cin >> year) || year < 1900 || year > 2024) {
            cout << "Year must be from 1900-2024\n";
            cin.clear(); // clear the fail state
            cin.ignore(); // ignore the bad input
            cout << "\nEnter the year of publication: ";
        }

        library.addBook(title, author, year);
    }

    //Method to display all Books.
    void displayBooks() {
        library.displayBooks();
    }

    //Method to search a Book.
    void searchBook() {
        string title;
        cin.ignore();

        cout << "\nEnter Title of the Book: ";
        getline(cin, title);

        while (title.empty()) {
            cout<<"Title cannot be empty.\n";
            cout << "\nEnter Title of the Book: ";
            getline(cin, title);
        }

        library.searchBook(title);
    }

    //Method to display Borrowed History.
    void displayBorrowedHistory() {
        library.displayBorrowedHistory();
    }

    //Method to display Search History.
    void displaySearchHistory() {
        library.displaySearchHistory();
    }
};


//Derived Librarian Class.
class Librarian : public User {
    Library library;

public:
    //Default Constructor.
    Librarian () : User() {};

    //Destructor.
    ~Librarian() override = default;

    //Implement the pure virtual function login.
    bool login() override {
        return (username == "user" && password == "password");
    };

    //Method to add a Book.
    void addBook() {
        string title, author;
        int year;

        cin.ignore();

        cout << "\nEnter Title of the Book: ";
        getline(cin, title);

        while (title.empty()) {
            cout<<"Title cannot be empty.\n";
            cout << "\nEnter Title of the Book: ";
            getline(cin, title);
        }

        cout << "\nEnter Author Name: ";
        getline(cin, author);

        while (author.empty()) {
            cout<<"Author Name cannot be empty.\n";
            cout << "\nEnter Author Name: ";
            getline(cin, author);
        }

        cout << "\nEnter the year of publication: ";
        while(!(cin >> year) || year < 1900 || year > 2024) {
            cout << "Year must be from 1900-2024\n";
            cin.clear(); // clear the fail state
            cin.ignore(); // ignore the bad input
            cout << "\nEnter the year of publication: ";
        }

        library.addBook(title, author, year);
    }


    //Method to remove a Book.
    void removeBook() {
        string title, author;
        int year;

        cin.ignore();

        cout << "\nEnter Title of the Book: ";
        getline(cin, title);

        while (title.empty()) {
            cout<<"Title cannot be empty.\n";
            cout << "\nEnter Title of the Book: ";
            getline(cin, title);
        }

        cout << "\nEnter Author Name: ";
        getline(cin, author);

        while (author.empty()) {
            cout<<"Author Name cannot be empty.\n";
            cout << "\nEnter Author Name: ";
            getline(cin, author);
        }

        cout << "\nEnter the year of publication: ";
        while(!(cin >> year) || year < 1900 || year > 2024) {
            cout << "Year must be from 1900-2024\n";
            cin.clear(); // clear the fail state
            cin.ignore(); // ignore the bad input
            cout << "\nEnter the year of publication: ";
        }

        library.removeBook(title, author, year);
    }

    //Method to add a student.
    void addStudent() {
        string username, password;
        cin.ignore();

        cout << "\nEnter Username: ";
        cin >> username;

        cout << "\nEnter Password: ";
        cin >> password;

        library.addStudent(username, password);
    }


    //Method to remove a student.
    void removeStudent() {
        string username, password;
        cin.ignore();

        cout << "\nEnter Username: ";
        cin >> username;

        cout << "\nEnter Password: ";
        cin >> password;

        library.removeStudent(username, password);
    }
};

//Function to display Student Main Menu.
void displayStudentMainMenu() {
    cout<< ("\n\n");
    cout<< ("\t\t\t\t\t   ______________________________________________________________\n");
    cout<< ("\t\t\t\t\t  |                                                             |\n");
    cout<< ("\t\t\t\t\t  |                                                             |\n");
    cout<< ("\t\t\t\t\t  |                                                             |\n");
    cout<< ("\t\t\t\t\t  |                                                             |\n");
    cout<< ("\t\t\t\t\t  |                         WELCOME                             |\n");
    cout<< ("\t\t\t\t\t  |                           TO                                |\n");
    cout<< ("\t\t\t\t\t  |                      Haseeb's Library                       |\n");
    cout<< ("\t\t\t\t\t  |                                                             |\n");
    cout<< ("\t\t\t\t\t  |                                                             |\n");
    cout<< ("\t\t\t\t\t  |                                                             |\n");
    cout<< ("\t\t\t\t\t  |                                                             |\n");
    cout<< ("\t\t\t\t\t  |_____________________________________________________________|\n");

    cout << "1. Borrow a Book" << endl;
    cout << "2. Return a Book" << endl;
    cout << "3. Search a Book" << endl;
    cout << "4. Display all Books" << endl;
    cout << "5. Display Search History" << endl;
    cout << "6. Display Borrowed History" << endl;
    cout << "7. Return to Main Menu" << endl;
    cout << "8. Exit" << endl;
    cout << "---------------------------------------" << endl;
    cout << "Enter your choice: ";
};


//Display Librarian Main Menu.
void displayLibrarianMainMenu() {
    cout<< ("\n\n");
    cout<< ("\t\t\t\t\t   ______________________________________________________________\n");
    cout<< ("\t\t\t\t\t  |                                                             |\n");
    cout<< ("\t\t\t\t\t  |                                                             |\n");
    cout<< ("\t\t\t\t\t  |                                                             |\n");
    cout<< ("\t\t\t\t\t  |                                                             |\n");
    cout<< ("\t\t\t\t\t  |                         WELCOME                             |\n");
    cout<< ("\t\t\t\t\t  |                           TO                                |\n");
    cout<< ("\t\t\t\t\t  |                      Haseeb's Library                       |\n");
    cout<< ("\t\t\t\t\t  |                                                             |\n");
    cout<< ("\t\t\t\t\t  |                                                             |\n");
    cout<< ("\t\t\t\t\t  |                                                             |\n");
    cout<< ("\t\t\t\t\t  |                                                             |\n");
    cout<< ("\t\t\t\t\t  |_____________________________________________________________|\n");

    cout << "1. Add a Student" << endl;
    cout << "2. Remove a Student" << endl;
    cout << "3. Add a Book" << endl;
    cout << "4. Remove a Book" << endl;
    cout << "5. Display Search History" << endl;
    cout << "6. Display Borrowed History" << endl;
    cout << "7. Return to Main Menu" << endl;
    cout << "8. Exit" << endl;
    cout << "---------------------------------------" << endl;
    cout << "Enter your choice: ";
};


//Main Function.
int main() {
    Student student;
    Librarian librarian;

    //Adding Books in Library.
    student.addBook("The Alchemist", "Paulo Coelho", 1988);
    student.addBook("The Da Vinci Code", "Dan Brown", 2003);
    student.addBook("The Great Gatsby", "F. Scott Fitzgerald", 1925);
    student.addBook("The Catcher in the Rye", "J.D. Salinger", 1951);
    student.addBook("To Kill a Mockingbird", "Harper Lee", 1960);

        cout << "\n\n\n===================================================" << endl;
        cout << "       Welcome to the Library Management System!" << endl;
        cout << "=====================================================\n" << endl;

    while (true) {
        cout<<"\nHow do you want to login?"<<endl;
        cout<<"  1. Student"<<endl;
        cout<<"  2. Librarian"<<endl;
        cout<<"  3. Exit"<<endl;

        int choice;
        cout<<"\nEnter your choice: ";

        while (!(cin>>choice)) {
            cout << "Invalid Choice!" << endl;
            cin.clear();
            cin.ignore();
            cout << "\nEnter your choice: ";
        }

        switch (choice) {
            case 1: {
                for (int i = 0; i < 3; i++) {
                    student.setCredentials();
                    if (student.login()) {
                        cout << "Login Successful!" << endl;

                        while (true) {
                            displayStudentMainMenu();
                            int choice;

                            while (!(cin>>choice)) {
                                cout << "Invalid Choice!" << endl;
                                cin.clear();
                                cin.ignore();
                                cout << "\nEnter your choice: ";
                            }

                            switch (choice) {
                                case 1: {
                                    student.borrowBook();
                                    break;
                                }
                                case 2: {
                                    student.returnBook();
                                    break;
                                }
                                case 3: {
                                    student.searchBook();
                                    break;
                                }
                                case 4: {
                                    student.displayBooks();
                                    break;
                                }
                                case 5: {
                                    student.displaySearchHistory();
                                    break;
                                }
                                case 6: {
                                    student.displayBorrowedHistory();
                                    break;
                                }
                                case 7: {
                                    cout << "Returning to Main Menu..." << endl;
                                    break;
                                }
                                case 8: {
                                    cout << "Exiting..." << endl;
                                    exit(0);
                                }
                                default: {
                                    cout << "Invalid Choice!" << endl;
                                    break;
                                }
                            }

                            if (choice == 7) {
                                break; // Go back to the login menu
                            }
                        }
                    } else {
                        cout<<"Remaining Attempts:"<<(2-i)<<endl;
                    }
                }
                break;
            }

            case 2: {
                for (int i = 0; i < 3; i++) {
                    librarian.setCredentials();
                    if (librarian.login()) {
                        cout << "Login Successful!" << endl;

                        while (true) {
                            displayLibrarianMainMenu();
                            int choice;

                            while (!(cin>>choice)) {
                                cout << "Invalid Choice!" << endl;
                                cin.clear();
                                cin.ignore();
                                cout << "\nEnter your choice: ";
                            }

                            switch (choice) {
                                case 1: {
                                    librarian.addStudent();
                                    break;
                                }
                                case 2: {
                                    librarian.removeStudent();
                                    break;
                                }
                                case 3: {
                                    librarian.addBook();
                                    break;
                                }
                                case 4: {
                                    librarian.removeBook();
                                    break;
                                }
                                case 5: {
                                    cout << "Display Search History" << endl;
                                    break;
                                }
                                case 6: {
                                    cout << "Display Borrowed History" << endl;
                                    break;
                                }
                                case 7: {
                                    cout << "Returning to Main Menu..." << endl;
                                    break;
                                }
                                case 8: {
                                    cout << "Exiting..." << endl;
                                    exit(0);
                                }
                                default: {
                                    cout << "Invalid Choice!" << endl;
                                    break;
                                }
                            }

                            if (choice == 7) {
                                break; // Go back to the login menu
                            }
                        }
                    } else {
                        cout<<"Remaining Attempts:"<<(2-i)<<endl;
                    }
                }
                break;
            }

            case 3: {
                cout << "Exiting..." << endl;
                exit(0);
            }

            default: {
                cout << "Invalid Choice!" << endl;
                break;
            }
        }
    }
};