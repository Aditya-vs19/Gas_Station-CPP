#include <iostream>
#include <fstream>  // Include for file handling
#include <string>
#include <vector>   // Include for vector
using namespace std;

// Structure to hold transaction details
struct Transaction {
    string customerName;
    long long contact;
    string fuelType;
    double totalCost;
};

// Base Class: Customer
class Customer {
public:
    string name;
    int age;
    string address;
    long long contact;

    Customer() {
        // Constructor doesn't print anything now
    }

    void inputCustomerDetails() {
        cout << "\nEnter full name: ";
        cin.ignore(); 
        getline(cin, name);  

        cout << "\nEnter age: ";
        cin >> age;
        

        cout << "\nEnter address: ";
        cin.ignore();  
        getline(cin, address);  
        cout << "\nEnter contact number: ";
        cin >> contact;
    }
};

// Derived Class: Vehicle from Customer
class Vehicle : public Customer {
public:
    string type;
    string number;

    Vehicle() {
        // No constructor message
    }

    void inputVehicleDetails() {
        cout << "\nEnter the type of vehicle: ";
        cin.ignore();  // Consume the newline left in the input buffer
        getline(cin, type);

        cout << "\nEnter the registered number of your vehicle: ";
        getline(cin, number);
    }
};

// Base Class: Fuel (Virtual Base Class)
class Fuel : public Vehicle {
protected:
    double price = 0;
    double quantity = 0;

public:
    virtual void inputFuelDetails() = 0;
    virtual void calculateTotal() = 0;
    virtual double getPrice() const = 0;
    virtual double getQuantity() const = 0;
};

// Derived Class: Petrol
class Petrol : public Fuel {
    const double pricePerLiter = 100;

public:
    void inputFuelDetails() override {
        cout << "\nEnter the amount of petrol in liters: ";
        cin >> quantity;
    }

    void calculateTotal() override {
        price = pricePerLiter * quantity;
    }

    double getPrice() const override {
        return price;
    }

    double getQuantity() const override {
        return quantity;
    }
};

// Derived Class: Diesel
class Diesel : public Fuel {
    const double pricePerLiter = 80;

public:
    void inputFuelDetails() override {
        cout << "\nEnter the amount of diesel in liters: ";
        cin >> quantity;
    }

    void calculateTotal() override {
        price = pricePerLiter * quantity;
    }

    double getPrice() const override {
        return price;
    }

    double getQuantity() const override {
        return quantity;
    }
};

// Derived Class: CNG
class CNG : public Fuel {
    const double pricePerKg = 60;

public:
    void inputFuelDetails() override {
        cout << "\nEnter the amount of CNG in kilograms: ";
        cin >> quantity;
    }

    void calculateTotal() override {
        price = pricePerKg * quantity;
    }

    double getPrice() const override {
        return price;
    }

    double getQuantity() const override {
        return quantity;
    }
};

// Class for generating price tickets and maintaining transaction history
class PriceTicket {
private:
    Fuel* fuel = nullptr;
    double totalCost = 0;
    string fuelDetails;
    vector<Transaction> transactions;  // Vector to hold transaction details

public:
    ~PriceTicket() {
        delete fuel;  // Free dynamically allocated memory
    }

    void selectFuelType() {
        char fuelType;
        cout << "\nSelect fuel type (P for Petrol, D for Diesel, C for CNG): ";
        cin >> fuelType;

        switch (fuelType) {
        case 'P':
            fuel = new Petrol(); // Assign the derived class Petrol to the base class pointer
            break;
        case 'D':
            fuel = new Diesel(); // Assign the derived class Diesel to the base class pointer
            break;
        case 'C':
            fuel = new CNG();    // Assign the derived class CNG to the base class pointer
            break;
        default:
            cout << "Invalid fuel type!" << endl;
            return;
        }

        fuel->inputFuelDetails();
        fuel->calculateTotal();
        totalCost = fuel->getPrice();
        fuelDetails = "Quantity: " + to_string(fuel->getQuantity()) + (fuelType == 'C' ? " kilograms" : " liters");
    }

