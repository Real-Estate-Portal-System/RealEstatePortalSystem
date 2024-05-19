#pragma once // Preprocessor directive to ensure this header file is included only once during compilation
#ifndef USER_H // Preprocessor directive to check if USER_H macro is not defined
#define USER_H // Defines USER_H macro to prevent multiple inclusion of this header file

#include <string> // Including the string header file
#include <unordered_map> // Including the unordered_map header file
using namespace std; // Using the standard namespace

class User // Declaration of the User class
{
private: // Private access specifier for class members
    string username; // Variable to store the username
    string password; // Variable to store the password
    string fname; // Variable to store the first name
    string lname; // Variable to store the last name
    

public:
    // Constructor for User class
    User(); // Default constructor
    User(const string& username, const string& password,
        const string& fname, const string& lname); // Parameterized constructor

    // Getters
    string getUsername() const; // Getter for username
    string getPassword() const; // Getter for password
    string getFname() const; // Getter for first name
    string getLname() const; // Getter for last name
    void setPassword(const string& newPassword); // Setter for password
    void setFname(const string& newFname); // Setter for first name
    void setLname(const string& newLname); // Setter for last name
    

    // Load user data from file and populate the hash map
    static void loadUserDataFromFile(const string& user_data);

    // Write all the user data from the hash map to file
    static void writeUserDataToFile(const string& user_data);

    // Sign up a new user
    static bool signup();

    // User Login 
    static bool login();

    // User menu after log in
    void user_menu();

    // Update user info
    void user_personal_info(const string& username);
    bool updateInfo(const string& newPassword, const string& newFname, const string& newLname);

    // Counts the total number of users
    int countUsers();
};

// Main welcome page for user with signup and login options
void welcome_page_user();

// Update user info - Admin
bool update_user_info();

// Hash function
string hash_djb2(const string& str);

#endif // End of USER_H ifndef directive
