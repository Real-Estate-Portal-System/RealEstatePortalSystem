#include "PropertyManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <locale> 


using namespace std;

// Default constructor
PropertyManager::PropertyManager() {
    searchCount = 0;
}

// Method to add a new property to the property map
void PropertyManager::addProperty(int propertyNumber, const string& builtYear, int numberOfBedrooms, double marketValue,
    double squareFootage, const string& condition, const string& street,
    const string& city, const string& state, double price, const string& type) {

    if (propertyMap.find(propertyNumber) != propertyMap.end()) {
        cout << "The Property Number " << propertyNumber << " Already Exists in the System" << endl;
    }
    else {
        Property newProperty(propertyNumber, builtYear, numberOfBedrooms, marketValue, squareFootage,
            condition, street, city, state, price, type);
        propertyMap[propertyNumber] = newProperty;
        cout << "Property with Property Number " << propertyNumber << " Added Successfully" << endl;
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
            cout << "Wound you like to Undo Deletion? Press Yes(1),No(2): ";
            cin >> choice;
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

// Method to search for properties based on various criteria
void PropertyManager::searchProperty() {
    int choice;

    do {
        cout << "\n\t\tSearch Options:\n";
        cout << "\t\t1. By Location\n";
        cout << "\t\t2. By Price Range\n";
        cout << "\t\t3. By Bedrooms\n";
        cout << "\t\t4. By Property Type\n";
        cout << "\t\t5. Exit\n";

        cout << "Choose a search criterion: ";
        while (!(cin >> choice) || choice < 1 || choice > 5 || cin.peek() != '\n' || cin.peek() == '.') {
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
            searchCount++;
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
                cout << "Invalid input. Please enter a number greater than or equal to " << minPrice << ": ";
            }

            searchByPriceRange(minPrice, maxPrice);
            searchFrequency["Price Range"]++; // Increment frequency for price range search
            searchCount++;
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
            searchCount++;
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
            searchCount++;
        }
        break;
        case 5:
            cout << "Exiting search...\n";
            break;
        }
    } while (choice != 5);
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
                cout << "\t\t 1. Edit The Property's Number of Bedrooms" << endl;
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
        cout << "No properties found within the specified price range.\n";
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


void PropertyManager::generateReport() {
    // Total number of properties added
    int totalProperties = propertyMap.size();

    // Total number of searches made
    int totalSearches = searchCount;
    double totalTaxRevenue = calculateTotalTaxRevenue();
    double averageMarketValue = calculateAverageMarketValue();


    // Leading search (search with the highest frequency)
    string leadingSearch;
    int leadingSearchCount = 0;
    for (const auto& search : searchFrequency) {
        if (search.second > leadingSearchCount) {
            leadingSearchCount = search.second;
            leadingSearch = search.first;
        }
    }


    cout << "----- Property Management Report -----" << endl;
    cout << "Total Properties Added: " << totalProperties << endl;
    cout << "Total Searches Made: " << totalSearches << endl;
    cout << "Leading Search: " << leadingSearch << " (" << leadingSearchCount << " times)" << endl;
    cout << "Total Tax Revenue Generated: $" << totalTaxRevenue << endl;
    cout << "Average Market Value of Properties: $" << averageMarketValue << endl;
}
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

// Function to read property data from file
void PropertyManager::readPropertyDataFromFile(unordered_map<int, Property>& propertyMap, const std::string& propertyData) {
    ifstream inFile(propertyData);
    if (!inFile.is_open()) {
        std::cerr << "Error: Unable to open file for reading: " << propertyData << std::endl;
        return;
    }

    propertyMap.clear(); // Clear existing data before reading from file

    std::string line;
    while (getline(inFile, line)) {
        std::cout << "Reading line: " << line << std::endl; // Print the entire line
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;

        while (getline(ss, token, '|')) { // Split the line by '|'
            tokens.push_back(token);
        }

        if (tokens.size() != 11) {
            std::cerr << "Error: Invalid data format in file: " << propertyData << std::endl;
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
void PropertyManager::writePropertyDataToFile(const unordered_map<int, Property>& propertyMap, const string& propertyData) {
    std::ofstream outFile(propertyData);
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open file for writing: " << propertyData << std::endl;
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

