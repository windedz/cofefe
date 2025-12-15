#include <iostream>
#include "receiptVector.h"
#define HACPAHO std::cout << "HACPAHO" << std::endl;

using namespace std;

void showMenu() {
	cout << "==== Menu ===\n"
		<< "1. Add receipt\n"
		<< "2. Show all \n"
		<< "3. Show by month & year\n"
		<< "4. Show sorted by date\n"
		<< "5. Show by id\n"
		<< "6. Load from receipts.txt\n"
		<< "7. Save to receipts.txt\n"
		<< "8. Exit\n";
}

int main() {
	HACPAHO;
	receiptVector rv;
	while (true)
	{
		int answ;
		showMenu();
		cin >> answ;
		if (answ == 1) {
			string name;
			float priceOfOneCup;
			int quantity;
			int year;
			int month;
			int day;
			bool boughtDessert;
			cout << "Enter coffe type: ";
			cin >> name;
			cout << endl;
			cout << "Enter price of one cup: ";
			cin >> priceOfOneCup;
			cout << endl;
			cout << "Enter quantity: ";
			cin >> quantity;
			cout << endl;
			cout << "Enter year: ";
			cin >> year;
			cout << endl;
			cout << "Enter month: ";
			cin >> month;
			cout << endl;
			cout << "Enter day: ";
			cin >> day;
			cout << endl;
			cout << "Set bought dessert(1/0): ";
			cin >> boughtDessert;
			cout << endl;
			rv.addReceipt(name, priceOfOneCup, quantity, dateTime(year, month, day, 0, 0), boughtDessert);
		}
		else if (answ == 2) {
			rv.showAllReceipts();
		}
		else if (answ == 3) {
			int year;
			int month;
			cout << "Enter year: ";
			cin >> year;
			cout << endl;
			cout << "Enter month: ";
			cin >> month;
			cout << endl;
			rv.showForPerticularMonthAndYear(month, year);
		}
		else if (answ == 4) {
			rv.showSortedByDate();
		}
		else if (answ == 5) {
			string id;
			cout << "Enter target id: ";
			cin >> id;
			cout << endl;
		}
		else if (answ == 6) {
			rv.loadFromFile("receipts.txt");
		}
		else if (answ == 7) {
			rv.saveToFile("receipts.txt");
		}
		else {
			break;
		}
	}
}