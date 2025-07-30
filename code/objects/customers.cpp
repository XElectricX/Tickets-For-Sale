#include <string>
#include <code/objects/customers.h>

using std::string;

Customer::Customer(string name, double money, int age, int amount_willing_to_pay,
					 int tickets_wanted, string preferred_ticket_class, int patience, int importance_of_trip)
	: name(name), money(money), age(age), amount_willing_to_pay(amount_willing_to_pay),
	  tickets_wanted(tickets_wanted), preferred_ticket_class(preferred_ticket_class),
	  patience(patience), importance_of_trip(importance_of_trip)
{}
