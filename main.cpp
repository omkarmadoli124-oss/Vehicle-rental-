// ===================================================
//  Project : Vehicle Rental Management System
//  Language: C++ (console application, single file)
//  Theme   : Gray and Brown coloured text interface
// ===================================================
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

// ---------- Colour codes (ANSI escape codes) ----------
// These special strings change the colour of the text in the console.
const string BROWN  = "\033[38;5;130m";            // brown text
const string GRAY   = "\033[38;5;250m";            // gray text
const string HEADER = "\033[48;5;94m\033[97m";     // brown background, white text
const string RESET  = "\033[0m";                   // back to normal colour

// ---------- Class 1: Vehicle ----------
// Stores the data of ONE vehicle (encapsulation: data is private).
class Vehicle {
private:
    int id;
    string name;
    string type;
    double pricePerDay;
    bool rented;            // true = rented, false = available
    string customerName;    // who rented it
    int days;               // for how many days

public:
    // Constructor: runs automatically when an object is created
    Vehicle(int i, string n, string t, double p) {
        id = i;
        name = n;
        type = t;
        pricePerDay = p;
        rented = false;     // a new vehicle is always available
        customerName = "";
        days = 0;
    }

    // Getter functions: give safe read-only access to private data
    int getId()            { return id; }
    string getName()       { return name; }
    string getType()       { return type; }
    double getPrice()      { return pricePerDay; }
    bool isRented()        { return rented; }
    string getCustomer()   { return customerName; }
    int getDays()          { return days; }

    // Mark the vehicle as rented
    void rentVehicle(string cust, int d) {
        rented = true;
        customerName = cust;
        days = d;
    }

    // Mark the vehicle as available again
    void returnVehicle() {
        rented = false;
        customerName = "";
        days = 0;
    }

    // Total rent = price per day x number of days
    double calculateRent(int d) {
        return pricePerDay * d;
    }

    // Print one row of the vehicle table
    void display() {
        cout << GRAY << left
             << setw(6)  << id
             << setw(18) << name
             << setw(10) << type
             << setw(12) << pricePerDay
             << BROWN << (rented ? "Rented" : "Available")
             << RESET << endl;
    }
};

// ---------- Class 2: RentalSystem ----------
// Controls all vehicles and all menu operations.
class RentalSystem {
private:
    vector<Vehicle> vehicles;   // list of all vehicles

    // Return the position of a vehicle in the list, or -1 if not found
    int findVehicle(int id) {
        for (int i = 0; i < (int)vehicles.size(); i++) {
            if (vehicles[i].getId() == id)
                return i;
        }
        return -1;
    }

    // Print the table heading
    void printTableHeading() {
        cout << HEADER << left
             << setw(6)  << "ID"
             << setw(18) << "Name"
             << setw(10) << "Type"
             << setw(12) << "Price/Day"
             << setw(12) << "Status" << RESET << endl;
    }

public:
    // Constructor: adds some predefined vehicles at the start
    RentalSystem() {
        vehicles.push_back(Vehicle(101, "Maruti Swift", "Car", 1500));
        vehicles.push_back(Vehicle(102, "Hyundai Creta", "Car", 2500));
        vehicles.push_back(Vehicle(103, "Honda Activa", "Scooter", 500));
        vehicles.push_back(Vehicle(104, "Royal Enfield", "Bike", 900));
        vehicles.push_back(Vehicle(105, "Tata Ace", "Truck", 3000));
    }

    // Feature 1: show only available vehicles
    void displayAvailable() {
        cout << BROWN << "\n--- AVAILABLE VEHICLES ---\n" << RESET;
        printTableHeading();
        int count = 0;
        for (int i = 0; i < (int)vehicles.size(); i++) {
            if (!vehicles[i].isRented()) {
                vehicles[i].display();
                count++;
            }
        }
        if (count == 0)
            cout << GRAY << "No vehicle is available right now.\n" << RESET;
    }

    // Feature 2: add a new vehicle
    void addVehicle() {
        int id;
        string name, type;
        double price;

        cout << GRAY << "Enter vehicle ID: " << RESET;
        cin >> id;
        if (findVehicle(id) != -1) {          // ID must be unique
            cout << BROWN << "Error: This ID already exists!\n" << RESET;
            return;
        }
        cin.ignore();                         // remove the leftover Enter key
        cout << GRAY << "Enter vehicle name: " << RESET;
        getline(cin, name);
        cout << GRAY << "Enter vehicle type (Car/Bike/Scooter/Truck): " << RESET;
        getline(cin, type);
        cout << GRAY << "Enter rent per day: " << RESET;
        cin >> price;

        if (price <= 0) {
            cout << BROWN << "Error: Price must be greater than zero!\n" << RESET;
            return;
        }
        vehicles.push_back(Vehicle(id, name, type, price));
        cout << BROWN << "Vehicle added successfully!\n" << RESET;
    }

