#include "PropertyManager.h" // Includes the header file for the PropertyManager class.
#include "User.h" // Includes the header file for the User class.
#include "Admin.h" // Includes the header file for the Admin class.
#include <iostream> // Includes the input/output stream library.
#include <iomanip> // Includes the input/output manipulators library for formatting.
#include <fstream> // Includes the file stream library for file input/output operations.
#include <sstream> // Includes the string stream library for string input/output operations.
#include <locale> // Includes the localization library for formatting numeric and monetary information.
#include <queue> // Includes the queue library for implementing queue data structure.

using namespace std;

// Stores approved properties
static std::unordered_map<int, Property> propertyMap;

// Additional member variables for tracking statistics
int searchCount;
static std::unordered_map<std::string, int> searchFrequency;

// Stores unapproved properties
static std::queue<Property> unApprovedProperties;

// Default constructor for PropertyManager
PropertyManager::PropertyManager() {
    searchCount = 0; // Initializes the search count to zero.
}


// Method to add a new property to the property map.
void PropertyManager::addProperty(int propertyNumber, const string& builtYear, int numberOfBedrooms,
    double marketValue, double squareFootage, const string& condition, const string& street,
    const string& city, const string& state, double price, const string& type) {

    // Check if the property number already exists in the propertyMap.
    if (propertyMap.find(propertyNumber) != propertyMap.end()) {
        system("cls");
        cout << "The Property Number " << propertyNumber << " Already Exists in the System." << endl;
    }
    else {
        // Add the property to the property Map.
        Property newProperty(propertyNumber, builtYear, numberOfBedrooms, marketValue, squareFootage,
            condition, street, city, state, price, type);
        propertyMap[propertyNumber] = newProperty;
        system("cls");
        cout << "Property with Property Number " << propertyNumber << " Added Successfully." << endl;
    }
}

// Method for users to add properties to the Queue for approval.
void PropertyManager::addUnApprovedProperty(int propertyNumber, const string& builtYear, int numberOfBedrooms, double marketValue,
    double squareFootage, const string& condition, const string& street,
    const string& city, const string& state, double price, const string& type) {

    // Create a temporary queue to hold unapproved properties while checking for duplicates.
    std::queue<Property> tempQueue;

    // Check if the property number already exists in the unapproved properties queue.
    bool propertyExists = false;
    while (!unApprovedProperties.empty()) {
        Property& property = unApprovedProperties.front();
        if (property.getPropertyNumber() == propertyNumber) {
            cout << "\nThe Property Number " << propertyNumber << " is already in the unapproved properties queue.\n" << endl;
            propertyExists = true;
            break;
        }
        tempQueue.push(property);
        unApprovedProperties.pop();
    }

    // Push back properties from the temporary queue to the original queue.
    while (!tempQueue.empty()) {
        unApprovedProperties.push(tempQueue.front());
        tempQueue.pop();
    }

    // If the property doesn't exist in the unapproved properties queue, print a message.
    if (!propertyExists) {
        cout << "\nThe Property Number " << propertyNumber << " Doesn't Exist in the System.Therefore," << endl;
    }

    // Check if the property number already exists in the propertyMap.
    if (propertyMap.find(propertyNumber) != propertyMap.end()) {
        system("cls");
        cout << "\nThe Property Number " << propertyNumber << " Already Exists in the System." << endl;
    }
    else {
        // Add the property to the unapproved properties queue.
        Property newProperty(propertyNumber, builtYear, numberOfBedrooms, marketValue, squareFootage,
            condition, street, city, state, price, type);
        unApprovedProperties.push(newProperty);
        cout << " The Property is Added Successfully To the List and Waiting Approval.\n" << endl;
    }
}

// Method for approving unapproved properties in the queue to the property list in the map.
void PropertyManager::approveProperties() {
    Property propertyToApprove;
    queue<Property> temp;

    // Check if the queue is empty.
    if (unApprovedProperties.empty()) {
        cout << "The Property Queue is Empty. Please wait until new properties are added." << endl;
    }
    else {
        while (!unApprovedProperties.empty()) {// While there are still properties in the queue.
            propertyToApprove = unApprovedProperties.front();// Pop the first property.
            displayPropertyDetails(propertyToApprove);// Display it.
            cout << "**************************************************\n" << endl;
            unApprovedProperties.pop();// Pop it out of the queue.
            cout << "Would you like to add this property to the Property List?"
                "(Yes: 1 / No : 2) or 3 to Exit : ";
            int choice;

            while (!(cin >> choice) || choice < 1 || choice > 3 || cin.peek() != '\n' || cin.peek() == '.') {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid choice. Please enter a number from 1 to 3: ";
            }

            if (choice == 1) {// Add the property to the list.
                system("cls");
                propertyMap[propertyToApprove.getPropertyNumber()] = propertyToApprove;
                cout << "Property with Property Number " << propertyToApprove.getPropertyNumber() << " added successfully." << endl;
            }
            else if (choice == 2) {// Push the property to a temporary queue.
                system("cls");
                cout << "Property with Property Number " << propertyToApprove.getPropertyNumber() << " not Approved!!" << endl;
                temp.push(propertyToApprove);
            }
            else {
                system("cls");
                cout << "Thanks for You time!!" << endl;
                break;
            }
        }
    }

    // Push back properties that were not approved back into the unapproved queue.
    while (!temp.empty()) {
        unApprovedProperties.push(temp.front());
        temp.pop();
    }
}


