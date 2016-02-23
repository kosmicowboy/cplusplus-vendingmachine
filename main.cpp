#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Product {
public:
    Product(string d, int p ) :desc(d), price(p) {}
    string getDescription() const { return desc; }
    int getPrice() const { return price ;}
    void print() {
        cout << " " << desc << " price = " << price ;
    }
private:
    string desc;
    int price;
};

class ProductQ :public Product {
public:
    ProductQ(string d, int p, int q):Product(d,p) {
        quantity = q;
    }
    void setQuantity() { quantity--; }; //sold an item
    int getQuantity() { return quantity; }
private:
    int quantity;
};

class ProductRow {
public:
    ProductRow() {}
    ProductRow(vector<ProductQ> p) :v(p){}
    ProductQ getItem(int i) const { return v[i]; } // single item returned
    vector<ProductQ> getItems() const { return v; } // all items returned
private:
    vector<ProductQ> v;
};

class Keypad {
public:
    Keypad() {}
    void getInput() {
        cin >> input;
    }

    string getUserInput() { return input; }
private:
    string input;
};

class Money {
public:
    Money(int t = 0) :total(t) { currentTotal = 0; }
    void addCoin() { currentTotal++; }
    int getCurrentTotal() const { return currentTotal; }
    void resetCurrentTotal() { currentTotal = 0; }
    void addToTotal() { total += currentTotal; }
private:
    int total; //total inside the vending machine;
    int currentTotal;
};

class Display {
public:
    Display(string m = "Enter C for coins or S1, S2, S3 for products") { message = m; };
    void print() const { cout << message << "\n"; }
    void setMessage(string m) { message = m; }
private:
    string message;
};

class Vending {
public:
    Vending(const Keypad &keypad, const ProductRow &prodRow, const Money &money, const Display &dis) : keypad(keypad),
                                                                                                       prodRow(prodRow),
                                                                                                       money(money),
                                                                                                       dis(dis) { }
    void print() const {
        for (int i = 0; i < prodRow.getItems().size(); i++) {
            prodRow.getItem(i).print();
        }
    }

    void run() {
        bool more = true;
        while (more) {
            dis.setMessage("Enter C for coins or S1, S2, ... for products");
            print();
            dis.print();
            keypad.getInput();
            if (keypad.getUserInput().at(0) == 'C') {
                money.addCoin();
            }
            else if (keypad.getUserInput().at(0) == 'S') {
                if( keypad.getUserInput() == "S1" && money.getCurrentTotal() == 4 ) {
                    dis.setMessage("Soda is dispensed");
                    dis.print();
                    money.addToTotal();
                    money.resetCurrentTotal();
                    prodRow.getItem(0).setQuantity();
                }
                else if( keypad.getUserInput() == "S2" && money.getCurrentTotal() == 3 ) {
                    dis.setMessage("Water is dispensed");
                    dis.print();
                    money.addToTotal();
                    money.resetCurrentTotal();
                    prodRow.getItem(1).setQuantity();
                }
                else if( keypad.getUserInput()=="S3" && money.getCurrentTotal() == 4 ) {
                    dis.setMessage("Cookies are dispensed");
                    dis.print();
                    money.addToTotal();
                    money.resetCurrentTotal();
                    prodRow.getItem(2).setQuantity();
                }
            }
        }
    }


private:
    Keypad keypad;
    Money money;
    Display dis;
    ProductRow prodRow;
};

int main () {
    ProductQ p1( "Soda", 4, 10 );
    ProductQ p2( "Water", 3, 8 );
    ProductQ p3( "Cookies", 4, 10 );

    vector <ProductQ> vpq;
    vpq.push_back(p1); vpq.push_back(p2); vpq.push_back(p3);
    ProductRow prodRow(vpq);
    Display d;
    Keypad k;
    Money m;

    Vending vend( k, prodRow, m, d );

//    cout << "\n first way:";
//
//    for ( int i = 0; i < vpq.size(); i++ ) {
//        vpq[i].print();
//    }
//
//    cout << "\n second way:";
//
//    for ( int i = 0; i < vpq.size(); i++ ) {
//        prodRow.getItem(i).print();
//    }
//
//    vend.print();

    vend.run();

    return 0;
}