    // Feature 3: rent a vehicle and print the bill
    void rentVehicle() {
        int id, days;
        string customer;

        displayAvailable();
        cout << GRAY << "\nEnter vehicle ID to rent: " << RESET;
        cin >> id;

        int pos = findVehicle(id);
        if (pos == -1) {                              // wrong ID
            cout << BROWN << "Error: Invalid vehicle ID!\n" << RESET;
            return;
        }
        if (vehicles[pos].isRented()) {               // already rented
            cout << BROWN << "Sorry, this vehicle is already rented!\n" << RESET;
            return;
        }

        cout << GRAY << "Enter number of rental days: " << RESET;
        cin >> days;
        if (days <= 0) {                              // days must be > 0
            cout << BROWN << "Error: Days must be greater than zero!\n" << RESET;
            return;
        }

        cin.ignore();
        cout << GRAY << "Enter customer name: " << RESET;
        getline(cin, customer);

        vehicles[pos].rentVehicle(customer, days);    // mark as rented
        printBill(pos);
    }

    // Feature 4: return a vehicle
    void returnVehicle() {
        int id;
        cout << GRAY << "Enter vehicle ID to return: " << RESET;
        cin >> id;

        int pos = findVehicle(id);
        if (pos == -1) {
            cout << BROWN << "Error: Invalid vehicle ID!\n" << RESET;
            return;
        }
        if (!vehicles[pos].isRented()) {
            cout << BROWN << "This vehicle was not rented!\n" << RESET;
            return;
        }
        vehicles[pos].returnVehicle();                // make it available
        cout << BROWN << "Vehicle returned successfully. It is available now.\n" << RESET;
    }

    // Feature 5: show only rented vehicles
    void displayRented() {
        cout << BROWN << "\n--- RENTED VEHICLES ---\n" << RESET;
        printTableHeading();
        int count = 0;
        for (int i = 0; i < (int)vehicles.size(); i++) {
            if (vehicles[i].isRented()) {
                vehicles[i].display();
                cout << GRAY << "      Customer: " << vehicles[i].getCustomer()
                     << " | Days: " << vehicles[i].getDays() << RESET << endl;
                count++;
            }
        }
        if (count == 0)
            cout << GRAY << "No vehicle is rented right now.\n" << RESET;
    }

    // Feature 6: show all vehicles
    void displayAll() {
        cout << BROWN << "\n--- ALL VEHICLES ---\n" << RESET;
        printTableHeading();
        for (int i = 0; i < (int)vehicles.size(); i++)
            vehicles[i].display();
    }

    // Print the rental bill of the vehicle at position pos
    void printBill(int pos) {
        double total = vehicles[pos].calculateRent(vehicles[pos].getDays());
        cout << BROWN << "\n==============================\n";
        cout << "        RENTAL BILL\n";
        cout << "==============================\n" << GRAY;
        cout << "Customer     : " << vehicles[pos].getCustomer() << endl;
        cout << "Vehicle      : " << vehicles[pos].getName() << endl;
        cout << "Rental Days  : " << vehicles[pos].getDays() << endl;
        cout << "Price/Day    : Rs. " << vehicles[pos].getPrice() << endl;
        cout << BROWN << "------------------------------\n";
        cout << "TOTAL AMOUNT : Rs. " << total << endl;
        cout << "==============================\n" << RESET;
    }
};

// ---------- Show the main menu ----------
void showMenu() {
    cout << HEADER << "\n   VEHICLE RENTAL MANAGEMENT SYSTEM    " << RESET << endl;
    cout << GRAY;
    cout << " 1. Display Available Vehicles\n";
    cout << " 2. Add New Vehicle\n";
    cout << " 3. Rent a Vehicle\n";
    cout << " 4. Return a Vehicle\n";
    cout << " 5. Display Rented Vehicles\n";
    cout << " 6. Display All Vehicles\n";
    cout << " 7. Exit\n" << RESET;
    cout << BROWN << "Enter your choice: " << RESET;
}

// ---------- main function ----------
int main() {
    RentalSystem shop;      // object of RentalSystem (constructor adds vehicles)
    int choice;

    do {
        showMenu();
        if (!(cin >> choice)) {          // user typed letters instead of a number
            cin.clear();                 // clear the error
            cin.ignore(1000, '\n');      // throw away the wrong input
            choice = 0;
        }

        switch (choice) {
            case 1: shop.displayAvailable(); break;
            case 2: shop.addVehicle();       break;
            case 3: shop.rentVehicle();      break;
            case 4: shop.returnVehicle();    break;
            case 5: shop.displayRented();    break;
            case 6: shop.displayAll();       break;
            case 7: cout << BROWN << "Thank you! Goodbye.\n" << RESET; break;
            default: cout << BROWN << "Invalid choice! Try again.\n" << RESET;
        }
    } while (choice != 7);

    return 0;
}
