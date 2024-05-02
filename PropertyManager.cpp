#include "PropertyManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <locale> 
#include<queue>


using namespace std;

static std::unordered_map<int, Property> propertyMap;
// Additional member variables for tracking statistics
int searchCount;
static std::unordered_map<std::string, int> searchFrequency;
//Stores Unapproved properties
static std::queue<Property> unApprovedProperties;

// Default constructor
PropertyManager::PropertyManager() {
    searchCount = 0;
}



// Method to add a new property to the property map
void PropertyManager::addProperty(int propertyNumber, const string& builtYear, int numberOfBedrooms, double marketValue,
    double squareFootage, const string& condition, const string& street,
    const string& city, const string& state, double price, const string& type) {

    //We Check if the property number already exists in the propertyMap
    if (propertyMap.find(propertyNumber) != propertyMap.end()) {
        cout << "The Property Number " << propertyNumber << " Already Exists in the System" << endl;
    }
    else {
        // We Add the property to the property Map
        Property newProperty(propertyNumber, builtYear, numberOfBedrooms, marketValue, squareFootage,
            condition, street, city, state, price, type);
        propertyMap[propertyNumber] = newProperty;
        cout << "Property with Property Number " << propertyNumber << " Added Successfully" << endl;
    }
}

// Method for users to add propert(y)ies to the Queue for approval. 

void PropertyManager::addUnApprovedProperty(int propertyNumber, const string& builtYear, int numberOfBedrooms, double marketValue,
    double squareFootage, const string& condition, const string& street,
    const string& city, const string& state, double price, const string& type) {

    // We Create a temporary queue to hold unapproved properties while checking for duplicates
    std::queue<Property> tempQueue;

    // We Check if the property number already exists in the unapproved properties queue
    bool propertyExists = false;
    while (!unApprovedProperties.empty()) {
        Property& property = unApprovedProperties.front();
        if (property.getPropertyNumber() == propertyNumber) {
            cout << "The Property Number " << propertyNumber << " is already in the unapproved properties queue." << endl;
            propertyExists = true;
            break;
        }
        tempQueue.push(property);
        unApprovedProperties.pop();
    }

    //We  Push back properties from the temporary queue to the original queue
    while (!tempQueue.empty()) {
        unApprovedProperties.push(tempQueue.front());
        tempQueue.pop();
    }

    // If the property doesn't exist in the unapproved properties queue,And we print a message
    if (!propertyExists) {
        cout << "The Property Number " << propertyNumber << " Doesn't Exist in the System" << endl;
    }

    //We Check if the property number already exists in the propertyMap
    if (propertyMap.find(propertyNumber) != propertyMap.end()) {
        cout << "The Property Number " << propertyNumber << " Already Exists in the System" << endl;
    }
    else {
        // We Add the property to the unapproved properties queue
        Property newProperty(propertyNumber, builtYear, numberOfBedrooms, marketValue, squareFootage,
            condition, street, city, state, price, type);
        unApprovedProperties.push(newProperty);
        cout << "Property with Property Number " << propertyNumber << " Added Successfully To the List and Waiting Approval" << endl;
    }
}


// Method for approving unapproved properties in the queue to the property list in the map
void PropertyManager::approveProperties() {
    Property propertyToApprove;
    queue<Property> temp;

    // we check if the queue is empty.
    if (unApprovedProperties.empty()) {
        cout << "The Property Queue is Empty. Please wait until new properties are added." << endl;
    }
    else {
        while (!unApprovedProperties.empty()) {// while there are still properties in the queue
            propertyToApprove = unApprovedProperties.front();// pop the first property
            displayPropertyDetails(propertyToApprove);// display it
            cout << "**************************************************\n" << endl;
            unApprovedProperties.pop();// pop it out of the queue
            cout << "Would you like to add this property to the Property List? (Yes: 1 / No: 2): ";
            int choice;
         
            while (!(cin >> choice) || choice < 1 || choice > 2 || cin.peek() != '\n' || cin.peek() == '.') {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid choice. Please enter a number between 1 and 2: ";
            }

            if (choice == 1) {// we add the property to the list
                propertyMap[propertyToApprove.getPropertyNumber()] = propertyToApprove;
                cout << "Property with Property Number " << propertyToApprove.getPropertyNumber() << " added successfully." << endl;
            }
            else if (choice == 2) {// we push  the property to a temporary queue
                temp.push(propertyToApprove);
            }
        }
    }


    // we Push back properties that were not approved back into the unapproved queue
    while (!temp.empty()) {
        unApprovedProperties.push(temp.front());
        temp.pop();
    }
}



