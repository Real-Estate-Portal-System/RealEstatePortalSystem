#pragma once // Include guard to prevent multiple inclusion of header file
#include <unordered_map> // Include unordered_map header
#include "Property.h" // Include Property header

class PropertyManager {
public:
    // Constructor for PropertyManager
    PropertyManager();

    // ***** Property management functions *****

    // Add an approved property to the system
    void addProperty(int propertyNumber, const std::string& builtYear, int numberOfBedrooms, double marketValue,
        double squareFootage, const std::string& condition, const std::string& street,
        const std::string& city, const std::string& state, double price, const std::string& type);

    // Add an unapproved property to the system
    void addUnApprovedProperty(int propertyNumber, const std::string& builtYear, int numberOfBedrooms, double marketValue,
        double squareFootage, const std::string& condition, const std::string& street,
        const std::string& city, const std::string& state, double price, const std::string& type);

    void approveProperties(); // Approve unapproved properties
    void deleteProperty(int propertyNumber); // Delete a property
    void displayPropertyDetails(const Property& property); // Display details of a property
    void editProperty(int propertyNumber); // Edit property details
    double calculateTaxes(int propertyNumber); // Calculate property taxes
    void propertyManagerUser(); // User-specific property management menu
    void propertyManagerAdmin(); // Admin-specific property management menu
    void compareProperties(); // Compare property values
    void searchBysquareFootageRange(double minFootage, double maxFootage); // Search properties by square footage range

    // **** Search functions ****

    void searchProperty(); // General property search
    Property* getPropertyByNumber(int propertyNumber); // Get property by property number
    void searchByPriceRange(double minPrice, double maxPrice); // Search properties by price range
    void searchByBedrooms(int minBedrooms, int maxBedrooms); // Search properties by number of bedrooms
    void searchByLocation(const std::string& location); // Search properties by location
    void searchByPropertyType(const std::string& type); // Search properties by type

    // *** Report generation functions ***

    void generateReport(); // Generate property-related, user-related, and admin-related reports
    double calculateTotalTaxRevenue(); // Calculate total tax revenue
    double calculateAverageMarketValue() const; // Calculate average market value
    int calculateTotalSearches() const; // Calculate total property searches

    // Function for writing property data to file
    void writePropertyDataToFile(const std::string& filename);

    // Function for reading property data from file
    void readPropertyDataFromFile(const std::string& filename);

    // Function to read search data from a file
    void readSearchDataFromFile(const std::string& searchDataFile);

    // Function to write search data to a file
    void writeSearchDataToFile(const std::string& searchDataFile);

    // Function for writing unapproved properties to a file
    void writeUnapprovedPropertiesToFile(const std::string& unapprovedDataFile);

    // Function for reading unapproved properties from a file back to the queue
    void readUnapprovedPropertiesFromFile(const std::string& unapprovedDataFile);
};
