#pragma once
#ifndef USER_H
#define USER_H

#include <string>
#include <unordered_map>
using namespace std;

class User
{
private:
	string username;
	string password;
	string fname;
	string lname;
	bool isAdmin;

public:
	//Constractor for User class
	User();
	User(const string& username, const string& password,
		const string& fname, const string& lname, bool isAdmin = false);
	//Getters
	string getUsername() const;
	string getPassword() const;
	string getFname() const;
	string getLname() const;
	void setPassword(const string& newPassword);
	void setFname(const string& newFname);
	void setLname(const string& newLname);
	bool isAdminUser() const;

	// Load user data from file and populate the hash map
	static void loadUserDataFromFile(const string& user_data);

	// Write all the user data from the hash map to file
	static void writeUserDataToFile(const string& user_data);

	//Sign up a new user
	static bool signup();

	//User Login 
	static bool login();
	//User menu after log in
	void user_menu();
	//Update user info
	void user_personal_info(const string& username);
	bool updateInfo(const string& newPassword, const string& newFname, const string& newLname);
	//counts the total number of users
	int countUsers();


};
//Main welcome page for user with signup and login options
void welcome_page_user();
//Update user info - Admin
bool update_user_info();
string hash_djb2(const string& str);
#endif
