// serialization.h - nlohmann::json (de)serialization for Ticket, Ticket_Datum, Customer, and Game
#pragma once
#include <nlohmann/json.hpp>
#include "objects/tickets.h"
#include "objects/customers.h"
#include "game.h"

using nlohmann::json;

// --- Ticket ---
inline void to_json(json& j, const Ticket& t) {
    j = json{{"ticket_class", t.ticket_class}, {"price_paid", t.price_paid}, {"route", t.route}};
}
inline void from_json(const json& j, Ticket& t) {
    j.at("ticket_class").get_to(t.ticket_class);
    j.at("price_paid").get_to(t.price_paid);
    j.at("route").get_to(t.route);
}

// --- Ticket_Datum ---
inline void to_json(json& j, const Ticket_Datum& td) {
    j = json{{"route", td.route}, {"price", td.price}, {"amount_available", td.amount_available}, {"ticket_class", td.ticket_class}};
}
inline void from_json(const json& j, Ticket_Datum& td) {
    j.at("route").get_to(td.route);
    j.at("price").get_to(td.price);
    j.at("amount_available").get_to(td.amount_available);
    j.at("ticket_class").get_to(td.ticket_class);
}

// --- Customer ---
inline void to_json(json& j, const Customer& c) {
    j = json{{"name", c.name}, {"money", c.money}, {"age", c.age}, {"gender", c.gender}, {"amount_willing_to_pay", c.amount_willing_to_pay}, {"tickets_wanted", c.tickets_wanted}, {"preferred_ticket_class", c.preferred_ticket_class}, {"patience", c.patience}, {"importance_of_trip", c.importance_of_trip}};
}
inline void from_json(const json& j, Customer& c) {
    j.at("name").get_to(c.name);
    j.at("money").get_to(c.money);
    j.at("age").get_to(c.age);
    j.at("gender").get_to(c.gender);
    j.at("amount_willing_to_pay").get_to(c.amount_willing_to_pay);
    j.at("tickets_wanted").get_to(c.tickets_wanted);
    j.at("preferred_ticket_class").get_to(c.preferred_ticket_class);
    j.at("patience").get_to(c.patience);
    j.at("importance_of_trip").get_to(c.importance_of_trip);
}

// --- Game ---
inline void to_json(json& j, const Game& g) {
    j = json{
        {"player_name", g.player_name},
        {"business_name", g.business_name},
        {"money", g.money},
        {"ticket_inventory", g.ticket_inventory},
        {"tickets_for_sale", g.tickets_for_sale},
        {"customers", g.customers},
        {"total_customers", g.total_customers},
        {"total_tickets_sold", g.total_tickets_sold},
        {"total_tickets_bought", g.total_tickets_bought},
        {"total_revenue", g.total_revenue},
        {"total_expenses", g.total_expenses}
    };
}
inline void from_json(const json& j, Game& g) {
    j.at("player_name").get_to(g.player_name);
    j.at("business_name").get_to(g.business_name);
    j.at("money").get_to(g.money);
    j.at("ticket_inventory").get_to(g.ticket_inventory);
    j.at("tickets_for_sale").get_to(g.tickets_for_sale);
    j.at("customers").get_to(g.customers);
    j.at("total_customers").get_to(g.total_customers);
    j.at("total_tickets_sold").get_to(g.total_tickets_sold);
    j.at("total_tickets_bought").get_to(g.total_tickets_bought);
    j.at("total_revenue").get_to(g.total_revenue);
    j.at("total_expenses").get_to(g.total_expenses);
}
