#pragma once
#include <string>

struct Location {
    std::string Street;
    std::string City;
    std::string State;
};

class Property {
private:
    int propertyNumber;
    std::string YearBuilt;
    int bedRoomNumber;
    double marketValue;
    double squareFootage;
    std::string conditionState;
    Location propertyLocation;
    double price;
    std::string propertyType;

public:
    Property();
    Property(int propertyNumber, std::string YearBuilt, int bedRoomNumber, double marketValue,
        double squareFootage, std::string conditionState,
        std::string proStreet, std::string proCity, std::string proState,
        double price, std::string propertyType);
    // Setter Methods

    void setBedRoomNumber(int bedRoomNumber);
    void setMarketValue(double marketValue);
    void setConditionState(std::string conditionState);
    void setPrice(double price);
    void setPropertyType(std::string propertyType);
    // Getter Methods
    int getBedRoomNumber() const;
    double getMarketValue() const;
    std::string getConditionState() const;
    int getPropertyNumber() const;
    double getSquareFootage() const;
    std::string getYearBuilt() const;
    Location getPropertyLocation() const;
    std::string getPropertyType() const;
    double getPrice() const;
};