// Method to delete a property from the property map.
void PropertyManager::deleteProperty(int propertyNumber) {
    int choice;
    if (!propertyMap.empty()) {
        auto it = propertyMap.find(propertyNumber);
        if (it != propertyMap.end()) {
            Property pro = propertyMap.at(propertyNumber);
            propertyMap.erase(it);
            cout << "The Property with number " << propertyNumber << " has been deleted successfully." << endl;
            system("cls");
            cout << "Would you like to undo the deletion? Press Yes(1)/No(2): ";
            // User input validation.
            while (!(cin >> choice) || choice < 1 || choice > 2 || cin.peek() != '\n' || cin.peek() == '.') {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid choice. Please enter 1 or 2: ";
            }
            if (choice == 1) {
                propertyMap[propertyNumber] = pro;
                cout << "Deletion undone!!" << endl;
            }
        }
        else {
            cout << "The Property Number " << propertyNumber << " Does Not Exist in the Property List." << endl;
        }
    }
    else {
        cout << "Sorry, No Properties Currently Available in the Rental Portal System." << endl;
    }
}

// Method to display details of a property.
void PropertyManager::displayPropertyDetails(const Property& property) {
    cout << "\n\t\tProperty Details\n";
    cout << "Property Number: " << property.getPropertyNumber() << endl;
    cout << "Number of Bedrooms: " << property.getBedRoomNumber() << endl;
    cout << "Market Value: " << property.getMarketValue() << endl;
    cout << "Built Year: " << property.getYearBuilt() << endl;
    cout << "Square Footage: " << property.getSquareFootage() << endl;
    cout << "Condition: " << property.getConditionState() << endl;
    cout << "Price: $" << property.getPrice() << endl;
    cout << "Property Type: " << property.getPropertyType() << endl;
    cout << "Location: " << property.getPropertyLocation().Street << ", "
        << property.getPropertyLocation().City << ", "
        << property.getPropertyLocation().State << endl;
}

// Compare properties method.
void PropertyManager::compareProperties() {
    int numPropertiesToCompare;

    // Prompt the user to enter how many properties they want to compare.
    cout << "Enter the number of properties you want to compare (up to 4): ";
    // Validate the user input.
    while (!(cin >> numPropertiesToCompare) || numPropertiesToCompare < 2 || numPropertiesToCompare > 4 || cin.peek() != '\n' || cin.peek() == '.') {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid number of properties. Please enter a number between 2 and 4." << endl;
    }

    std::vector<int> propertyNumbers(numPropertiesToCompare);

    // Prompt the user to enter property numbers.
    cout << "Enter " << numPropertiesToCompare << " property numbers" << endl;
    for (int i = 0; i < numPropertiesToCompare; ++i) {
        cin >> propertyNumbers[i];
    }
    system("cls");
    // Display details of each property.
    vector<Property> propertiesToCompare;
    for (int i = 0; i < numPropertiesToCompare; ++i) {
        auto it = propertyMap.find(propertyNumbers[i]);
        if (it != propertyMap.end()) {
            propertiesToCompare.push_back(it->second);
        }
        else {
            
            cout << "Property with number " << propertyNumbers[i] << " not found." << endl;
        }
    }

    
    cout << "\n\t\t*****Performing Comparison Portal*****" << endl;

    for (int i = 0; i < propertiesToCompare.size(); ++i) {
        cout << "\n\t\t-----Property " << i + 1 << " Information Below-----\n\n" << endl;
        displayPropertyDetails(propertiesToCompare[i]);
        cout << "-------------------------------------------------" << endl;
    }

    // Compare market values.
    double minMarketValue = propertiesToCompare[0].getMarketValue();
    double maxMarketValue = propertiesToCompare[0].getMarketValue();
    for (int i = 1; i < propertiesToCompare.size(); ++i) {
        double marketValue = propertiesToCompare[i].getMarketValue();
        if (marketValue < minMarketValue) {
            minMarketValue = marketValue;
        }
        if (marketValue > maxMarketValue) {
            maxMarketValue = marketValue;
        }
    }

    cout << "Minimum Market Value: " << minMarketValue << endl;
    cout << "Maximum Market Value: " << maxMarketValue << "\n\n" << endl;
}

