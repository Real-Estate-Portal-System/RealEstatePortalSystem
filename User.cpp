#include "User.h" // Including the User header file
#include "welcome.h" // Including the welcome header file
#include "PropertyManager.h" // Including the PropertyManager header file
#include <iostream> // Including the iostream header file
#include <fstream> // Including the fstream header file
using namespace std; // Using the standard namespace

// The Hash map to store user data
static ::unordered_map<string, User> users;

User::User() : isAdmin(false) {} // Default constructor for User class
User::User(const string& username, const string& password,
    const string& fname, const string& lname, bool isAdmin) :
    username(username), password(password),
    fname(fname), lname(lname), isAdmin(isAdmin) {} // Parameterized constructor for User class

// Getters
string User::getUsername() const {
    return username;
}
string User::getPassword() const {
    return password;
}
string User::getFname() const {
    return fname;
}
string User::getLname() const {
    return lname;
}
bool User::isAdminUser() const {
    return isAdmin;
}

//Setters
void User::setPassword(const string& newPassword) {
    password = newPassword;
}
void User::setFname(const string& newFname) {
    fname = newFname;
}
void User::setLname(const string& newLname) {
    lname = newLname;
}

void User::loadUserDataFromFile(const string& user_data) {
    // Open file for reading
    ifstream inFile(user_data);
    if (!inFile) {
        // Error opening file
        cerr << "Error: Unable to open file '" << user_data << "' for reading." << std::endl;
        return;
    }

    // Variables to store user data from file
    string saved_username, saved_password, saved_fname, saved_lname;

    // Read data from file and populate the hash map
    while (inFile >> saved_username >> saved_password >> saved_fname >> saved_lname) {
        users[saved_username] = User(saved_username, saved_password, saved_fname, saved_lname);
    }

    // Close file
    inFile.close();
}

void User::writeUserDataToFile(const string& user_data) {
    // Open file for writing
    ofstream outFile(user_data);
    if (!outFile) {
        // Error opening file
        cerr << "File not found!" << endl;
        return;
    }

    // Write user data to file
    for (const auto& pair : users) {
        const User& user = pair.second;
        outFile << user.getUsername() << '\t'
            << user.getPassword() << '\t'
            << user.getFname() << '\t'
            << user.getLname() << '\t' << endl;
    }

    // Close file
    outFile.close();
}

bool User::signup() {
    // Variables for user data
    string username, password, hashpassword, fname, lname;
    bool isAdmin = false;

    // Input user data
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
    hashpassword = hash_djb2(password); // Hash the password

    cout << "Enter first name: ";
    cin >> fname;
    cout << "Enter last name: ";
    cin >> lname;

    // Create new user object and add to the hash map
    users[username] = User(username, hashpassword, fname, lname, isAdmin);
    system("cls");
    cout << "Sign up successful, please login" << endl;
    return true;
}

bool User::login() {
    // Variables for username and password
    string username, password;

    // Input username
    cout << "Enter username: ";
    cin >> username;

    // Check if username exists
    if (users.find(username) == users.end()) {
        system("cls");
        cout << "User not found." << endl;
        welcome_page_user();
        return false;
    }

    // Input password
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

// Function to display user menu after login
void User::user_menu() {
    PropertyManager manager;
    system("cls");
    bool exitFlag = false;

    // Display user menu options
    while (!exitFlag) {
        cout << "Hello, @" << username << endl << endl;
        cout << "\t************ USER MENU *************" << endl << endl;
        cout << "\t\t1. Personal Info" << endl;
        cout << "\t\t2. Property Management" << endl;
        cout << "\t\t3. Log out" << endl;

        int choices;
        cout << "Please Enter Your Choice: ";
        // Validate user input
        while (!(cin >> choices) || choices < 1 || choices > 3 || cin.peek() != '\n' || cin.peek() == '.') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter a number between 1 and 3: ";
        }

        // Switch case to handle user choices
        switch (choices) {
        case 1: {
            system("cls");
            user_personal_info(username);
            break;
        }
        case 2: {
            manager.propertyManagerUser();
            break;
        }
        case 3: {
            system("cls");
            exitFlag = true;
            cout << "Thanks for Your Time, Goodbye!!" << endl;
            break;
        }
        default:
            cout << "Enter a valid option" << endl;
        }
    }
}

