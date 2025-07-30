#include <vector>
#include <utility>
#include <algorithm>
#include <tuple>
#include "tickets.h"
#include "../helpers.h"
#include "../defines.h"
using std::move;
using std::string;
using std::vector;

Ticket_Datum::Ticket_Datum(Ticket_Class ticket_class, string route, int price, int amount_available)
	// Initializer list
	: ticket_class(ticket_class), route(move(route)), price(price), amount_available(amount_available)
{
}

vector<Ticket> Ticket_Datum::create_ticket(int amount_to_create)
{
	vector<Ticket> tickets;
	for (int i = 0; i < amount_to_create; ++i)
	{
		if (amount_available <= 0)
		{
			// If no tickets are available, break the loop
			break;
		}
		// If no tickets are available, return an empty ticket
		tickets.push_back(Ticket(ticket_class, price, route));
		--amount_available;
	}
	return tickets;
}

Ticket::Ticket(Ticket_Class ticket_class, int price_paid, string route)
	// Initializer list
	: ticket_class(ticket_class), price_paid(price_paid), route(move(route))
{
}

void Ticket::test_print() const
{
	print("Ticket: " + route + "\n"
							   "Class: " +
		  std::to_string(static_cast<int>(ticket_class)) + "\n"
														   "Price Paid: " +
		  std::to_string(price_paid));
}

// Helper: Generate a random ticket inventory
std::vector<Ticket> random_ticket_inventory(std::mt19937 &rng)
{
	std::vector<Ticket> tickets;
	std::vector<std::pair<Ticket_Class, std::string>> routes = {
		{Ticket_Class::TICKET_CLASS_ECONOMY, "New York to Los Angeles"},
		{Ticket_Class::TICKET_CLASS_BUSINESS, "Chicago to Miami"},
		{Ticket_Class::TICKET_CLASS_LUXURY, "San Francisco to Paris"},
		{Ticket_Class::TICKET_CLASS_ECONOMY, "Dallas to Seattle"},
		{Ticket_Class::TICKET_CLASS_BUSINESS, "Boston to London"}};
	int num_tickets = 3 + (rng() % 4); // 3-6 tickets
	for (int i = 0; i < num_tickets; ++i)
	{
		auto &r = routes[rng() % routes.size()];
		int price = 50 + (rng() % 200);
		tickets.emplace_back(r.first, price, r.second);
	}
	return tickets;
}

// Helper: Generate random tickets for sale from suppliers
std::vector<Ticket_Datum> random_tickets_for_sale(std::mt19937 &rng)
{
	std::vector<Ticket_Datum> tickets_for_sale;
	std::vector<std::tuple<Ticket_Class, std::string, int, int>> supplier_offers = {
		{Ticket_Class::TICKET_CLASS_ECONOMY, "Atlanta to Denver", 75, 5},
		{Ticket_Class::TICKET_CLASS_ECONOMY, "Phoenix to Portland", 85, 3},
		{Ticket_Class::TICKET_CLASS_BUSINESS, "Houston to Nashville", 150, 4},
		{Ticket_Class::TICKET_CLASS_BUSINESS, "San Diego to Seattle", 180, 2},
		{Ticket_Class::TICKET_CLASS_LUXURY, "Las Vegas to Miami", 350, 2},
		{Ticket_Class::TICKET_CLASS_LUXURY, "San Francisco to New York", 450, 1},
		{Ticket_Class::TICKET_CLASS_ECONOMY, "Chicago to Philadelphia", 95, 6},
		{Ticket_Class::TICKET_CLASS_BUSINESS, "Detroit to Orlando", 200, 3}};

	// Select 4-6 random offers from suppliers
	int num_offers = 4 + (rng() % 3); // 4-6 offers
	std::vector<int> selected_indices;

	// Generate unique random indices
	while (selected_indices.size() < static_cast<size_t>(num_offers) && selected_indices.size() < supplier_offers.size())
	{
		int idx = rng() % supplier_offers.size();
		if (std::find(selected_indices.begin(), selected_indices.end(), idx) == selected_indices.end())
		{
			selected_indices.push_back(idx);
		}
	}

	// Create Ticket_Datum objects from selected offers
	for (int idx : selected_indices)
	{
		auto &offer = supplier_offers[idx];
		Ticket_Class ticket_class = std::get<0>(offer);
		std::string route = std::get<1>(offer);
		int base_price = std::get<2>(offer);
		int base_amount = std::get<3>(offer);

		// Add some price variation (±20%)
		int price_variation = (rng() % 41) - 20; // -20 to +20
		int final_price = base_price + (base_price * price_variation / 100);
		if (final_price < 25)
			final_price = 25; // Minimum price

		// Add some amount variation
		int amount_variation = (rng() % 3) - 1; // -1, 0, or +1
		int final_amount = base_amount + amount_variation;
		if (final_amount < 1)
			final_amount = 1; // Minimum 1 ticket

		tickets_for_sale.emplace_back(ticket_class, route, final_price, final_amount);
	}

	return tickets_for_sale;
}
