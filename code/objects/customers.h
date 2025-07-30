#pragma once

#include <string>
#include <random>
#include <fstream>

using std::string;

class Customer
{
public:
	string name;
	double money;
	int age;
	bool gender;

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

	// Default constructor for JSON deserialization
	Customer() : name(""), money(0), age(0), gender(false), amount_willing_to_pay(100), tickets_wanted(1), preferred_ticket_class("Economy"), patience(1), importance_of_trip(1) {}
	
	Customer(string name, double money, int age, bool gender, int amount_willing_to_pay,
			int tickets_wanted, string preferred_ticket_class, int patience, int importance_of_trip);
};

//Used for customer name generation
struct NameLists
{
	//Lists of names for each gender type
	std::vector<string> male, female, neutral;
};


// Read customer names from a file (declaration only; definition in customers.cpp)
NameLists read_customer_names(const string& filename);

Customer random_customer(const NameLists& names, std::mt19937& rng);
