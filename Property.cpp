#include "Property.h"



// Default constructor for the property class Implementation
Property::Property() : propertyNumber(0), YearBuilt(""), bedRoomNumber(0), marketValue(0.0), 
squareFootage(0.0), conditionState(""), propertyType(""), price(0.0) {}

//Parameterised constructor implementation
Property::Property(int propertyNumber, std::string YearBuilt, int bedRoomNumber, double marketValue,
    double squareFootage, std::string conditionState,
    std::string proStreet, std::string proCity, std::string proState,
    double price, std::string propertyType) {

    this->propertyNumber = propertyNumber;
    this->YearBuilt = YearBuilt;
    this->bedRoomNumber = bedRoomNumber;
    this->marketValue = marketValue;
    this->squareFootage = squareFootage;
    this->conditionState = conditionState;
    this->propertyLocation.Street = proStreet;
    this->propertyLocation.City = proCity;
    this->propertyLocation.State = proState;
    this->price = price;
    this->propertyType = propertyType;
}

//setter function for property's number of bedrooms
void Property::setBedRoomNumber(int bedRoomNumber) {
    this->bedRoomNumber = bedRoomNumber;
}

//setter function for  property's market value
void Property::setMarketValue(double marketValue) {
    this->marketValue = marketValue;
}

//setter function for property's condition
void Property::setConditionState(std::string conditionState) {
    this->conditionState = conditionState;
}

//setter function for property's price
void Property::setPrice(double price) {
    this->price = price;
}

// setter function for property's type
void Property::setPropertyType(std::string propertyType) {
    this->propertyType = propertyType;
}

// getter function for the property's number of bedrooms

int Property::getBedRoomNumber() const {
    return bedRoomNumber;
}

// getter function for property's market value
double Property::getMarketValue() const {
    return marketValue;
}

//getter function for the property's condition
std::string Property::getConditionState() const {
    return conditionState;
}

//getter function for the property's number
int Property::getPropertyNumber() const {
    return propertyNumber;
}

// getter function for property's squarefootage 
double Property::getSquareFootage() const {
    return squareFootage;
}

//getter function for property's yearBuilt
std::string Property::getYearBuilt() const {
    return YearBuilt;
}

// getter function for property's location
Location Property::getPropertyLocation() const {
    return propertyLocation;
}

//getter function for property's type
std::string Property::getPropertyType() const {
    return propertyType;
}

// getter function for property's price
double Property::getPrice() const {
    return price;
}
