#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// Structure representing a drink with name, price, and stock quantity.
struct drink {
    string drinks;
    float price;
    float stock;
};

// Structure representing an order with drink number, sugar level, occupation, size, and price.
struct order{
    int numberdrink, sugerlevel, ocup;
    string sizedrink;
    float price;
};

// A 2D vector holding lists of drinks categorized into Coffee (index 0) and Tea (index 1).
vector<vector<drink>> d = {
    {
        {"Espresso", 2, 50}, {"Coffee_with_milk", 1.5, 50}, {"Black_coffee", 1.5, 50}, 
        {"Honey_black_coffee", 2, 50}, {"Cappuccino", 2, 50}, {"Latte\t\t", 2, 50}, {"Mocha", 2, 50}
    },
    {
        {"Green_tea_with_milk", 1.5, 50}, {"Milk_tea", 1.5, 50}, {"Lemonade_tea", 1, 50}, 
        {"Green_tea_honey_lime", 1, 50}, {"Red_tea_with_milk", 1.5, 50}, {"Red_tea_honey_lime", 1, 50}
    }
};

// A vector of strings to hold the type of drinks - "Coffee" and "Tea".
vector<string> typedrink {"Coffee", "Tea"};

// Class to handle saving and loading drink data to and from files.
class savefile {
public:
    // Function to save coffee and tea data to "Coffeesave.txt" and "Teasave.txt" respectively.
    void drinksave() {
        ofstream write("Coffeesave.txt");
        if (write.is_open()) {
            write << typedrink[0] << endl;  // Write the type "Coffee"
            for (const auto& drink : d[0]) {
                write << drink.stock << " " << drink.price << " " << drink.drinks << "\n";  // Write stock, price, and name of each coffee
            }
            write.close();
        }

        ofstream write2("Teasave.txt");
        if (write2.is_open()) {
            write2 << typedrink[1] << endl;  // Write the type "Tea"
            for (const auto& drink : d[1]) {
                write2 << drink.stock << " " << drink.price << " " << drink.drinks << "\n";  // Write stock, price, and name of each tea
            }
            write2.close();
        }
    }

    // Function to load coffee and tea data from "Coffeesave.txt" and "Teasave.txt" respectively.
    void drinkload() {
        ifstream read("Coffeesave.txt");
        if (read.is_open()) {
            d[0].clear();  // Clear existing coffee data
            string line;
            getline(read, line);  // Read the type (Coffee)
            drink loadcoffee;
            while (read >> loadcoffee.stock >> loadcoffee.price) {
                read.ignore();
                getline(read, loadcoffee.drinks);  // Read stock, price, and name of each coffee
                d[0].push_back(loadcoffee);  // Add loaded coffee data to the vector
            }
            read.close();
        }

        ifstream read2("Teasave.txt");
        if (read2.is_open()) {
            d[1].clear();  // Clear existing tea data
            string line;
            getline(read2, line);  // Read the type (Tea)
            drink loadtea;
            while (read2 >> loadtea.stock >> loadtea.price) {
                read2.ignore();
                getline(read2, loadtea.drinks);  // Read stock, price, and name of each tea
                d[1].push_back(loadtea);  // Add loaded tea data to the vector
            }
            read2.close();
        }
    }
};

// Class to display coffee and tea lists.
class drinkview{
public: 
    // Function to display the coffee list with details like name, price, and stock.
    void coffeelist() {
        cout << "\n===== " << typedrink[0] << " ======\n";
        cout << "No\t| Drink name \t\t\t| Price \t| stock \t|\n\n";
        for(size_t j = 0; j < d[0].size(); j++) {            
            cout << j + 1 << "\t|" << d[0][j].drinks << "\t\t\t| " << d[0][j].price << "$\t| " << d[0][j].stock << " cup\t|\n";
        }
    }

    // Function to display the tea list with details like name, price, and stock.
    void tealist() {
        cout << "\n===== " << typedrink[1] << " ======\n";
        cout << "No\t| Drink name \t\t\t| Price \t| stock \t|\n\n";
        for(size_t j = 0; j < d[1].size(); j++) {            
            cout << j + 1 << "\t|" << d[1][j].drinks << "\t\t\t| " << d[1][j].price << "$\t| " << d[1][j].stock << " cup\t|\n";
        } 
    }
};


class updatedrinks : public drinkview {
public: 
    savefile save;  // Instance of savefile class to handle saving drink data