// Method to search for properties based on various criteria.
void PropertyManager::searchProperty() {
    int choice;
    system("cls");
    do {
        cout << "\n\t\tSearch Options:\n";
        cout << "\t\t1. By Location\n";
        cout << "\t\t2. By Price Range\n";
        cout << "\t\t3. By Bedrooms\n";
        cout << "\t\t4. By Property Type\n";
        cout << "\t\t5. By SquareFootage Range\n";
        cout << "\t\t6. Exit\n";

        cout << "Choose a search criterion: ";
        while (!(cin >> choice) || choice < 1 || choice > 6 || cin.peek() != '\n' || cin.peek() == '.') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter a number between 1 and 6: ";
        }

        switch (choice) {
        case 1: // Search by Location
        {
            system("cls");
            string location;
            cout << "Enter the location to search: ";
            cin.ignore();
            getline(cin, location);
            searchByLocation(location);
            searchFrequency[location]++; // Increment frequency for the location
        }
        break;

        case 2: // Search by Price Range
        {
            system("cls");
            double minPrice;
            double maxPrice;
            cout << "Enter the minimum price: ";
            while (!(cin >> minPrice) || minPrice < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a non-negative number: ";
            }

            cout << "Enter the maximum price: ";
            while (!(cin >> maxPrice) || maxPrice < minPrice) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number greater than " << minPrice << ": ";
            }

            searchByPriceRange(minPrice, maxPrice);
            searchFrequency["Price Range"]++; // Increment frequency for price range search
        }
        break;

        case 3: // Search by Bedrooms
        {
            system("cls");
            int minBedrooms;
            int maxBedrooms;
            cout << "Enter the minimum number of bedrooms: ";

            while (!(cin >> minBedrooms) || minBedrooms < 0 || cin.peek() != '\n' || cin.peek() == '.') {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a non-negative integer: ";
            }

            cout << "Enter the maximum number of bedrooms: ";

            while (!(cin >> maxBedrooms) || (maxBedrooms < 0 && maxBedrooms > minBedrooms) || cin.peek() != '\n' || cin.peek() == '.') {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a non-negative integer: ";
            }

            searchByBedrooms(minBedrooms, maxBedrooms);
            searchFrequency["Bedrooms"]++; // Increment frequency for bedrooms search
        }
        break;

        case 4: // Search by Property Type
        {
            system("cls");
            string type;
            cout << "Enter the property type to search: ";
            cin.ignore();
            getline(cin, type);
            searchByPropertyType(type);
            searchFrequency[type]++; // Increment frequency for property type search
        }
        break;

        case 5: { // Search by SquareFootage range
            system("cls");
            double minFootage;
            double maxFootage;
            cout << "Enter the minimum SquareFootage: ";
            while (!(cin >> minFootage) || minFootage < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a non-negative number: ";
            }

            cout << "Enter the maximum SquareFootage: ";
            while (!(cin >> maxFootage) || maxFootage < minFootage) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number greater than " << minFootage << ": ";
            }

            searchBysquareFootageRange(minFootage, maxFootage);
            searchFrequency["SquareFootage Range"]++; // Increment frequency for squareFootage range search
        }
              break;

        case 6:
            system("cls");
            cout << "Exiting search...\n";
            break;

        default:
            cout << "Please enter a valid option" << endl;
        }
       
       
    } while (choice != 6);
}

// Method to edit a property's details.
void PropertyManager::editProperty(int propertyNumber) {
    string condition; // New condition
    int numberOfBedrooms; // New number of bedrooms
    double newMarketValue; // New market value

    bool exitFlag = false;

    if (!propertyMap.empty()) {
        auto& properties = propertyMap;

        if (properties.find(propertyNumber) != properties.end()) {
            Property& foundProperty = properties.at(propertyNumber);

            while (!exitFlag) {
                int choice;
                cout << "\t\t\t****Property Editing Platform****" << endl;
                cout << "\n\t\t 1. Edit The Property's Number of Bedrooms" << endl;
                cout << "\t\t 2. Edit Condition of the Property" << endl;
                cout << "\t\t 3. Edit Market Value of the Property" << endl;
                cout << "\t\t 4. Exit\n" << endl;

                cout << "Enter choice To Execute: ";
                while (!(cin >> choice) || choice < 1 || choice > 4 || cin.peek() != '\n' || cin.peek() == '.') {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid choice. Please enter a number between 1 and 4: ";
                }

                switch (choice) {
                case 1: // Edit property's number of bedrooms
                    system("cls");
                    cout << "Enter the new Number of Bedrooms: ";
                    while (!(cin >> numberOfBedrooms) || numberOfBedrooms < 0 || cin.peek() != '\n' || cin.peek() == '.') {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter a non-negative integer: ";
                    }
                    foundProperty.setBedRoomNumber(numberOfBedrooms);
                    cout << "The number of Bedrooms Updated to " << foundProperty.getBedRoomNumber() << endl;
                    break;

                case 2: // Edit property's Condition
                    system("cls");
                    cout << "Enter the new Condition of the Property: ";
                    cin >> condition;
                    foundProperty.setConditionState(condition);
                    cout << "The State Condition of the Property updated to " << foundProperty.getConditionState() << endl;
                    break;

                case 3: // Edit property's Market Value
                    system("cls");
                    cout << "Enter the new Market Value of the Property: ";
                    while (!(cin >> newMarketValue) || newMarketValue < 0) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter a non-negative number: ";
                    }
                    foundProperty.setMarketValue(newMarketValue);
                    cout << "The Market Value of the Property Updated to " << foundProperty.getMarketValue() << endl;
                    break;

                case 4: // Exit the switch case when user enter choice 4
                    system("cls");
                    exitFlag = true;
                    cout << "Thank You for Your Time, Goodbye!!" << endl;
                    break;

                default:
                    cout << "Enter a valid option" << endl;
                }
            }
        }
        else {
            cout << "The Property Number " << propertyNumber << " Doesn't Exist in the Property System." << endl;
        }
    }
    else {
        cout << "Sorry, No Properties Currently Available in the Rental Portal System." << endl;
    }
}

