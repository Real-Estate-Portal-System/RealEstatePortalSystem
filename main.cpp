#include "User.h"
#include "Admin.h"
#include "welcome.h"
#include "PropertyManager.h"
#include <iostream>

using namespace std;

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


 