    // Function to update the stock of drinks (both coffee and tea)
    void updatestock() {
        string option;
        int No;
        int cup;
        while(1) {
            // Display menu for updating stock
            cout << "\n=== Updating drink stock =====\n";
            cout << "1. Coffee\n";
            cout << "2. Tea\n";
            cout << "3. Quit\n";
            cout << "Please enter your option: ";
            cin >> option;

            if(option == "1") {
                // Show coffee list and prompt for input
                coffeelist();
                cout << "Enter drink No: ";
                cin >> No;
                cout << "How many cups do you want to add more: ";
                cin >> cup;

                // Validate input and update stock
                if(No > 0 && No <= d[0].size()) {
                    for(size_t j = 0; j < d[0].size(); j++) {
                        if(No == j + 1) {
                            d[0][j].stock += cup;
                            cout << "Successfully added\n";
                        }
                    }
                } else {
                    cout << "Please enter a valid number.\n";
                }

            } else if(option == "2") {
                // Show tea list and prompt for input
                tealist();
                cout << "Enter drink No: ";
                cin >> No;
                cout << "How many cups do you want to add more: ";
                cin >> cup;

                // Validate input and update stock
                if(No > 0 && No <= d[1].size()) {
                    for(size_t j = 0; j < d[1].size(); j++) {
                        if(No == j + 1) {
                            d[1][j].stock += cup;
                            cout << "Successfully added\n";
                        }
                    }
                } else {
                    cout << "Please enter a valid number.\n";
                }

            } else if(option == "3") {
                // Save updated stock to files and exit loop
                save.drinksave();
                break;
            }
        }
    }

    // Function to update the price of drinks (both coffee and tea)
    void updateprice() {
        string option;
        int No;
        double price;
        while(1) {
            // Display menu for updating price
            cout << "\n=== Updating drink price =====\n";
            cout << "1. Coffee\n";
            cout << "2. Tea\n";
            cout << "3. Quit\n";
            cout << "Please enter your option: ";
            cin >> option;

            if(option == "1") {
                // Show coffee list and prompt for input
                coffeelist();
                cout << "Enter drink No: ";
                cin >> No;
                cout << "What price do you want to change to: ";
                cin >> price;

                // Validate input and update price
                if(No > 0 && No <= d[0].size()) {
                    for(size_t j = 0; j < d[0].size(); j++) {
                        if(No == j + 1) {
                            cout << d[0][j].drinks << " from " << d[0][j].price << "$ to "; 
                            d[0][j].price = price;
                            cout << d[0][j].price << "$\n";
                            cout << "Successfully added\n";
                        }
                    }
                } else {
                    cout << "Please enter a valid number.\n";
                }

            } else if(option == "2") {
                // Show tea list and prompt for input
                tealist();
                cout << "Enter drink No: ";
                cin >> No;
                cout << "What price do you want to change to: ";
                cin >> price;

                // Validate input and update price
                if(No > 0 && No <= d[1].size()) {
                    for(size_t j = 0; j < d[1].size(); j++) {
                        if(No == j + 1) {
                            cout << d[1][j].drinks << " from " << d[1][j].price << "$ to "; 
                            d[1][j].price = price;
                            cout << d[1][j].price << "$\n";
                            cout << "Successfully added\n";
                        }
                    }
                } else {
                    cout << "Please enter a valid number.\n";
                }

            } else if(option == "3") {
                // Save updated prices to files and exit loop
                save.drinksave();
                break;
            }
        }
    }