// Method to calculate taxes for a property.
double PropertyManager::calculateTaxes(int propertyNumber) {
    if (propertyMap.empty()) {
        throw runtime_error("No properties currently available in the rental portal system.");
    }

    auto it = propertyMap.find(propertyNumber);
    if (it == propertyMap.end()) {
        throw invalid_argument("The property with property number " + to_string(propertyNumber) + " does not exist in the property system.");
    }

    const Property& foundProperty = it->second;

    // Calculate taxes based on property's market value, square footage.
    double taxRate = 0.0002; // Tax rate (0.02%)
    double taxes = foundProperty.getMarketValue() * taxRate * foundProperty.getSquareFootage();

    return taxes;
}

// Method to search for properties by location.
void PropertyManager::searchByLocation(const string& location) {
    int count = 0;

    // Iterate through property map to find properties matching the specified location.
    for (const auto& entry : propertyMap) {
        const Property& property = entry.second;
        if (property.getPropertyLocation().City == location) {
            displayPropertyDetails(property); // Display property details if found.
            ++count;
        }
    }

    // If no properties are found for the specified location, display a message.
    if (count == 0) {
        cout << "No properties found for the specified location.\n";
    }
}

// Method to search for properties within a price range.
void PropertyManager::searchByPriceRange(double minPrice, double maxPrice) {
    int count = 0;

    // Iterate through property map to find properties within the specified price range.
    for (const auto& entry : propertyMap) {
        const Property& property = entry.second;
        if (property.getPrice() >= minPrice && property.getPrice() <= maxPrice) {
            displayPropertyDetails(property); // Display property details if found.
            ++count;
        }
    }

    // If no properties are found within the specified price range, display a message.
    if (count == 0) {
        cout << "No properties found within the specified price range.\n";
    }
}

// Method to search for properties within a SquareFootage range.
void PropertyManager::searchBysquareFootageRange(double minFootage, double maxFootage) {
    int count = 0;

    // Iterate through property map to find properties within the specified SquareFootage range.
    for (const auto& entry : propertyMap) {
        const Property& property = entry.second;
        if (property.getSquareFootage() >= minFootage && property.getSquareFootage() <= maxFootage) {
            displayPropertyDetails(property); // Display property details if found.
            ++count;
        }
    }

    // If no properties are found within the specified SquareFootage range, display a message.
    if (count == 0) {
        cout << "No properties found within the specified SquareFootage range.\n";
    }
}

// Method to search for properties by number of bedrooms.
void PropertyManager::searchByBedrooms(int minBedrooms, int maxBedrooms) {
    int count = 0;

    // Iterate through property map to find properties within the specified number of bedrooms.
    for (const auto& entry : propertyMap) {
        const Property& property = entry.second;
        int bedrooms = property.getBedRoomNumber();
        if (bedrooms >= minBedrooms && bedrooms <= maxBedrooms) {
            displayPropertyDetails(property); // Display property details if found.
            ++count;
        }
    }

    // If no properties are found within the specified number of bedrooms, display a message.
    if (count == 0) {
        cout << "No properties found within the specified number of bedrooms.\n";
    }
}

// Method to search for properties by property type.
void PropertyManager::searchByPropertyType(const string& type) {
    int count = 0;

    // Iterate through property map to find properties of the specified type.
    for (const auto& entry : propertyMap) {
        const Property& property = entry.second;
        if (property.getPropertyType() == type) {
            displayPropertyDetails(property); // Display property details if found.
            ++count;
        }
    }

    // If no properties are found of the specified type, display a message.
    if (count == 0) {
        cout << "No properties found of the specified type.\n";
    }
}

// Method to get a property by its number.
Property* PropertyManager::getPropertyByNumber(int propertyNumber) {
    auto it = propertyMap.find(propertyNumber);
    if (it != propertyMap.end()) {
        return &(it->second); // Return pointer to property if found.
    }
    else {
        cout << "The property with number " << propertyNumber << " does not exist." << endl; // Display error message if property not found.
        return nullptr;
    }
}


