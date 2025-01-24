# Gas_Station-CPP

# Overview

* The Fuel Management System is an object-oriented C++ application designed to manage customer transactions in a fuel station. It allows users to capture customer and vehicle details, select fuel types, generate price tickets, and maintain transaction records. This system emphasizes modular design, inheritance, polymorphism, and efficient file handling.

# Features

* Customer Management:
Captures and stores customer details such as name, age, address, and contact.

* Vehicle Management:
Records vehicle details, including type and registration number.

* Fuel Selection and Pricing:
Supports Petrol, Diesel, and CNG with specific price rates for each.

* Transaction Management:
Generates price tickets with detailed information.
Maintains a history of all transactions.

* User-Friendly Interface:
Provides a structured and interactive experience for users.

-----------------------------------------------------------------------------------------------------
# Classes and Functions

1. Customer Class

Attributes: name, age, address, contact
Functions: inputCustomerDetails()

2. Vehicle Class

Attributes: type, number

Functions: inputVehicleDetails()

3. Fuel Class

Attributes: price, quantity

Virtual Functions:

inputFuelDetails()

calculateTotal()

getPrice()

getQuantity()

4. Derived Fuel Classes (Petrol, Diesel, CNG)

Implements inputFuelDetails() and calculateTotal() for each fuel type with specific rates.

5. PriceTicket Class

Functions:

selectFuelType()

generateTicket()

showTransactionHistory()

calculateTotalEarnings()
