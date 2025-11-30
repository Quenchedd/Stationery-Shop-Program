#include <iostream>
#include <string>
using namespace std;

struct Item
{
    int id;
    string name;
    float price;
    int quantity;
};

class Store
{
private:

    /* data */

public:
    void addItem();
    void viewItems();
    void editItem();
    void removeItem();
    void searchItem();
};

void Store::addItem(){

}

void Store::viewItems(){

}

void Store::editItem(){
    
}

void Store::removeItem(){
    
}

void Store::searchItem(){
    
}


int main()
{
    Store cart;
    int choice;

    do
    {
        cout<<"=====STATIONERY SHOP MENU====="<<endl;
        cout<<endl<<"1. Add Item to Cart"<<endl;
        cout<<"2. View Cart"<<endl;
        cout<<"3. Edit Cart"<<endl;
        cout<<"4. Remove Item from Cart"<<endl;
        cout<<"5. Search Item"<<endl;
        cout<<"6. Exit"<<endl<<endl;

        cout<<"Enter choice : ";
        cin>>choice;

        switch (choice)
        {
            case 1:
                cart.addItem();
                break;
            case 2:
                cart.viewItems();
                break;  
            case 3:
                cart.editItem();
                break;
            case 4:
                cart.removeItem();
                break;
            case 5:
                cart.searchItem();
                break;
            case 6:
                cout<<"Program exited.";
                break;
            default:
                cout<<"Invalid choice. Please input a valid choice (1-6)"<<endl;
                break;
        }

    } while (choice != 6);   

    return 0;
}

