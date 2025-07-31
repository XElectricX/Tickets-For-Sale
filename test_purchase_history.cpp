#include <vector>
#include <iostream>
#include <string>

// Simulate the ticket structure
struct Ticket_Datum {
    std::string name;
    int price;
    std::string supplier;
};

int main() {
    std::vector<Ticket_Datum> tickets_for_sale;
    
    // Simulate some tickets
    tickets_for_sale.push_back({"Concert Ticket", 50, "TicketMaster"});
    tickets_for_sale.push_back({"Sports Event", 75, "StubHub"});
    tickets_for_sale.push_back({"Theater Show", 100, "Broadway Direct"});
    
    std::cout << "Testing vector access patterns...\n";
    
    // Test the old problematic approach (using display index)
    std::cout << "\n=== Old approach (problematic) ===\n";
    for (size_t idx = 0; idx < tickets_for_sale.size(); idx++) {
        std::cout << "Display index " << idx << ": ";
        // This would be problematic if idx doesn't match actual vector index
        if (idx < tickets_for_sale.size()) {
            std::cout << tickets_for_sale[idx].name << " - $" << tickets_for_sale[idx].price << std::endl;
        } else {
            std::cout << "OUT OF BOUNDS!" << std::endl;
        }
    }
    
    // Test the new safe approach (using actual vector index)
    std::cout << "\n=== New approach (safe) ===\n";
    for (size_t i = 0; i < tickets_for_sale.size(); i++) {
        std::cout << "Vector index " << i << ": ";
        // Always safe because we're iterating within vector bounds
        std::cout << tickets_for_sale[i].name << " - $" << tickets_for_sale[i].price << std::endl;
    }
    
    // Test bounds checking
    std::cout << "\n=== Bounds checking test ===\n";
    size_t test_index = 5; // Out of bounds
    if (test_index < tickets_for_sale.size()) {
        std::cout << "Index " << test_index << " is safe: " << tickets_for_sale[test_index].name << std::endl;
    } else {
        std::cout << "Index " << test_index << " is OUT OF BOUNDS (vector size: " << tickets_for_sale.size() << ")" << std::endl;
    }
    
    std::cout << "\nTest completed successfully - no crashes!\n";
    return 0;
}
