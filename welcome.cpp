#include "welcome.h"
#include "User.h"
#include "Admin.h"

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
        exit;
        break;
    default:
    {
        cout << "Invalid choice!" << endl;
        welcome_page();
    }
    }
}