// Function to display user's personal info for updating
void User::user_personal_info(const string& username) {
    // Display user information
    cout << "Username: " << username << '\t';
    cout << "First Name: " << fname << '\t';
    cout << "Last Name: " << lname << endl;

    int answer;
    cout << "\tDo you want to update information?" << endl;
    cout << "\t1: Yes" << endl;
    cout << "\t2: No" << endl;

    cout << "Please Enter Your Choice: ";
    // Validate user input
    while (!(cin >> answer) || answer < 1 || answer > 2 || cin.peek() != '\n' || cin.peek() == '.') {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice. Please enter 1 or 2: ";
    }

    // Switch case to handle user choices
    switch (answer) {
    case 1: {
        string newPassword, newFirstName, newLastName, hashpassword;

        cout << "Enter the new password: ";
        cin >> newPassword;
        hashpassword = hash_djb2(newPassword);

        cout << "Enter the new first name: ";
        cin >> newFirstName;

        cout << "Enter the new last name: ";
        cin >> newLastName;

        // Call updateInfo function with the collected input
        if (updateInfo(hashpassword, newFirstName, newLastName)) {
            system("cls");
            cout << "User information updated successfully!" << endl;
        }
        else {
            cout << "Failed to update user information. Please try again." << endl;
        }
        break;
    }
    case 2:
        system("cls");
        break;
    default: {
        system("cls");
        cout << "Invalid choice, please try again!" << endl;
        user_personal_info(username);
    }
    }
}


// Function to update user information
bool User::updateInfo(const string& newPassword, const string& newFirstName, const string& newLastName) {
    // Check if updates provided
    if (newPassword.empty() && newFirstName.empty() && newLastName.empty()) {
        // No updates provided
        return false;
    }

    // Update user information
    this->password = newPassword.empty() ? password : newPassword;
    this->fname = newFirstName.empty() ? fname : newFirstName;
    this->lname = newLastName.empty() ? lname : newLastName;
    users[username] = User(username, newPassword, newFirstName, newLastName, isAdmin);
    return true;
}

// Function to count total number of users
int User::countUsers() {
    int userCount = users.size();
    return userCount;
}

// Function for admin to update a particular user's info
bool update_user_info() {
    // Displaying the list of all users
    cout << "List of all users:" << endl;
    for (const auto& pair : users) {
        const User& user = pair.second;
        cout << "Username: " << user.getUsername() << endl;
        cout << "First Name: " << user.getFname() << endl;
        cout << "Last Name: " << user.getLname() << endl;
        cout << endl;
    }

    // Prompt for entering the username of the user to update
    string username;
    cout << "Enter the username of the user you want to update: ";
    cin >> username;

    // Check if the entered username exists
    if (users.find(username) != users.end()) {
        // Prompt for new information
        string newPassword, hashpassword, newFirstName, newLastName;
        cout << "Enter the new password: ";
        cin >> newPassword;
        hashpassword = hash_djb2(newPassword);
        cout << "Enter the new first name: ";
        cin >> newFirstName;
        cout << "Enter the new last name: ";
        cin >> newLastName;

        // Update user information
        users[username].setPassword(hashpassword);
        users[username].setFname(newFirstName);
        users[username].setLname(newLastName);

        cout << "User information updated successfully!" << endl;
        return true;
    }
    else {
        cout << "User not found." << endl;
        return false;
    }


}

// Main welcome page for users with signup and login options
void welcome_page_user() {
    int choice;
    bool exitFlag = false;

    // Display welcome page options
    while (!exitFlag) {
        cout << "\t\t**Welcome to the User Management System**\n" << endl;
        cout << "\t\t\t1. Sign Up" << endl;
        cout << "\t\t\t2. Login" << endl;
        cout << "\t\t\t3. Exit\n" << endl;

        cout << "Please Enter Your Selection: ";
        // Validate user input
        while (!(cin >> choice) || choice < 1 || choice > 3 || cin.peek() != '\n' || cin.peek() == '.') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please select an option between 1 and 3: ";
        }

        // Switch case to handle user choices
        switch (choice) {
        case 1: {
            system("cls");
            User::signup();
            welcome_page_user();
            break;
        }
        case 2: {
            system("cls");
            User::login();
            break;
        }
        case 3: {
            // Exit
            system("cls");
            exitFlag = true;
            cout << "Thank you for using the User Management System. Goodbye!" << endl;
            welcome_page();
            break;
        }
        default: {
            cout << "Invalid choice!" << endl;
            welcome_page_user();
        }
        }
    }
}

// Function used to encrypt users' and admins' passwords
string hash_djb2(const string& str) {
    unsigned long hash = 5381;
    for (char c : str) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return to_string(hash);
}
