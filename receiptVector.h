#pragma once
#include "vector.h"
#include "receipt.h"
#include "nlohmann/json.hpp"
#include <fstream>

using namespace collections;

class receiptVector {
	collections::vector<receipt> _receiptVector;
public:
	void showAllReceipts() {
		for (int i = 0; i < _receiptVector.getSize(); i++)
		{
			_receiptVector[i].showReceipt();
		}
	}
	void showForPerticularMonthAndYear(const int& month, const int& year) {	
		for (int i = 0; i < _receiptVector.getSize(); i++)
		{
			if (_receiptVector[i].getDate().getMonth() == month && _receiptVector[i].getDate().getYear() == year) {
				_receiptVector[i].showReceipt();
			}
		}
	}
	void showByID(const string& id) {
		for (int i = 0; i < _receiptVector.getSize(); i++)
		{
			if (_receiptVector[i].getId() == id) {
				_receiptVector[i].showReceipt();
			}
		}
	}
	float getTotalIncomeFromeType(const string& name) {
		float reslt = 0.0;
		for (int i = 0; i < _receiptVector.getSize(); i++)
		{
			if (_receiptVector[i].getName() == name) {
				reslt += _receiptVector[i].getTotalIncome();
			}
		}
		return reslt;
	}
	void addReceipt(const string& name = "",float priceOfOneCup = 0.0f,int quantity = 0,const dateTime& date = dateTime(),bool boughtDessert = false) {
		receipt newReceipt(name, priceOfOneCup, quantity, date, boughtDessert);
		_receiptVector.pushBack(newReceipt);
	}

	void saveToFile(const string& filename) {
		json j = json::array();

		for (int i = 0; i < _receiptVector.getSize(); i++) {
			j.push_back(_receiptVector[i]);
		}

		std::ofstream file(filename);
		file << j.dump(4);
		file.close();
	}

	void loadFromFile(const string& filename) {
		std::ifstream file(filename);
		json j;
		file >> j;
		file.close();

		_receiptVector.clear();

		for (const auto& item : j) {
			receipt r = item.get<receipt>();
			_receiptVector.pushBack(r);
		}
	}

	void showSortedByDate() {
		for(int i = 0; i < _receiptVector.getSize() - 1; i++) {
			for (int j = 0; j < _receiptVector.getSize() - i - 1; j++) {

				if (_receiptVector[j + 1].getDate() < _receiptVector[j].getDate()) {
					_receiptVector[i].showReceipt();
				}
			}
		}
	}
};