    void adddrink() {
    string o;
    drink AddDrink;

    while (1) {
        // Display menu for adding a new drink
        cout << "=== Add more drink ===\n";
        cout << "What type of new drink do you want to add\n";
        cout << "1. Coffee\n";
        cout << "2. Tea\n";
        cout << "3. Quit\n";
        cout << "Please enter your option: ";
        cin >> o;

        if (o == "3") {
            // Save new drinks to file and exit loop
            save.drinksave();
            break;
        }

        // Get new drink details from the user
        cout << "Please enter new drink name: ";
        cin.ignore();
        getline(cin, AddDrink.drinks);
        cout << "Please enter new drink price: ";
        cin >> AddDrink.price;
        cout << "Please enter new drink stock: ";
        cin >> AddDrink.stock;

        // Add new drink to the appropriate list
        if (o == "1") {
            d[0].push_back(AddDrink);
            cout << "New drink is added successfully.\n";
        } else if (o == "2") {
            d[1].push_back(AddDrink);
        }
    }
}

void deletedrink() {
    int No;
    string option;

    while (1) {
        // Display menu for deleting a drink
        cout << "=== Delete drink ===\n";
        cout << "What type of drink do you want to delete\n";
        cout << "1. Coffee\n";
        cout << "2. Tea\n";
        cout << "3. Quit\n";
        cout << "Please enter your option: ";
        cin >> option;

        if (option == "3") {
            // Save changes to file and exit loop
            save.drinksave();
            break;
        }

        if (option == "1") {
            // Show coffee list and prompt for drink number to delete
            coffeelist();
            cout << "Please enter drink No: ";
            cin >> No;

            // Validate input and delete selected drink
            if (No > 0 && No <= d[0].size()) {
                for (size_t j = 0; j < d[0].size(); j++) {
                    if (No == j + 1) {
                        d[0].erase(d[0].begin() + j);
                        cout << "Successfully deleted\n";
                    }
                }
            } else {
                cout << "Please enter a valid number.\n";
            }
        } else if (option == "2") {
            // Show tea list and prompt for drink number to delete
            tealist();
            cout << "Please enter drink No: ";
            cin >> No;

            // Validate input and delete selected drink
            if (No > 0 && No <= d[1].size()) {
                for (size_t j = 1; j < d[1].size(); j++) {
                    if (No == j + 1) {
                        d[1].erase(d[1].begin() + j);
                        cout << "Successfully deleted\n";
                    }
                }
            } else {
                cout << "Please enter a valid number.\n";
            }
        }
    }
}
};
class seller : public updatedrinks{
    public: 
        void viewdrinks() {
    // Display the list of all drinks (both coffee and tea) with their prices and stock levels
    for (size_t i = 0; i < typedrink.size(); i++) {
        cout << "\n===== " << typedrink[i] << " ======\n";
        cout << "No\t| Drink name \t\t\t\t| Price | stock \t|\n\n";
        for (size_t j = 0; j < d[i].size(); j++) {            
            cout << j + 1 << "\t|" << d[i][j].drinks << "\t\t\t| " << d[i][j].price << "$\t| " << d[i][j].stock << " cup\t|\n";
        }    
    }
    // Save the updated drink data to the file
    save.drinksave();
}

void updatedrink() {
    string opt;

    while (1) {
        // Display the menu for updating drink information
        cout << "\n=== Update drink ====\n";
        cout << "1. Update drink stock\n";
        cout << "2. Update drink price\n";
        cout << "3. Add more drink\n";
        cout << "4. Delete drink\n";
        cout << "5. Quit\n";
        cout << "Please enter your option: ";
        cin >> opt;

        // Handle the user's option
        if (opt == "1") {
            updatestock();  // Update the stock of a drink
        } else if (opt == "2") {
            updateprice();  // Update the price of a drink
        } else if (opt == "3") {
            adddrink();  // Add a new drink to the list
        } else if (opt == "4") {
            deletedrink();  // Delete a drink from the list
        } else if (opt == "5") {
            break;  // Exit the loop and stop updating drinks
        }
    }
}

void lowdrinklist() {
    bool found = false;

    // Display drinks with low stock (<= 10)
    for (size_t i = 0; i < typedrink.size(); i++) {
        cout << "\n===== " << typedrink[i] << " ======\n";
        cout << "No\t| Drink name \t\t\t\t| Price | stock \t|\n\n";
        for (size_t j = 0; j < d[i].size(); j++) {
            if (d[i][j].stock <= 10) {            
                cout << j + 1 << "\t|" << d[i][j].drinks << "\t\t\t| " << d[i][j].price << "$\t| " << d[i][j].stock << " cup\t|\n";
                found = true;
            }
        }    
    }

    // If no low stock drinks were found, print a message
    if (!found) {
        cout << "There is no low drink stock.\n";
    }

    // Save the updated drink data to the file
    save.drinksave();
}

};
class customer : public drinkview {
    private: 
        int customers = 0; // Tracks the number of customers
        vector<vector<order>> coffeeorders; // Stores coffee orders for multiple customers
        vector<vector<order>> teaorders; // Stores tea orders for multiple customers
        vector<float> totalcost; // Stores the total cost for each customer

