#pragma once

#include <string>

using std::string;

class Customer
{
public:
	string name;
	double money;
	int age;

	//Percentage of the ticket price they are willing to pay
	//50% means they will pay half the price, 200% means they will pay double the price
	int amount_willing_to_pay;
	//How many tickets they want to buy
	int tickets_wanted;
	//What class of ticket they prefer
	string preferred_ticket_class;
	//How many more times a customer is willing to barter
	int patience;
	//1 to 5 scale; 1 means a customer may decide not to buy at all, 5 means they will always buy
	int importance_of_trip;

	Customer(string name, double money, int age, int amount_willing_to_pay,
			int tickets_wanted, string preferred_ticket_class, int patience, int importance_of_trip);
};
