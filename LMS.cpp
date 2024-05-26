//Library Management System developed by 'M. Haseeb Amjad'.
//The default userame and password is 'student' and 'student123' respectively.

#include <iostream> // For input/output.
#include <cstdlib> // For exit() function.
#include <string> // For importing string.
#include <windows.h> // For Windows API.
#include <conio.h> // For getch() function.

using namespace std;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(int textColor, int bgColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}

void loading() {
    int j;
    gotoxy(32, 20);
    cout << "Loading.......";
    gotoxy(0, 22);
    for (j = 0; j <= 167; j++) {
        cout << (char)219;
        Sleep(10);
    }
    Sleep(1000);
    system("cls");
}


//Abstract User Class.
class User {
protected:
    string username;
    string password;

public:
    // Default Constructor.
    User() = default;

    // Credentials Validation.
    bool isValidUsername(string uname) {
        return (uname == "student");
    }

    bool isValidPassword(string pwd) {
        return (pwd == "student123");
    }

    // Method to set Username and Password.
    void setCredentials() {
        string uname, pwd;
        cout << "\n\n\n===================================================" << endl;
        cout << "       Welcome to the Library Management System!" << endl;
        cout << "=====================================================\n" << endl;

        cout << "Enter Username: ";
        cin >> uname;
        cout<< endl;

        if (isValidUsername(uname)) {
            this->username = uname;
        } else {
            cout << "Invalid Username."<< endl;
            exit(EXIT_FAILURE);
        }

        cout << "Enter Password: ";
        cin >> pwd;

        if (isValidPassword(pwd)) {
            this->password = pwd;
        } else {
            cout << "Invalid Password." << endl;
            exit(EXIT_FAILURE);
        }
    }

    // Abstract Method.
    virtual bool login() = 0;
};


//Book CLass.
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


//Library Class.
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
    void returnBook(const string& title,const string& author,const int& year) {
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
    }

    //Borrow a Book Method.
    void borrowBook(const string& title,const string& author,const int& year) {

        if (!head) {
            cout<<"Library is Empty.\n";
            return;
        }

        Book* temp = head;
        Book* prev = nullptr;

        while (temp) {
            if (temp->getTitle() == title && temp->getAuthor() == author && temp->getYear() == year) {
                if (!prev) {
                    head = temp -> next;
                } else {
                    prev->next = temp->next;
                }

                delete temp;
                return;
            }
            prev = temp;
            temp = temp -> next;
        }

        cout<<"Book not found.\n";
    }

    //Method to Search Book.
    void searchBook(string& title) {
        if (!head) {
            cout<<"Library is empty.\n";
            return;
        }

        Book* temp = head;
        while (temp) {
            if (temp->getTitle() == title) {
                cout<<"Book found: "<<endl;
                cout<<"  Title: "<<temp->getTitle()<<endl;
                cout<<"  Author: "<<temp->getAuthor()<<endl;
                cout<<"  Year: "<<temp->getYear()<<endl;
                return;
            }
            temp = temp -> next;
        }

        cout<<"No Book found with this title...\n";
    }


    //Display all Books.
    void displayBooks() {
        if (!head) {
            cout<<"Library is empty.\n";
            return;
        }

        Book* temp = head;
        cout<<"Displaying Books in the Library.\n\n";
        while (temp) {
            cout << " Book:" << endl;
            cout << "   Title: " << temp->getTitle() << endl;
            cout << "   Author: " << temp->getAuthor() << endl;
            cout << "   Year: " << temp->getYear() << endl<<endl;
            temp = temp->next;
        }
    }
};


//Inheriting the User class.
class Student : public User{
private:
    Library library;

public:
    //Default Constructor.
    Student () : User() {
        setCredentials();
    };

    //Destructor.
    ~Student () = default;

    //Implement the pure virtual function login.
    bool login() override {
        return (username == "student" && password == "student123");
    };

    // Method to add a book to the library
    void addBook(const string& title, const string& author, const int& year) {
        library.returnBook(title, author, year);
    };

    //Additional Methods for Student Class.
    void borrowBook() {
        string title;
        string author;
        int year;

        cin.ignore();

        cout<<"Enter name of the Book: ";
        getline(cin, title);
        cout<<endl;

        if (title.empty()) {
            cout << "Title can't be empty." << endl;
            return;
        }

        cout<<"Enter name of the Author: ";
        getline(cin, author);
        cout<<endl;

        if (author.empty()) {
            cout << "Author name can't be empty." << endl;
            return;
        }

        cout<<"Enter the year of publication: ";
        cin>>year;
        cout<<endl;

        if (year< 1900 || year > 2024) {
            cout << "Year must be from 1900-2024." << endl;
            return;
        }

        library.borrowBook(title, author, year);
        cout<<"The Book has been Borrowed."<<endl;
    }

    void returnBook() {
        string title;
        string author;
        int year;

        cin.ignore();

        cout<<"Enter name of the Book: ";
        getline(cin, title);
        cout<<endl;

        if (title.empty()) {
            cout << "Title can't be empty." << endl;
            return;
        }

        cout<<"Enter name of the Author: ";
        getline(cin, author);
        cout<<endl;

        if (author.empty()) {
            cout << "Author name can't be empty." << endl;
            return;
        }

        cout<<"Enter the year of publication: ";
        cin>>year;
        cout<<endl;

        if (year< 1900 || year > 2024) {
            cout << "Year must be from 1900-2024." << endl;
            return;
        }

        library.returnBook(title, author, year);
        cout<<"The Book has been Returned."<<endl;
    }

    void searchBook() {
        string title;
        cin.ignore();
        
        cout<<"Enter title of the Book: ";
        getline(cin, title);

        if (title.empty()) {
            cout<<"Title can't be empty.\n";
            return;
        }

        library.searchBook(title);
    }

    void displayBooks() {
        library.displayBooks();
    }

    void displayProfile() {
        cout<<"Displaying User Profile..."<<endl;
        cout<<"  Username: "<<username<<endl;
        cout<<"  Password: "<<password<<endl;
    }
};

void displayMainMenu() {
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
    cout << "5. Display Profile Info" << endl;
    cout << "6. Return to Main Menu" << endl;
    cout << "7. Exit" << endl;
    cout << "---------------------------------------" << endl;
    cout << "Enter your choice: ";
};

int main() {
    loading();
    setColor(14, 0);

    //Creating an object of Student class.
    Student student;

    //Adding Some Books in the Library.
    student.addBook("The Alchemist", "Paulo Coelho", 1988);
    student.addBook("The Da Vinci Code", "Dan Brown", 2003);
    student.addBook("The Great Gatsby", "F. Scott Fitzgerald", 1925);
    student.addBook("The Catcher in the Rye", "J.D. Salinger", 1951);
    student.addBook("The Hobbit", "J.R.R. Tolkien", 1937);

    bool isLoggedin = student.login();

    if (!isLoggedin) {
        cout << "Login failed. Exiting program." << endl;
        return EXIT_FAILURE;
    }

    while (true) {
        displayMainMenu();
        int choice;
        cin>>choice;
        cout<<endl;

        switch (choice) {
            case 1:
                student.borrowBook();
            break;

            case 2:
                student.returnBook();
            break;

            case 3:
                student.searchBook();
            break;

            case 4:
                student.displayBooks();
            break;

            case 5:
                student.displayProfile();
            break;

            case 6:
                cout << "Returning to Main Menu..." << endl;
            break;

            case 7:
                cout << "Exiting program..." << endl;
            return EXIT_SUCCESS;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
        getch(); // To hold the screen until a key is pressed.
    }
}