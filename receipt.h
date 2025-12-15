#pragma once
#include <iostream>
#include "dateTime.h"
#include "nlohmann/json.hpp"

using std::string, std::cout, std::endl;

const int RECEIPT_ID_LENGTH = 10;

string getRandomId() {
    string charsSet = "123456789qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
    string result;

    for (int i = 0; i < RECEIPT_ID_LENGTH; i++) {
        result += charsSet[rand() % charsSet.size()];
    }

    return result;
}

class receipt {
    string _id;
    string _name;
    float _priceOfOneCup;
    int _quantity;
    dateTime _date;
    bool _boughtDessert;

public:
    receipt(
        const string& name = "",
        float priceOfOneCup = 0.0f,
        int quantity = 0,
        const dateTime& date = dateTime(),
        bool boughtDessert = false
    )
        : _id(getRandomId()),
        _name(name),
        _priceOfOneCup(priceOfOneCup),
        _quantity(quantity),
        _date(date),
        _boughtDessert(boughtDessert){}

    string getId() const { return _id; }
    const string& getName() const { return _name; }
    float getPriceOfOneCup() const { return _priceOfOneCup; }
    int getQuantity() const { return _quantity; }
    const dateTime& getDate() const { return _date; }
    bool getBoughtDessert() const { return _boughtDessert; }

    void setId(int id) { _id = id; }
    void setName(const string& name) { _name = name; }
    void setPriceOfOneCup(float price) { _priceOfOneCup = price; }
    void setQuantity(int quantity) { _quantity = quantity; }
    void setDate(const dateTime& date) { _date = date; }
    void setBoughtDessert(bool boughtDessert) { _boughtDessert = boughtDessert; }

    void showReceipt() {
        cout << "ID: " << _id << "; Name: " << _name << "; Price of one cup: " << _priceOfOneCup << "; Quantity: " << _quantity << "; Date: (year: " 
            << _date.getYear() << "; month: " << _date.getMonth() << "; day: " << _date.getDay() << endl;
    }
    float getTotalIncome() {
        return _quantity * _priceOfOneCup;
    }
};

void to_json(json& j, const receipt& rec) {
    j = {
        {"id", rec.getId()},
        {"name", rec.getName()},
        {"price_of_one", rec.getPriceOfOneCup()},
        {"quantity", rec.getQuantity()},
        {"date", rec.getDate()},
        {"bought_dessert", rec.getBoughtDessert()}
    };
}

void from_json(const json& j, receipt& rec) {
    rec.setId(j.at("id").get<int>());
    rec.setName(j.at("name").get<string>());
    rec.setPriceOfOneCup(j.at("priceOfOneCup").get<float>());
    rec.setQuantity(j.at("quantity").get<int>());
    rec.setDate(j.at("date").get<dateTime>());
    rec.setBoughtDessert(j.at("boughtDessert").get<bool>());
}
