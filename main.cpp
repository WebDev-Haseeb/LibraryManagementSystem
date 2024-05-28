#include <iostream>
using namespace std;

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


//Derived Student Class.
class Student : public User {
public:
    //Default Constructor.
    Student () : User() {};

    //Destructor.
    ~Student() override = default;

    //Implement the pure virtual function login.
    bool login() override {
        return (username == "user" && password == "password");
    };
};


//Derived Librarian Class.
class Librarian : public User {
public:
    //Default Constructor.
    Librarian () : User() {};

    //Destructor.
    ~Librarian() override = default;

    //Implement the pure virtual function login.
    bool login() override {
        return (username == "user" && password == "password");
    };
};


int main() {
    cout << "\n\n\n===================================================" << endl;
    cout << "       Welcome to the Library Management System!" << endl;
    cout << "=====================================================\n" << endl;

    cout<<"How do you want to login?"<<endl;
    cout<<"  1. Student"<<endl;
    cout<<"  2. Librarian"<<endl;
    cout<<"  3. Exit"<<endl;

    int choice;
    cout<<"Enter your choice: ";
    cin>>choice;

    switch (choice) {
        case 1: {
            Student student;
            for (int i = 0; i < 3; i++) {
                student.setCredentials();
                if (student.login()) {
                    cout << "Login Successful!" << endl;
                    break;
                } else {
                    cout << "Login Failed! Please try again.\nRemaining Attempts: "<<(2-i) << endl;
                }
            }
            break;
        }
        case 2: {
            Librarian librarian;
            for (int i = 0; i < 3; i++) {
                librarian.setCredentials();
                if (librarian.login()) {
                    cout << "Login Successful!" << endl;
                    break;
                } else {
                    cout << "Login Failed! Please try again.\nRemaining Attempts: "<<(2-i) << endl;
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
};