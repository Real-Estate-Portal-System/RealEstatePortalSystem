#include "User.h"
#include "PropertyManager.h"
#include <iostream>
#include <fstream>
using namespace std;
//The Hash map to store user data
static ::unordered_map<string, User > users;

User::User() : isAdmin(false) {}
User::User(const string& username, const string& password,
    const string& fname, const string& lname, bool isAdmin) :
    username(username), password(password),
    fname(fname), lname(lname), isAdmin(isAdmin) {}

string User::getUsername()const {
    return username;
}
string User::getPassword()const {
    return password;
}
string User::getFname()const {
    return fname;
}
string User::getLname()const {
    return lname;
}
bool User::isAdminUser() const {
    return isAdmin;
}

void User::loadUserDataFromFile(const string& user_data) {
    ifstream inFile(user_data);
    if (!inFile) {
        // Error opening file
        cerr << "Error: Unable to open file '" << user_data << "' for reading." << std::endl;

        return;
    }
    string saved_username, saved_password, saved_fname, saved_lname;

    while (inFile >> saved_username >> saved_password >> saved_fname >> saved_lname) {
        users[saved_username] = User(saved_username, saved_password, saved_fname, saved_lname);
    }

    inFile.close();
}
void User::writeUserDataToFile(const string& user_data) {
    std::ofstream outFile(user_data);
    if (!outFile) {
        // Error opening file
        cerr << "File not found!" << endl;
        return;
    }

    for (const auto& pair : users) {
        const User& user = pair.second;
        outFile << user.getUsername() << '\t'
            << user.getPassword() << '\t'
            << user.getFname() << '\t'
            << user.getLname() << '\t' << endl;
    }

    outFile.close();
}
bool User::signup() {
    string username, password, hashpassword, fname, lname;
    bool isAdmin = false;

    cout << "Enter username: ";
    cin >> username;

    // Check if username already exists
    if (users.find(username) != users.end()) {
        system("cls");
        cout << "Username already exists. Please choose another username." << endl;
        return false;
    }

    cout << "Enter password: ";
    cin >> password;
    hashpassword = hash_djb2(password);

    cout << "Enter first name: ";
    cin >> fname;
    cout << "Enter last name: ";
    cin >> lname;

    users[username] = User(username, hashpassword, fname, lname, isAdmin);
    system("cls");
    cout << "Sign up successful, please login" << endl;
    return true;
}
bool User::login() {
    string username, password;

    cout << "Enter username: ";
    cin >> username;

    // Check if username exists
    if (users.find(username) == users.end()) {
        system("cls");
        cout << "User not found." << endl;
        welcome_page_user();
        return false;

    }

    cout << "Enter password: ";
    cin >> password;
    string hashedPassword = hash_djb2(password); // Hash the entered password

    // Check if password matches
    if (users[username].getPassword() == hashedPassword) {
        system("cls");
        cout << "Login successful!" << endl;
        User user = users[username];
        user.user_menu();
        return true;
    }
    else {
        system("cls");
        cout << "Incorrect password." << endl;
        welcome_page_user();
        return false;
    }
}
//Function that displays only User's accessed options
void User::user_menu() {
    PropertyManager manager;
    system("cls");
    cout << "Hello , @" << username << endl << endl;
    cout << "*************************" << endl << endl;
    cout << "1.Personal Info" << endl;
    cout << "2.Register Properties" << endl;
    cout << "3.Search for Properties" << endl;
    cout << "4.Compare Properties" << endl;
    cout << "5.Log out" << endl;

    int choices;
    cin >> choices;

    switch (choices) {
    case 1:
        system("cls");
        User::updateInfo(password, lname, lname);
        break;
    case 2: {
        system("cls");
        int propertyNumber, numberOfBedrooms;
        double marketValue, squareFootage, price;
        string builtYear, condition, street, city, state, type;

        cout << "Enter The Property Number: ";
        while (!(cin >> propertyNumber) || propertyNumber < 0 || cin.peek() != '\n' || cin.peek() == '.') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a non-negative integer for the Property Number: ";
        }

        cout << "Enter Property's Built Year: ";
        cin.ignore();
        getline(cin, builtYear);

        cout << "Enter Property's Number of Bedrooms: ";
        while (!(cin >> numberOfBedrooms) || numberOfBedrooms < 0 || cin.peek() != '\n' || cin.peek() == '.') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a non-negative integer for the Property Number: ";
        }

        cout << "Enter Property's Market Value: ";
        while (!(cin >> marketValue) || marketValue < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a non-negative number for the Market Value: ";
        }

        cout << "Enter Property's SquareFootage: ";
        while (!(cin >> squareFootage) || squareFootage < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a non-negative number for the SquareFootage: ";
        }

        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Property's Condition: ";
        getline(cin, condition);

        cout << "Enter Property's Street: ";
        getline(cin, street);
        cout << "Enter Property's City: ";
        getline(cin, city);
        cout << "Enter Property's State: ";
        getline(cin, state);

        cout << "Enter Property's Price: ";
        while (!(cin >> price) || price < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a non-negative number for the Price: ";
        }

        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Property's Type: ";
        getline(cin, type);

        manager.addProperty(propertyNumber, builtYear, numberOfBedrooms, marketValue, squareFootage,
            condition, street, city, state, price, type);
        cout << "**************************************************\n" << endl;
        user_menu();
        break;
    }
    case 3:
        system("cls");
        manager.searchProperty();
        cout << "**************************************************\n" << endl;
        break;
    case 4: system("cls");

        break;
    case 5:
        system("cls");
        welcome_page_user();

        break;
    default: {
        system("cls");
        cout << "Incorrect option" << endl;
        User::user_menu();
    }

    }
}

// Function to display user choices from the options provided above
/*void choices(const string& username) {

    int answer;
    cout << "Do you want to update info? " << endl;
    cout << "1: Yes " << endl;
    cout << "2: No " << endl;

    cin >> answer;
    switch (answer) {
    case 1:
        update_info(username);
        break;
    case 2:
        system("cls");
        user_menu(username);
        break;

    default: {
        system("cls");
        cout << "Invalid choice, try again!" << endl;
        choices(username);
    }
    }
}*/
bool User::updateInfo(const string& newPassword, const string& newFirstName, const string& newLastName) {
    if (newPassword.empty() && newFirstName.empty() && newLastName.empty()) {
        // No updates provided
        return false;
    }
    this->password = newPassword.empty() ? password : newPassword;
    this->fname = newFirstName.empty() ? fname : newFirstName;
    this->lname = newLastName.empty() ? lname : newLastName;
    return true;
}

void welcome_page_user() {
    

    int choice;
    bool exitFlag = false;
    
    while (!exitFlag) {

        cout << "Welcome to the User Management System" << endl;
        cout << "1. Sign Up" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cin >> choice;
        switch (choice) {
        case 1:
            // Sign Up
        {
            system("cls");
            User::signup();
            welcome_page_user();
            break;
        }
        
        case 2:
            // Login
        {
            system("cls");
            User::login();
            break;
        }

        
        case 3: {
            // Exit
            system("cls");
            exitFlag = true;
            // welcome_page();
            break;
        }
        default:
        {
            cout << "Invalid choice!" << endl;
            welcome_page_user();
        }
        }
    }
}
string hash_djb2(const  string& str) {
    unsigned long hash = 5381;
    for (char c : str) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return to_string(hash);
}
