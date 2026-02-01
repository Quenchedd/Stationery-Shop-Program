#include <iostream>
#include <iomanip> // for output alignment
#include <string>
#include <cctype> // for case insensitive searching
using namespace std;

// Declaring item details to be placed in catalog array
struct Item
{
    int id;
    string name;
    float price;
    Item *next;
};

// Declaring data node for hash table
struct HashNode {
    Item data;
    HashNode *next;
    
    HashNode(int id, string name, float price) {
        data.id = id;
        data.name = name;
        data.price = price;
        next = NULL;
    }
};

class Inventory {
private:
    static const int TABLE_SIZE = 30;
    HashNode* catalog[TABLE_SIZE]; // Declaring hash table

    // Linking ID as key for hash function
    int hashFunction(int id) { 
        return id % TABLE_SIZE; // common hash function using modulo
    }

public:

    // Initializes the hash table by emptying all array elements
    Inventory() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            catalog[i] = NULL;
        }
    }

    // Pushes all items into the catalog stack array using hashing with chaining
    void pushItem(int id, string name, float price) {

        int index = hashFunction(id); // hash function called to convert key to index
        HashNode* newNode = new HashNode(id, name, price); // store the item data in a new Hash Node for chaining
        newNode->next = catalog[index]; 
        catalog[index] = newNode;

    }

    // Search if the item ID exists in the catalog and return item details
    Item* searchId(int id) {
        int index = hashFunction(id);
        HashNode* temp = catalog[index];

        // Loops to check every element slot to find the ID that matches
        while (temp != NULL) {
            if (temp->data.id == id) {
                return &(temp->data); // matching ID found, returning item data(name, price)
            }
            temp = temp->next;
        }
        return NULL; // Not found
    }

    // Displays all items available for purchase
    void showCatalog() {
        cout << "\n======= STATIONERY CATALOG ========" << endl;
        bool isEmpty = true;

        // Loop through every index in the hash table
        for (int i = 0; i < TABLE_SIZE; i++) {
            HashNode* temp = catalog[i];

        // Go through each node of every index
        while (temp != NULL) {
            isEmpty = false;
            cout << "ID: " << temp->data.id 
                 << " | " << setw(25) << left << temp->data.name 
                 << " | Price: RM" << fixed << setprecision(2) << temp->data.price << endl;
            temp = temp->next;
            }
        }

        if (isEmpty) cout << "The catalog is currently empty." << endl;
    }

    void searchName(string query) {
        bool found = false;
    
        // Convert user query to lowercase once
        string lowerQuery = query;
        for (int i = 0; i < lowerQuery.length(); i++) {
            lowerQuery[i] = tolower(lowerQuery[i]);
        }

        cout << "\n----Search Results----" << endl;

        for (int i = 0; i < TABLE_SIZE; i++) {
            HashNode* temp = catalog[i];

            while (temp != NULL) {

                // Convert item name to lowercase temporarily for comparison
                string lowerItemName = temp->data.name;
                for (int j = 0; j < lowerItemName.length(); j++) {
                    lowerItemName[j] = tolower(lowerItemName[j]);
                }

                // Perform the search on the lowercase versions
                if (lowerItemName.find(lowerQuery) != string::npos) {

                    // display all items that match the keyword
                    cout << "ID: " << temp->data.id << " | " << setw(25) << left << temp->data.name 
                         << " | Price: RM" << fixed << setprecision(2) << temp->data.price << endl;
                    found = true;

                }
                temp = temp->next;
            }
        }
        if (!found) cout << "No items found matching \"" << query << "\"." << endl;
    }
};

// Declaring item details to be placed in cart
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
    Inventory inv; // declare object for Inventory 

    CartItem* head; // declare both front and back of linked queue
    CartItem* tail;

    // declare top pointer and search history stack array
    int top;
    static const int MAX_HISTORY = 5;
    string searchHistory[MAX_HISTORY];

