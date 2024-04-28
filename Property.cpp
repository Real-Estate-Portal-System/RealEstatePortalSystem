#include "Property.h"

Property::Property() : propertyNumber(0), YearBuilt(""), bedRoomNumber(0), marketValue(0.0), squareFootage(0.0), conditionState(""), propertyType(""), price(0.0) {}

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

void Property::setBedRoomNumber(int bedRoomNumber) {
    this->bedRoomNumber = bedRoomNumber;
}

void Property::setMarketValue(double marketValue) {
    this->marketValue = marketValue;
}

void Property::setConditionState(std::string conditionState) {
    this->conditionState = conditionState;
}

void Property::setPrice(double price) {
    this->price = price;
}

void Property::setPropertyType(std::string propertyType) {
    this->propertyType = propertyType;
}



int Property::getBedRoomNumber() const {
    return bedRoomNumber;
}

double Property::getMarketValue() const {
    return marketValue;
}

std::string Property::getConditionState() const {
    return conditionState;
}

int Property::getPropertyNumber() const {
    return propertyNumber;
}

double Property::getSquareFootage() const {
    return squareFootage;
}

std::string Property::getYearBuilt() const {
    return YearBuilt;
}

Location Property::getPropertyLocation() const {
    return propertyLocation;
}

std::string Property::getPropertyType() const {
    return propertyType;
}

double Property::getPrice() const {
    return price;
}
