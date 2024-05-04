#pragma once
#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <unordered_map>

using namespace std;

class Admin
{
private:
    string username; // Username of the admin
    string password; // Password of the admin
    string fname; // First name of the admin
    string lname; // Last name of the admin
    bool isAdmin; // Flag indicating if the admin is an administrator

public:
    // Default constructor for the Admin class
    Admin();

    // Parameterized constructor for the Admin class
    Admin(const string& username, const string& password,
        const string& fname, const string& lname, bool isAdmin = true);

    // Getter for admin username
    string getAdminUsername() const;

    // Getter for admin password
    string getAdminPassword() const;

    // Getter for admin first name
    string getAdminFname() const;

    // Getter for admin last name
    string getAdminLname() const;

    // Getter for admin status
    bool isAdminUser() const;

    // Load admin data from file and populate the hash map
    static void loadAdminDataFromFile(const string& admin_data);

    // Write all the admin data from the hash map to file
    static void writeAdminDataToFile(const string& admin_data);

    // Sign up a new admin
    static bool signupAdmin();

    // Admin Login
    static bool loginAdmin();

    // Admin menu after login
    void admin_menu();

    // Update admin info
    void admin_personal_info(const string& username);

    // Admin updates his personal info
    bool admin_updateInfo(const string& newPassword, const string& newFname, const string& newLname);

    // Admin creates a new admin
    void createNewAdmin();

    // User management functions
    void user_management();

    // Function to count total number of admins
    int countAdmins();
};

// Main welcome page for admins with signup and login options
void welcome_page_admin();

#endif