// Method that generates reports.
void PropertyManager::generateReport() {

    // Initialize user and admin objects.
    User users;
    Admin admins;

    // Total number of properties.
    int totalProperties = propertyMap.size();
    // Total number of unapproved properties.
    int totalUnapprovedProperties = unApprovedProperties.size();
    // Total number of searches made.
    int totalSearches = calculateTotalSearches();
    // Total tax generated on all properties.
    double totalTaxRevenue = calculateTotalTaxRevenue();
    // Average market value of all properties.
    double averageMarketValue = calculateAverageMarketValue();
    // Total number of users.
    int totalUsers = users.countUsers();
    // Total number of admins.
    int totalAdmins = admins.countAdmins();
    // Initialize the percentage of the leading search.
    double percentageofmaxsearch = 0;

    // Leading search (search with the highest frequency).
    string leadingSearch;
    int leadingSearchCount = 0;
    for (const auto& search : searchFrequency) {
        if (search.second > leadingSearchCount) {
            leadingSearchCount = search.second;
            leadingSearch = search.first;
        }
    }
    // Percentage of leading search.
    percentageofmaxsearch = ((double)leadingSearchCount / (double)totalSearches) * 100;

    // Property Management Report.
    cout << "----- Property Management Report -----\n\n";

    cout << "The total number of users has grown to " << totalUsers << " users." << endl;
    cout << "The system has " << totalAdmins << " admin(s) who contribute to a successful user experience." << endl;
    cout << "The total number of properties has risen to " << totalProperties << " properties." << endl;
    cout << "The total number of Unapproved property(ies) is " << totalUnapprovedProperties << " property(ies)." << endl;
    cout << "The total number of searches across the platform has reached a groundbreaking " << totalSearches << " searches." << endl;
    cout << "The leading search, \"" << leadingSearch << "\", has amassed an outstanding " << leadingSearchCount << " searches." << endl;
    cout << "Total tax revenue generated: $" << fixed << setprecision(3) << totalTaxRevenue << ". This number is expected to grow with the addition of new properties into the system." << endl;
    cout << "Average market value of properties has settled at $" << setprecision(3) << averageMarketValue << "." << endl;
    cout << setprecision(2) << percentageofmaxsearch << "% of searches are related to \"" << leadingSearch << "\".\n\n" << endl;

}

// Method to calculate the total tax revenue on all properties in the property list.
double PropertyManager::calculateTotalTaxRevenue() {
    // Check if the property map is empty
    if (propertyMap.empty()) {
        return 0.0; // Return 0 if no properties exist
    }

    double totalTaxRevenue = 0.0;

    // Iterate through each property in the property map and calculate the tax revenue for each property
    for (const auto& entry : propertyMap) {
        const Property& property = entry.second;
        double propertyTax = calculateTaxes(property.getPropertyNumber());
        totalTaxRevenue += propertyTax; // Add the calculated tax revenue to the total tax revenue
    }

    return totalTaxRevenue; // Return the total tax revenue
}

// Method to calculate the total number of searches from the searchFrequency map.
int PropertyManager::calculateTotalSearches() const {
    // Check if the search frequency map is empty
    if (searchFrequency.empty()) {
        return 0; // Return 0 if no searches have been made
    }

    int totalSearches = 0;

    // Iterate through each entry in the search frequency map and sum up the number of searches
    for (auto const& entry : searchFrequency) {
        int search = entry.second;
        totalSearches += search; // Add the number of searches to the total searches
    }

    return totalSearches; // Return the total number of searches
}


// Method to calculate the average market value of all properties in the property list.
double PropertyManager::calculateAverageMarketValue() const{
    // Check if the property map is empty
    if (propertyMap.empty()) {
        return 0.0; // Return 0 if no properties exist
    }

    double totalMarketValue = 0.0;

    // Iterate through each property in the property map and sum up their market values
    for (const auto& entry : propertyMap) {
        const Property& property = entry.second;
        totalMarketValue += property.getMarketValue();
    }

    // Calculate the average market value by dividing the total market value by the number of properties
    double averageMarketValue = totalMarketValue/ propertyMap.size();

    return averageMarketValue; // Return the calculated average market value
}