    public: 
        savefile save; // Instance of savefile to manage saving/loading operations
        
        // Constructor to initialize and resize the vectors for handling up to 100 customers
        customer() {
            coffeeorders.resize(100); // Resize to handle 100 customers' coffee orders
            teaorders.resize(100); // Resize to handle 100 customers' tea orders
            totalcost.resize(100); // Resize to handle 100 customers' total costs
        }
        
        // Function to load customer orders from files
        void customersload() {
            ifstream readcoffee("customercoffeesave.txt"); // Open file to read coffee orders
            ifstream readtea("customerteasave.txt"); // Open file to read tea orders

            // Clear existing data in vectors to prepare for loading new data
            coffeeorders.clear();
            teaorders.clear();
            totalcost.clear();

            // Loop to read and load customer orders from the files
            while (true) {
                int coffeesize, teasize; // Variables to store the number of coffee/tea orders for a customer
                order ord; // Variable to store a single order
                vector<order> coffeeOrderList, teaOrderList; // Temporary vectors to hold orders for a customer
                double cost; // Variable to store the total cost for a customer

                // Read the number of coffee orders for the current customer
                if (!(readcoffee >> coffeesize)) break; // Break the loop if reading fails or reaches the end
                for (int i = 0; i < coffeesize; i++) {
                    // Read the details of each coffee order and add it to the list
                    readcoffee >> ord.sugerlevel
                               >> ord.sizedrink
                               >> ord.ocup
                               >> ord.price
                               >> ord.numberdrink;
                    coffeeOrderList.push_back(ord); // Add the order to the coffee order list
                }

                // Read the number of tea orders for the current customer
                if (!(readtea >> teasize)) break; // Break the loop if reading fails or reaches the end
                for (int i = 0; i < teasize; i++) {
                    // Read the details of each tea order and add it to the list
                    readtea >> ord.sugerlevel
                            >> ord.sizedrink
                            >> ord.ocup
                            >> ord.price
                            >> ord.numberdrink;
                    teaOrderList.push_back(ord); // Add the order to the tea order list
                }

                // Read the total cost for the current customer
                if (!(readtea >> cost)) break; // Break the loop if reading fails or reaches the end

                // Store the lists of coffee and tea orders and the total cost for the customer
                coffeeorders.push_back(coffeeOrderList);
                teaorders.push_back(teaOrderList);
                totalcost.push_back(cost);

                customers++; // Increment the customer count
            }

            // Close the files after reading
            readcoffee.close();
            readtea.close();
        }