    void generateTicket(Customer& customer, Vehicle& vehicle) {
        // Create and open the .txt file
        ofstream ticketFile("AdityaGASStation.txt");

        // Write ticket details to the file
        ticketFile << "---------------------------------------\n";
        ticketFile << "|       -- ADITYA GAS STATION--     |\n";
        ticketFile << "|         --- Price Ticket ---      |\n";
        ticketFile << "---------------------------------------\n";
        ticketFile << "| Customer Details:                   |\n";
        ticketFile << "| Name: " << customer.name << endl;
        ticketFile << "| Age: " << customer.age << endl;
        ticketFile << "| Address: " << customer.address << endl;
        ticketFile << "| Contact: " << customer.contact << endl;
        ticketFile << "---------------------------------------\n";
        ticketFile << "| Vehicle Details:                    |\n";
        ticketFile << "| Type: " << vehicle.type << endl;
        ticketFile << "| Registered Number: " << vehicle.number << endl;
        ticketFile << "---------------------------------------\n";
        ticketFile << "| Fuel Details:                       |\n";
        ticketFile << "| " << fuelDetails << endl;
        ticketFile << "| Total Cost: $" << totalCost << endl;
        ticketFile << "---------------------------------------\n";
        ticketFile.close();

        // Add transaction to the list
        transactions.push_back({ customer.name, customer.contact, fuelDetails, totalCost });

        // Print the ticket in color on the console
        cout << "\n---------------------------------------" << endl;
        cout << "|       ---- GPP GAS STATION----     |" << endl;
        cout << "|         ---  Price Ticket ---      |" << endl;
        cout << "---------------------------------------" << endl;
        cout << "| CUSTOMER DETAILS:                  |" << endl;
        cout << "| Name: " << customer.name << endl;
        cout << "| Age: " << customer.age << endl;
        cout << "| Address: " << customer.address << endl;
        cout << "| Contact: " << customer.contact << endl;
        cout << "---------------------------------------" << endl;
        cout << "| VEHICLE DETAILS:                   |" << endl;
        cout << "| Type: " << vehicle.type << endl;
        cout << "| Registered Number: " << vehicle.number << endl;
        cout << "---------------------------------------" << endl;
        cout << "| FUEL DETAILS:                      |" << endl;
        cout << "| " << fuelDetails << endl;
        cout << "| Total Cost: $" << totalCost << endl;
        cout << "---------------------------------------" << endl;

        cout << "\nThe ticket has been saved to 'AdityaGASStation.txt' file." << endl;
    }

    void showTransactionHistory() const {
        cout << "\n--- Customer Transaction History ---" << endl;
        if (transactions.empty()) {
            cout << "No transactions found for today." << endl;
            return;
        }
        for (const auto& transaction : transactions) {
            cout << "Customer Name: " << transaction.customerName << endl;
            cout << "Contact: " << transaction.contact << endl;
            cout << "Fuel Purchased: " << transaction.fuelType << endl;
            cout << "Total Amount: $" << transaction.totalCost << endl;
            cout << "---------------------------------------" << endl;
        }
    }

    double calculateTotalEarnings() const {
        double totalEarnings = 0;
        for (const auto& transaction : transactions) {
            totalEarnings += transaction.totalCost;
        }
        return totalEarnings;
    }
};

void welcomeScreen() {
    cout << "\n---------------------------------------" << endl;
    cout << "|       WELCOME TO GPP GAS STATION       |" << endl;
    cout << "|----------------------------------------|" << endl;
    cout << "| PLEASE SELECT AN OPTION:               |" << endl;
    cout << "|----------------------------------------|" << endl;
    cout << "| 1. Add New Customer                    |" << endl;
    cout << "|----------------------------------------|" << endl;
    cout << "| 2. View Today's Customers              |" << endl;
    cout << "|----------------------------------------|" << endl;
    cout << "| 3. View Today's Earnings               |" << endl;
    cout << "|----------------------------------------|" << endl;
    cout << "| 4. Exit                                |" << endl;
    cout << "------------------------------------------" << endl;
}

int main() {
    PriceTicket ticket;
    int choice;

    do {
        welcomeScreen();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Customer customer;
                Vehicle vehicle;

                customer.inputCustomerDetails();
                vehicle.inputVehicleDetails();
                ticket.selectFuelType();
                ticket.generateTicket(customer, vehicle);
                break;
            }
            case 2:
                ticket.showTransactionHistory();  // Display transaction history
                break;
            case 3: {
                double earnings = ticket.calculateTotalEarnings();
                cout << "\nToday's Total Earnings: $" << earnings << endl;
                break;
            }
            case 4:
                cout << "Exiting the program. Thank you!" << endl;
                break;
            default:
                cout << "Invalid option! Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