// Method to handle admin's Property Management functionalities.
void PropertyManager::propertyManagerAdmin() {
    PropertyManager manager;
    Property property;
    bool exitFlag = false;

    // File paths for properties, searches, and unapproved properties
    string propertyData = "PropertyData.txt";
    string searchDataFile = "searchDataFile.txt";
    string unapprovedDataFile = "unapprovedDataFile.txt";

    // Read property data from file
    manager.readPropertyDataFromFile(propertyData);

    // Read searches data from file
    manager.readSearchDataFromFile(searchDataFile);

    // Read unapproved property data from file
    manager.readUnapprovedPropertiesFromFile(unapprovedDataFile);

    system("cls");
    cout << "\t\t***Welcome To The Property Manager PlatForm*** \n\n" << endl;

    while (!exitFlag) {
        int choice;
        cout << "\t\t1. Add A Property" << endl;
        cout << "\t\t2. Edit Property Details" << endl;
        cout << "\t\t3. Delete A Property" << endl;
        cout << "\t\t4. Calculate Property Tax" << endl;
        cout << "\t\t5. Display Property Details" << endl;
        cout << "\t\t6. Search for A Property" << endl;
        cout << "\t\t7. Generate Report" << endl;
        cout << "\t\t8. Approve New Properties" << endl;
        cout << "\t\t9. Exit Property Manager Platform\n" << endl;

        cout << "Please Enter Your Choice: ";
        while (!(cin >> choice) || choice < 1 || choice > 9 || cin.peek() != '\n' || cin.peek() == '.') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter a number between 1 and 9: ";
        }

        cout << "**************************************************\n" << endl;

        switch (choice) {

        case 1: {
            // Adding a new property
            int propertyNumber;
            int numberOfBedrooms;
            double marketValue;
            double squareFootage;
            double price;
            string builtYear;
            string condition;
            string street;
            string city;
            string state;
            string type;

            system("cls");
            cout << "Enter The Property Number: ";
            while (!(cin >> propertyNumber) || propertyNumber < 0 || cin.peek() != '\n' || cin.peek() == '.') {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a non-negative integer for the Property Number: ";
            }

            cout << "Enter Property's Built Year: ";
            cin.ignore();
            getline(cin, builtYear);

            cout << "Enter Property's Number of Bedrooms: ";
            while (!(cin >> numberOfBedrooms) || numberOfBedrooms < 0 || cin.peek() != '\n' || cin.peek() == '.') {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a non-negative integer for the Number of Bedrooms: ";
            }

            cout << "Enter Property's Market Value: ";
            while (!(cin >> marketValue) || marketValue < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a non-negative number for the Market Value: ";
            }

            cout << "Enter Property's Square Footage: ";
            while (!(cin >> squareFootage) || squareFootage < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a non-negative number for the Square Footage: ";
            }

            // Clear input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter Property's Condition: ";
            getline(cin, condition);

            cout << "Enter Property's Street: ";
            getline(cin, street);
            cout << "Enter Property's City: ";
            getline(cin, city);
            cout << "Enter Property's State: ";
            getline(cin, state);

            cout << "Enter Property's Price: ";
            while (!(cin >> price) || price < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a non-negative number for the Price: ";
            }

            // Clear input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter Property's Type: ";
            getline(cin, type);

            // Add the property
            manager.addProperty(propertyNumber, builtYear, numberOfBedrooms, marketValue, squareFootage,
                condition, street, city, state, price, type);
            cout << "**************************************************\n" << endl;
            break;
        }

        case 2: {
            // Editing property details
            system("cls");
            int propertyNumber;
            cout << "Enter the Property Number to edit: ";
            while (!(cin >> propertyNumber) || propertyNumber < 0 || cin.peek() != '\n' || cin.peek() == '.') {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a non-negative integer for the Property Number: ";
            }
            manager.editProperty(propertyNumber);
            cout << "**************************************************\n" << endl;
            break;
        }

        case 3: {
            // Deleting a property
            system("cls");
            int propertyNumber;
            cout << "Enter the Property Number to delete: ";
            while (!(cin >> propertyNumber) || propertyNumber < 0 || cin.peek() != '\n' || cin.peek() == '.') {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a non-negative integer for the Property Number: ";
            }
            manager.deleteProperty(propertyNumber);
            cout << "**************************************************\n" << endl;
            break;
        }

        case 4: {
            // Calculating property taxes
            system("cls");
            int propertyNumber;
            double taxes;
            cout << "Enter the Property Number to calculate taxes: ";
            while (!(cin >> propertyNumber) || propertyNumber < 0 || cin.peek() != '\n' || cin.peek() == '.') {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a non-negative integer for the Property Number: ";
            }
            try {
                taxes = manager.calculateTaxes(propertyNumber);
                cout << "The Property Taxes: $" << fixed << setprecision(3) << taxes << " Yearly" << endl;
            }
            catch (const system_error & e) {
                cerr << "Error: " << e.what() << endl;
            }
            cout << "**************************************************\n" << endl;
            break;
        }

        case 5: {
            // Displaying property details
            system("cls");
            int propertyNumber;
            cout << "Enter the Property Number to display details: ";
            while (!(cin >> propertyNumber) || propertyNumber < 0 || cin.peek() != '\n' || cin.peek() == '.') {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a non-negative integer for the Property Number: ";
            }
            Property const* myProperty = manager.getPropertyByNumber(propertyNumber);
            if (myProperty != nullptr) {
                manager.displayPropertyDetails(*myProperty);
                cout << "**************************************************\n" << endl;
            }
            break;
        }

        case 6: {
            // Searching for properties
            system("cls");
            manager.searchProperty();
            cout << "**************************************************\n" << endl;
            break;
        }

        case 7: {
            // Generating a report
            system("cls");
            manager.generateReport();
            cout << "**************************************************\n" << endl;
            break;
        }

        case 8: {
            // Approving new properties
            system("cls");
            manager.approveProperties();
            cout << "**************************************************\n" << endl;
            break;
        }

        case 9: {
            // Exiting Property Manager
            system("cls");
            exitFlag = true;
            cout << "Thanks for Your Time, Goodbye!!\n\n" << endl;
            cout << "**************************************************\n" << endl;
            // Write data to files before exiting
            manager.writePropertyDataToFile(propertyData); // Write property data back to property HashMap
            manager.writeSearchDataToFile(searchDataFile); // Write search data back to Search map
            manager.writeUnapprovedPropertiesToFile(unapprovedDataFile); // Write unapproved property data back to Queue
            break;
        }
        default:
            cout << "Enter a valid option" << endl;
        }
    }
}