    void CoffeE() {
    string order_answer; // Variable to store the user's response for ordering more coffee
    order order_drink; // Variable to store the details of the current coffee order
    
    // Prompt the user to start ordering coffee for the current customer
    cout << "Order for " << customers + 1 << " customers\n";
    coffeelist(); // Display the list of available coffee options
    
    while (1) { // Loop to handle multiple coffee orders for a customer
        // Prompt the user for coffee order details
        cout << "\nWhat coffee do you want to order: ";
        cout << "\nPlease enter your drink No number: ";
        cin >> order_drink.numberdrink;
        cout << "What size do you want (L, M, or S): ";
        cin >> order_drink.sizedrink;
        cout << "Please enter your sugar level number in percent (%): ";
        cin >> order_drink.sugerlevel;
        cout << "How many cups do you want for this drink: ";
        cin >> order_drink.ocup;

        // Update stock and calculate the price based on the drink size
        if (order_drink.numberdrink > 0 && order_drink.numberdrink <= d[0].size()) {
            d[0][order_drink.numberdrink - 1].stock -= order_drink.ocup; // Decrease the stock by the number of cups ordered

            // Adjust the price based on the size of the drink
            if (order_drink.sizedrink == "L" || order_drink.sizedrink == "l") {
                order_drink.price = (d[0][order_drink.numberdrink - 1].price + 0.5) * order_drink.ocup;
            } else if (order_drink.sizedrink == "M" || order_drink.sizedrink == "m") {
                order_drink.price = d[0][order_drink.numberdrink - 1].price * order_drink.ocup;
            } else if (order_drink.sizedrink == "S" || order_drink.sizedrink == "s") {
                order_drink.price = (d[0][order_drink.numberdrink - 1].price - 0.25) * order_drink.ocup;
            }

            // Store the coffee order for the current customer
            coffeeorders[customers].push_back(order_drink);
        } else {
            cout << "Invalid drink number. Please try again.\n"; // Handle invalid drink numbers
            continue; // Continue to the next iteration of the loop
        }

        // Ask the user if they want to order more coffee
        cout << "Do you want to order more coffee?\n(yes|no)?: ";
        cin >> order_answer;

        if (order_answer == "yes") {
            // If the user wants to order more coffee, continue the loop
        } else {
            save.drinksave(); // Save the drink order if the user is done
            break; // Exit the loop
        }
    }
}

void Tea() {
    string order_answer; // Variable to store the user's response for ordering more tea
    order order_drink; // Variable to store the details of the current tea order
    
    // Prompt the user to start ordering tea for the current customer
    cout << "Order for " << customers + 1 << " customers\n";
    tealist(); // Display the list of available tea options
    
    while (1) { // Loop to handle multiple tea orders for a customer
        // Prompt the user for tea order details
        cout << "\nWhat tea do you want to order: ";
        cout << "\nPlease enter your drink No number: ";
        cin >> order_drink.numberdrink;
        cout << "What size do you want (L, M, or S): ";
        cin >> order_drink.sizedrink;
        cout << "Please enter your sugar level number in percent (%): ";
        cin >> order_drink.sugerlevel;
        cout << "How many cups do you want for this drink: ";
        cin >> order_drink.ocup;

        // Update stock and calculate the price based on the drink size
        if (order_drink.numberdrink > 0 && order_drink.numberdrink <= d[1].size()) {
            d[1][order_drink.numberdrink - 1].stock -= order_drink.ocup; // Decrease the stock by the number of cups ordered

            // Adjust the price based on the size of the drink
            if (order_drink.sizedrink == "L" || order_drink.sizedrink == "l") {
                order_drink.price = (d[0][order_drink.numberdrink - 1].price + 0.5) * order_drink.ocup;
            } else if (order_drink.sizedrink == "M" || order_drink.sizedrink == "m") {
                order_drink.price = d[0][order_drink.numberdrink - 1].price * order_drink.ocup;
            } else if (order_drink.sizedrink == "S" || order_drink.sizedrink == "s") {
                order_drink.price = (d[0][order_drink.numberdrink - 1].price - 0.25) * order_drink.ocup;
            }

            // Store the tea order for the current customer
            teaorders[customers].push_back(order_drink);
        } else {
            cout << "Invalid drink number. Please try again.\n"; // Handle invalid drink numbers
            continue; // Continue to the next iteration of the loop
        }

        // Ask the user if they want to order more tea
        cout << "Do you want to order more coffee?\n(yes|no)?: ";
        cin >> order_answer;

        if (order_answer == "yes") {
            // If the user wants to order more tea, continue the loop
        } else {
            save.drinksave(); // Save the drink order if the user is done
            break; // Exit the loop
        }
    }
}