// Method to delete a property from the property map
void PropertyManager::deleteProperty(int propertyNumber) {
    int choice;
    if (!propertyMap.empty()) {
        auto it = propertyMap.find(propertyNumber);
        if (it != propertyMap.end()) {
            Property pro = propertyMap.at(propertyNumber);
            propertyMap.erase(it);
            cout << "The Property with number " << propertyNumber << " has been deleted Successfully." << endl;
            cout << "Wound you like to Undo Deletion? Press Yes(1)/No(2): ";
            while (!(cin >> choice) || choice < 1 || choice > 2 || cin.peek() != '\n' || cin.peek() == '.') {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid choice. Please enter a number between 1 and 2: ";
            }
            if (choice == 1) {
                propertyMap[propertyNumber] = pro;
                cout << "Deletion Undone!!" << endl;
            }
        }
        else {
            cout << "The Property Number " << propertyNumber << " Does Not Exist in the Property List" << endl;
        }
    }
    else {
        cout << "Sorry, No Properties Currently Available in the Rental Portal System." << endl;
    }
}



// Method to display details of a property
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


// compare properties method.

void PropertyManager::compareProperties() {
    int numPropertiesToCompare;

    //We prompt the user to enter how many properties they want to compare
    cout << "Enter the number of properties you want to compare (up to 4): ";
    cin >> numPropertiesToCompare;

    if (numPropertiesToCompare <= 0 || numPropertiesToCompare > 4) {
        cout << "Invalid number of properties. Please enter a number between 1 and 4." << endl;
        return;
    }

    std::vector<int> propertyNumbers(numPropertiesToCompare);

    // Prompt the user to enter property numbers
    cout << "Enter " << numPropertiesToCompare << " property numbers" << endl;
    for (int i = 0; i < numPropertiesToCompare; ++i) {
        cin >> propertyNumbers[i];
    }

    // Display details of each property
    std::vector<Property> propertiesToCompare;
    for (int i = 0; i < numPropertiesToCompare; ++i) {
        auto it = propertyMap.find(propertyNumbers[i]);
        if (it != propertyMap.end()) {
            propertiesToCompare.push_back(it->second);
        }
        else {
            cout << "Property with number " << propertyNumbers[i] << " not found." << endl;
        }
    }


    cout << "\n\t\tPerforming comparison" << endl;
    for (int i = 0; i < propertiesToCompare.size(); ++i) {
        std::cout << "\t\tProperty " << i + 1 << " Details" << endl;
        displayPropertyDetails(propertiesToCompare[i]);
        cout << "-----------------------" << endl;
    }

    // Compare market values
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
    cout << "Maximum Market Value: " << maxMarketValue << endl;
}




// Method to search for properties based on various criteria
void PropertyManager::searchProperty() {
    int choice;

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
            cout << "Invalid choice. Please enter a number between 1 and 5: ";
        }

        switch (choice) {
        case 1: // Search by Location
        {
            string location;
            cout << "Enter the location to search: ";
            cin.ignore();
            getline(cin, location);
            searchByLocation(location);
            searchFrequency[location]++; // Increment frequency for the location
            //searchCount++;
        }
        break;

        case 2: // Search by Price Range
        {
            double minPrice, maxPrice;
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
            //searchCount++;
        }
            break;
        
        case 3: // Search by Bedrooms
        {
            int minBedrooms, maxBedrooms;
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
            //searchCount++;
        }
        break;


        case 4: // Search by Property Type
        {
            string type;
            cout << "Enter the property type to search: ";
            cin.ignore();
            getline(cin, type);
            searchByPropertyType(type);
            searchFrequency[type]++; // Increment frequency for property type search
            //searchCount++;
        }
        break;


        case 5: {// search by SquareFootage range
            double minFootage, maxFootage;
            cout << "Enter the minimum SquareFootage: ";
            while (!(cin >> minFootage) || minFootage < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a non-negative number: ";
            }

            cout << "Enter the maximum price: ";
            while (!(cin >> maxFootage) || maxFootage < minFootage) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number greater than  " << minFootage << ": ";
            }

            searchBysquareFootageRange(minFootage, maxFootage);
            searchFrequency["SquareFootage Range"]++; // Increment frequency for squareFootage range search
            //searchCount++;

        }
              break;

        case 6:
            cout << "Exiting search...\n";
            break;
        }
    } while (choice != 6);
}