public:

    // Initialize all stationery items into catalog
    Store() {

        // PENS
        inv.pushItem(101, "Gel Pen Black", 3.50);
        inv.pushItem(102, "Gel Pen Blue", 3.50);
        inv.pushItem(103, "Gel Pen Red", 3.50);
        inv.pushItem(104, "Ballpoint Pen", 1.20);
        inv.pushItem(105, "Signature Pen", 15.00);

        // PAPER
        inv.pushItem(111, "A4 Paper 70gsm", 12.50);
        inv.pushItem(112, "A4 Paper 80gsm", 14.00);
        inv.pushItem(113, "Spiral Notebook", 4.50);
        inv.pushItem(114, "Sticky Notes", 2.00);
        inv.pushItem(115, "Sketchbook A3", 8.50);

        // PENCILS/ERASERS
        inv.pushItem(121, "2B Pencil Pack", 5.00);
        inv.pushItem(122, "Mechanical Pencil", 3.00);
        inv.pushItem(123, "Pencil Lead 0.5", 1.50);
        inv.pushItem(124, "Exam Eraser", 1.00);
        inv.pushItem(125, "Electric Eraser", 12.00);

        // OTHER ACCESSORIES
        inv.pushItem(131, "Steel Ruler 30cm", 2.50);
        inv.pushItem(132, "Scissors", 4.00);
        inv.pushItem(133, "Glue Stick", 2.20);
        inv.pushItem(134, "Correction Tape", 3.50);
        inv.pushItem(135, "Expanding Folder", 6.80);
        
        // Initialize Linked Queue by emptying front and back pointers
        head = tail = NULL;

        // Intialize Stack Array top pointer
        top = -1;
    }

    // Push the user's search history into the stack
    void pushHistory(string query){

        // Checks if the stack is full (user previously searched more than 5 times)
        if (top < MAX_HISTORY - 1)
        {
            top++;
            searchHistory[top] = query;
        }
        else
        {
            // If stack is full, shift items to keep most recent search history
            for (int i = 0; i < MAX_HISTORY - 1; i++)
            {
                searchHistory[i] = searchHistory[i+1];
            }
            searchHistory[top] = query;   
        }
    }

    // Peek the user's recent search history from the stack
    void showHistory(){

        // Checks if stack is empty
        if (top == -1)
        {
            cout<<"\nNo recent search history.\n";
        }
        else
        {
            // If not empty, display all of user's recent searches
            cout<<"\n-----Recent Searches-----\n";
            for (int i = top; i >= 0; i--) {
            cout << (top - i + 1) << ". " << searchHistory[i] << endl;
            }
        }
    }

    // Function to add an item to cart
    void addItem(){
        int add, qty;
        inv.showCatalog();// Display available items
        cout<<"\nEnter ID of item to add : ";
        cin>>add;

        // Search if user has entered a valid ID
        Item* foundItem = inv.searchId(add);

        // Check if item found
        if (foundItem != NULL) {
            cout << "Enter quantity : ";
            cin >> qty;

            // reinput if user enter invalid amount
            while (qty < 1) {
                cout << "Enter valid quantity (> 0): ";
                cin >> qty;
            }

            bool updated = false;
            CartItem *checkDup = head;

            // Check if user has already added this item 
            while (checkDup != NULL) {

                // If item to add matches the item in cart
                if (checkDup->name == foundItem->name) {

                    // Instead of inserting in a new Node, increase quantity of the Node that contains this item
                    checkDup->quantity += qty; 
                    checkDup->totalPrice = checkDup->quantity * foundItem->price;
                    updated = true;
                    break;

                }
                checkDup = checkDup->next; // check the next Node 
            }

            // If item isn't in cart
            if (!updated) {
                CartItem *temp = new CartItem; // make a new Node to input item details
                temp->name = foundItem->name;
                temp->quantity = qty;
                temp->totalPrice = foundItem->price * qty;
                temp->next = NULL; // Terminate the queue by setting the last node's pointer to NULL

                // If the cart is empty
                if (head == NULL) 
                head = tail = temp; // Set head and tail pointing to the first item

                else { 
                    tail->next = temp; // else link the queue by pointing the tail(recent item) to the new item added 
                    tail = temp; // Set tail as the new item
                }
            }
            cout << "\nSuccess: Item added to cart.\n";
        } else {
            cout << "Invalid ID. Please try again.\n";
        }
    }

    // View items in cart
    void viewItems(){

        // Check if cart is empty
        if(head == NULL){
            cout<<"\nYour cart is currently empty.\n";
            return;
        }

        // Intialize temp as the first item 
        CartItem *temp = head;
        cout<<"\n=====Your Cart=====\n";

        int i = 1;
        while (temp != NULL)
        {
            // Display all items in cart
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
        
        // Show all items in cart
        viewItems();

        int selection;
        cout<<"\nEnter number of item to edit : ";
        cin>>selection;

        CartItem *temp = head;
        // Find the Node that user selected
        for (int i = 1; i < selection && temp != NULL; i++)
        {
            temp = temp->next;
        }

        // Display error message if user enter a number higher than items in cart or < 1
        if (temp == NULL || selection < 1)
        {
            cout<<"Invalid selection. Please try again.\n";
            return;
        }
        
        int edit, qty;
        inv.showCatalog();
        cout<<"\nEnter ID of the item to edit to : ";
        cin>>edit;

        // Search item Id in catalog
        Item* foundItem = inv.searchId(edit);

        // Similar to addItem
        if (foundItem != NULL) {
            cout << "Enter quantity : ";
            cin >> qty;
            
            while (qty < 1) {
                cout << "Enter valid quantity (> 0): ";
                cin >> qty;
            }

                temp->name = foundItem->name;
                temp->quantity = qty;
                temp->totalPrice = foundItem->price * qty;
                
                cout<<"\nSuccess : Cart Updated.\n";
        }
        else{
            cout<<"Invalid item ID. Please try again.\n";
        }

    }

    // Remove item from cart
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

        // Loop to the next Node until temp is pointing to the item to remove
        for (int i = 1; i < option && temp != NULL; i++)
        {
            prev = temp;
            temp = temp->next;
        }

        // Display error message if user enter a number higher than items in cart or < 1
        if (temp == NULL || option < 1)
        {
            cout<<"Invalid selection. Please try again.\n";
            return;
        }

        // If user wish to remove first item
        if (temp == head)
        {
            head = head->next; // make second item as new head

            if (head == NULL) // if no second item, set tail as NULL
                tail = NULL;
        }
        else{
            prev->next = temp->next; // link previous Node with the next Node of removed item

            // If item to remove is the most recent item
            if (temp == tail)
            {
                tail = prev; // set previous Node as new tail
                tail->next = NULL;
            }      
        }
        delete temp; // remove item from cart
        cout<<"\nSuccess : Item removed from cart.\n";
        
    }

    // Search item in catalog
    void searchItem(){

        string query;
        showHistory(); // Display search history
        cout << "\nEnter keyword to search: ";
        getline(cin>>ws, query); // to allow spaces in search
        pushHistory(query); // Store search history in stack
        inv.searchName(query); // calls searchName function to linear search through the catalog 

    }

    void receipt() {

        if (head == NULL) {
            cout << "\nYour cart is empty. No receipt to generate.\n";
            return;
        }

    float total = 0.00;
    cout << "\n================ RECEIPT ===============" << endl;
    cout << left << setw(30) << "Item" << "Price (RM)" << endl;
    cout << "----------------------------------------" << endl;

    // Displays all items in cart
    CartItem *temp = head;
    while (temp != NULL) {

        cout << left << setw(35) << temp->name 
             << fixed << setprecision(2) << temp->totalPrice << endl;
        
        // Tally up the total price of each item
        total += temp->totalPrice;
        temp = temp->next;

    }

    cout << "----------------------------------------" << endl;
    cout << left << setw(33) << "TOTAL:" 
         << "RM" << fixed << setprecision(2) << total << endl;
    cout << "========================================" << endl;
    cout << "          THANKS FOR SHOPPING!          " << endl;
    cout << "========================================" << endl;
}

};


int main()
{
    Store shop; // declare object for Store
    int choice;

    do
    {
        cout<<"\n=====STATIONERY SHOP MENU====="<<endl;
        cout<<endl<<"1. Add Item to Cart"<<endl;
        cout<<"2. View Cart"<<endl;
        cout<<"3. Edit Cart"<<endl;
        cout<<"4. Remove Item from Cart"<<endl;
        cout<<"5. Search Item"<<endl;
        cout<<"6. Checkout"<<endl<<endl;

        cout<<"Enter choice : ";
        cin>>choice;

        // Direct choice numbers to their respective functions
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
                shop.receipt();
                cout<<"\nProgram exited.";
                break;
            default:
                cout<<"Invalid choice. Please input a valid choice (1-6)"<<endl;
                break;
        }

    } while (choice != 6);   

    return 0;
}