    void vieworder() {
    bool tfounded = false, cfounded = false; // Flags to check if any tea or coffee orders are found

    // Open a file to write the receipt for the current customer
    ofstream write("Recipt" + to_string(customers + 1) + ".txt");

    // Write header information for the receipt
    write << "Customer " << customers + 1 << "'s receipt" << endl;

    float coffeetotal = 0, teatotal = 0, total = 0; // Variables to store the total costs
    cout << customers + 1 << "# " << "Customer\n"; // Display customer number
    cout << "== Coffee order ==\n"; // Display section header for coffee orders
    write << "== Coffee order ==\n"; // Write section header for coffee orders to the file
    
    // Loop through the coffee orders for the current customer
    for (size_t i = 0; i < coffeeorders[customers].size(); i++) {
        // Display and write each coffee order's details
        cout << i + 1 << ". " << d[0][coffeeorders[customers][i].numberdrink - 1].drinks
             << "\tSugar level: " << coffeeorders[customers][i].sugerlevel
             << "\tSize: " << coffeeorders[customers][i].sizedrink
             << "\tQuantity: " << coffeeorders[customers][i].ocup << " cups"
             << "\tPrice: " << coffeeorders[customers][i].price << "$\n";

        write << i + 1 << ". " << d[0][coffeeorders[customers][i].numberdrink - 1].drinks
             << "\tSugar level: " << coffeeorders[customers][i].sugerlevel
             << "\tSize: " << coffeeorders[customers][i].sizedrink
             << "\tQuantity: " << coffeeorders[customers][i].ocup << " cups"
             << "\tPrice: " << coffeeorders[customers][i].price << "$\n";

        if (coffeeorders.size() > 0) {
            cfounded = true; // Set flag if coffee orders are found
        }

        coffeetotal += coffeeorders[customers][i].price; // Add to the total coffee cost
    }

    if (cfounded == false) {
        cout << "There are no coffee orders from " << customers + 1 << "# customer." << endl; // Display if no coffee orders are found
        write << "There are no coffee orders from " << customers + 1 << "# customer." << endl; 
    }

    cout << "== Tea order ==\n"; // Display section header for tea orders
    write << "== Tea order ==\n"; // Write section header for tea orders to the file
    
    // Loop through the tea orders for the current customer
    for (size_t i = 0; i < teaorders[customers].size(); i++) {
        // Display and write each tea order's details
        cout << i + 1 << ". " << d[1][teaorders[customers][i].numberdrink - 1].drinks
             << "\tSugar level: " << teaorders[customers][i].sugerlevel
             << "\tSize: " << teaorders[customers][i].sizedrink
             << "\tQuantity: " << teaorders[customers][i].ocup << " cups"
             << "\tPrice: " << teaorders[customers][i].price << "$\n";

        write << i + 1 << ". " << d[1][teaorders[customers][i].numberdrink - 1].drinks
             << "\tSugar level: " << teaorders[customers][i].sugerlevel
             << "\tSize: " << teaorders[customers][i].sizedrink
             << "\tQuantity: " << teaorders[customers][i].ocup << " cups"
             << "\tPrice: " << teaorders[customers][i].price << "$\n";

        if (teaorders.size() > 0) {
            tfounded = true; // Set flag if tea orders are found
        }

        teatotal += teaorders[customers][i].price; // Add to the total tea cost
    }

    if (tfounded == false) {
        cout << "There are no tea orders from " << customers + 1 << "# customer." << endl; // Display if no tea orders are found
        write << "There are no tea orders from " << customers + 1 << "# customer." << endl;
    }

    total = coffeetotal + teatotal; // Calculate the total cost for the customer
    totalcost[customers] = total; // Set the total cost for the current customer
    
    // Display the total cost
    cout << "=======================================================================\n";
    cout << "\t\t\t\t Total cost: " << total << "$" << endl;
    customers++; // Increment the customer count

    // Write the total cost to the receipt file
    write << "=======================================================================\n";
    write << "\t\t\t\t Total cost: " << total << "$" << endl;

    save.drinksave(); // Save the drink orders
}

void customersave() {
    // Open files to save coffee and tea orders
    ofstream writecoffee("customercoffeesave.txt");
    ofstream writetea("customerteasave.txt");

    // Loop through all customers to save their orders
    for (int i = 0; i < customers; i++) {
        // Write coffee orders
        writecoffee << coffeeorders[i].size() << endl;
        for (size_t j = 0; j < coffeeorders[i].size(); j++) {
            writecoffee << coffeeorders[i][j].sugerlevel << " "
                        << coffeeorders[i][j].sizedrink << " "
                        << coffeeorders[i][j].ocup << " "
                        << coffeeorders[i][j].price << " "
                        << coffeeorders[i][j].numberdrink << endl;
        }

        // Write tea orders
        writetea << teaorders[i].size() << endl;
        for (size_t j = 0; j < teaorders[i].size(); j++) {
            writetea << teaorders[i][j].sugerlevel << " "
                     << teaorders[i][j].sizedrink << " "
                     << teaorders[i][j].ocup << " "
                     << teaorders[i][j].price << " "
                     << teaorders[i][j].numberdrink << endl;
        }

        // Write total cost
        writetea << totalcost[i] << endl;
    }
}