// Method to edit a property's details
void PropertyManager::editProperty(int propertyNumber) {
    string condition; // new condition
    int numberOfBedrooms; // new number of bedrooms
    double newMarketValue; // new market value

    bool exitFlag = false;

    if (!propertyMap.empty()) {
        auto& properties = propertyMap;

        if (properties.find(propertyNumber) != properties.end()) {
            Property& foundProperty = properties.at(propertyNumber);

            while (!exitFlag) {
                int choice;
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
                    cout << "Enter the new Condition of the Property: ";
                    cin >> condition;
                    foundProperty.setConditionState(condition);
                    cout << "The State Condition of the Property updated to " << foundProperty.getConditionState() << endl;
                    break;

                case 3: // Edit property's Market Value
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
                    exitFlag = true;
                    cout << "Thank You for Your Time, Goodbye!!" << endl;
                    break;
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



// Method to calculate taxes for a property
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
    double taxRate = 0.02; // Example tax rate (2%)
    double taxes = foundProperty.getMarketValue() * taxRate * foundProperty.getSquareFootage();

    return taxes;
}



// Method to search for properties by location
void PropertyManager::searchByLocation(const string& location) {
    int count = 0;

    for (const auto& entry : propertyMap) {
        const Property& property = entry.second;
        if (property.getPropertyLocation().City == location) {
            displayPropertyDetails(property);
            ++count;
        }
    }

    if (count == 0) {
        cout << "No properties found for the specified location.\n";
    }
}

// Method to search for properties within a price range
void PropertyManager::searchByPriceRange(double minPrice, double maxPrice) {
    int count = 0;

    for (const auto& entry : propertyMap) {
        const Property& property = entry.second;
        if (property.getPrice() >= minPrice && property.getPrice() <= maxPrice) {
            displayPropertyDetails(property);
            ++count;
        }
    }

    if (count == 0) {
        cout << "No properties found within the specified Price range.\n";
    }
}

// Method to search for properties within a SquareFootage range

void PropertyManager::searchBysquareFootageRange(double minFootage, double maxFootage) {
    int count = 0;

    for (const auto& entry : propertyMap) {
        const Property& property = entry.second;
        if (property.getSquareFootage() >= minFootage && property.getSquareFootage() <= maxFootage) {
            displayPropertyDetails(property);
            ++count;
        }
    }

    if (count == 0) {
        cout << "No properties found within the specified SquareFootage range.\n";
    }

}





// Method to search for properties by number of bedrooms
void PropertyManager::searchByBedrooms(int minBedrooms, int maxBedrooms) {
    int count = 0;

    for (const auto& entry : propertyMap) {
        const Property& property = entry.second;
        int bedrooms = property.getBedRoomNumber();
        if (bedrooms >= minBedrooms && bedrooms <= maxBedrooms) {
            displayPropertyDetails(property);
            ++count;
        }
    }

    if (count == 0) {
        cout << "No properties found within the specified number of bedrooms.\n";
    }
}

// Method to search for properties by property type
void PropertyManager::searchByPropertyType(const string& type) {
    int count = 0;

    for (const auto& entry : propertyMap) {
        const Property& property = entry.second;
        if (property.getPropertyType() == type) {
            displayPropertyDetails(property);
            ++count;
        }
    }

    if (count == 0) {
        cout << "No properties found of the specified type.\n";
    }
}

// Method to get a property by its number
Property* PropertyManager::getPropertyByNumber(int propertyNumber) {
    auto it = propertyMap.find(propertyNumber);
    if (it != propertyMap.end()) {
        return &(it->second);
    }
    else {
        cout << "The property with number " << propertyNumber << " does not exist." << endl;
        return nullptr;
    }
}

// Method that generates reports 

void PropertyManager::generateReport() {
    // Total number of properties added
    int totalProperties = propertyMap.size();

    // Total number of searches made
    int totalSearches = calculateTotalSearches();
    double totalTaxRevenue = calculateTotalTaxRevenue();
    double averageMarketValue = calculateAverageMarketValue();
    double percentageofmaxsearch = 0;


    // Leading search (search with the highest frequency)
    string leadingSearch;
    int leadingSearchCount = 0;
    for (const auto& search : searchFrequency) {
        if (search.second > leadingSearchCount) {
            leadingSearchCount = search.second;
            leadingSearch = search.first;
        }
    }

    percentageofmaxsearch = ((double)leadingSearchCount / (double)totalSearches) * 100;

    cout << "----- Property Management Report -----" << endl;
    cout << "Total Properties Added: " << totalProperties << endl;
    cout << "Total Searches Made: " << totalSearches << endl;
    cout << "Leading Search: " << leadingSearch << " (" << leadingSearchCount << " times)" << endl;
    cout << "Total Tax Revenue Generated: $" << totalTaxRevenue << endl;
    cout << "Average Market Value of Properties: $" << averageMarketValue << endl;
    cout << percentageofmaxsearch << "% of searches are " << leadingSearch << " Search" << endl;
}

// method to calculate the total Tax revenue on all properties in the Property List

double PropertyManager::calculateTotalTaxRevenue() {
    if (propertyMap.empty()) {
        return 0.0;
    }

    double totalTaxRevenue = 0.0;

    for (const auto& entry : propertyMap) {
        const Property& property = entry.second;
        double propertyTax = calculateTaxes(property.getPropertyNumber());
        totalTaxRevenue += propertyTax;
    }

    return totalTaxRevenue;
}


// calculate total searches from the searchFrequancy Map
int PropertyManager::calculateTotalSearches() {
    if (searchFrequency.empty()) {
        return 0; 
    }

    int totalSearches = 0;

    for (auto& entry : searchFrequency) {
        int search = entry.second;
        totalSearches += search;
    }

    return totalSearches;
}

// Method to Calculate the Average market value of all properties in the Property list

double PropertyManager::calculateAverageMarketValue() {
    if (propertyMap.empty()) {
        return 0.0;
    }

    double totalMarketValue = 0.0;


    for (const auto& entry : propertyMap) {
        const Property& property = entry.second;
        totalMarketValue += property.getMarketValue();
    }

    double averageMarketValue = totalMarketValue / propertyMap.size();

    return averageMarketValue;
}

//Method to Handle admin's Property Management functions

void PropertyManager ::propertyManagerAdmin() {
    PropertyManager manager;
    Property property;
    bool exitFlag = false;

    // for properties
    string  propertyData = "PropertyData.txt";
    manager.readPropertyDataFromFile( propertyData);

    //for searches
    string searchDataFile = "searchDataFile.txt";
    manager.readSearchDataFromFile(searchDataFile);

    //for unapproved properties

    string unapprovedDataFile = "unapprovedDataFile.txt";
    manager.readUnapprovedPropertiesFromFile(unapprovedDataFile);

    cout << "\t\t\t\tWelcome To The Property Manager \n\n" << endl;

    while (!exitFlag) {
        int choice;
        cout << "\t\tPress 1:To Add A Property" << endl;
        cout << "\t\tPress 2:To Edit A Property Details" << endl;
        cout << "\t\tPress 3:To Delete A Property" << endl;
        cout << "\t\tPress 4:To Calculate Property Tax" << endl;
        cout << "\t\tPress 5:To Display Property" << endl;
        cout << "\t\tPress 6:To Search Property" << endl;
        cout << "\t\tPress 7:To Generate Report" << endl;
        cout << "\t\tPress 8:To Approve new Properties" << endl;
        cout << "\t\tPress 9:To Exit Property Manager\n" << endl;

        cout << "Please Enter Your Choice: ";
        while (!(cin >> choice) || choice < 1 || choice > 9 || cin.peek() != '\n' || cin.peek() == '.') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter a number between 1 and 9: ";
        }


        cout << "**************************************************\n" << endl;

        switch (choice) {

        case 1: {
            int propertyNumber, numberOfBedrooms;
            double marketValue, squareFootage, price;
            string builtYear, condition, street, city, state, type;

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
                cout << "Invalid input. Please enter a non-negative integer for the Property Number: ";
            }

            cout << "Enter Property's Market Value: ";
            while (!(cin >> marketValue) || marketValue < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a non-negative number for the Market Value: ";
            }

            cout << "Enter Property's SquareFootage: ";
            while (!(cin >> squareFootage) || squareFootage < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a non-negative number for the SquareFootage: ";
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

            manager.addProperty(propertyNumber, builtYear, numberOfBedrooms, marketValue, squareFootage,
                condition, street, city, state, price, type);
            cout << "**************************************************\n" << endl;
            break;
        }
        case 2: {
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
        }case 3: {
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
                cout << "The Property Taxes: $" << taxes << endl;
            }
            catch (const exception& e) {
                cerr << "Error: " << e.what() << endl;
            }
            cout << "**************************************************\n" << endl;
            break;
        }
        case 5: {
            int propertyNumber;
            cout << "Enter the Property Number to display details: ";
            while (!(cin >> propertyNumber) || propertyNumber < 0 || cin.peek() != '\n' || cin.peek() == '.') {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a non-negative integer for the Property Number: ";
            }
            Property* property = manager.getPropertyByNumber(propertyNumber);
            if (property != nullptr) {
                manager.displayPropertyDetails(*property);
                cout << "**************************************************\n" << endl;
            }
            break;
        }
        case 6:
            manager.searchProperty();
            cout << "**************************************************\n" << endl;
            break;


        case 7:
            manager.generateReport();
            cout << "**************************************************\n" << endl;
            break;


        case 8:
            manager.approveProperties();
            cout << "**************************************************\n" << endl;
            break;

        case 9:
            exitFlag = true;
            cout << "Thanks for Your Time,Goodbye!!\n\n" << endl;
            cout << "**************************************************\n" << endl;
            manager.writePropertyDataToFile( propertyData);// writing property data back to property Hashmap
            manager.writeSearchDataToFile(searchDataFile);// writing search data back to Search map
            manager.writeUnapprovedPropertiesToFile(unapprovedDataFile);// writing unapproved property data  back to Queue
            break;//break out of the switch case
        }
    }
}

void PropertyManager::propertyManagerUser() {

    PropertyManager manager;
    Property property;
    bool exitFlag = false;

    //for property data
    string  propertyData = "PropertyData.txt";
    manager.readPropertyDataFromFile( propertyData);

    // for searches data
    string searchDataFile = "searchDataFile.txt";
    manager.readSearchDataFromFile(searchDataFile);

    //  for unapproved property data
    string unapprovedDataFile = "unapprovedDataFile.txt";
    manager.readUnapprovedPropertiesFromFile(unapprovedDataFile);

    cout << "\t\t\t\tWelcome To The Property Manager \n\n" << endl;
    while (!exitFlag) {
        int choice;
        cout << "\t\tPress 1:To Add A Property List" << endl;
        cout << "\t\tPress 2:To Display Property" << endl;
        cout << "\t\tPress 3:To Search Property" << endl;
        cout << "\t\tPress 4:To Compare Up To 4 Properties" << endl;
        cout << "\t\tPress 5:To Exit Property Manager\n" << endl;

        cout << "Please Enter Your Choice: ";
        while (!(cin >> choice) || choice < 1 || choice > 5 || cin.peek() != '\n' || cin.peek() == '.') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter a number between 1 and 4: ";
        }

        cout << "**************************************************\n" << endl;

        switch (choice) {

        case 1: {
            int propertyNumber, numberOfBedrooms;
            double marketValue, squareFootage, price;
            string builtYear, condition, street, city, state, type;

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
                cout << "Invalid input. Please enter a non-negative integer for the Property Number: ";
            }

            cout << "Enter Property's Market Value: ";
            while (!(cin >> marketValue) || marketValue < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a non-negative number for the Market Value: ";
            }

            cout << "Enter Property's SquareFootage: ";
            while (!(cin >> squareFootage) || squareFootage < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a non-negative number for the SquareFootage: ";
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

            //manager.addProperty(propertyNumber, builtYear, numberOfBedrooms, marketValue, squareFootage,
            //condition, street, city, state, price, type);

            manager.addUnApprovedProperty(propertyNumber, builtYear, numberOfBedrooms, marketValue, squareFootage,
                condition, street, city, state, price, type);
            cout << "**************************************************\n" << endl;
            break;

        }


        case 2: {
            int propertyNumber;
            cout << "Enter the Property Number to display details: ";
            while (!(cin >> propertyNumber) || propertyNumber < 0 || cin.peek() != '\n' || cin.peek() == '.') {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a non-negative integer for the Property Number: ";
            }
            Property* property = manager.getPropertyByNumber(propertyNumber);
            if (property != nullptr) {
                manager.displayPropertyDetails(*property);
                cout << "**************************************************\n" << endl;
            }
            break;
        }


        case 3:
            manager.searchProperty();
            cout << "**************************************************\n" << endl;
            break;


        case 4:
            manager.compareProperties();
            cout << "**************************************************\n" << endl;
            break;

        case 5:
            exitFlag = true;
            cout << "Thanks for Your Time,Goodbye!!\n\n" << endl;
            cout << "**************************************************\n" << endl;
            manager.writePropertyDataToFile( propertyData);
            manager.writeSearchDataToFile(searchDataFile);
            manager.writeUnapprovedPropertiesToFile(unapprovedDataFile);
            break;
        }
    }

}



