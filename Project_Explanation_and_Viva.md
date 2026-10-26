# Vehicle Rental Management System Using C++
Gray and brown coloured console interface | Single file: main.cpp

## 1. Classes and their purpose
- **Vehicle**: stores data of one vehicle (ID, name, type, price per day, rented status, customer name, days). Data is private; public functions give access.
- **RentalSystem**: holds the list (vector) of all vehicles and performs add, rent, return, display and billing.

## 2. Constructors and objects
- `Vehicle(int, string, string, double)` sets values; every new vehicle starts as available.
- `RentalSystem()` adds 5 predefined vehicles.
- `shop` (in main) is the RentalSystem object. Each vehicle is a Vehicle object.

## 3. Rent function
1. Show available vehicles, ask for ID.
2. `findVehicle()` searches the ID; if not found, print error.
3. If already rented, refuse.
4. Ask days; if days <= 0, refuse.
5. Ask customer name, call `rentVehicle()` (sets rented = true), print bill.

## 4. Return function
Ask ID, check it exists and is rented, then `returnVehicle()` sets rented = false and clears customer and days.

## 5. Rental charge
`Total Rent = pricePerDay * days` (function `calculateRent()`).

## 6. OOP concepts used
Class and object, constructor, encapsulation, private/public access specifiers.
(Inheritance, polymorphism, overloading and file handling were not forced in.)

## 7. Compile and run
```
g++ main.cpp -o rental
./rental            (Windows: rental.exe)
```
Colours work in VS Code terminal, Windows Terminal, Linux and macOS terminals.

## 8. Ten viva questions
1. **What is a class?** A blueprint that groups data and functions together.
2. **What is an object?** A real copy of a class, like `shop`.
3. **What is a constructor?** A function with the class name that runs automatically when an object is created.
4. **What is encapsulation?** Hiding data as private and giving access only through public functions.
5. **Why is data private?** So nobody can change it by mistake.
6. **What does findVehicle() do?** Loops through the list and returns the position of the vehicle, or -1 if not found.
7. **How do you stop double renting?** I check isRented() before renting; if true, the program refuses.
8. **Why use a vector?** It grows automatically when we add vehicles, unlike a fixed array.
9. **Why cin.ignore()?** It removes the leftover Enter key so getline() reads correctly.
10. **What do codes like \033[0m do?** They are special text codes that change or reset the console text colour.
