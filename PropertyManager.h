#pragma once
#include <unordered_map>
#include "Property.h"


class PropertyManager {
public:
    std::unordered_map<int, Property> propertyMap;
    // Additional member variables for tracking statistics
    int searchCount;
    std::unordered_map<std::string, int> searchFrequency;

public:
    PropertyManager();

    // Property management functions
    void addProperty(int propertyNumber, const std::string& builtYear, int numberOfBedrooms, double marketValue,
        double squareFootage, const std::string& condition, const std::string& street,
        const std::string& city, const std::string& state, double price, const std::string& type);
    void deleteProperty(int propertyNumber);
    void displayPropertyDetails(const Property& property);
    void editProperty(int propertyNumber);
    double calculateTaxes(int propertyNumber);

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

    // Declaration for writing property data to file
    void writePropertyDataToFile(const std::unordered_map<int, Property>& propertyMap, const std::string& filename);
    // Declaration for reading property data from file
    void readPropertyDataFromFile(std::unordered_map<int, Property>& propertyMap, const std::string& filename);
};