// Function to read property data from file
void PropertyManager::readPropertyDataFromFile( const string& propertyData) {
    ifstream inFile(propertyData);
    if (!inFile.is_open()) {
        cerr << "Error: Unable to open file for reading: " << propertyData <<endl;
        return;
    }

    propertyMap.clear(); // Clear existing data before reading from file

    string line;
    while (getline(inFile, line)) {
        cout << "Reading line: " << line <<endl; // Print the entire line
        stringstream ss(line);
        string token;
        vector<string> tokens;

        while (getline(ss, token, '|')) { // Split the line by '|'
            tokens.push_back(token);
        }

        if (tokens.size() != 11) {
            cerr << "Error: Invalid data format in file: " << propertyData <<endl;
            continue;
        }

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
        cerr << "Error: Unable to open file for writing: " << propertyData <<endl;
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


// Function to write Searches data to file

void PropertyManager::writeSearchDataToFile(const string& searchDataFile) {
    ofstream outFile(searchDataFile);
    if (!outFile.is_open()) {
        cerr << "Error: Unable to open file for writing: " << searchDataFile <<endl;
        return;
    }

    for (const auto& entry : searchFrequency) {
        outFile << entry.first << "|" << entry.second <<endl;
    }

    outFile.close();
}

// Function to read Searches data to file

void PropertyManager::readSearchDataFromFile(const string& searchDataFile) {
    ifstream inFile(searchDataFile);
    if (!inFile.is_open()) {
        cerr << "Error: Unable to open file for reading: " << searchDataFile <<endl;
        return;
    }

    searchFrequency.clear(); // Clear existing search frequency data before reading from file

    string line;
    while (getline(inFile, line)) {
        cout << "Reading line: " << line <<endl; // Print the entire line
        stringstream ss(line);
        string key;
        int frequency;

        if (getline(ss, key, '|') && ss >> frequency) {
            searchFrequency[key] = frequency;
        }
        else {
            cerr << "Error: Invalid data format in file: " << searchDataFile <<endl;
        }
    }

    inFile.close();
}

// function for writing the unapproved properties to the file

void PropertyManager::writeUnapprovedPropertiesToFile(const string& unapprovedDataFile) {
    ofstream outFile(unapprovedDataFile);
    if (!outFile.is_open()) {
        cerr << "Error: Unable to open file for writing: " << unapprovedDataFile <<endl;
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
            << property.getPropertyType() <<endl;

        unApprovedProperties.pop();
    }

    outFile.close();
}

// A function for reading the unapproved propeties from file back to the Queue

void PropertyManager::readUnapprovedPropertiesFromFile(const string& unapprovedDataFile) {
    ifstream inFile(unapprovedDataFile);
    if (!inFile.is_open()) {
        cerr << "Error: Unable to open file for reading: " << unapprovedDataFile <<endl;
        return;
    }

    // Clear existing unapproved properties before reading from file
    while (!unApprovedProperties.empty()) {
        unApprovedProperties.pop();
    }

    string line;
    while (getline(inFile, line)) {
        cout << "Reading line: " << line <<endl; // Print the entire line
        stringstream ss(line);
        string token;
        vector<string> tokens;

        while (getline(ss, token, '|')) { // Split the line by '|'
            tokens.push_back(token);
        }

        if (tokens.size() != 11) {
            cerr << "Error: Invalid data format in file: " << unapprovedDataFile <<endl;
            continue;
        }

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

