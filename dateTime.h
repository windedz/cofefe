#pragma once

#include <iostream>
#include <nlohmann/json.hpp>

using nlohmann::json;

#include <iostream>
#include <exception>

class dateTime {

    int _year;
    int _month;
    int _day;
    int _hour;
    int _minute;

    // Допоміжна функція для перевірки високосного року
    bool isLeapYear(int year) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            return true;
        }
        return false;
    }

    // Допоміжна функція для перевірки кількості днів у місяці
    int daysInMonth(int month, int year) {
        switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return isLeapYear(year) ? 29 : 28;
        default:
            return 0; // Некоректний місяць
        }
    }

public:
    // Конструктор за замовчуванням
    dateTime(int year = 1900, int month = 1, int day = 1, int hour = 0, int minute = 0) {
        setYear(year);
        setMonth(month);
        setDay(day);
        setHour(hour);
        setMinute(minute);
    }

    // Геттер і Сеттер для року
    int getYear() const { 
        return _year; 
    }
    int getMonth() const { 
        return _month; 
    }
    int getDay() const { 
        return _day; 
    }
    int getHour() const { 
        return _hour; 
    }
    int getMinute() const { 
        return _minute; 
    }

    void setYear(int year) {
        if (year < 0) throw std::exception("invalid year");
        _year = year;
    }
    void setMonth(int month) {
        if (month < 1 || month > 12) throw std::exception("invalid month"); 
        _month = month;
    }
    void setDay(int day) {
        if (day < 1 || day > daysInMonth(_month, _year)) {
            throw std::exception("invalid day");
        }
        _day = day;
    }
    void setHour(int hour) {
        if (hour < 0 || hour >= 24) throw std::exception("invalid hour");
        _hour = hour;
    }
    void setMinute(int minute) {
        if (minute < 0 || minute >= 60) throw std::exception("invalid minute"); 
        _minute = minute;
    }

    bool operator<(const dateTime& other) const {
        if (_year != other._year)   return _year < other._year;
        if (_month != other._month) return _month < other._month;
        if (_day != other._day)     return _day < other._day;
        if (_hour != other._hour)   return _hour < other._hour;
        return _minute < other._minute;
    }
};

void to_json(json& j, const dateTime& t) {

    j = {
        { "year", t.getYear()},
        { "month", t.getMonth()},
        { "day", t.getDay()},
        { "minute", t.getMinute()},
        { "hour", t.getHour()}
    };
}

void from_json(const json& j, dateTime& d) {
    d.setYear(j.at("year").get<int>());
    d.setMonth(j.at("month").get<int>());
    d.setDay(j.at("day").get<int>());
    d.setHour(j.at("hour").get<int>());
    d.setMinute(j.at("minute").get<int>());
}