    void history() {
    bool tfounded[100], cfounded[100]; // Arrays to check if any tea or coffee orders are found for each customer

    // Initialize all elements of tfounded and cfounded to false
    for (int i = 0; i <= 100; i++) {
        tfounded[i] = false;
        cfounded[i] = false;
    }

    // Loop through each customer
    for (int i = 0; i < customers; i++) {
        cout << i + 1 << "# " << "Customer\n"; // Display customer number
        cout << "== Coffee order ==\n"; // Display section header for coffee orders
        
        // Loop through and display each coffee order for the current customer
        for (size_t j = 0; j < coffeeorders[i].size(); j++) {
            cout << j + 1 << ". " << d[0][coffeeorders[i][j].numberdrink - 1].drinks
                 << "\tSugar level: " << coffeeorders[i][j].sugerlevel
                 << "\tSize: " << coffeeorders[i][j].sizedrink
                 << "\tQuantity: " << coffeeorders[i][j].ocup << " cups"
                 << "\tPrice: " << coffeeorders[i][j].price << "$\n";
        }

        // Set the flag if any coffee orders exist for the current customer
        if (coffeeorders[i].size() > 0) {
            cfounded[i] = true;
        }

        // If no coffee orders are found, display a message
        if (cfounded[i] == false) {
            cout << "There are no coffee orders from " << i + 1 << "# customer." << endl;
        }

        cout << "== Tea order ==\n"; // Display section header for tea orders
        
        // Loop through and display each tea order for the current customer
        for (size_t j = 0; j < teaorders[i].size(); j++) {
            cout << j + 1 << ". " << d[1][teaorders[i][j].numberdrink - 1].drinks
                 << "\tSugar level: " << teaorders[i][j].sugerlevel
                 << "\tSize: " << teaorders[i][j].sizedrink
                 << "\tQuantity: " << teaorders[i][j].ocup << " cups"
                 << "\tPrice: " << teaorders[i][j].price << "$\n";
        }

        // Set the flag if any tea orders exist for the current customer
        if (teaorders[i].size() > 0) {
            tfounded[i] = true;
        }

        // If no tea orders are found, display a message
        if (tfounded[i] == false) {
            cout << "There are no tea orders from " << i + 1 << "# customer." << endl;
        }

        // Display the total cost for the current customer
        cout << "=======================================================================\n";
        cout << "\t\t\t\t Total cost: " << totalcost[i] << "$" << endl;
    }
    save.drinksave(); // Save the drink orders
}

};

int main() {
    savefile save; // Create a savefile object to handle saving and loading of drink data
    save.drinkload(); // Load the saved drink data
    string choice; // Variable to store user choices
    seller s; // Create a seller object
    customer c; // Create a customer object
    c.customersload(); // Load customer data

    while (1) { // Infinite loop for the main menu
        cout << "===== Coffee Shop Management ======" << endl;
        cout << "1. Use as the seller.\n";
        cout << "2. Use as the customer.\n";
        cout << "3. Shut down the system.\n";
        cout << "Please enter your choice: ";
        cin >> choice;

        c.customersave(); // Save customer data after each operation
        
        // Check if the user chose to use the seller system
        if (choice == "1") {
            while (1) { // Loop for password prompt
                string password;
                cout << "Please enter the password: ";
                cin >> password;

                if (password == "1234") { // Correct password to access the seller menu
                    break;
                } else {
                    cout << "Password is incorrect.\nPlease try again.\n";
                }
            }
            
            // Seller menu loop
            while (1) {
                string option;
                cout << "=== Seller Menu ===\n";
                cout << "1. View all drinks stock.\n";
                cout << "2. Update drink.\n";
                cout << "3. View all low stock drinks.\n";
                cout << "4. View order history.\n";
                cout << "5. Exit the seller system.\n";
                cout << "Please enter your option: ";
                cin >> option;

                // Perform actions based on the seller's choice
                if (option == "1") {
                    s.viewdrinks();
                } else if (option == "2") {
                    s.updatedrink();
                } else if (option == "3") {
                    s.lowdrinklist();
                } else if (option == "4") {
                    c.history(); // View the order history for all customers
                } else if (option == "5") {
                    break; // Exit the seller menu
                }
            }
        }

        // Check if the user chose to use the customer system
        else if (choice == "2") {
            while (1) { // Customer menu loop
                string option;
                cout << "=== Customer Menu ===\n";
                cout << "1. Order coffee.\n";
                cout << "2. Order tea.\n";
                cout << "3. View your order and Quit.\n";
                cout << "Please enter your option: ";
                cin >> option;

                // Perform actions based on the customer's choice
                if (option == "1") {
                    c.CoffeE(); // Place a coffee order
                } else if (option == "2") {
                    c.Tea(); // Place a tea order
                } else if (option == "3") {
                    c.vieworder(); // View the order summary
                    system("pause"); // Pause the system before quitting
                    break;
                }
            }
        }

        // Check if the user chose to shut down the system
        else if (choice == "3") {
            break; // Exit the main menu loop and shut down the system
        }
    }
}