// Method to handle user's property management functionalities.
void PropertyManager::propertyManagerUser() {
    system("cls");
    PropertyManager manager;
    Property property;
    bool exitFlag = false;

    // File paths for property data, searches data, and unapproved property data
    string propertyData = "PropertyData.txt";
    string searchDataFile = "searchDataFile.txt";
    string unapprovedDataFile = "unapprovedDataFile.txt";

    // Read property data from file
    manager.readPropertyDataFromFile(propertyData);

    // Read searches data from file
    manager.readSearchDataFromFile(searchDataFile);

    // Read unapproved property data from file
    manager.readUnapprovedPropertiesFromFile(unapprovedDataFile);

    cout << "\t\t***Welcome To The Property Manager PlatForm** \n\n" << endl;
    while (!exitFlag) {
        int choice;
        cout << "\t\tPress 1: To Add A Property List" << endl;
        cout << "\t\tPress 2: To Display Property" << endl;
        cout << "\t\tPress 3: To Search Property" << endl;
        cout << "\t\tPress 4: To Compare Up To 4 Properties" << endl;
        cout << "\t\tPress 5: To Check Monetary Tax On Your Property" << endl;
        cout << "\t\tPress 6: To Exit Property Manager\n" << endl;

        cout << "Please Enter Your Choice: ";
        while (!(cin >> choice) || choice < 1 || choice > 6 || cin.peek() != '\n' || cin.peek() == '.') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter a number between 1 and 6: ";
        }

        cout << "**************************************************\n" << endl;

        switch (choice) {

        case 1: {
            system("cls");
            // Adding a new property
            int propertyNumber;
            int numberOfBedrooms;
            double marketValue;
            double squareFootage;
            double price;
            string builtYear;
            string condition;
            string street;
            string city;
            string state;
            string type;

            // Input property details from user
            // Property number
            cout << "Enter The Property Number: ";
            while (!(cin >> propertyNumber) || propertyNumber < 0 || cin.peek() != '\n' || cin.peek() == '.') {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a non-negative integer for the Property Number: ";
            }

            // Built year
            cout << "Enter Property's Built Year: ";
            cin.ignore();
            getline(cin, builtYear);

            // Number of bedrooms
            cout << "Enter Property's Number of Bedrooms: ";
            while (!(cin >> numberOfBedrooms) || numberOfBedrooms < 0 || cin.peek() != '\n' || cin.peek() == '.') {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a non-negative integer for the Number of Bedrooms: ";
            }

            // Market value
            cout << "Enter Property's Market Value: ";
            while (!(cin >> marketValue) || marketValue < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a non-negative number for the Market Value: ";
            }

            // Square footage
            cout << "Enter Property's Square Footage: ";
            while (!(cin >> squareFootage) || squareFootage < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a non-negative number for the Square Footage: ";
            }

            // Condition
            cout << "Enter Property's Condition: ";
            cin.ignore();
            getline(cin, condition);

            // Address details
            cout << "Enter Property's Street: ";
            getline(cin, street);
            cout << "Enter Property's City: ";
            getline(cin, city);
            cout << "Enter Property's State: ";
            getline(cin, state);

            // Price
            cout << "Enter Property's Price: ";
            while (!(cin >> price) || price < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a non-negative number for the Price: ";
            }

            // Property type
            cout << "Enter Property's Type: ";
            cin.ignore();
            getline(cin, type);

            // Add unapproved property
            manager.addUnApprovedProperty(propertyNumber, builtYear, numberOfBedrooms, marketValue, squareFootage,
                condition, street, city, state, price, type);

            cout << "**************************************************\n" << endl;
            break;
        }

        case 2: {
            system("cls");
            // Displaying property details
            int propertyNumber;
            cout << "Enter the Property Number to display details: ";
            while (!(cin >> propertyNumber) || propertyNumber < 0 || cin.peek() != '\n' || cin.peek() == '.') {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a non-negative integer for the Property Number: ";
            }
            Property* myProperty = manager.getPropertyByNumber(propertyNumber);
            if (myProperty != nullptr) {
                manager.displayPropertyDetails(*myProperty);
                cout << "**************************************************\n" << endl;
            }
            break;
        }

        case 3:
            system("cls");
            // Searching for properties
            manager.searchProperty();
            cout << "**************************************************\n" << endl;
            break;

        case 4:
            system("cls");
            // Comparing properties
            manager.compareProperties();
            cout << "**************************************************\n" << endl;
            break;

        case 5:
            system("cls");
            // Calculating property taxes
            int propertyNumber;
            double taxes;
            cout << "Enter the Property Number to calculate taxes: ";
            while (!(cin >> propertyNumber) || propertyNumber < 0 || cin.peek() != '\n' || cin.peek() == '.') {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a non-negative integer for the Property Number: ";
            }
            try {
                taxes = manager.calculateTaxes(propertyNumber);
                cout << "The Property Taxes: $" << fixed << setprecision(3) << taxes << " Yearly" << endl;
            }
            catch (const system_error & e) {
                cerr << "Error: " << e.what() << endl;
            }
            cout << "**************************************************\n" << endl;
            break;

        case 6:
            system("cls");
            // Exiting Property Manager
            exitFlag = true;
            cout << "Thanks for Your Time, Goodbye!!\n\n" << endl;
            cout << "**************************************************\n" << endl;
            // Write data to files before exiting
            manager.writePropertyDataToFile(propertyData);
            manager.writeSearchDataToFile(searchDataFile);
            manager.writeUnapprovedPropertiesToFile(unapprovedDataFile);
            break;

        default:
            cout << "Enter a valid Option" << endl;
        }
    }
}

