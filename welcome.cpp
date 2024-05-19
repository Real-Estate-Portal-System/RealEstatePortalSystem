#include "welcome.h" // Including the header file for the welcome module
#include "User.h" // Including the header file for the User module
#include "Admin.h" // Including the header file for the Admin module

// Function to display the welcome page menu
void welcome_page() {
    // Displaying the welcome message and menu options
    cout << "\t***WELCOME TO THE REAL ESTATE PORTAL SYSTEM***\n" << endl;
    cout << "\t\t\t1. USER " << endl;
    cout << "\t\t\t2. ADMIN " << endl;
    cout << "\t\t\t3. EXIT  \n\n" << endl;

    cout << "\n\n\tWelcome to our platform, offering an array of amazing functions for both Admins and Users.\n";
    cout << "\tWith our system, you can efficiently manage profiles and properties,\n"
            "\taccessing administrative tools and property listings management.\n";
    cout << "\n\n\t\"Real estate is about the safest investment in the world.\"\n\n" << endl;


    int choice;

    // Prompting the user for input and validating the choice
    cout << "Please Enter Your Choice: ";
    while (!(cin >> choice) || choice < 1 || choice > 3 || cin.peek() != '\n' || cin.peek() == '.') {
        cin.clear(); // Clearing the input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignoring any invalid input
        cout << "Invalid choice. Please enter a number between 1 and 3: ";
    }

    // Switch case to handle user's choice
    switch (choice) {
    case 1:
        // If user chooses option 1 (USER), redirect to user sign up function
        system("cls"); // Clearing the screen
        welcome_page_user();
        break;
    case 2:
        // If user chooses option 2 (ADMIN), redirect to admin login function
        system("cls"); // Clearing the screen
        welcome_page_admin();
        break;
    case 3: {
        // If user chooses option 3 (EXIT), display goodbye message and return
        system("cls");
        cout << "\n\n\tThank you for your time, dear user!\n\tLooking forward to seeing you again soon. \n\tFarewell for now!\n\n" << endl;
        break;
    }
    default:
        // Handling any invalid input by displaying a message and recursively calling welcome_page()
        cout << "Invalid choice!" << endl;
        welcome_page();
    }
}
