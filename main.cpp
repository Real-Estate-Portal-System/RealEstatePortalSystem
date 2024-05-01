#include "User.h"
#include "Admin.h"
#include "PropertyManager.h"
#include <iostream>

using namespace std;

void welcome_page();


int main() {

    
    string user_data = "user_data.txt";
    string admin_data = "admin_data.txt";

    User::loadUserDataFromFile(user_data);
    Admin::loadAdminDataFromFile(admin_data);
    

    welcome_page();

    User::writeUserDataToFile(user_data);
    Admin::writeAdminDataToFile(admin_data);
   
    return 0;
}
void welcome_page() {
   

    cout << "\t\t\t***Welcome to the Real Estate Portal System***\n" << endl;
    cout << "\t\t\t1. User" << endl;
    cout << "\t\t\t2. Admin" << endl;
    cout << "\t\t\t3. Exit" << endl;

    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
        // Sign Up
        system("cls");
        welcome_page_user();
        break;
    case 2:
        // Login

        system("cls");
        welcome_page_admin();
        break;
    case 3:
        system("cls");
        break;
    default:
    {
        cout << "Invalid choice!" << endl;
        welcome_page();
    }
    }
}