// Function to read property data from file
void PropertyManager::readPropertyDataFromFile(const string& propertyData) {
    ifstream inFile(propertyData);
    if (!inFile.is_open()) {
        cerr << "Error: Unable to open file for reading: " << propertyData << endl;
        return;
    }

    propertyMap.clear(); // Clear existing data before reading from file

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;

        // Split the line by '|'
        while (getline(ss, token, '|')) {
            tokens.push_back(token);
        }

        if (tokens.size() != 11) {
            cerr << "Error: Invalid data format in file: " << propertyData << endl;
            continue;
        }

        // Convert string data to appropriate types
        int propertyNumber = stoi(tokens[0]);
        int numberOfBedrooms = stoi(tokens[2]);
        double marketValue = stod(tokens[3]);
        double squareFootage = stod(tokens[4]);
        double price = stod(tokens[9]);

        // Construct Property object and insert into propertyMap
        Property property(propertyNumber, tokens[1], numberOfBedrooms, marketValue, squareFootage,
            tokens[5], tokens[6], tokens[7], tokens[8], price, tokens[10]);
        propertyMap[propertyNumber] = property;
    }

    inFile.close();
}

// Function to write property data to file
void PropertyManager::writePropertyDataToFile(const string& propertyData) {
    ofstream outFile(propertyData);
    if (!outFile.is_open()) {
        cerr << "Error: Unable to open file for writing: " << propertyData << endl;
        return;
    }

    for (const auto& entry : propertyMap) {
        const Property& property = entry.second;
        outFile << property.getPropertyNumber() << "|"
            << property.getYearBuilt() << "|"
            << property.getBedRoomNumber() << "|"
            << property.getMarketValue() << "|"
            << property.getSquareFootage() << "|"
            << property.getConditionState() << "|"
            << property.getPropertyLocation().Street << "|"
            << property.getPropertyLocation().City << "|"
            << property.getPropertyLocation().State << "|"
            << property.getPrice() << "|"
            << property.getPropertyType() << endl;
    }

    outFile.close();
}

// Function to write search data to file
void PropertyManager::writeSearchDataToFile(const string& searchDataFile) {
    ofstream outFile(searchDataFile);
    if (!outFile.is_open()) {
        cerr << "Error: Unable to open file for writing: " << searchDataFile << endl;
        return;
    }

    for (const auto& entry : searchFrequency) {
        outFile << entry.first << "|" << entry.second << endl;
    }

    outFile.close();
}

// Function to read search data from file
void PropertyManager::readSearchDataFromFile(const string& searchDataFile) {
    ifstream inFile(searchDataFile);
    if (!inFile.is_open()) {
        cerr << "Error: Unable to open file for reading: " << searchDataFile << endl;
        return;
    }

    searchFrequency.clear(); // Clear existing search frequency data before reading from file

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string key;
        int frequency;

        if (getline(ss, key, '|') && ss >> frequency) {
            searchFrequency[key] = frequency;
        }
        else {
            cerr << "Error: Invalid data format in file: " << searchDataFile << endl;
        }
    }

    inFile.close();
}

// Function to write unapproved properties to file
void PropertyManager::writeUnapprovedPropertiesToFile(const string& unapprovedDataFile) {
    ofstream outFile(unapprovedDataFile);
    if (!outFile.is_open()) {
        cerr << "Error: Unable to open file for writing: " << unapprovedDataFile << endl;
        return;
    }

    while (!unApprovedProperties.empty()) {
        const Property& property = unApprovedProperties.front();
        outFile << property.getPropertyNumber() << "|"
            << property.getYearBuilt() << "|"
            << property.getBedRoomNumber() << "|"
            << property.getMarketValue() << "|"
            << property.getSquareFootage() << "|"
            << property.getConditionState() << "|"
            << property.getPropertyLocation().Street << "|"
            << property.getPropertyLocation().City << "|"
            << property.getPropertyLocation().State << "|"
            << property.getPrice() << "|"
            << property.getPropertyType() << endl;

        unApprovedProperties.pop();
    }

    outFile.close();
}

// Function to read unapproved properties from file
void PropertyManager::readUnapprovedPropertiesFromFile(const string& unapprovedDataFile) {
    ifstream inFile(unapprovedDataFile);
    if (!inFile.is_open()) {
        cerr << "Error: Unable to open file for reading: " << unapprovedDataFile << endl;
        return;
    }

    // Clear existing unapproved properties before reading from file
    while (!unApprovedProperties.empty()) {
        unApprovedProperties.pop();
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;

        // Split the line by '|'
        while (getline(ss, token, '|')) {
            tokens.push_back(token);
        }

        if (tokens.size() != 11) {
            cerr << "Error: Invalid data format in file: " << unapprovedDataFile << endl;
            continue;
        }

        // Convert string data to appropriate types
        int propertyNumber = stoi(tokens[0]);
        int numberOfBedrooms = stoi(tokens[2]);
        double marketValue = stod(tokens[3]);
        double squareFootage = stod(tokens[4]);
        double price = stod(tokens[9]);

        // Construct Property object and push into unApprovedProperties queue
        Property property(propertyNumber, tokens[1], numberOfBedrooms, marketValue, squareFootage,
            tokens[5], tokens[6], tokens[7], tokens[8], price, tokens[10]);
        unApprovedProperties.push(property);
    }

    inFile.close();
}

