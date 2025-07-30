#include <string>
#include <random>
#include <vector>
#include <fstream>
#include <code/objects/customers.h>

using std::string;

Customer::Customer(string name, double money, int age, bool gender, int amount_willing_to_pay,
					 int tickets_wanted, string preferred_ticket_class, int patience, int importance_of_trip)
	: name(name), money(money), age(age), gender(gender), amount_willing_to_pay(amount_willing_to_pay),
	  tickets_wanted(tickets_wanted), preferred_ticket_class(preferred_ticket_class),
	  patience(patience), importance_of_trip(importance_of_trip)
{}

//Generate a random customer
Customer random_customer(const NameLists& names, std::mt19937& rng)
{
	std::uniform_int_distribution<int> gender_dist(0, 2); // 0=male, 1=female, 2=neutral
	int gender = gender_dist(rng);
	string name;
	if (gender == 0 && !names.male.empty())
		name = names.male[rng() % names.male.size()];
	else if (gender == 1 && !names.female.empty())
		name = names.female[rng() % names.female.size()];
	else if (!names.neutral.empty())
		name = names.neutral[rng() % names.neutral.size()];
	else
		name = "Alex";

	//Generate random attributes
	double money = 20 + (rng() % 200); // $20-$220
	int age = 18 + (rng() % 50);
	int amount_willing_to_pay = 80 + (rng() % 141); // 80%-220%
	int tickets_wanted = 1 + (rng() % 4);
	std::vector<string> ticket_classes = {"Economy", "Business", "Luxury"};
	string preferred_ticket_class = ticket_classes[rng() % ticket_classes.size()];
	int patience = 1 + (rng() % 5);
	int importance_of_trip = 1 + (rng() % 5);

	return Customer(name, money, age, gender == 0, amount_willing_to_pay, tickets_wanted, preferred_ticket_class, patience, importance_of_trip);
}

// Read customer names from a file (definition moved from header)
NameLists read_customer_names(const string& filename)
{
	NameLists names;
	std::ifstream file(filename);
	string line;
	enum { NONE, MALE, FEMALE, NEUTRAL } section = NONE;
	while(std::getline(file, line))
	{
		if (line.find("Male:") != string::npos)
			section = MALE;
		else if (line.find("Female:") != string::npos)
			section = FEMALE;
		else if (line.find("Neutral:") != string::npos)
			section = NEUTRAL;
		else if (!line.empty())
		{
			switch (section)
			{
				case MALE: names.male.push_back(line); break;
				case FEMALE: names.female.push_back(line); break;
				case NEUTRAL: names.neutral.push_back(line); break;
				default: break;
			}
		}
	}

	return names;
}
