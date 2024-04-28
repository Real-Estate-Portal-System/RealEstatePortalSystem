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


    PropertyManager manager;
    string  propertyData = "PropertyData.txt";
    manager.readPropertyDataFromFile(manager.propertyMap, propertyData);
    

    welcome_page();

    User::writeUserDataToFile(user_data);
    Admin::writeAdminDataToFile(admin_data);
    //manager.writePropertyDataToFile(manager.propertyMap, propertyData);
    return 0;
}
void welcome_page() {
    /*PropertyManager manager;
    string  propertyData = "PropertyData.txt";
    manager.readPropertyDataFromFile(manager.propertyMap, propertyData);*/

    cout << "Welcome to the User Management System" << endl;
    cout << "1. User" << endl;
    cout << "2. Admin" << endl;
    cout << "3. Exit" << endl;

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



