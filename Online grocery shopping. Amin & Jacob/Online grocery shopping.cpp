//Weekcha2 Jacob & Amin
#include <iostream>
#include <vector>

// Parent
class GroceryItem {
protected:
    std::string name;
    double price;

public:
    GroceryItem(const std::string& _name, double _price) : name(_name), price(_price) {}


    virtual double calculateTotalCost(int quantity) {
        return price * quantity;
    }
};

// Child
class FreshProduce : public GroceryItem {
private:
    std::string origin;
    double weightInKg;

public:
    FreshProduce(const std::string& _name, double _price, const std::string& _origin, double _weight)
        : GroceryItem(_name, _price), origin(_origin), weightInKg(_weight) {}

    double calculateTotalCost(int quantity) override {
        return price * weightInKg;
    }
};

class CannedGoods : public GroceryItem {
private:
    int quantityInCans;

public:
    CannedGoods(const std::string& _name, double _price, int _quantity)
        : GroceryItem(_name, _price), quantityInCans(_quantity) {}

    double calculateTotalCost(int quantity) override {
        return price * quantityInCans;
    }
};

class BakeryItems : public GroceryItem {
private:
    int quantityInPieces;

public:
    BakeryItems(const std::string& _name, double _price, int _quantity)
        : GroceryItem(_name, _price), quantityInPieces(_quantity) {}

    double calculateTotalCost(int quantity) override {
        return price * quantityInPieces;
    }
};


template<typename T>
double calculateTotalCost(const std::vector<T*>& items, int numItems) {
    double totalCost = 0;
    for (const auto& item : items) {
        totalCost += item->calculateTotalCost(numItems);
    }
    return totalCost;
}

int main() {
    bool shopping = true;
    std::vector<GroceryItem*> shoppingCart;
    std::string origin; // Onödig men står i instruktion
    double discount, totalCost, quantity{};
    char choice;

    while (shopping) {
        std::cout << "Grocery Shoping" << std::endl;
        std::cout << "1. Fresh Produce" << std::endl;
        std::cout << "2. Canned Goods" << std::endl;
        std::cout << "3. Bakery Items" << std::endl;
        std::cout << "4. Checkout" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        std::string name;
        double price;

        switch (choice) {
        case '1':
            name = "Apples";
            price = 29.95;
            std::cout << "Enter origin: ";
            std::cin >> origin;

            // Input validation for weight
            std::cout << "Enter weight in kg: ";
            while (!(std::cin >> quantity) || quantity <= 0) {
                std::cin.clear();  // Clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard invalid input
                std::cout << "Invalid input. Please enter a valid weight in kg: ";
            }

            shoppingCart.push_back(new FreshProduce(name, price, origin, quantity));
            break;

        case '2':
            name = "Canned Soup";
            price = 19.95;

            // Input validation for quantity
            std::cout << "Enter quantity: ";
            while (!(std::cin >> quantity) || quantity <= 0) {
                std::cin.clear();  // Clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard invalid input
                std::cout << "Invalid input. Please enter a valid quantity: ";
            }

            shoppingCart.push_back(new CannedGoods(name, price, quantity));
            break;

        case '3':
            name = "Whole Wheat Bread";
            price = 32.90;

            // Input validation for quantity
            std::cout << "Enter quantity: ";
            while (!(std::cin >> quantity) || quantity <= 0) {
                std::cin.clear();  // Clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard invalid input
                std::cout << "Invalid input. Please enter a valid quantity: ";
            }

            shoppingCart.push_back(new BakeryItems(name, price, quantity));
            break;

        case '4':
            std::cout << "Enter discount percentage: ";
            while (!(std::cin >> discount) || discount < 0 || discount > 100) {
                std::cin.clear();  // Clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard invalid input
                std::cout << "Invalid input. Please enter a valid discount percentage: ";
            }
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n" << std::endl;
            break;
        }
    }

    for (const auto& item : shoppingCart) {
        delete item;
    }

    return 0;
}
