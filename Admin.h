#pragma once
#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <unordered_map>
using namespace std;

class Admin
{
private:
	string username;
	string password;
	string fname;
	string lname;
	bool isAdmin;

public:
	//Constractor for User class
	Admin();
	Admin(const string& username, const string& password,
		const string& fname, const string& lname, bool isAdmin = true);

	//Getters
	string getAdminUsername() const;
	string getAdminPassword() const;
	string getAdminFname() const;
	string getAdminLname() const;
	bool isAdminUser() const;

	// Load user data from file and populate the hash map
	static void loadAdminDataFromFile(const string& admin_data);

	// Write all the user data from the hash map to file
	static void writeAdminDataToFile(const string& admin_data);

	//Sign up a new user
	static bool signupAdmin();

	//User Login 
	static bool loginAdmin();
	//User menu after log in
	void admin_menu();
	//Update user info
	bool updateAdminInfo(const string& newPassword, const string& newFname, const string& newLname);
	//Admin creating a new admin
	void createNewAdmin();

};
void welcome_page_admin();

#endif


