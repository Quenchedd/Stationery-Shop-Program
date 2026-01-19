#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Item
{
    int id;
    string name;
    float price;
};

class Inventory
{
public:
    Item catalog[20];
    int top;

    Inventory(){
        top = -1;
    }

    void pushItem(int id, string name, float price){
        if (top < 19)
        {
            top++;
            catalog[top].id = id;
            catalog[top].name = name;
            catalog[top].price = price;
        }
    }
    
};

struct CartItem
{
    string name;
    int quantity;
    float totalPrice;
    CartItem *next;
};

class Store
{
private:
    Inventory inv;      
    CartItem* head;
    CartItem* tail;

    void showCatalog(){
        for (int i = 0; i <= inv.top; i++) {
            cout<<i + 1<< ". "<<inv.catalog[i].name<<" | ID : "<<inv.catalog[i].id<<" | Price : RM"<<fixed<<setprecision(2)<< inv.catalog[i].price<<endl;
        }
    }

public:
    Store() {
        inv.pushItem(101, "2B Pencil", 0.60);
        inv.pushItem(102, "Sharpener", 1.50);
        inv.pushItem(103, "Ballpoint Black Pen", 0.80);
        inv.pushItem(104, "Black Marker Pen", 2.00);
        inv.pushItem(105, "Ballpoint Blue Pen", 0.80);
        inv.pushItem(106, "Ruler(15cm)", 1.00);
        
        head = tail = NULL;
    }

    void addItem(){
        int add, qty;
        showCatalog();
        cout<<"\nEnter ID of item to add : ";
        cin>>add;

        int found = 0;
        for (int i = 0; i <= inv.top; i++)
        {
            if (inv.catalog[i].id == add)
            {
                
                cout<<"Enter amount : ";
                cin>>qty;

                while (qty < 1)
                {
                    cout<<"\nPlease enter a valid amount (more than 0).\n";
                    cout<<"Enter amount : ";
                    cin>>qty;   
                }

                bool updated = false;
                CartItem *ptr = head;
                while (ptr != NULL)
                {
                    if (ptr->name == inv.catalog[i].name)
                    {
                        ptr->quantity += qty;
                        ptr->totalPrice = ptr->quantity * inv.catalog[i].price;
                        updated = true;
                        break;
                    }
                    ptr = ptr->next;
                }
                

                if (!updated)
                {

                    if (head == NULL)
                    {
                        head = new CartItem;
                        head->name = inv.catalog[i].name;
                        head->quantity = qty;
                        head->totalPrice = inv.catalog[i].price * qty;
                        head->next = NULL;
                        tail = head;
                    }
                    else{
                        CartItem *temp = new CartItem;
                        temp->name = inv.catalog[i].name;
                        temp->quantity = qty;
                        temp->totalPrice = inv.catalog[i].price * qty;
                        temp -> next = NULL;

                        tail->next = temp;
                        tail = temp;
                    }   
                }
                
                found = 1;
                cout<<"\nSuccess : Item added to cart.\n";
                return;
            }    
        }
        if (found == 0)
        {
            cout<<"Invalid item ID. Please try again.\n";
        }
        
    }

    void viewItems(){
        if(head == NULL){
            cout<<"\nYour cart is currently empty.\n";
            return;
        }

        CartItem *temp = head;
        cout<<"\n=====Your Cart=====\n";

        int i = 1;
        while (temp != NULL)
        {
            cout<<i<<". "<<temp->name<<" | Quantity : "<<temp->quantity<<" | Total : RM"<<fixed<<setprecision(2)<<temp->totalPrice;
            cout<<endl;
            i++;
            temp = temp -> next;
        }
    
    }

    void editItem(){

        if(head == NULL){
            cout<<"\nYour cart is currently empty.\n";
            return;
        }
        
        viewItems();

        int selection;
        cout<<"\nEnter number of item to edit : ";
        cin>>selection;

        CartItem *temp = head;
        for (int i = 1; i < selection && temp != NULL; i++)
        {
            temp = temp->next;
        }

        if (temp == NULL || selection < 1)
        {
            cout<<"Invalid selection. Please try again.";
            return;
        }
        
        int edit;
        showCatalog();
        cout<<"\nEnter ID of the item you wish to edit to : ";
        cin>>edit;

        int found = 0;
        for (int i = 0; i <= inv.top; i++)
        {
            if (inv.catalog[i].id == edit)
            {
                int qty;
                cout<<"Enter amount : ";
                cin>>qty;

                while (qty < 1)
                {
                    cout<<"\nPlease enter a valid amount (more than 0).\n";
                    cout<<"Enter amount : ";
                    cin>>qty;   
                }

                temp->name = inv.catalog[i].name;
                temp->quantity = qty;
                temp->totalPrice = inv.catalog[i].price * qty;
                
                found = 1;
                cout<<"\nSuccess : Cart Updated.\n";
                return;
            }    
        }
        if (found == 0)
        {
            cout<<"Invalid item ID. Please try again.\n";
        }

    }

    void removeItem(){

        if(head == NULL){
            cout<<"\nYour cart is currently empty.\n";
            return;
        }
        
        viewItems();

        int option;
        cout<<"\nEnter number of item to remove : ";
        cin>>option;

        CartItem *temp = head;
        CartItem *prev = NULL;
        for (int i = 1; i < option && temp != NULL; i++)
        {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL || option < 1)
        {
            cout<<"Invalid selection. Please try again.";
            return;
        }

        if (temp == head)
        {
            head = head->next;
            if (head == NULL)
                tail = NULL;
        }
        else{
            prev->next = temp->next;

            if (temp == tail)
            {
                tail = prev;
                tail->next = NULL;
            }      
        }
        delete temp;
        cout<<"\nSuccess : Item removed from cart.\n";
        
    }

    void searchItem(){
    
    }

};


int main()
{
    Store shop;
    int choice;

    do
    {
        cout<<"\n=====STATIONERY SHOP MENU====="<<endl;
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
                shop.addItem();
                break;
            case 2:
                shop.viewItems();
                break;  
            case 3:
                shop.editItem();
                break;
            case 4:
                shop.removeItem();
                break;
            case 5:
                shop.searchItem();
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