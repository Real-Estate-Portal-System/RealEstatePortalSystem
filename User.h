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
	bool updateInfo(const string& newPassword, const string& newFname, const string& newLname);


};
void welcome_page_user();
string hash_djb2(const string& str);
#endif
