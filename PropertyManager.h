#pragma once
#include <unordered_map>
#include "Property.h"


class PropertyManager {
  

public:
    PropertyManager();

    // Property management functions
    void addProperty(int propertyNumber, const std::string& builtYear, int numberOfBedrooms, double marketValue,
        double squareFootage, const std::string& condition, const std::string& street,
        const std::string& city, const std::string& state, double price, const std::string& type);

    void addUnApprovedProperty(int propertyNumber, const std::string& builtYear, int numberOfBedrooms, double marketValue,
        double squareFootage, const std::string& condition, const std::string& street,
        const std::string& city, const std::string& state, double price, const std::string& type);

    void approveProperties();
    void deleteProperty(int propertyNumber);
    void displayPropertyDetails(const Property& property);
    void editProperty(int propertyNumber);
    double calculateTaxes(int propertyNumber);
    void propertyManagerUser();
    void propertyManagerAdmin();
    void compareProperties();

    // Search functions
    void searchProperty();
    Property* getPropertyByNumber(int propertyNumber);
    void searchByPriceRange(double minPrice, double maxPrice);
    void searchByBedrooms(int minBedrooms, int maxBedrooms);
    void searchByLocation(const std::string& location);
    void searchByPropertyType(const std::string& type);
    
    // Report generation functions
    void generateReport();
    double  calculateTotalTaxRevenue();
    double calculateAverageMarketValue();
    int calculateTotalSearches();

    // Declaration for writing property data to file
    void writePropertyDataToFile(const std::string& filename);
    // Declaration for reading property data from file
    void readPropertyDataFromFile( const std::string& filename);

    // Function to read Searches data to file
    void readSearchDataFromFile(const std::string& searchDataFile);
    // Function to write Searches data to file
    void writeSearchDataToFile(const std::string& searchDataFile);

    // function for writing the unapproved properties to the file
    void writeUnapprovedPropertiesToFile(const std::string& unapprovedDataFile);
    // A function for reading the unapproved propeties from file back to the Queue
    void readUnapprovedPropertiesFromFile(const std::string& unapprovedDataFile);
};
